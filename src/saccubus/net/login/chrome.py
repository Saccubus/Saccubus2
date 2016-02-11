#! python3
# -*- coding: utf-8 -*-
'''
  Copyright (C) 2012 psi

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
'''

import sqlite3;
from http import cookiejar;
import os;
from . import constant, error;
from ctypes import *;
from ctypes.wintypes import DWORD;

class DATA_BLOB(Structure):
	_fields_ = [("cbData", DWORD), ("pbData", POINTER(c_char))]

def login(userid, password):
	return searchProfile(
		# inXP
		os.path.join(os.getenv('USERPROFILE', ''),'Local Settings','Application Data','Google','Chrome','User Data', 'Default' ),
		# in windows vista
		os.path.join(os.getenv('LOCALAPPDATA', ''), 'Google','Chrome','User Data','Default'),
		# linux
		os.path.join(os.getenv('HOME', ''), '.config','google-chrome','Default')
	);

def searchProfile(*dirs):
	for d in dirs:
		if os.path.exists(d) and os.path.isdir(d):
			try:
				return readDatabase(os.path.join(d, 'Cookies'));
			except:
				pass
	raise error.LoginError("Could not find Chrome cookie in {0}".format(repr(dirs)));

# DPAPIで復号
def decrypt(cipherText):
	# UI無効
	CRYPTPROTECT_UI_FORBIDDEN = 0x01

	# 暗号文
	cipherTextLen = len(cipherText)
	cipherTextBuf = c_buffer(cipherText, cipherTextLen)
	cipherTextBlob = DATA_BLOB(cipherTextLen, cipherTextBuf)

	# エントロピー (不要)
	entropyBlob = DATA_BLOB(0, c_buffer(0))

	# 復号結果の出力先
	outputBlob = DATA_BLOB()

	# 復号を実行
	if windll.crypt32.CryptUnprotectData(byref(cipherTextBlob), None, byref(entropyBlob), None, None, CRYPTPROTECT_UI_FORBIDDEN, byref(outputBlob)):
		# 復号したデータを文字列にして返す
		cbData = int(outputBlob.cbData)
		buffer = c_buffer(cbData)
		cdll.msvcrt.memcpy(buffer, outputBlob.pbData, cbData)
		windll.kernel32.LocalFree(outputBlob.pbData)
		return buffer.value.decode()
	else:
		return None

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
			
			# value があれば value を使う。なければ encrypted_value を復号して使う。
			if item['value']:
				value = item['value'];
			else:
				value = decrypt(item['encrypted_value']);

			cookie = cookiejar.Cookie(
					0,
					item['name'],
					value,
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
