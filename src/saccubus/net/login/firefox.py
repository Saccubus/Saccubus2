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
import os;

def login(userid, password):
	
	return searchProfile(
		# in windows vista
		os.path.join(os.getenv('APP_DATA'), 'Mozilla','Firefox','Profiles'),
		# in fedora 16
		os.path.join(os.getenv('HOME'), '.mozilla','firefox')
	);

def searchProfile(*prof_dirs):
	for d in prof_dirs:
		if os.path.isdir(d) and os.path.exists(d):
			for pdir in os.listdir(d):
				try:
					return readDatabase(os.path.join(pdir, 'cookies.sqlite'))
				except LoginError:
					pass
	raise LoginError("Firefoxのクッキーが見つかりませんでした");

'''
データベースファイルを読んで、データが存在すればクッキジャーに変換して返す。
読み取れなければエラーを送出。
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
	
