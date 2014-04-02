/* 
 * File:   definitions.h
 * Author: hanky
 *
 * Created on March 14, 2014, 10:02 AM
 */

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#include <krb5.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct fnasso_msk_t {
        unsigned char *key;
        int len;
    } fnasso_msk;

    typedef struct fnasso_user_t {
        fnasso_msk *msk;
        char *name;
        char *password;
    } fnasso_user;

    typedef struct fnasso_kdc_t {
        krb5_context *kctx;
        krb5_creds *kcreds;
        krb5_ccache *ccache;
    } fnasso_kdc;

    typedef struct fnasso_kadmin_t {
        char *realm;
        char *server;
        char *user;
        char *password;
    } fnasso_kadmin;

    typedef struct fnasso_context_t {
        fnasso_user *user;
        fnasso_kdc *kdc;
        fnasso_kadmin *kadmin;
        char *ccache_filename;
        char *roaming_realm;
    } fnasso_context;

#ifdef	__cplusplus
}
#endif

#endif	/* DEFINITIONS_H */

