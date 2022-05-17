from Crypto.Cipher import AES
import os

def validate_padding(ctext):

	count = 0
	rev = ctext[::-1]
	pad_byte = rev[0]
	for i in range(len(rev)):

		if rev[i] == pad_byte:
			count += 1
			continue
		else:
			break

	if count == pad_byte:

		return ctext[:-pad_byte]
 
	else:

		raise Exception("invalid padding")

def pad_bytes(text):

	diff = len(text) % 16
	text = text
	return text + bytes([16-diff])*(16-diff)

def escape(s):

	return s.replace(b';',b'\;').replace(b'=',b'\=')

def unescape(s):

	return s.replace(b'\;',b';').replace(b'\=',b'=')

def f1(usr_str,cipher):
	prefix = "comment1=cooking%20MCs;userdata=" #32 len
	suffix = ";comment2=%20like%20a%20pound%20of%20bacon" #42 len
	ret_str = escape(bytes(prefix + usr_str + suffix,encoding='utf-8'))
	return cipher.encrypt(pad_bytes(ret_str))

def f2(string,cipher):
	
	dec_string = validate_padding(cipher.decrypt(string))
	print("decrypted:", unescape(dec_string))
	return b';admin=true;' in unescape(dec_string)

#attack!!!
random_key = os.urandom(16)
iv = os.urandom(16)
enc_cipher = AES.new(random_key,AES.MODE_CBC,iv) 
dec_cipher = AES.new(random_key,AES.MODE_CBC,IV=iv)

#encrypt special plaintext 'admon=true'
usr_input = "wooww;admon=true"
#extract block needing to change 'o' to 'i'
ctext = f1(usr_input,enc_cipher)
#XOR the required byte in the ciphertext
xor_byte = ord('o') ^ ord('i')
tmp = bytearray(ctext)
#print("changing byte:", bytes([tmp[16*block_idx + byte_idx]]))
tmp[29] ^= xor_byte
ctext = bytes(tmp)
#sew the ctext back together and decrypt
print(f2(ctext,dec_cipher))

