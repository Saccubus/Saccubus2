#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
import unittest
from .resolve import Resolver;
from saccubus import test_common;
from saccubus.error import SaccubusError;
import os.path;

class Test(unittest.TestCase):
	def setUp(self):
		self.resource_path=os.path.join(test_common.path, "resources");
		pass


	def tearDown(self):
		pass


	def testInvalidArg(self):
		try:
			Resolver({});
		except SaccubusError:
			pass
		else:
			self.fail("解決パスを示していないのに例外が発生しない")
		try:
			Resolver({"resource_path":"/tmp/__not_exist__"});
		except SaccubusError:
			pass
		else:
			self.fail("存在しないパスを指定しているのに例外が発生しない")
		try:
			Resolver({"resource_path":self.resource_path})
		except SaccubusError as e:
			self.fail("例外が発生: {0}".format(e.what()))
		except :
			self.fail("未知の例外")
		else:
			pass

	def testBaseResolver(self):
		resolv = Resolver({"resource_path":self.resource_path})
		dic = resolv.resolve("sm0");
		
		self.assertEqual(dic['video'], os.path.join(self.resource_path,"sm0_video_test.mp4"), "動画の取得に失敗しています")
		self.assertEqual("test", dic['title'], "タイトルの取得に失敗しています");
		self.assertEqual(1, len(dic['thread']), "スレッドの数がおかしいです。{0}個ありますが、一個のはずです".format(len(dic['thread'])));
		self.assertEqual(dic['thread'][0], os.path.join(self.resource_path, "sm0_thread_123456.xml"), "スレッドの取得に失敗")
		self.assertEqual(dic['info'], os.path.join(self.resource_path,"sm0_info.txt"));


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()