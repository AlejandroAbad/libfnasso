#include "../debug.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string.h>
#include <errno.h>

/**
 * Converts a byte array to a null-ended byte array encoded using base64. The returned value contains the number of bytes written to the output buffer.
 * Note: Returned pointer -MUST- be released -ONLY IF- the function returns suscessfully (return value higher or equals 0)
 * 
 * @param input The input byte array to be encoded.
 * @param input_len Length of the input byte array given.
 * @param output Pointer to where the base64 encoded byte array will be written. This pointer -MUST- be released by the programmer -ONLY IF- return value is greater or equals 0.
 * @return The number of bytes writted to output or -1 if no output could be generated.
 */
int fnasso_base64_encode(const unsigned char *input, int input_len, char **output)
{
	F_BEGIN();
	BIO *bmem, *b64;
	char *data;
	int output_len;

	if (!output) RETURN(-1);
	if (input_len < 0) RETURN(-1);


	b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, input, input_len);

	*output = NULL;
	output_len = -1;

	if (BIO_flush(b64) > 0)
	{
		output_len = BIO_get_mem_data(b64, &data);
		*output = (char*) malloc(output_len + 1);
		memcpy(*output, data, output_len);
		(*output)[output_len] = '\0';
		//free(data);
	}
	else
	{
		ERROR(strerror(errno));
	}

	BIO_free_all(b64);
	CRYPTO_cleanup_all_ex_data();
	
	RETURN(output_len);
}

/**
 * Converts a byte array to a null-ended byte array representing the input in hexadecimal using ASCII characters.
 * Note: Returned pointer -MUST- be freed.
 * 
 * @param input The input byte array to be encoded.
 * @param input_len Length of the input byte array given.
 * @param output Pointer to where the hexadecimal representation will be written. This pointer -MUST- be freed by the programmer.
 * @return The number of bytes writted to output.
 */
int fnasso_hexstr_encode(const unsigned char *input, int input_len, char **output)
{
	F_BEGIN();
	//char* hexbuff;
	int i;
	
	if (!output) RETURN(-1);
	if (input_len < 0) RETURN(-1);
	
	if (!input)	input_len = 0;
	
	*output = (char*) malloc((input_len * 2) + 1);
	
	for (i = 0; i < input_len; i++)
	{
		sprintf((*output) + (i*2), "%02x", input[i]);
		//hexbuff += 2;
	}
	(*output)[input_len * 2] = '\0';
	RETURN(input_len * 2);
}
