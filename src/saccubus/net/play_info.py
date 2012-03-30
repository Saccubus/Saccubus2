#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''

INFO_API_URL="http://flapi.nicovideo.jp/api/getflv/{0}"

import urllib;
'''
動画DLのための情報を取得する。
meta_indoより、もっと動的な情報が手に入る。
DLサーバや、メッセージサーバのURLなどが含まれる。
'''
def getPlayInfo(jar, videoid):
	url = INFO_API_URL.format(videoid);
	resp = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar)).open(url);
	content = resp.read().decode('ascii')
	resp.close();
	return parsePlayInfo(content);


def parsePlayInfo(content):
	_info = dict( urllib.parse.parse_qsl(content, encoding='utf-8', errors='replace') )
	return _info