#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''

import os;
import urllib;
import shutil;
from ..util.filename import escapeFilename;
from ..resource.rule import formatVideoPrefix

WATCH_PAGE_URL='http://www.nicovideo.jp/watch/{0}'

'''
infoとjarを用いて、指定したディレクトリに動画を保存する。
拡張子は適当に決定する。
取得したファイルの保存先をstrで返します。
'''
def downloadVideo(jar, play_info, meta_info, resDir):
	fname = formatVideoPrefix(meta_info['video_id'])+escapeFilename(meta_info['title']);
	fname = os.path.join(resDir, fname)
	touchWatchPage(jar, meta_info['video_id'])
	if os.path.exists(fname):
		os.remove(fname)
	try:
		resp = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar)).open(play_info['url'])
		#FIXME: 見苦しい。
		orig_fname = resp.info()['Content-Disposition'].split('filename=')[1].replace('"', '').replace("'", "");
		_, ext = os.path.splitext(orig_fname)
		file = open(''.join((fname, ext)),'wb')
		shutil.copyfileobj(resp, file);
	finally:
		resp.close
		file.close()
	return fname

'''
事前にwatchページを見ないと、DLできないらしいので
touchしておきます。
'''
def touchWatchPage(jar, video_id):
	resp = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar)).open(WATCH_PAGE_URL.format(video_id))
	resp.close();
