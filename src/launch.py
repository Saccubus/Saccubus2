#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''

'''
他のプログラムを発見したりする際にのベースとなるディレクトリをSACCUBUS_PATHに設定すること。
'''
SACCUBUS_PATH='SACCUBUS_PATH'
SACCUBUS_INCLUDE_PATH=[
	'saccubus'
]

import os;
import sys;

def appendPath():
	saccubus_path = os.getenv(SACCUBUS_PATH);
	for path in SACCUBUS_INCLUDE_PATH:
		sys.path.insert(0, os.path.join(saccubus_path, path))

if __name__ == '__main__':
	print("launched")
	if os.getenv(SACCUBUS_PATH) == None:
		os.putenv(SACCUBUS_PATH, os.path.abspath(__file__));
	appendPath();
	