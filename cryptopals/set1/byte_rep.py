class DataRep:

    '''
    class to hold data for crypto challenges, 
    default representation is a bytearray
    '''
    
    def __init__(self):

        self.data = bytearray()

    def setFromString(self,string):

        self.data = bytearray(string,encoding='ascii')

    def setFromHexString(self,hexstr):

        self.data = bytearray.fromhex(hexstr)

    def setFromIntList(self,intlist):

        self.data = bytearray(intlist)

    def toString(self):

        return self.data.decode('ascii')

    def toHexString(self):

        return self.data.hex()

    def toIntList(self):

        return list(self.data)

    def toBinString(self):

        bin_str = ''
        for byte in self.data:

            bin_str += bin(byte)[2:].zfill(8)

        return bin_str

    def singleByteXOR(self,k):

        return [x ^ k for x in self.data]

    def multiByteXOR(self,k):

        keylen = len(k)
        datalen = len(self.data)
        return [self.data[i] ^ k[i % keylen] for i in range(datalen)]

