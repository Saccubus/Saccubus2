#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''
__all__=[
	'formatPlayInfoPrefix',
	'formatMetaInfoPrefix',
	'formatVideoPrefix',
	'formatThreadPrefix'
];

'''
名前規則
・play_info(getflv)： dir/[video_id]_play_info.txt
・meta_info(getthumbinfo)： dir/[video_id]_meta_info.xml
・動画： dir/[video_id]_video_title.<ext>
・コメント:dir/[video_id]_thread_<スレッドID>.<ext>
'''
PLAY_INFO_PREFIX="{0}_play_info"
META_INFO_PREFIX="{0}_meta_info"
VIDEO_PREFIX="{0}_video_"
THREAD_PREFIX="{0}_thread_"

def formatPlayInfoPrefix(video_id):
	return PLAY_INFO_PREFIX.format(video_id)
def formatMetaInfoPrefix(video_id):
	return META_INFO_PREFIX.format(video_id)
def formatVideoPrefix(video_id):
	return VIDEO_PREFIX.format(video_id)
def formatThreadPrefix(video_id):
	return THREAD_PREFIX.format(video_id)

