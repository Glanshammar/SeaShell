/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 2020-2021 The openssl Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OSSL_INTERNAL_PROPERTYERR_H
# define OSSL_INTERNAL_PROPERTYERR_H
# pragma once

# include <openssl/opensslconf.h>
# include <openssl/symhacks.h>

# ifdef  __cplusplus
extern "C" {
# endif

int ossl_err_load_PROP_strings(void);

/*
 * PROP reason codes.
 */
# define PROP_R_NAME_TOO_LONG                             100
# define PROP_R_NOT_AN_ASCII_CHARACTER                    101
# define PROP_R_NOT_AN_HEXADECIMAL_DIGIT                  102
# define PROP_R_NOT_AN_IDENTIFIER                         103
# define PROP_R_NOT_AN_OCTAL_DIGIT                        104
# define PROP_R_NOT_A_DECIMAL_DIGIT                       105
# define PROP_R_NO_MATCHING_STRING_DELIMITER              106
# define PROP_R_NO_VALUE                                  107
# define PROP_R_PARSE_FAILED                              108
# define PROP_R_STRING_TOO_LONG                           109
# define PROP_R_TRAILING_CHARACTERS                       110


# ifdef  __cplusplus
}
# endif
#endif