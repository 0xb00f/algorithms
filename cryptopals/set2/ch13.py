from Crypto.Cipher import AES
import os

def pad_bytes(text):

	diff = len(text) % 16

	if diff == 0:

		return text

	else:
		
		return text + (b'\x04' * (16-diff))

def parse_profile(string):

	split_string = string.split('&')
	ret = dict()

	for pair in split_string:

		[x,y] = pair.split('=')
		ret[x] = y

	return ret

def encode_profile(usrdict):

	return "email=" + usrdict['email'] + "&uid=" + usrdict['uid'] + "&role=" + usrdict['role']

def profile_for(user_email):
	
	sanitise_email = user_email.replace('=','').replace('&','')
	profile = { 'email' : sanitise_email, 'uid' : '10', 'role' : 'user'}
	return encode_profile(profile)

def encrypt_profile(profile,cipher):
	
	profile = pad_bytes(profile_for(profile).encode())
	return cipher.encrypt(profile)

def decrypt_profile(profile,cipher):
	
	decrypted = cipher.decrypt(profile).replace(b"\x04",b"")
	return parse_profile(decrypted.decode('ascii'))
#attack!!!
random_key = os.urandom(16)
cipher = AES.new(random_key,AES.MODE_ECB) 
paste_block = cipher.encrypt(pad_bytes(b'admin'))
email = "1234@1234.com"
enc_profile = encrypt_profile(email,cipher)
admin_profile = enc_profile[:-16] + paste_block
print(decrypt_profile(admin_profile,cipher))
