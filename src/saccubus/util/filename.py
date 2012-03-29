#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''

#FIXME: 明らかにこういうのはシステムに任せるべき処理なのだけど、APIが無いのだから仕方ない
FILENAME_FROM = '!?:;/\|,*"><'
FILENAME_TO = '！？：；／＼｜，＊”＞＜'
TRANS_TABLE=str.maketrans(FILENAME_FROM, FILENAME_TO)
# FIXME: WindowsはUnicodeに対応してる、でもFFmpeg(MinGW)は対応してない。
#import sys;
FILENAME_ENCODING='ms932'#sys.getfilesystemencoding();

def escapeFilename(_str):
	_bstr = _str.encode(encoding=FILENAME_ENCODING, errors='ignore')
	_str = _bstr.decode(encoding=FILENAME_ENCODING, errors='ignore')
	return _str.translate(TRANS_TABLE)

