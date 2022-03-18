from Crypto.Cipher import AES
import base64
import os
import random

def random_bytes(num):

	return os.urandom(num)

def to_blocks(data,size):

	return [data[i:i+size] for i in range(0,len(data),size)]

def pad_bytes(text):

	diff = len(text) % 16

	if diff == 0:

		return text

	else:
		
		return text + random_bytes(16-diff)

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
	
	extra_bytes = random_bytes(random.randint(5,10))
	ptext = pad_bytes(extra_bytes + ptext + extra_bytes)
	ptext_blocks = to_blocks(ptext,16)
	key = random_bytes(16)
	cipher = AES.new(key,AES.MODE_ECB)

	if random.randint(1,2) == 1:

		return ECB_encrypt(ptext_blocks,cipher), "ECB"

	else:

		return CBC_encrypt(ptext_blocks,cipher), "CBC"

def encryption_oracle(ctext):
	
	ctext_blocks = to_blocks(ctext,16)
	counts = {ctext_blocks.count(entry) for entry in ctext_blocks}
	
	return "ECB" if any(map(lambda x: x > 1, counts)) else "CBC"


ptext = b'SAMESAMESAMESAMEYELLOW SUBMARINESAMESAMESAMESAME'*10

true_modes = []
random_ctexts = []

for i in range(100):

	ctext, mode = random_encryption(ptext)
	random_ctexts.append(ctext)
	true_modes.append(mode)

oracle_modes = []

for rand_ctext in random_ctexts:

	oracle_modes.append(encryption_oracle(rand_ctext))

print([p==c for (p,c) in zip(oracle_modes,true_modes)])
