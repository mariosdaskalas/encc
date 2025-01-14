encc.c

A very simple C program for encrypting and decrypting text files using a key.

Compile the program
```
gcc -o encc encc.c
```

Encrypt the file using 'mykey' as a passphrase
```
./encc mykey < secret > encrypted_secret
```

Decrypt the file using 'mykey' as a passphrase
```
./encc mykey < encrypted_secret > decrypted_secret
```

Failure to decrypt the file using a wrong passphrase
```
./encc mykey2 < encrypted_secret > decrypted_secret_fail
```