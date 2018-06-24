#!/usr/bin/env python
# -*- coding: utf-8 -*-
import codecs
import os
import sys
import shutil
import re
import chardet

convertfiletypes = [
  ".txt",
  ".h",
  ".c",
  ".cpp",
  ".java"
  ]

target_encoding = 'utf-8'
  
def check_need_convert(filename):
    for filetype in convertfiletypes:
        if filename.lower().endswith(filetype):
            return True
    return False

def convert_encoding_to_utf_8(filename):
    with open(filename, "rb") as f:
        codeType = chardet.detect(f.read())['encoding']
    if codeType != target_encoding:
        try:
            print("\r\nconvert [ " + filename.split('\\')[-1] + " ].....From " + codeType + " --> " + target_encoding)
            f = codecs.open(filename, 'r', codeType)
            new_content = f.read()
            codecs.open(filename, 'w', target_encoding).write(new_content)
        except IOError as err:
            print("I/O error: {0}".format(err))

def convert_dir(root_dir):
    if os.path.exists(root_dir) == False:
        print("[error] dir:",root_dir,"do not exit")
        return
    print("work in",convertdir)
    for root, dirs, files in os.walk(root_dir):
        for f in files:
            if check_need_convert(f):
                filename = os.path.join(root, f)
                #print("\r\nstart convert file: ", filename)
                convert_encoding_to_utf_8(filename)

if __name__ == '__main__':
    if len(sys.argv) == 1:
        convertdir = os.getcwd()
    else:	
        convertdir = sys.argv[1]
    convert_dir(convertdir)
