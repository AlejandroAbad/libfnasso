#include "../fnasso_defs.h"
#include "../fnasso.h"
#include "../debug.h"
#include <string.h>
#include <stdlib.h>

fnasso_error fnasso_user_isset(const fnasso_context *ctx, int *isset)
{
	F_BEGIN();
	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);
	if (!isset) E_RETURN(FNASSO_ERR_OUTPUT_PTR_NULL);
	(*isset) = (ctx->user && ctx->user->name && ctx->user->password && strlen(ctx->user->name)) ? TRUE : FALSE ;
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_user_set_with_msk(fnasso_context *ctx, const unsigned char *msk, int key_len)
{
	F_BEGIN();
	fnasso_error error;
	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);
	if (!msk || key_len < 1) E_RETURN(FNASSO_ERR_NO_MSK);

	fnasso_user_init(ctx);
	ctx->user->msk = (fnasso_msk *) malloc(sizeof (fnasso_msk));
	ctx->user->msk->key = (unsigned char*) malloc(key_len);
	memcpy(ctx->user->msk-> key, msk, key_len);
	ctx->user->msk->len = key_len;

	error = fnasso_user_derivate_from_msk(ctx);
	if (error)
	{
		fnasso_user_free(ctx);
		E_THROW(error);
	}
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_user_set(fnasso_context *ctx, const char *username, const char *password)
{
	F_BEGIN();
	fnasso_error error;
	
	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);
	fnasso_user_init(ctx);

	if (username && strlen(username))
	{
		error = fnasso_split_name(username, &ctx->user->name, NULL);
		if (error)
		{
			fnasso_user_free(ctx);
			E_THROW(error);
		}
	}
	else
	{
		fnasso_user_free(ctx);
		E_RETURN(FNASSO_ERR_NO_USERNAME_SUPPLIED);
	}

	if (password)
	{
		ctx->user->password = (char *) malloc(strlen(password) + 1);
		strcpy(ctx->user->password, password);
	}
	else
	{
		ctx->user->password = (char *) calloc(1, 1);
		WARN("no password supplied for the user");
	}

	EVENT("suscessfully set username (%s) with password (%s)", ctx->user->name, ctx->user->password);
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_user_free(fnasso_context *ctx)
{
	F_BEGIN();

	if (ctx && ctx->user)
	{
		if (ctx->user->name) free(ctx->user->name);
		if (ctx->user->password) free(ctx->user->password);
		if (ctx->user->msk)
		{
			if (ctx->user->msk->key) free(ctx->user->msk->key);
			free(ctx->user->msk);
		}

		free(ctx->user);
		ctx->user = NULL;

	}
	RETURN(FNASSO_ERR_NONE);
}

