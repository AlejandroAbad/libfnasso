#include <stdio.h>
#include <string.h>
#include "fnasso_defs.h"
#include "fnasso.h"
#include "debug.h"

#define FNASSO_VERSION 103


char version_string[110];

char *fnasso_version(int *v)
{
	if (v) *v = 103;
	sprintf(version_string, "libfnasso v1.03 (%s %s)\nContact: Alejandro Abad <alejandroprimitivo.abad@um.es>", __DATE__, __TIME__);
	return version_string;
}

char *fnasso_strerror(fnasso_error errno)
{
	switch (errno)
	{
		case FNASSO_ERR_NONE:
			return "success";
		case FNASSO_ERR_EXTERNAL:
			return "in call to (%s): %s";
		case FNASSO_ERR_NO_CONTEXT_SUPPLIED:
			return "a NULL fnasso_context has been supplied";
		case FNASSO_ERR_NO_ROAMING_REALM:
			return "roaming realm supplied is NULL or empty";
		case FNASSO_ERR_NO_CCACHE_NAME:
			return "ccache name supplied is NULL or empty";
		case FNASSO_ERR_NO_MSK:
			return "no MSK has been supplied";
		case FNASSO_ERR_CANT_GENERATE_MSK_HASH:
			return "unable to generate a hash for the MSK";
		case FNASSO_ERR_CANT_GENERATE_BASE64_PASSWORD:
			return "unable to base64 encode the password";
		case FNASSO_ERR_NO_USERNAME_SUPPLIED:
			return "username supplied is empty";
		case FNASSO_ERR_BADFORMED_KERBEROS_USERNAME:
			return "supplied name (%s) is not a valid kerberos username";
		case FNASSO_ERR_OUTPUT_PTR_NULL:
			return "supplied pointer for output is NULL";
		case FNASSO_ERR_USER_DATA_NOT_SET:
			return "user data is not set";
		case FNASSO_ERR_CHLD_EXIT_SIGNAL:
			return "child exited due to signal (%d): (%s)";
		case FNASSO_ERR_CHLD_EXIT:
			return "child exited with status (%d)";
		case FNASSO_ERR_KADMIN_DATA_NOT_SET:
			return "kadmin data structure is not set";
		case FNASSO_ERR_KADMIN_REALM_EMPTY:
			return "supplied kadmin realm is empty";
		case FNASSO_ERR_KADMIN_SERVER_EMPTY:
			return "supplied kadmin server is empty";
		case FNASSO_ERR_KADMIN_USER_EMPTY:
			return "supplied kadmin username is empty";
		default:
			return "unknown error";
	}
}

fnasso_error fnasso_context_init(fnasso_context **ctx)
{
	F_BEGIN();
	*ctx = (fnasso_context *) calloc(1, sizeof (fnasso_context));
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_context_free(fnasso_context **ctx)
{
	F_BEGIN();
	if (ctx && *ctx)
	{
		fnasso_user_free(*ctx);
		fnasso_kdc_free(*ctx);
		fnasso_kadmin_free(*ctx);
		if ((*ctx)->ccache_filename) free((*ctx)->ccache_filename);
		if ((*ctx)->roaming_realm) free((*ctx)->roaming_realm);
		free(*ctx);
		*ctx = NULL;
		ctx = NULL;
	}
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_context_set_cache_name(fnasso_context *ctx, const char* ccache_name)
{
	F_BEGIN();
	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);

	if (!ccache_name)
	{
		if (ctx->ccache_filename) free(ctx->ccache_filename);
		ctx->ccache_filename = NULL;
		EVENT("Credentials cache filename has been set to OS default");
	}
	else
	{
		if (strlen(ccache_name))
		{
			ctx->ccache_filename = (char *) realloc(ctx->ccache_filename, strlen(ccache_name) + 1);
			strcpy(ctx->ccache_filename, ccache_name);
			EVENT("Credentials cache filename is now (%s)", ctx->ccache_filename);
		}
		else
		{
			E_RETURN(FNASSO_ERR_NO_CCACHE_NAME);
		}
	}
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_context_set_roaming_realm(fnasso_context *ctx, const char* roaming_realm)
{
	F_BEGIN();
	krb5_error_code kerberos_error;
	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);

	if (!roaming_realm)
	{
		if (ctx->roaming_realm) free(ctx->roaming_realm);
		ctx->roaming_realm = NULL;
		EVENT("roaming realm restored to default realm in /etc/krb5.conf");
	}
	else
	{
		if (strlen(roaming_realm))
		{
			ctx->roaming_realm = (char *) realloc(ctx->roaming_realm, strlen(roaming_realm) + 1);
			strcpy(ctx->roaming_realm, roaming_realm);
			EVENT("roaming realm is now (%s)", ctx->roaming_realm);
		}
		else
		{
			E_RETURN(FNASSO_ERR_NO_ROAMING_REALM);
		}
	}

	if (ctx->kdc && ctx->kdc->kctx)
	{
		EVENT("updating current KDC default realm");
		kerberos_error = krb5_set_default_realm(*ctx->kdc->kctx, ctx->roaming_realm);
		if (kerberos_error)
		{
			fnasso_kdc_free(ctx);
			E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_set_default_realm", error_message(kerberos_error));
		}
		DEBUG("krb5_set_default_realm OK");
	}

	RETURN(FNASSO_ERR_NONE);
}



