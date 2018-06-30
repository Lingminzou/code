#!/usr/bin/env python
# -*- coding: utf-8 -*-
import codecs
import os
import sys
import shutil
import re
import chardet

convertfiletypes = [
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
    '''
    完成文件编码格式转换与 dos2unix 的功能
    '''

    with open(filename, "rb") as f:
        codeType = chardet.detect(f.read())['encoding']
    if None == codeType:
        print("\r\nthe [ " + filename.split('\\')[-1] + " ] codeType is None, skip...")
        return
        
    f = codecs.open(filename, 'r', codeType)
    new_content = f.read()
    
    if codeType != target_encoding:
        try:
            print("\r\nconvert [ " + filename.split('\\')[-1] + " ].....From " + codeType + " --> " + target_encoding)
            new_content = re.sub(r'\r\n', r'\n', new_content)
            codecs.open(filename, 'wb', target_encoding).write(new_content)
        except IOError as err:
            print("I/O error: {0}".format(err))
    elif re.findall(r'\r\n', new_content):
        try:
            print("\r\nexec [ " + filename.split('\\')[-1] + " ] dos2unix...")
            new_content = re.sub(r'\r\n', r'\n', new_content)
            codecs.open(filename, 'wb', codeType).write(new_content)
        except IOError as err:
            print("I/O error: {0}".format(err))
    else:
        print("\r\nthe [ " + filename.split('\\')[-1] + " ] is " + codeType + " type unix file")
    
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
