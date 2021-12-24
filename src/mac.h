/*
 * Copyright (c) 2021, Alden Torres
 *
 * Licensed under the terms of the MIT license.
 * Copy of the license at https://opensource.org/licenses/MIT
 */

#ifndef ECC_MAC_H
#define ECC_MAC_H

#include "export.h"

#define ecc_mac_hmac_sha256_SIZE_CONST 32
/**
 * Size of the HMAC-SHA-256 digest.
 */
static const int ecc_mac_hmac_sha256_SIZE = ecc_mac_hmac_sha256_SIZE_CONST;

#define ecc_mac_hmac_sha256_KEYSIZE_CONST 32
/**
 * Size of a HMAC-SHA-256 key.
 */
static const int ecc_mac_hmac_sha256_KEYSIZE = ecc_mac_hmac_sha256_KEYSIZE_CONST;

/**
 * Computes the HMAC-SHA-256 of the input stream.
 *
 * See https://datatracker.ietf.org/doc/html/rfc2104
 * See https://datatracker.ietf.org/doc/html/rfc4868
 *
 * @param[out] digest the HMAC-SHA-256 of the input, size:ecc_mac_hmac_sha256_SIZE
 * @param text the input message, size:text_len
 * @param text_len the length of `input`
 * @param key authentication key, size:ecc_mac_hmac_sha256_KEYSIZE
 */
ECC_EXPORT
void ecc_mac_hmac_sha256(
    byte_t *digest,
    const byte_t *text, int text_len,
    const byte_t *key
);

#define ecc_mac_hmac_sha512_SIZE_CONST 64
/**
 * Size of the HMAC-SHA-512 digest.
 */
static const int ecc_mac_hmac_sha512_SIZE = ecc_mac_hmac_sha512_SIZE_CONST;

#define ecc_mac_hmac_sha512_KEYSIZE_CONST 32
/**
 * Size of a HMAC-SHA-512 key.
 */
static const int ecc_mac_hmac_sha512_KEYSIZE = ecc_mac_hmac_sha512_KEYSIZE_CONST;

/**
 * Computes the HMAC-SHA-512 of the input stream.
 *
 * See https://datatracker.ietf.org/doc/html/rfc2104
 * See https://datatracker.ietf.org/doc/html/rfc4868
 *
 * @param[out] digest the HMAC-SHA-512 of the input, size:ecc_mac_hmac_sha512_SIZE
 * @param text the input message, size:text_len
 * @param text_len the length of `input`
 * @param key authentication key, size:ecc_mac_hmac_sha512_KEYSIZE
 */
ECC_EXPORT
void ecc_mac_hmac_sha512(
    byte_t *digest,
    const byte_t *text, int text_len,
    const byte_t *key
);

#endif // ECC_MAC_H
