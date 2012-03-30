#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''

from saccubus.error import SaccubusError;
from . import rule;
import os;

class Resolver(object):
	'''
	ニコニコ動画の
	・動画
	・ユーザーコメント・投稿者コメント・オプショナルコメント
	・getfｌｖで手に入る動画情報
	を集め、所定のフォルダに格納します。
	'''

	def __init__(self, opts):
		'''
		コンストラクタ。
		さきゅばす本体から呼ばれる他、GUIからも呼んでも可
		オプションは辞書で渡してください。
		-resource_path:<string> リソースの置いてある場所を指定
		-override_video: <string>([video_id]:[filename])　命名規則を無視したい場合に。
		-override_thread: <string>([thread_id]:[filename])　命名規則を無視したい場合に。
		'''
		if 'resource_path' not in opts:
			raise SaccubusError("Invalid arguments!");
		
		self.resource_path = os.path.abspath( opts['resource_path'] )
		if not os.path.exists(self.resource_path):
			raise SaccubusError("Resource Path: {0} not exists!", self.resource_path);
		if not os.path.isdir(self.resource_path):
			raise SaccubusError("Resource Path: {0} is not a directory!", self.resource_path);
		
	def resolve(self, video_id):
		'''
		動画IDから、動画とコメントのファイルを解決して絶対パスを辞書で返します。
		'''
		files = filter(lambda f: f.startswith(video_id), os.listdir(self.resource_path))
		resolved = {'thread':[]};
		
		play_info_prefix=rule.formatPlayInfoPrefix(video_id)
		meta_info_prefix=rule.formatMetaInfoPrefix(video_id)
		video_prefix=rule.formatVideoPrefix(video_id)
		thread_prefix=rule.formatThreadPrefix(video_id)
		
		for fname in files:
			if fname.startswith(video_prefix):
				resolved['video'] = os.path.join(self.resource_path,fname);
				base, _ = os.path.splitext(fname);
				resolved['title'] = base[len(video_prefix):];
			elif fname.startswith(thread_prefix):
				resolved['thread'].append(os.path.join(self.resource_path,fname));
			elif fname.startswith(play_info_prefix):
				resolved['play_info'] = os.path.join(self.resource_path,fname);
			elif fname.startswith(meta_info_prefix):
				resolved['meta_info'] = os.path.join(self.resource_path,fname);
			pass
		return resolved
	
	def download(self, video_id, resolved):
		pass
	
	def resolveAndDownload(self, video_id):
		return self.download(self.resolve(video_id));
	