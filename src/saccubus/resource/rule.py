#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''
from ..util.filename import escapeFilename;

__all__=[
	'formatPlayInfoPrefix',
	'formatMetaInfoPrefix',
	'formatVideoPrefix',
	'formatVideoFilename',
	'formatThreadPrefix'
	'formatThreadFilename'
];

'''
名前規則
・play_info(getflv)： dir/[video_id]_play_info.txt
・meta_info(getthumbinfo)： dir/[video_id]_meta_info.xml
・動画： dir/[video_id]_video_title.<ext>
・コメント:dir/[video_id]_thread_<スレッドID>.<ext>
'''
PLAY_INFO_FORMAT="{video_id}_play_info.txt"
META_INFO_FORMAT="{video_id}_meta_info.xml"

VIDEO_PREFIX="{video_id}_video_"
VIDEO_FORMAT=VIDEO_PREFIX+"{title}{ext}"

THREAD_PREFIX="{video_id}_thread_"
THREAD_FORMAT=THREAD_PREFIX+"{thread_id}.xml"

def formatPlayInfoFilename(video_id):
	return PLAY_INFO_FORMAT.format(video_id=video_id)
def formatMetaInfoFilename(video_id):
	return META_INFO_FORMAT.format(video_id=video_id)

def formatVideoPrefix(video_id):
	return VIDEO_PREFIX.format(video_id=video_id)
def formatVideoFilename(video_id, title, ext):
	return VIDEO_FORMAT.format(video_id=video_id, title=escapeFilename(title), ext=ext)

def formatThreadPrefix(video_id):
	return THREAD_PREFIX.format(video_id=video_id)
def formatThreadFilename(video_id, thread_id):
	return THREAD_FORMAT.format(video_id=video_id, thread_id=thread_id)

