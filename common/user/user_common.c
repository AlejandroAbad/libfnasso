#include "../../fnasso_defs.h"
#include "../../fnasso.h"
#include "../../debug.h"
#include <string.h>

fnasso_error fnasso_user_init(fnasso_context *ctx)
{
	F_BEGIN();
	fnasso_error error;

	// First, ensure there is no crap in the user structure by freeing it
	error = fnasso_user_free(ctx);
	if (error) E_THROW(error);
	
	// Allocate the new user structure
	ctx->user = (fnasso_user *) calloc(1, sizeof (fnasso_user));
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_user_derivate_from_msk(fnasso_context *ctx)
{
	F_BEGIN();
	unsigned char *hashed_key;
	char *username;
	int hash_len, hex_len, base64_len;

	// Calculate MSK hash
	hash_len = fnasso_hash(ctx->user->msk->key, ctx->user->msk->len, &hashed_key);
	if (hash_len < 1)
	{
		free(hashed_key);
		E_RETURN(FNASSO_ERR_CANT_GENERATE_MSK_HASH);
	}
	DEBUG("MSK hash generated (%i bytes)", hash_len);

	// Username derivation using 'hashed_key'
	hex_len = fnasso_hexstr_encode(hashed_key, hash_len, &username);
	DEBUG("username hexstring generated (%s) (%i bytes)", username, hex_len);

	// Add '@roaming.realm' if isset
	if (ctx->roaming_realm)
	{
		DEBUG("found roaming realm (%s)", ctx->roaming_realm);
		username = (char*) realloc(username, 17 + strlen(ctx->roaming_realm));
		username[15] = '@';
		strcpy(username + 16, ctx->roaming_realm);
		username[16 + strlen(ctx->roaming_realm)] = '\0';
	}
	else
	{
		username = (char*) realloc(username, 16);
		username[15] = '\0';
	}
	ctx->user->name = username;
	EVENT("successfully derivated USERNAME (%s)", ctx->user->name);

	// Password derivation using 'hashed_key'
	base64_len = fnasso_base64_encode(hashed_key, hash_len, &ctx->user->password);
	if (!base64_len)
	{
		free(hashed_key);
		E_RETURN(FNASSO_ERR_CANT_GENERATE_BASE64_PASSWORD);
	}
	EVENT("successfully derivated PASSWORD (%s)", ctx->user->password);

	free(hashed_key);
	RETURN(FNASSO_ERR_NONE);
}
