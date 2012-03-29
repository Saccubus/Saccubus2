#! python3
# -*- coding: utf-8 -*-

from . import firefox, own, ie;
from .util import isLoggedIn;

'''
ニコニコ動画にログインし、CookieJarを返します。
ログインに失敗した場合はLoginErrorを送出します。
'''
def login(userid, password, method=None):
	if method == None:
		for _method in LOGIN_METHOD:
			try:
				return _method(userid, password)
			finally:
				pass
	else:
		if method not in LOGIN_METHOD:
			raise ValueError("Unknwon login method: {0}".format(method));
		else:
			return LOGIN_METHOD[method](userid, password)
		


'''
クッキーを取得する各メソッド。
シグネチャ：login(userid, password) => CookieJar
注意：　メソッド内でグローバル変数は使わない。
'''
LOGIN_METHOD={
	"ie": ie.login,
	"firefox": firefox.login,
	"chrome": None,
	"safari": None,
	"own": own.login
};

__all__=[
	'login',
];
