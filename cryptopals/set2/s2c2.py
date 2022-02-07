from Crypto.Cipher import AES
import base64

def to_blocks(data,size):

	return [data[i:i+size] for i in range(0,len(data),size)]

def pad_block(b,blen):

	diff = blen - len(b)
         
	return b + b'\x04'*diff

def CBC_encrypt(blocks,cipher,IV):

	return_bytes = b''

	for b in blocks:
	
		b = bytes([x^y for (x,y) in zip(b,IV)])
		enc_block = cipher.encrypt(b)
		return_bytes += enc_block
		IV = enc_block

	return return_bytes

def CBC_decrypt(blocks,cipher,IV):

	return_bytes = b''

	for b in blocks:
    	
		dec_block = cipher.decrypt(b)
		return_bytes += bytes([x^y for (x,y) in zip(dec_block,IV)])
		IV = b

	return return_bytes

# intialise cipher
IV = b'0000000000000000'
key = b'YELLOW SUBMARINE'
cipher = AES.new(key,AES.MODE_ECB)

#file data
with open('s2c2.txt') as _file:

	file_data = _file.read()
	data = base64.b64decode(file_data)

blocks = to_blocks(data,16)
decrypted_text = CBC_decrypt(blocks,cipher,IV)
print(decrypted_text)
