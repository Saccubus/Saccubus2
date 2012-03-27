#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
import unittest
from saccubus.resource.resolve import Resolve;
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
			Resolve({});
		except SaccubusError:
			pass
		else:
			self.fail("解決パスを示していないのに例外が発生しない")
		try:
			Resolve({"resource_path":"/tmp/__not_exist__"});
		except SaccubusError:
			pass
		else:
			self.fail("存在しないパスを指定しているのに例外が発生しない")
		try:
			Resolve({"resource_path":self.resource_path})
		except SaccubusError as e:
			self.fail("例外が発生: {0}".format(e.what()))
		except :
			self.fail("未知の例外")
		else:
			pass

	def testBaseResolve(self):
		resolv = Resolve({"resource_path":self.resource_path})
		dic = resolv.resolve("sm0");
		
		self.assertEqual(dic['video'], os.path.join(self.resource_path,"sm0_video_test.mp4"))
		self.assertEqual("test", dic['title'], "タイトルの取得に失敗しています");


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()