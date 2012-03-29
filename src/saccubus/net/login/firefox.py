#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''

import sqlite3;
from .error import LoginError;
from . import constant;
import http.cookiejar;

def login(userid, password):
	pass

'''
データベースファイルを読んで、データが存在すればクッキジャーに変換して返す。
読み取れなければエラー。
@param fname: sqliteデータベースへのパス
'''
def readDatabase(fname):
	jar = http.cookiejar.CookieJar();
	con = sqlite3.connect(fname)
	con.row_factory = sqlite3.Row
	try:
		cur = con.execute('select * from moz_cookies where host=?', [constant.COOKIE_DOMAIN])
		rowcount=0;
		for item in cur:
			rowcount+=1;
			cookie = http.cookiejar.Cookie(
					0,
					item['name'],
					item['value'],
					None,
					False,
					item['host'],
					item['host'].startswith('.'),
					item['host'].startswith('.'),
					item['path'],
					False,
					item['isSecure']!=0,
					int(item['expiry']),
					False,
					None,
					None,
					{});
			jar.set_cookie(cookie);
		if rowcount <= 0:
			raise LoginError("Failed to read firefox Cookie! => {0}", cur.rowcount);
		return jar;
	finally:
		con.close()
	
