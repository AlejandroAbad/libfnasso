/* 
 * File:   fnasso.h - Library for Single Sign-On during Federated Network Access
 * Author: Alejandro Abad Carrascosa <alejandroprimitivo.abad@um.es>
 *
 * Created on February 19, 2014, 8:09 PM
 * Version 1.3 - March 14, 2014
 */

#ifndef FNASSO_H
#define	FNASSO_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        FNASSO_ERR_NONE = 0,
        FNASSO_ERR_EXTERNAL,
        FNASSO_ERR_NO_CONTEXT_SUPPLIED,
        FNASSO_ERR_NO_ROAMING_REALM,
        FNASSO_ERR_NO_CCACHE_NAME,
        FNASSO_ERR_NO_MSK,
        FNASSO_ERR_CANT_GENERATE_MSK_HASH,
        FNASSO_ERR_CANT_GENERATE_BASE64_PASSWORD,
        FNASSO_ERR_NO_USERNAME_SUPPLIED,
        FNASSO_ERR_BADFORMED_KERBEROS_USERNAME,
        FNASSO_ERR_OUTPUT_PTR_NULL,
        FNASSO_ERR_USER_DATA_NOT_SET,
        FNASSO_ERR_CHLD_EXIT_SIGNAL,
        FNASSO_ERR_CHLD_EXIT,
        FNASSO_ERR_KADMIN_DATA_NOT_SET,
        FNASSO_ERR_KADMIN_REALM_EMPTY,
        FNASSO_ERR_KADMIN_SERVER_EMPTY,
        FNASSO_ERR_KADMIN_USER_EMPTY
    } fnasso_error;

    typedef struct fnasso_context_t fnasso_ctx;
    
    /**
     * Returns a descriptive string of the library version and compilation date.
     * @param v If not null, the integer pointed will store the current library version
     * @return The descriptive string of the version and compilation date/time.
     */
    char *fnasso_version(int *v);

    /**
     * Returns a pointer to the string representation of a given fnasso_error value.
     * If the error code is undefined, a default "unknown error" string will be pointed as return value.
     * Note: Returned pointer is statically defined and it's contents -MUST NOT- be modified.
     * 
     * @param errno The error value.
     * @return A pointer to the char array describing the given error.
     */
    char *fnasso_strerror(fnasso_error errno);

    /**
     * Initialization of a kerberos based FNASSO context (fnasso_context).
     * Note: The FNASSO context pointed MUST be deallocated using the provided fnasso_free_context() function.
     * 
     * @context Pointer to where the context structure will be allocated. This pointer doesn't need to be allocated previously.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_context_init(fnasso_ctx **context);

    /**
     * Frees all data contained in a FNASSO context.
     * 
     * @param Pointer to where the context structure is allocated.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_context_free(fnasso_ctx **context);

    /**
     * Sets the roaming realm that will be used in order to contact the local KDC and derivate user names. Usually, this realm is configured
     * in '/etc/krb5.conf', nevertheless, this configuration won't be reliable in most cases where the user is in roaming.
     * A NULL value for default_realm will restore the system's default value (if any).
     * Note: Empty strings will return an error.
     * 
     * @param context A pointer to the FNASSO context where the new roaming realm will be set.
     * @param roaming_realm The pointer to the -null-ended- char array containing the value of the roaming realm or a NULL pointer to reset to the default value.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_context_set_roaming_realm(fnasso_ctx *context, const char* roaming_realm);

    /**
     * Sets the credentials cache name that will be used to store TGTs. If a NULL value is
     * passed, the credential cache file will be the OS default file (ie. "/tmp/krb5cc_1000").
     * 
     * Note: A cache name has the format "METHOD:residual" (ie. "FILE:/tmp/fnasso_cc"). Refer to
     * mit.edu for more info about ccaches methods.
     * 
     * @param context A pointer to the FNASSO context where the new ccache name will be set.
     * @param ccache_filename The pointer to the -null-ended- where is stored the ccache name where to store the credential cache. If pointer is NULL, the default credential cache name will be used.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_context_set_cache_name(fnasso_ctx *context, const char* ccache_name);



    

    //////////////////////////////////////
    // User management
    //////////////////////////////////////
    /**
     * Sets a new user in the FNASSO context whose name and password are generated with a deterministic algorithm
     * in function of an octet array, usually a MSK (Master Session Key) derived in an EAP negotiation.
     * 
     * @param context A pointer to the FNASSO context where the user will be set.
     * @param msk An octet array with the input for the username and password algotimh generator.
     * @param key_len The length of given octet array (in bytes).
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_user_set_with_msk(fnasso_ctx *context, const unsigned char *msk, int key_len);

    /**
     * Sets the user of a FNASSO context with the name and password specified.
     * Note: The function will automatically try to obtain a realm name from the username.
     * 
     * @param context A pointer to the FNASSO context where the user will be set.
     * @param username The username for the kerberos user.
     * @param password The password for the kerberos user.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_user_set(fnasso_ctx *context, const char *username, const char *password);

    /**
     * Checks if the user stored in a FNASSO context is valid for autenticantion or user administration.
     * The isset value will be set to TRUE or FALSE, determining if the context's user is set or not.
     * Note: isset MUST be not NULL or an error will be raised.
     * 
     * @param context A pointer to the FNASSO context with the user to be checked.
     * @param isset A pointer to an integer that will be set to TRUE if the user is set, or FALSE if user is not set.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_user_isset(const fnasso_ctx *context, int *isset);

    /**
     * Frees all information related to the user in a given FNASSO context.
     * 
     * @param context A pointer to the FNASSO context where the user will be cleared.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_user_free(fnasso_ctx *context);





    ////////////////////////////////////////////////
    // Kerberos KDC client functions
    ////////////////////////////////////////////////
    /**
     * Performs an authentication against the kerberos KDC (roaming realm's KDC set) using the user in the FNASSO context supplied.
     * After a successful authentication, a initial kerberos credentials will be available in the default credentials cache.
     * If a previous TGT already exists in cache, it's replaced with the new one.
     * If not NULL, the life_time pointer will store the time in seconds the TGT is valid.
     * 
     * @param context A pointer to the FNASSO context where is set the user that will be authenticated against the KDC.
     * @param life_time A pointer to an integer that will store the TGT's lifetime if the operation is successufully completed. This param can be NULL.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kdc_get_tgt(fnasso_ctx *ctx, int *life_time);


    /**
     * Checks if a TGT exists in cache, and fills life_time with the TGT's lifetime in seconds. If no valid TGT is found
     * in the current credentials cache, a value of -1 will be set.
     * Note: life_time MUST be not NULL or an error will be raised.
     * 
     * @param context A pointer to the FNASSO context where the TGT will be looked for.
     * @param life_time A pointer to an integer that will store the TGT's lifetime (if any) or -1 if no valid TGT was found.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kdc_check_tgt(fnasso_ctx *ctx, int *life_time);

    /**
     * Frees all information related to the KDC peer in a given FNASSO context.
     * 
     * @param context A pointer to the FNASSO context where the KDC data will be wiped out.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kdc_free(fnasso_ctx *ctx);





    ////////////////////////////////////////////////
    // Kerberos Kadmin functions
    ////////////////////////////////////////////////

    /**
     * Checks wherever the kadmin context is set and ready to execute queries against a kadm server or not.
     * @param context The FNASSO context where to check the kadmin data.
     * @param isset A pointer to an integer that will be set to 0 if the kadmin context is not set, or non-zero in other case.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kadmin_isset(fnasso_ctx *context, int *isset);

    /**
     * Sets the kerberos realm that will be administrated. A NULL value will unset any previous value.
     * Note: Empty strings will return an error.
     * 
     * @param context The FNASSO context where the changes may be applied.
     * @param realm The realm name to be administrated using kadmin functions.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kadmin_set_realm(fnasso_ctx *context, const char* realm);

    /**
     * Sets the hostname where the kadmin server is allocated. A NULL value will unset any previous value.
     * Note: Empty strings will return an error.
     * 
     * @param context The FNASSO context where the changes may be applied.
     * @param realm The hostname where the kadmin server is allocated.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kadmin_set_server(fnasso_ctx *context, const char* server);

    /**
     * Sets the username that will be used to login into the kadmin server.
     * If either username or password. If either username or password are set to NULL,
     * all kadmin user related information will be cleared.
     * Note: Empty strings are only permitted in the password parameter, an empty string
     * in the username will return an error.
     * 
     * @param context The FNASSO context where the changes may be applied.
     * @param username Username for login into the kadmin server.
     * @param password Password supplied for the kadmin user.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kadmin_set_admin(fnasso_ctx *context, const char* username, const char* password);

    /**
     * Asks the kadmin server to create a new user principal in the kerberos database. The user created data
     * is retrieved from the user in the FNASSO context.
     * 
     * @param context The FNASSO context where the changes may be applied.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kadmin_create_user(fnasso_ctx *context);

    /**
     * Clears all kadmin data contained in the FNASSO context and frees unnecesary memory.
     * 
     * @param context The FNASSO context where the changes may be applied.
     * @return FNASSO_ERR_NONE in case of success, an error value in case of failure.
     */
    fnasso_error fnasso_kadmin_free(fnasso_ctx *context);


#ifdef	__cplusplus
}
#endif

#endif	/* FNASSO_H */

