#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
import urllib;
import http;
from .error import LoginError;
from .constant import COOKIE_DOMAIN, LOGIN_URL;

def login(userid, password):
	auth = {
		"mail":userid,
		"password":password
	};
	jar = http.cookiejar.CookieJar()
	authPayload = urllib.parse.urlencode(auth).encode('utf-8')
	request = urllib.request.Request(LOGIN_URL, authPayload)
	opener = urllib.request.build_opener(
		urllib.request.HTTPCookieProcessor(jar),
		)
	try:
		resp = opener.open(request)
	except urllib.error.HTTPError as e:
		raise LoginError("Failed to login: {0}".format(e));
	resp.close()
	for cookie in jar:
		if cookie.domain == COOKIE_DOMAIN:
			return jar
	raise LoginError("Failed to login Nicovideo.");
