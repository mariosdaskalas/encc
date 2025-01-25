```
ens.c
```

A very simple C program for encrypting and decrypting text files using a key.

Compile the program
```
gcc -o ens ens.c
```

Encrypt the file using 'mykey' as a passphrase
```
./ens mykey < secret > encrypted_secret
```

Decrypt the file using 'mykey' as a passphrase
```
./ens mykey < encrypted_secret > decrypted_secret
```

Failure to decrypt the file using a wrong passphrase
```
./ens mykey2 < encrypted_secret > decrypted_secret_fail
```