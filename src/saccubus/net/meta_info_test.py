#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''
import unittest
from . import meta_info;
from . import error;
class Test(unittest.TestCase):


	def setUp(self):
		pass


	def tearDown(self):
		pass
	def testSucceed(self):
		t = meta_info.getMetaInfo('sm60');
		self.assertEqual(t['title'], "なに勘違いしているんだ")
	
	def testFailure(self):
		try:
			t = meta_info.getMetaInfo('sm0');
		except error.LoadError:
			pass
		except:
			self.fail("未知のエラーが発生")
		else:
			self.fail("sm0は存在しないのに、タイトルが取得できてしまった => {0}".format(t))


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()