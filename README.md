# AES
an AES implementation i made while bored at 16 years old.

The entire implementation was made in C, and includes:
  128, 192, 256 modes,
  decryption and encryption,
  ECB and CBC block modes,
  galois field arithmetic,
  round key generation.
with a library layer on top.

issues:
  CTR is ennumed but not implemented,
  rand() is used for a random key, which is not secure cryptographically.

Compile Instructions:
1. compile each .c file in the src folder into its .o file in the bin folder (create bin if it doesn't exist)
2. compile all the .o files in bin into a file called 'libaes.a' inside a lib folder (create lib if needed) using ar
3. linking against libaes.a works the same as any other library, e.g.:
   gcc main.c -Llib -laes -o aes.exe
