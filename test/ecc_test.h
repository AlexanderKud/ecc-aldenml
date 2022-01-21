/*
 * Copyright (c) 2022, Alden Torres
 *
 * Licensed under the terms of the MIT license.
 * Copy of the license at https://opensource.org/licenses/MIT
 */

#ifndef ECC_TEST_H
#define ECC_TEST_H

typedef struct ecc_json ecc_json_t;

ecc_json_t *ecc_json_load(const char *filename);

void ecc_json_destroy(ecc_json_t *json);

int ecc_json_is_valid(ecc_json_t *json);

const char *ecc_json_string(ecc_json_t *json, const char *path);

int ecc_json_array_size(ecc_json_t *json, const char *path);

const char *ecc_json_array_string(ecc_json_t *json, const char *path, int index);

#endif // ECC_TEST_H