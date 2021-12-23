# ecc

[![npm](https://img.shields.io/npm/v/@aldenml/ecc)](https://www.npmjs.com/package/@aldenml/ecc)

This is the javascript version of the [ecc](https://github.com/aldenml/ecc) library.

It is a WebAssembly compilation with a thin layer on
top to expose the cryptographic primitives. It also provides
the same protocol implementations as the more specialized
(and a lot smaller) libraries.

| Library |   |
|---|---|
| OPAQUE Asymmetric PAKE Protocol | [![npm](https://img.shields.io/npm/v/@aldenml/opaque)](https://www.npmjs.com/package/@aldenml/opaque) |
| OPRF Oblivious pseudo-random | [![npm](https://img.shields.io/npm/v/@aldenml/oprf)](https://www.npmjs.com/package/@aldenml/oprf) |

### BLS12-381 Pairing

In the context of pairing friendly elliptic curves, a pairing is a map `e: G1xG2 -> GT` such
that for each a, b, P and Q
```
e(a * P, b * Q) = e(P, Q)^(a * b)
```
You can use this to obtain such pairings:
```js
const libecc = await libecc_module();

const a = new Uint8Array(32);
const b = new Uint8Array(32);
libecc.ecc_bls12_381_scalar_random(a);
libecc.ecc_bls12_381_scalar_random(b);

const aP = new Uint8Array(96);
const bQ = new Uint8Array(192);

libecc.ecc_bls12_381_g1_scalarmult_base(aP, a); // a * P
libecc.ecc_bls12_381_g2_scalarmult_base(bQ, b); // b * Q

const pairing = new Uint8Array(576);
libecc.ecc_bls12_381_pairing(pairing, aP, bQ); // e(a * P, b * Q)
```

Read more at:<br/>
https://hackmd.io/@benjaminion/bls12-381 <br/>
https://en.wikipedia.org/wiki/Pairing-based_cryptography

### Proxy Re-Encryption (PRE)

With a pairing-friendly elliptic curve and a well-defined pairing operation,
you can implement a proxy re-encryption scheme. This library provides an
implementation using BLS12-381.

Example of how to use it:
```js
// client A setup public/private keys and signing keys
const keysA = await pre_schema1_KeyGen();
const signingA = await pre_schema1_SigningKeyGen();

// client B setup public/private keys (signing keys are not used here)
const keysB = await pre_schema1_KeyGen();

// proxy server setup signing keys
const signingProxy = await pre_schema1_SigningKeyGen();

// client A select a plaintext message, this message
// in itself is random, but can be used as a seed
// for symmetric encryption keys
const message = await pre_schema1_MessageGen();

// client A encrypts the message to itself, making it
// possible to send this ciphertext to the proxy.
const ciphertextLevel1 = await pre_schema1_Encrypt(message, keysA.pk, signingA);

// client A sends ciphertextLevel1 to the proxy server and
// eventually client A allows client B to see the encrypted
// message, in this case the proxy needs to re-encrypt
// ciphertextLevel1 (without ever knowing the plaintext).
// In order to do that, the client A needs to create a re-encryption
// key that the proxy can use to perform such operation.

// client A creates a re-encryption key that the proxy can use
// to re-encrypt the ciphertext (ciphertextLevel1) in order for
// client B be able to recover the original message
const reEncKey = await pre_schema1_ReKeyGen(keysA.sk, keysB.pk, signingA);

// the proxy re-encrypt the ciphertext ciphertextLevel1 with such
// a key that allows client B to recover the original message
const ciphertextLevel2 = await pre_schema1_ReEncrypt(
    ciphertextLevel1,
    reEncKey,
    signingA.spk, keysB.pk,
    signingProxy
);

// client B is able to decrypt ciphertextLevel2 and the result
// is the original plaintext message
const messageDecrypted = await pre_schema1_DecryptLevel2(
    ciphertextLevel2,
    keysB.sk, signingProxy.spk
);

// now both client A and client B share the same plaintext message
// messageDecrypted is equal to message
```

Read more at:<br/>
"A Fully Secure Unidirectional and Multi-user Proxy Re-encryption Scheme" by H. Wang and Z. Cao, 2009 <br/>
"A Multi-User CCA-Secure Proxy Re-Encryption Scheme" by Y. Cai and X. Liu, 2014 <br/>
"Cryptographically Enforced Orthogonal Access Control at Scale" by B. Wall and P. Walsh, 2018 <br/>
https://en.wikipedia.org/wiki/Proxy_re-encryption