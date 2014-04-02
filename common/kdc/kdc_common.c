#include "../../fnasso_defs.h"
#include "../../fnasso.h"
#include "../../debug.h"
#include <krb5.h>
#include <string.h>

fnasso_error fnasso_kdc_init(fnasso_context *ctx)
{
	F_BEGIN();
	krb5_error_code kerberos_error;
	krb5_context *context;
	
	if (!ctx->kdc)
	{
		ctx->kdc = (fnasso_kdc*) calloc(1, sizeof(fnasso_kdc));
	}

	if (!ctx->kdc->kctx)
	{
		context = ctx->kdc->kctx = (krb5_context *) malloc(sizeof (krb5_context));

		kerberos_error = krb5_init_context(context);
		if (kerberos_error)
		{
			fnasso_kdc_free(ctx);
			E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_init_context", error_message(kerberos_error));
		}
		DEBUG("krb5_init_context OK");
	}
	else
	{
		context = ctx->kdc->kctx;
		DEBUG("context allready initialized");
	}


	// Setup the right roaming kerberos realm
	if (ctx->roaming_realm)
	{
		EVENT("found kerberos roaming realm (%s), overwriting default realm", ctx->roaming_realm);
		kerberos_error = krb5_set_default_realm(*context, ctx->roaming_realm);
		if (kerberos_error)
		{
			fnasso_kdc_free(ctx);
			E_RETURN(FNASSO_ERR_EXTERNAL, "krb5_set_default_realm", error_message(kerberos_error));
		}
		DEBUG("krb5_set_default_realm OK");
	}
	else
	{
		WARN("default realm not found in context, using default realm from /etc/krb5.conf");
	}

	RETURN(FNASSO_ERR_NONE);
}


