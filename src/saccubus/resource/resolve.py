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

from saccubus.error import SaccubusError;
from . import rule;
import os;

'''
	オプションはタプルのシーケンスで渡してください。
	-video-id:<string>　解決する動画IDを渡してください
	-resource-path:<string> リソースの置いてある場所を指定
	-override-video: <string>([video_id]:[filename])　命名規則を無視したい場合に。（最後の引数優先）
	-override-thread: <string>([video_id]:[filename])　命名規則を無視したい場合に。（複数OK）
'''
def fromNative(*opts):
	optDict = dict(opts);
	override_table = {'video':{}, 'thread':{}};
	if 'resource-path' not in optDict:
		raise SaccubusError("Invalid arguments! 'resource-path' is required.");
	if 'video-id' not in optDict:
		raise SaccubusError("Invalid arguments! 'video-id' is required.")
	for k,v in opts:
		if k=='override-video':
			vid, file = splitOverride(v);
			override_table['video'][vid]=file
		elif k=='override-thread':
			vid, file = splitOverride(v);
			if vid in override_table['thread']:
				override_table['thread'][vid].append(file)
			else:
				override_table['thread'][vid] = [file];
		else:
			pass
	resolver = Resolver(optDict['resource-path'], override_table);
	resolved = resolver.resolve(optDict['video-id']);
	#TODO: Nativeへは、str->strの辞書しか返さない約束なので、ここで変換してしまう。ここでいいの？
	resolved['thread'] = '\n'.join(resolved['thread']);
	return resolved;

def splitOverride(val):
	vid=val[:val.index(':')]
	file = val[val.index(':')+1:]
	return vid, file

class Resolver(object):
	'''
	ニコニコ動画の
	・動画
	・ユーザーコメント・投稿者コメント・オプショナルコメント
	・getfｌｖで手に入る動画情報
	を集め、所定のフォルダに格納します。
	さきゅばす本体から呼ばれる他、GUIからも呼んでも可
	'''
	def __init__(self, resource_path, override_table={'video':{}, 'thread':{}}):
		'''
		コンストラクタ。
		'''
		self.resource_path = resource_path;
		self.override_table = override_table;
		
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
		
		play_info_prefix=rule.formatPlayInfoFilename(video_id)
		meta_info_prefix=rule.formatMetaInfoFilename(video_id)
		video_prefix=rule.formatVideoPrefix(video_id)
		thread_prefix=rule.formatThreadPrefix(video_id)
		
		for fname in files:
			if fname.startswith(video_prefix):
				resolved['video'] = os.path.join(self.resource_path,fname);
				base, _ = os.path.splitext(fname);
				resolved['title'] = base[len(video_prefix):];
			elif fname.startswith(thread_prefix):
				resolved['thread'].append(os.path.join(self.resource_path,fname));
			elif fname == play_info_prefix:
				resolved['play_info'] = os.path.join(self.resource_path,fname);
			elif fname == meta_info_prefix:
				resolved['meta_info'] = os.path.join(self.resource_path,fname);
			pass
		if video_id in self.override_table['thread']:
			resolved['thread'] = self.override_table['thread'][video_id];
		if video_id in self.override_table['video']:
			resolved['video'] = self.override_table['video'][video_id];
		return resolved
	
	def download(self, video_id, resolved):
		pass
	
	def resolveAndDownload(self, video_id):
		return self.download(self.resolve(video_id));
