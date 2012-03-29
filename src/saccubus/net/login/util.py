#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/28

@author: psi
'''

import urllib;
import os;
import re;
from http import cookiejar;
from . import constant;
from time import time

'''
指定されたクッキジャーのセッションは、ニコニコ動画で有効かどうか調べます。
@param jar: ログインされてるかどうかを判定するcookiejar
'''
def isLoggedIn(jar):
	request = urllib.request.Request(constant.MYPAGE_URL)
	opener = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar))
	resp = opener.open(request)
	resp.close()
	return resp.geturl() == constant.MYPAGE_URL;

'''
指定されたセッションIDから、ニコニコ動画のセッションとなるクッキージャーを作ります。
有効なセッションでない場合は、Noneを返します。
@param session_id: セッションID
'''
def createCookieFrom(session_id):
	cookie = cookiejar.Cookie(
			0,
			constant.SESSION_NAME,
			session_id,
			None,
			False,
			constant.COOKIE_DOMAIN,
			constant.COOKIE_DOMAIN.startswith('.'),
			constant.COOKIE_DOMAIN.startswith('.'),
			constant.SESSION_PATH,
			False,
			False, #item['isSecure']!=0,
			int(time())+7*24*3600,#int(item['expiry']),
			False,
			None,
			None,
			{});
	jar = cookiejar.CookieJar();
	jar.set_cookie(cookie);
	if isLoggedIn(jar):
		return jar
	return None;

'''
任意のファイルのリストを読んで、ニコニコ動画の有効なセッションがあるか確認する。
存在を確認できれば、そのセッションを格納したクッキジャーを返す。
見つからなければ、Noneを返す
@param path_or_dir: ファイル名かディレクトリの配列
'''
def searchNicoSessionFrom(*path_or_dir):
	'''
	このメソッド内だけで使う。
	ファイルの中身からバイナリでセッションパターンを探して、クッキーを作る
	作れなかったらNoneを返す
	'''
	def read_file(file):
		f = open(file, 'rb');
		content = f.read();
		f.close();
		for match in re.finditer(constant.SESSION_PATTERN.encode(), content):
			jar = createCookieFrom(match.group(0).decode('US-ASCII'))
			if jar != None:
				return jar;
		return None;
	'''
	具体的な検索処理はここから。
	'''
	for elem in path_or_dir:
		if os.path.isdir(elem):
			for root, _, files in os.walk(elem):
				for file in files:
					jar=read_file(os.path.join(root, file))
					if jar != None:
						return jar
		elif os.path.isfile(elem):
			jar=read_file(elem)
			if jar != None:
				return jar
	return None;
