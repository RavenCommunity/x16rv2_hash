import x16rv2_hash, os, sys, time, binascii

def gennonce(decnonce):
  hexnonce = str(hex(decnonce)).replace('0x','')
  while len(hexnonce) < 8:
    hexnonce = '0' + hexnonce
  return str(hexnonce)

#main
header = '00112233'
while len(header) < 152:
  header = '00' + header

target = "00000fff00000000000000000000000000000000000000000000000000000000"
targetbin = binascii.unhexlify(target)
nonce = 0
while True:
  
  complete_header = str(header) + str(gennonce(nonce))
  hashbin = x16rv2_hash.getPoWHash(binascii.unhexlify(complete_header))[::-1]

  if hashbin < targetbin:
     print('block ' + str(binascii.hexlify(hashbin)))
     print('nonce was ' + str(nonce))
     sys.exit(0)

  if (nonce % 128 == 0):
     fnonce = str(hex(nonce)).replace('0x','')
     while len(fnonce) < 8:
      fnonce = '0' + fnonce
     print(fnonce)

  nonce += 1

