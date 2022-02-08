from Crypto.Cipher import AES
import base64
import os

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

def ECB_encrypt(blocks,cipher):

	return_bytes = b''

	for b in blocks:

		return_bytes += cipher.encrypt(b)
	
	return return_bytes

def encryption_oracle(ctext):
	
	ctext_blocks = to_blocks(ctext,16)
	counts = {ctext_blocks.count(entry) for entry in ctext_blocks}
	
	return "ECB" if any(map(lambda x: x > 1, counts)) else "CBC"

bytes_to_append = base64.b64decode("Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK")
ptext = b'SAMESAMESAMESAMEYELLOW SUBMARINESAMESAMESAMESAME'*10
ptext = ptext + bytes_to_append
random_key = random_bytes(16)
cipher = AES.new(random_key,AES.MODE_ECB)
