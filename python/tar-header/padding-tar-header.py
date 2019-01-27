#!/usr/bin/env python3
# -*- codeing: utf-8 -*-

'''
https://www.ibm.com/support/knowledgecenter/sv/ssw_aix_71/com.ibm.aix.files/tar.h.htm

/* POSIX tar Header Block, from POSIX 1003.1-1990  */
#define TAR_BLOCK_SIZE 512
#define NAME_SIZE      100
#define NAME_SIZE_STR "100"
typedef struct tar_header_t {     /* byte offset */
	char name[NAME_SIZE];     /*   0-99 */
	char mode[8];             /* 100-107 */
	char uid[8];              /* 108-115 */
	char gid[8];              /* 116-123 */
	char size[12];            /* 124-135 */
	char mtime[12];           /* 136-147 */
	char chksum[8];           /* 148-155 */
	char typeflag;            /* 156-156 */
	char linkname[NAME_SIZE]; /* 157-256 */
	/* POSIX:   "ustar" NUL "00" */
	/* GNU tar: "ustar  " NUL */
	/* Normally it's defined as magic[6] followed by
	 * version[2], but we put them together to save code.
	 */
	char magic[8];            /* 257-264 */
	char uname[32];           /* 265-296 */
	char gname[32];           /* 297-328 */
	char devmajor[8];         /* 329-336 */
	char devminor[8];         /* 337-344 */
	char prefix[155];         /* 345-499 */
	char padding[12];         /* 500-512 (pad to exactly TAR_BLOCK_SIZE) */
} tar_header_t;

'''

import os,sys

class tarHeader(object):

    def __init__(self, path, header):
        self.path = path
        self.header = bytearray(header)
        self.name = header[:100].decode('ascii')
        self.chksum = header[148:156]
        self.uname = header[265:297].decode('ascii')
        self.gname = header[297:329].decode('ascii')

    def print_info(self):
        print('file name: ' + self.name)
        print('tar header chksum: ' + self.chksum.decode())
        print('file owner: ' + self.uname)
        print('file group: ' + self.gname)

    def __refresh_chksum(self):                       # add '__' mean is private
        self.header[148:156] = b'        '
        chksum = 0
        for data in self.header:
            chksum += data
        chksum = str(oct(chksum)).replace('o', '')    # oct like: 0oXXXX
        temp = str.encode(chksum) + b'\x00'           # string to byte adn add string end byte 0x00
        self.header[148:(148 + len(temp))] = temp
        #print(self.header[148:156])
        with open(self.path, 'r+b') as f:             # user '+' update file
            f.write(self.header)

    def padding(self, data):                          # data: bytes
        if len(data) >= 12:
            print('Padding content needs to be less than 12 bytes...')
        else:
            self.header[500:(500 + len(data))] = data
            self.__refresh_chksum()

if __name__=='__main__':
    if len(sys.argv) == 1:
        print('Plase input tar file...')
        sys.exit(0)
    else:
        tarFile = sys.argv[1]
        
    with open(tarFile, 'rb') as f:
         header = tarHeader(tarFile, f.read(512))
         header.padding(b'my magic\x00')

