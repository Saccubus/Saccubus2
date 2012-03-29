#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''

TITLE_API_URL = "http://ext.nicovideo.jp/api/getthumbinfo/{0}"

import xml.dom.minidom;
import urllib;
from . import error;

'''
ニコニコ動画からタイトルを取得する。
タイトルの取得にはログインは必要ない。
'''
def getTitle(video_id):
	resp = urllib.request.urlopen(TITLE_API_URL.format(video_id))
	dom = xml.dom.minidom.parseString(resp.read()).documentElement;
	resp.close();
	if dom.attributes['status'].value != 'ok':
		raise error.LoadError("Video {0} not found", video_id);
	title_node = dom.getElementsByTagName('thumb')[0].getElementsByTagName('title')[0];
	return title_node.childNodes[0].data;
	
	