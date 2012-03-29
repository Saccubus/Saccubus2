#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/28

@author: psi
'''

from . import util, error;
import os;

'''
IEのクッキーでログインし、CookieJarを返す
読み取れなければエラーを送出
@param userid: 無視されます。
@param password: 無視されます。
'''
def login(userid, password):
	return readCookieFile(
			# in windows vista
			os.path.join(os.getenv("APPDATA"), "Microsoft","Windows","Cookies")
		);
	pass

'''
指定されたディレクトリ内からクッキーを読み取ります
'''
def readCookieFile(d):
	jar = util.searchNicoSessionFrom(d)
	if jar == None:
		raise error.LoginError("IE Cookie not found: {0}", str(d));
	return jar
