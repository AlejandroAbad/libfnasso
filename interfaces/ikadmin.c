#include "../fnasso_defs.h"
#include "../fnasso.h"
#include "../debug.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
//#include <kadm5/admin.h>

fnasso_error fnasso_kadmin_isset(fnasso_context *ctx, int *isset)
{
	F_BEGIN();

	// Validate argumets
	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);
	if (!isset) E_RETURN(FNASSO_ERR_OUTPUT_PTR_NULL);

	(*isset) = (ctx->kadmin &&
		  ctx->kadmin->user && ctx->kadmin->password && ctx->kadmin->realm && ctx->kadmin->server &&
		  strlen(ctx->kadmin->user) && strlen(ctx->kadmin->realm) && strlen(ctx->kadmin->server))
		  ? TRUE : FALSE;
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_kadmin_create_user(fnasso_context *ctx)
{
	F_BEGIN();
	fnasso_error error;
	pid_t chld_pid, ret_pid;
	int status, retval, query_size;
	char *query;

	// Check the user is set (this checks if ctx isset)
	error = fnasso_user_isset(ctx, &retval);
	if (error) E_THROW(error);
	if (retval == FALSE) E_RETURN(FNASSO_ERR_USER_DATA_NOT_SET);

	// Check the kadmin data is set
	error = fnasso_kadmin_isset(ctx, &retval);
	if (error) E_THROW(error);
	if (retval == FALSE) E_RETURN(FNASSO_ERR_KADMIN_DATA_NOT_SET);

	// Create a child process
	switch (chld_pid = fork())
	{
		case -1:
		{
			// Call to fork has failed
			E_RETURN(FNASSO_ERR_EXTERNAL, "fork", strerror(errno));
		}
		case 0:
		{
			// Construct command line instruction like
			// kadmin -r here.com -s kadmin.here.com -q addprinc -pw 1234 juanito -p fnasso/admin -w 1234
			query_size = 15 + strlen(ctx->user->password) + strlen(ctx->user->name);
			query = (char *) malloc(query_size);
			query[query_size] = '\0';
			sprintf(query, "addprinc -pw %s %s", ctx->user->password, ctx->user->name);
			DEBUG("query: %s", query);

			char *args[] = {"kadmin",
				"-r", ctx->kadmin->realm,
				"-s", ctx->kadmin->server,
				"-q", query,
				"-p", ctx->kadmin->user,
				"-w", ctx->kadmin->password, NULL};

			DEBUG("execvp: (kadmin -r %s -s %s -q %s -p %s -w %s)", ctx->kadmin->realm, ctx->kadmin->server, query, ctx->kadmin->user, ctx->kadmin->password, NULL);

			execvp("kadmin", args);
			ERROR("execvp: %s", strerror(errno));
			exit(errno);
		}
		default:
		{
			// Wait for the child process to end
fnasso_kadmin_create_principal_waitpid:
			ret_pid = waitpid(chld_pid, &status, 0);
			if (ret_pid < 0)
			{
				// If waitpid was interrupted, go again to waitpid
				if (errno == EINTR)
					goto fnasso_kadmin_create_principal_waitpid;

				E_RETURN(FNASSO_ERR_EXTERNAL, "waitpid", strerror(errno));
			}

			// Child process ends with 'status'
			EVENT("kadmin exited with status (%d)", status);
			if (status > 128)
				E_RETURN(FNASSO_ERR_CHLD_EXIT_SIGNAL, status, strsignal(status - 128))
			else if (status)
				E_RETURN(FNASSO_ERR_CHLD_EXIT, status)
			else
				RETURN(FNASSO_ERR_NONE);
		}
	}
}

fnasso_error fnasso_kadmin_set_realm(fnasso_context *ctx, const char* realm)
{
	F_BEGIN();
	fnasso_error error;

	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);
	error = fnasso_kadmin_init(ctx);
	if (error) E_THROW(error);

	if (!realm)
	{
		if (ctx->kadmin->realm) free(ctx->kadmin->realm);
		ctx->kadmin->realm = NULL;
		EVENT("kadmin realm has been unset");
	}
	else
	{
		if (strlen(realm))
		{
			ctx->kadmin->realm = (char *) realloc(ctx->kadmin->realm, strlen(realm) + 1);
			strcpy(ctx->kadmin->realm, realm);
			EVENT("kadmin realm is now (%s)", ctx->kadmin->realm);
		}
		else
		{
			E_RETURN(FNASSO_ERR_KADMIN_REALM_EMPTY);
		}
	}
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_kadmin_set_server(fnasso_context *ctx, const char* server)
{
	F_BEGIN();
	fnasso_error error;

	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);
	error = fnasso_kadmin_init(ctx);
	if (error) E_THROW(error);

	if (!server)
	{
		if (ctx->kadmin->server) free(ctx->kadmin->server);
		ctx->kadmin->server = NULL;
		EVENT("kadmin server has been unset");
	}
	else
	{
		if (strlen(server))
		{
			ctx->kadmin->server = (char *) realloc(ctx->kadmin->server, strlen(server) + 1);
			strcpy(ctx->kadmin->server, server);
			EVENT("kadmin server is now (%s)", ctx->kadmin->server);
		}
		else
		{
			E_RETURN(FNASSO_ERR_KADMIN_SERVER_EMPTY);
		}
	}
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_kadmin_set_admin(fnasso_context *ctx, const char* username, const char* password)
{
	F_BEGIN();
	fnasso_error error;
	
	if (!ctx) E_RETURN(FNASSO_ERR_NO_CONTEXT_SUPPLIED);
	error = fnasso_kadmin_init(ctx);
	if (error) E_THROW(error);


	if (!username || !password)
	{
		if (ctx->kadmin->user) free(ctx->kadmin->user);
		if (ctx->kadmin->password) free(ctx->kadmin->password);
		EVENT("kadmin user has been cleared.");
	}
	else
	{
		if (strlen(username))
		{
			ctx->kadmin->user = (char *) realloc(ctx->kadmin->user, strlen(username) + 1);
			strcpy(ctx->kadmin->user, username);

			ctx->kadmin->password = (char *) realloc(ctx->kadmin->password, strlen(password) + 1);
			strcpy(ctx->kadmin->password, password);

			EVENT("kadmin user is now (%s) with password (%s)", ctx->kadmin->user, ctx->kadmin->password);
		}
		else
		{
			E_RETURN(FNASSO_ERR_KADMIN_USER_EMPTY);
		}
	}
	RETURN(FNASSO_ERR_NONE);
}

fnasso_error fnasso_kadmin_free(fnasso_context *ctx)
{
	F_BEGIN();
	if (ctx && ctx->kadmin)
	{
		if (ctx->kadmin->user) free(ctx->kadmin->user);
		if (ctx->kadmin->password) free(ctx->kadmin->password);
		if (ctx->kadmin->server) free(ctx->kadmin->server);
		if (ctx->kadmin->realm) free(ctx->kadmin->realm);
		free(ctx->kadmin);
		ctx->kadmin = NULL;
	}
	RETURN(FNASSO_ERR_NONE);
}

/*
fnasso_error fnasso_test(fnasso_context *ctx)
{
	krb5_context context;
	void *kadmin;
	char *db_args;
	char kadmin_server[100];
	
	kadm5_get_admin_service_name(context, ctx->kadmin->realm, kadmin_server, 100);
	kadm5_init_with_password(context, ctx->kadmin->user, ctx->kadmin->password, kadmin_server, NULL, 0, 0, &db_args, &kadmin);
}*/