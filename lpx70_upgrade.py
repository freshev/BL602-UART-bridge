import hashlib  
import struct  
import os
import sys 
import time 
import shutil  
import pathlib 
import fnmatch 
import glob  
import re  
import binascii  

def calculate_md5(filename, offset, length):  
    with open(filename, 'rb') as f:  
        f.seek(offset)  
        data = f.read(length)  
        f.close()
    hash_md5 = hashlib.md5()  
    hash_md5.update(data)  
    digest = hash_md5.hexdigest()  
    return digest  
    
def crc32_halfbyte(filename,offset,length):   
    with open(filename, 'rb') as f:  
        f.seek(offset-8)  
        hffilelen = f.read(4) 
        readlen=int.from_bytes(hffilelen, byteorder="little")+length
        f.seek(offset)        
        byte_array  = f.read(readlen) 
        f.close()
        
    crc = 0 
    lut = [  
        0x00000000, 0x1DB71064, 0x3B6E20C8, 0x26D930AC,  
        0x76DC4190, 0x6B6B51F4, 0x4DB26158, 0x5005713C,  
        0xEDB88320, 0xF00F9344, 0xD6D6A3E8, 0xCB61B38C,  
        0x9B64C2B0, 0x86D3D2D4, 0xA00AE278, 0xBDBDF21C  
    ]  
  
    while len(byte_array) > 0:  

        crc = lut[(crc ^ byte_array[0]) & 0x0F] ^ (crc >> 4)   
        crc = lut[(crc ^ (byte_array[0]>>4)) & 0x0F] ^ (crc >> 4)  
        byte_array = byte_array[1:]  
        
    print("crc: 0x%08X" % crc)  
    return crc   
    
filepath=sys.argv[1]    
print(filepath)        
with open(filepath, 'rb+') as f:  
    f.seek(36)  
    f.write(bytes([1])) 
    f.close()     
crcvalue=crc32_halfbyte(filepath,24,232); 
bytes_arr=struct.pack('<I', crcvalue) 
with open(filepath, 'rb+') as f:  

    f.seek(20)  

    f.write(bytes_arr)  
    f.close()
print('finish')
