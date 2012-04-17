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
