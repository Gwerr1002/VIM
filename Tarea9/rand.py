import random
import struct

with open("seeds.r",'wb') as f:
    f.write(struct.pack("B",random.randint(0,20)))
'''
with open("seeds.r",'rb') as f:
    print(f.read())
'''
