from Crypto.Cipher import AES
import base64
import os
import random

def random_bytes(num):

	return os.urandom(num)

def to_blocks(data,size):

	return [data[i:i+size] for i in range(0,len(data),size)]

def CBC_encrypt(blocks,cipher):
	
	IV = random_bytes(16)
	return_bytes = b''
	
	for b in blocks:
	
		b = bytes([x^y for (x,y) in zip(b,IV)])
		enc_block = cipher.encrypt(b)
		return_bytes += enc_block
		IV = enc_block

	return return_bytes

def ECB_encrypt(blocks,cipher):

	return_bytes = b''

	for b in blocks:

		return_bytes += cipher.encrypt(b)
	
	return return_bytes

def random_encryption(ptext):
	
 	#TODO: prepend/append random 5-10 bytes to ptext
	key = random_bytes(16)
	print("random key:",key)
	cipher = AES.new(key,AES.MODE_ECB)

	if random.randint(1,2) == 1:

		return ECB_encrypt(ptext,cipher), "ECB"

	else:

		return CBC_encrypt(ptext,cipher), "CBC"

ptext = b'SAMESAMESAMESAMEYELLOW SUBMARINESAMESAMESAMESAME'*10
ptext = to_blocks(ptext,16)

true_modes = []
random_ctexts = []

for i in range(100):

	ctext, mode = random_encryption(ptext)
	random_ctexts.append(ctext)
	true_modes.append(mode)

for thing in list(zip(random_ctexts,true_modes)):

	print(thing)
