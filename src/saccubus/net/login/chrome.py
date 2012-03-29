#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''

import sqlite3;
from http import cookiejar;
import os;
from . import constant, error;

def login(userid, password):
	return searchProfile(
		# in windows vista
		os.path.join(os.getenv('LOCALAPPDATA'), 'Google','Chrome','User Data','Default')
	);

def searchProfile(*dirs):
	for d in dirs:
		if os.path.isdir(d) and os.path.exists(d):
			try:
				return readDatabase(os.path.join(d, 'Cookie'));
			except:
				pass
	raise error.LoginError("Chromeのクッキーは取得できませんでした");
	

def readDatabase(fname):
	jar = cookiejar.CookieJar();
	con = sqlite3.connect(fname)
	con.row_factory = sqlite3.Row
	try:
		# https://groups.google.com/forum/?hl=ja&fromgroups#!topic/chromium-extensions/c4lnssuNAFI
		delta = 11644473600
		cur = con.execute('SELECT * FROM cookies where host_key=?;', [constant.COOKIE_DOMAIN])
		rowcount=0;
		for item in cur:
			rowcount+=1;
			_expire = (int(int(item['expires_utc'])/1000000)-delta);
			cookie = cookiejar.Cookie(
					0,
					item['name'],
					item['value'],
					None,
					False,
					item['host_key'],
					item['host_key'].startswith('.'),
					item['host_key'].startswith('.'),
					item['path'],
					False,
					item['secure']!=0,
					_expire,
					False,
					None,
					None,
					{});
			jar.set_cookie(cookie);
		if rowcount <= 0:
			raise error.LoginError("Failed to read Chrome Cookie! => {0}", cur.rowcount);
		return jar;
	finally:
		con.close()
