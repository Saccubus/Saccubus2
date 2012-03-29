#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''
import unittest
from . import title, error;

class Test(unittest.TestCase):


	def setUp(self):
		pass


	def tearDown(self):
		pass

	def testSucceed(self):
		t = title.getTitle("sm60")
		self.assertEqual(t, "なに勘違いしているんだ")
	
	def testFailure(self):
		try:
			t = title.getTitle('sm0')
		except error.LoadError:
			pass
		except:
			self.fail("未知のエラーが発生")
		else:
			self.fail("sm0は存在しないのに、タイトルが取得できてしまった => {0}", t)


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()