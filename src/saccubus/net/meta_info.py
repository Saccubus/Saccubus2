#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''

META_API_URL = "http://ext.nicovideo.jp/api/getthumbinfo/{0}"
import xml.dom.minidom;
import urllib;
from . import error;

__all__=['getMetaInfo']

'''
動画のメタ情報を取得する。
タイトルなどが含まれる
'''
def getMetaInfo(video_id):
	resp = urllib.request.urlopen(META_API_URL.format(video_id))
	dom = xml.dom.minidom.parseString(resp.read()).documentElement;
	resp.close();
	return parseMetaInfo(dom, video_id)

'''
DOMを解析する
'''
def parseMetaInfo(dom, video_id):
	if dom.attributes['status'].value != 'ok':
		raise error.LoadError("Video {0} not found", video_id);
	thumb_node = dom.getElementsByTagName('thumb')[0];
	info = {};
	node = thumb_node._get_firstChild();
	for node in thumb_node.childNodes:
		if node.nodeType == node.ELEMENT_NODE and node.hasChildNodes():
			info[node.nodeName] = node.childNodes[0].data;
	return info;
