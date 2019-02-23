#!/usr/bin/env python3
# -*- codeing: utf-8 -*-

import os,sys

def usrage():
    print("./create-svn-diff.py diff -r xxx:xxx path")

def svn_checkout_file(path, ver):
    items = path.split('/')

    tempDir = './temp/'

    for item in items:
        cmd = 'cd ' + tempDir + ';' + 'svn up --depth empty ' + item + ' -r ' + ver
        print(cmd) 
        if os.system(cmd) == 0:
            tempDir = tempDir + '/' + item
        else:
            cmd = 'cd ' + tempDir + ';' + 'svn up ' + item + ' -r ' + ver
            os.system(cmd)

if __name__=='__main__':

    if len(sys.argv) != 5:
        usrage()
        sys.exit(0)

    link = sys.argv[4]
    cmd = 'svn co --depth empty ' + link + ' temp'
    os.system(cmd)

    cmd = 'svn --summarize ' + sys.argv[1] + ' ' + sys.argv[2] + ' ' + sys.argv[3] + ' ' + sys.argv[4]
    f = os.popen(cmd)

    lines = f.readlines()

    for line in lines:
        line = line.strip()
        if len(line) == 0 or line[0] == 'D':
            continue

        line = line[1:]
        line = line.strip()
        
        path = line.replace(link, '')
        path = path.lstrip('/')

        svn_checkout_file(path, sys.argv[3].split(':')[1])

    os.system('cp -rf temp old')
    
    cmd = 'cd ./old; svn up -r ' + sys.argv[3].split(':')[0]
    os.system(cmd)

    tempDir = 'svn-diff-' + sys.argv[3].split(':')[0] + '-' + sys.argv[3].split(':')[1]
    cmd = 'mv temp new;rm -rf ./new/.svn;rm -rf ./old/.svn;mkdir -p ' + tempDir + ';mv new ' + tempDir + ';mv old ' + tempDir
    os.system(cmd)

