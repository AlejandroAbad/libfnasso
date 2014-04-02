#include "../debug.h"
#include <openssl/sha.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/**
 * Generates a HASH of an input byte array supplied. The output hash string is -NOT- null-ended, nevertheless, the output length is returned.
 * Note: The output byte array -MUST- be freed by the programmer -ONLY IF- the hash is suscessfully calculated (return value higher or equals zero).
 *  
 * @param input A pointer to the beggining of the input byte array to be hashed.
 * @param input_length The length in bytes of the input byte array.
 * @param output A pointer to where the hashed output will be written. This output will be allocated inside this function, so it -MUST- be released by the programmer.
 * @return The number of bytes writted to output, or -1 if the hash coulnd't be generated.
 */
int fnasso_hash(const unsigned char *input, int input_length, unsigned char **output)
{
	F_BEGIN();
	if (!output) RETURN(-1);
	if (input_length < 0) RETURN(-1);

	(*output) = (char *) malloc(SHA_DIGEST_LENGTH);
	SHA1(input, input_length, (*output));
	if (!(*output))
	{
		free(*output);
		ERROR(strerror(errno));
		RETURN(-1);
	}
	RETURN(SHA_DIGEST_LENGTH);
}
