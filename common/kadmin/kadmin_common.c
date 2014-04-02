#include "../../debug.h"
#include "../../fnasso_defs.h"
#include "../../fnasso.h"

fnasso_error fnasso_kadmin_init(fnasso_context *ctx)
{
	F_BEGIN();

	if (!ctx->kadmin)
		ctx->kadmin = (fnasso_kadmin *) calloc(1, sizeof (fnasso_kadmin));

	RETURN(FNASSO_ERR_NONE);
}
