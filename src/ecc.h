/*
 * Copyright (c) 2021, Alden Torres
 *
 * Licensed under the terms of the MIT license.
 * Copy of the license at https://opensource.org/licenses/MIT
 */

#ifndef ECC_ECC_H
#define ECC_ECC_H

#include "util.h"
#include "hash.h"
#include "mac.h"
#include "kdf.h"
#include "h2c.h"
#include "oprf.h"
#include "opaque.h"

#include "export.h"

ECC_EXPORT
int ecc_is_zero(const BYTE *n, int len);

ECC_EXPORT
void ecc_increment(BYTE *n, int len);

ECC_EXPORT
void ecc_add(BYTE *a, const BYTE *b, int len);

ECC_EXPORT
void ecc_sub(BYTE *a, const BYTE *b, int len);

#endif // ECC_ECC_H
