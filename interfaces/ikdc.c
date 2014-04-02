#include "../fnasso_defs.h"
#include "../fnasso.h"
#include "../debug.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <krb5.h>

fnasso_error fnasso_kdc_get_tgt(fnasso_context *ctx, int *life_time)
{
	F_BEGIN();
	fnasso_error error;
	krb5_error_code kerberos_error;
	int retval;
	krb5_context context;
	krb5_creds kcreds;
	krb5_ccache ccache;
	krb5_principal client;

	error = fnasso_user_isset(ctx, &retval);
	if (error) E_THROW(error);
	if (retval == FALSE) E_RETURN(FNASSO_ERR_USER_DATA_NOT_SET);

	error = fnasso_kdc_init(ctx);
	if (error) E_THROW(error);

	context = *(ctx->kdc->kctx);
	// Generate a cache_name.
	if (ctx->ccache_filename)
	{
		kerberos_error = krb5_cc_resolve(context, ctx->ccache_filename, &ccache);
		if (kerberos_error)
		{
			krb5_cc_close(context, ccache);
			E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_cc_resolve", error_message(kerberos_error));
		}
		DEBUG("krb5_cc_resolve OK");
	}
	else
	{
		kerberos_error = krb5_cc_default(context, &ccache);
		if (kerberos_error)
		{
			krb5_cc_close(context, ccache);
			E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_cc_default", error_message(kerberos_error));
		}
		DEBUG("krb5_cc_default OK");
	}



	kerberos_error = krb5_parse_name(context, ctx->user->name, &client);
	if (kerberos_error)
	{
		krb5_free_principal(context, client);
		krb5_cc_close(context, ccache);
		E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_parse_name", error_message(kerberos_error));
	}
	DEBUG("krb5_parse_name OK");

	kerberos_error = krb5_cc_initialize(context, ccache, client);
	if (kerberos_error)
	{
		krb5_free_principal(context, client);
		krb5_cc_close(context, ccache);
		E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_cc_initialize", error_message(kerberos_error));
	}
	DEBUG("krb5_cc_initialize OK");

	memset((char *) &kcreds, 0, sizeof (kcreds));
	kerberos_error = krb5_get_init_creds_password(context, &kcreds, client, ctx->user->password, NULL, NULL, 0, NULL, NULL);
	if (kerberos_error)
	{
		DEBUG("si falla, las limpia");
		krb5_free_cred_contents(context, &kcreds);
		krb5_free_principal(context, client);
		krb5_cc_close(context, ccache);
		E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_get_init_creds_password", error_message(kerberos_error));
	}
	DEBUG("krb5_get_init_creds_password OK");


	// We have the TGT, save it to the ccache
	EVENT("adding the new TGT to the credentials cache");
	kerberos_error = krb5_cc_store_cred(context, ccache, &kcreds);
	if (kerberos_error)
	{
		krb5_free_cred_contents(context, &kcreds);
		krb5_free_principal(context, client);
		krb5_cc_close(context, ccache);
		E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_cc_store_cred", error_message(kerberos_error));
	}
	DEBUG("krb5_cc_store_cred OK");

	// Set returned lifetime if requested
	if (life_time)
	{
		(*life_time) = kcreds.times.endtime - time(NULL);
		DEBUG("ticket lifetime is (%d seconds)", *life_time);
	}

	ctx->kdc->ccache = (krb5_ccache*) malloc(sizeof (krb5_ccache));
	memcpy((char*) ctx->kdc->ccache, (char*) &ccache, sizeof (krb5_ccache));

	ctx->kdc->kcreds = (krb5_creds*) malloc(sizeof (krb5_creds));
	memcpy((char*) ctx->kdc->kcreds, (char*) &kcreds, sizeof (krb5_creds));

	krb5_free_principal(context, client);

	if (life_time) DEBUG("TGT lifetime is (%d)", *life_time);
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_kdc_check_tgt(fnasso_context *ctx, int *life_time)
{
	F_BEGIN();

	krb5_error_code kerberos_error;
	krb5_context context;
	krb5_ccache ccache;
	krb5_creds kcreds, cached_kcreds;

	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);
	if (!life_time) E_RETURN(FNASSO_ERR_OUTPUT_PTR_NULL);

	if (!ctx->kdc || !ctx->kdc->kctx || !ctx->kdc->ccache || !ctx->kdc->kcreds)
	{
		(*life_time) = -1;
		EVENT("no kdc data found, no TGT available");
	}
	else
	{
		context = *(ctx->kdc->kctx);
		ccache = *(ctx->kdc->ccache);
		kcreds = *(ctx->kdc->kcreds);

		kerberos_error = krb5_cc_retrieve_cred(context, ccache, 0, &kcreds, &cached_kcreds);
		if (kerberos_error)
		{
			(*life_time) = -1;
			EVENT("couldn't retrieve user TGT from cache");
		}
		else
		{
			(*life_time) = kcreds.times.endtime - time(NULL);
			krb5_free_cred_contents(context, &cached_kcreds);
			EVENT("found TGT in cache, valid for (%d) seconds", (*life_time));
		}
	}

	DEBUG("TGT lifetime is (%d)", *life_time);
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_kdc_free(fnasso_context *ctx)
{
	F_BEGIN();
	
	/**
	 * Note: When authenticating an user, a memory leak is produced in 'krb5_get_init_creds_password'.
	 * The problem is caused by an error in the getaddrinfo() implementation in Unix and Solaris systems.
	 * It seems that only 216 bytes are leaked, independent of how many time 'krb5_get_init_creds_password' is called for getting a TGT,
	 * so there may not be problems while executing the lib during loing time periods.
	 * 
	 * HEAP SUMMARY:
	 *    in use at exit: 216 bytes in 1 blocks
	 *    total heap usage: 102,745 allocs, 102,744 frees, 4,872,393 bytes allocated
	 * 
	 * 216 bytes in 1 blocks are still reachable in loss record 1 of 1
	 *    at 0x4C2B6CD: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
	 *    by 0x55F4CF8: make_request (check_pf.c:249)
	 *    by 0x55F5193: __check_pf (check_pf.c:342)
	 *    by 0x55AA5F4: getaddrinfo (getaddrinfo.c:2372)
	 *    by 0x5284E14: k5_sendto (sendto_kdc.c:736)
	 *    by 0x528550B: krb5_sendto_kdc (sendto_kdc.c:339)
	 *    by 0x525E00A: init_creds_get (get_in_tkt.c:578)
	 *    by 0x525E156: krb5int_get_init_creds (get_in_tkt.c:1649)
	 *    by 0x525F55C: krb5_get_init_creds_password (gic_pwd.c:258)
	 *    by 0x407C4F: fnasso_kdc_get_tgt (ikdc.c:72)
	 *    by 0x402B61: _KDC_test (kdc.c:167)
	 *    by 0x402CC4: kdc (kdc.c:196)
	 * 
	 * LEAK SUMMARY:
	 *    definitely lost: 0 bytes in 0 blocks
	 *    indirectly lost: 0 bytes in 0 blocks
	 *    possibly lost: 0 bytes in 0 blocks
	 *    still reachable: 216 bytes in 1 blocks
	 *    suppressed: 0 bytes in 0 blocks
	 * 
	 * Discussion thread available at the MIT kerberos mailing lists
	 * http://kerberos.996246.n3.nabble.com/Memory-Leak-problems-with-krb5-get-init-creds-password-td12383.html
	 */
	
	if (ctx && ctx->kdc)
	{
		if (ctx->kdc->ccache)
		{
			krb5_cc_close(*ctx->kdc->kctx, *ctx->kdc->ccache);
			free(ctx->kdc->ccache);
		}

		if (ctx->kdc->kcreds)
		{
			krb5_free_creds(*ctx->kdc->kctx, ctx->kdc->kcreds);
		}

		if (ctx->kdc->kctx)
		{
			krb5_free_context(*ctx->kdc->kctx);
			free(ctx->kdc->kctx);
		}

		free(ctx->kdc);
		ctx->kdc = NULL;
	}

	RETURN(FNASSO_ERR_NONE);
}


