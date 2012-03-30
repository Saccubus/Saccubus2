#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
import unittest
from . import own;
from .error import LoginError;
from ... import test_common;

class Test(unittest.TestCase):


	def setUp(self):
		pass


	def tearDown(self):
		pass


	def testNone(self):
		try:
			own.login(None, None)
		except LoginError:
			pass
		except:
			self.fail("ログイン中に未知のエラーが発生")
		else:
			self.fail("(None, None)でログイン成功？")

	def testLogin(self):
		self.assertIsNotNone(
			own.login(test_common.TEST_USER,test_common.TEST_PASS),
			"正しいパスワードでもログインできません"
			)

	def testLoginFailure(self):
		try:
			own.login(test_common.TEST_USER,"__invalid_password__")
		except LoginError:
			pass
		except:
			self.fail("ログイン中に未知のエラーが発生")
		else:
			self.fail("間違ったパスワードでログインできちゃう？？")


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testLogin']
	unittest.main()