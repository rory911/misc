package main

// #include <unistd.h>
import "C"

import (
	"bytes"
	"fmt"
	"crypto/aes"
	"crypto/cipher"
	"crypto/md5"
	"encoding/hex"
	"io"
	"io/ioutil"
	"os"
)

// Step-by-step AES seal
func encrypt(data []byte, passwrd string) []byte {
	hash := md5.New()
	hash.Write([]byte(passwrd))
	chksum := hash.Sum(nil)
	key := hex.EncodeToString(chksum)
	block, _ := aes.NewCipher([]byte(key))
	gcm, _ := cipher.NewGCM(block)
	nonce := make([]byte, gcm.NonceSize())
	rdr := bytes.NewReader(nil)
	io.ReadFull(rdr, nonce)
	encrypted := gcm.Seal(nonce, nonce, data, nil)
	return encrypted
}

// Step-by-step AES open
func decrypt(data []byte, passwrd string) []byte {
	hash := md5.New()
	hash.Write([]byte(passwrd))
	chksum := hash.Sum(nil)
	key := hex.EncodeToString(chksum)
	block, _ := aes.NewCipher([]byte(key))
	gcm, _ := cipher.NewGCM(block)
	nonceSize := gcm.NonceSize()
	nonce, encrypted := data[:nonceSize], data[nonceSize:]
	decrypted, _ := gcm.Open(nil, nonce, encrypted, nil)
	return decrypted
}

//
// A simple unbatched version of crypt(1) using AES. It is primary an example
// of calling C from Golang, along with sealing or opening via the AES module.
// AES is symmetric, so don't forget the "key," because it's the only password
// that will open the encrypted data.
//
//	To encrypt, usage: crypt [-e] < ifile > ofile 
//
//	To decrypt, usage: crypt -d < ifile > ofile
//
// Unlike the original, this Golang version requires a user to enter the key
// from the console (see getpass(3)).
//
func main() {
	args := os.Args

	// Fetch the symmetric key and read stdin
	passwrd := C.getpass(C.CString("Enter key: "))
	data, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		fmt.Printf("%s: failed to read os.Stdin\n", args[0])
		return;
	}

	// Either seal or open via AES
	crypto := encrypt
	if len(args) > 1 && args[1] == "-d" {
		crypto = decrypt
	}
	secret := crypto(data, C.GoString(passwrd))
	fmt.Print(string(secret))
}
