from Crypto.Cipher import AES
import base64
import os

def random_bytes(num):

	return os.urandom(num)

def pad_bytes(text):

	diff = len(text) % 16

	if diff == 0:

		return text

	else:
		
		return text + (b'A' * (16-diff)) #random_bytes(16-diff)
	
def to_blocks(data,size):

	return [data[i:i+size] for i in range(0,len(data),size)]

def random_encryption(cipher,ptext,bsize):

	return ECB_encrypt(ptext,cipher,b''), "ECB"

def ECB_encrypt(ptext,cipher,bytes_to_append):

	return_bytes = b''
	input_ptext = pad_bytes(ptext + bytes_to_append)
	blocks = to_blocks(input_ptext,16)

	for b in blocks:

		return_bytes += cipher.encrypt(b)
	
	return return_bytes

def encryption_oracle(ctext):
	
	ctext_blocks = to_blocks(ctext,16)
	counts = {ctext_blocks.count(entry) for entry in ctext_blocks}
	
	return "ECB" if any(map(lambda x: x > 1, counts)) else "CBC"

def decrypt_bytes(unknown_bytes,cipher,bsize):

	ret = b''
	mlen = len(pad_bytes(unknown_bytes))
	for j in range(1,mlen+1):

		block_dict = dict()
		short_block = b'A' * (mlen-j) 
		
		for i in range(256):
			
			block_dict[i] = ECB_encrypt(short_block+ret+bytes([i]),cipher,unknown_bytes)[:mlen]
		
		target_block = ECB_encrypt(short_block, cipher, unknown_bytes)[:mlen]
		
		for key in block_dict:

			if block_dict[key] == target_block:
				
				ret += bytes([key])
	
	return ret

block_size = 0
random_key = random_bytes(16)
cipher = AES.new(random_key,AES.MODE_ECB)

#determmine block size
for bsize in range(1,256+1):
	
	test_block = b'A' * bsize

	try:
		cipher.encrypt(test_block)
		block_size = bsize
		break
	except:
		continue 

print("block size is",block_size)

#detect encryption mode
test_ptext = b'A' * 10 * block_size
random_ctexts = []
true_modes = []

for i in range(100):
	
	ctext, mode = random_encryption(cipher,test_ptext,block_size)
	random_ctexts.append(ctext)
	true_modes.append(mode)

oracle_modes = []

for rand_ctext in random_ctexts:

	oracle_modes.append(encryption_oracle(rand_ctext))

compare_results = list(zip(oracle_modes,true_modes))

is_ECB = True

for (x,y) in compare_results:

	if x == "ECB" and y != "ECB":

		is_ECB = False
		break

if is_ECB:

	print("ECB mode detected by oracle")

else:

	print("ECB mode not detected by oracle")

# BREAK ENCRYPTION
mystery_bytes = base64.b64decode("Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK")

decrypted = decrypt_bytes(mystery_bytes,cipher,block_size)

if decrypted[:len(mystery_bytes)] == mystery_bytes:

	print("SUCCESS! Decrypted bytes are:\n",decrypted[:len(mystery_bytes)])

else:

	print("FAILED TO DECRYPT!")
