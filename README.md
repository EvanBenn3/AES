# AES
an AES implementation i made while bored at 16 years old.
The entire implementation was made in C, and includes:
  128, 192, 258 modes,
  decryption and encryption,
  ECB and CBC block modes,
  galois field arithmetic,
  round key generation.
with a library layer on top.
issues:
  CTR is ennumed but not implemented,
  rand() is used for a random key, which is not secure cryptographically.

compilation is trivial, it's a basic command that simply combines all of the source files into a library file, of which can be linked against.
