#include "../fnasso_defs.h"
#include "../fnasso.h"
#include "../debug.h"
#include <string.h>
#include <stdlib.h>

/* Split an "username@realm.com" formatted string into an username and a realm. There may be various situations variing on the input supplied.
 * +----------------+----------+----------+--------------+-------------+
 * | string	        | username | realm    | username_out | realm_out   |
 * +----------------+----------+----------+--------------+-------------+
 * | bob@there.com  | NOT NULL | NOT_NULL | bob          | there.com   |
 * | bob@there.com  | NOT_NULL | NULL     | bob          | (n/a)	     |
 * | bob@there.com  | NULL     | NOT_NULL | (n/a)        | there.com   |
 * | bob            | NOT_NULL | NOT_NULL | bob          | (empty str) |
 * | bob            | NOT_NULL | NULL     | bob          | (n/a)       |
 * | there.com      | NULL     | NOT_NULL | (n/a)        | there.com   |
 * | @there.com     | ERROR !! This is not a valid krb principal !!    |
 * | bob@           | ERROR !! This is not a valid krb principal !!    |
 * +----------------+----------+----------+---------------+------------+
 * Note: Output pointers -MUST- be freed by the programmer if they had been supplied and there is no error in the return code, otherwise, no allocations will be made inside this function.
 *
 * @param string A pointer to where a -NULL ENDED- input 'username@realm.com' is stored.
 * @param username A pointer to where the the username will be written (ended with a NULL byte). If NULL, the username will be discarded.
 * @param realm A 
 * @return FNASSO_ERR_NONE if the string could be splitted, other error codes in case of failure.
 */
fnasso_error fnasso_split_name(const char *string, char **username, char **realm)
{
	F_BEGIN();
	char *at_ptr;
	int at_position;

	if (!string || !strlen(string)) E_RETURN(FNASSO_ERR_NO_USERNAME_SUPPLIED);

	DEBUG("Splitting the string (%s)", string);
	at_ptr = strchr(string, '@');
	// The string supplied is either an username or a realm name
	if (!at_ptr)
	{
		DEBUG("Supplied string (%s) doesn't have an @ character, assumming empty realm", string);
		if (username)
		{
			(*username) = (char*) malloc((strlen(string) + 1) * sizeof (char));
			strcpy(*username, string);
			DEBUG("username splitted is (%s)", (*username));
		}

		if (realm)
		{
			if (!username)
			{
				DEBUG("username pointer is null, assuming the string supplied is a realm name");
				(*realm) = (char*) malloc((strlen(string) + 1) * sizeof (char));
				strcpy(*realm, string);
			}
			else
			{
				(*realm) = (char *) malloc(1);
				(*realm)[0] = '\0';
			}
			DEBUG("realm splitted is (%s)", (*realm));
		}
		RETURN(FNASSO_ERR_NONE);
	}


	at_position = at_ptr - string;
	DEBUG("found an '@' character at position (%i)", at_position);

	if (at_position == 0 || at_position == strlen(string) - 1)
		E_RETURN(FNASSO_ERR_BADFORMED_KERBEROS_USERNAME, string);



	if (username)
	{
		(*username) = (char*) malloc((at_position + 1) * sizeof (char));
		memcpy(*username, string, at_position);
		(*username)[at_position] = '\0';
		DEBUG("username splitted is (%s)", (*username));
	}

	if (realm)
	{
		(*realm) = (char*) malloc((strlen(string) - at_position) * sizeof (char));
		strcpy(*realm, at_ptr + 1);
		DEBUG("realm splitted is (%s)", (*realm));
	}

	RETURN(FNASSO_ERR_NONE);
}
