 /* sha1.c
 *
 * This file is part of mbed TLS (https://tls.mbed.org).
 *
 */

#ifndef _SHA1_H
#define _SHA1_H

#include <stddef.h>
#include <stdint.h>


/**
 * \brief          Output = SHA-1( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   SHA-1 checksum result
 */
void SHA1( const unsigned char *input, size_t ilen, unsigned char output[20] );


#ifdef __cplusplus
}
#endif

#endif /* sha1.h */

