#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
import unittest
from .resolve import Resolver, fromNative;
from saccubus import test_common;
from saccubus.error import SaccubusError;
import os.path;

class Test(unittest.TestCase):
	def setUp(self):
		self.resource_path=os.path.join(test_common.PATH, "resources");
		pass


	def tearDown(self):
		pass


	def testInvalidArg(self):
		try:
			Resolver();
		except TypeError:
			pass
		else:
			self.fail("解決パスを示していないのに例外が発生しない")
		try:
			Resolver("/tmp/__not_exist__");
		except SaccubusError:
			pass
		else:
			self.fail("存在しないパスを指定しているのに例外が発生しない")
		try:
			Resolver(self.resource_path)
		except SaccubusError as e:
			self.fail("例外が発生: {0}".format(e.what()))
		except :
			self.fail("未知の例外")
		else:
			pass

	def testBaseResolver(self):
		resolv = Resolver(self.resource_path)
		dic = resolv.resolve("sm0");
		
		self.assertEqual(dic['video'], os.path.join(self.resource_path,"sm0_video_test.mp4"), "動画の取得に失敗しています")
		self.assertEqual("test", dic['title'], "タイトルの取得に失敗しています");
		self.assertEqual(1, len(dic['thread']), "スレッドの数がおかしいです。{0}個ありますが、一個のはずです".format(len(dic['thread'])));
		self.assertEqual(dic['thread'][0], os.path.join(self.resource_path, "sm0_thread_123456.xml"), "スレッドの取得に失敗")
		self.assertEqual(dic['play_info'], os.path.join(self.resource_path,"sm0_play_info.txt"));
		self.assertEqual(dic['meta_info'], os.path.join(self.resource_path,"sm0_meta_info.xml"));

	def testNativeBasic(self):
		opt = [];
		opt.append(('resource-path', self.resource_path))
		opt.append(('video-id', 'sm0'))
		dic = fromNative(*opt)
		self.assertEqual(dic['video'], os.path.join(self.resource_path,"sm0_video_test.mp4"), "動画の取得に失敗しています")
		self.assertEqual("test", dic['title'], "タイトルの取得に失敗しています");
		self.assertEqual(1, len(dic['thread']), "スレッドの数がおかしいです。{0}個ありますが、一個のはずです".format(len(dic['thread'])));
		self.assertEqual(dic['thread'][0], os.path.join(self.resource_path, "sm0_thread_123456.xml"), "スレッドの取得に失敗")
		self.assertEqual(dic['play_info'], os.path.join(self.resource_path,"sm0_play_info.txt"));
		self.assertEqual(dic['meta_info'], os.path.join(self.resource_path,"sm0_meta_info.xml"));
	
	def testNativeOverride(self):
		opt = [];
		opt.append(('resource-path', self.resource_path))
		opt.append(('video-id', 'sm0'))
		opt.append(('override-video', 'sm0:noodle'))
		opt.append(('override-thread', 'sm0:udon'))
		opt.append(('override-thread', 'sm0:soba'))
		dic = fromNative(*opt)
		self.assertEqual(dic['video'], 'noodle', "動画のオーバーライドに失敗しています")
		self.assertListEqual(dic['thread'], ['udon', 'soba'], "スレッドのオーバーライドに失敗しています")

if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()