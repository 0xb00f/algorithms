from base64 import b64decode
from Crypto.Cipher import AES

with open('c7.txt') as _file:

    data = b64decode(_file.read())
    key = b'YELLOW SUBMARINE'
    cipher = AES.new(key,AES.MODE_ECB)
    print(cipher.decrypt(data))
