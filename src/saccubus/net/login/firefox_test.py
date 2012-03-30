#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
import unittest
import os.path;
from saccubus import test_common;
from . import firefox, constant;

class Test(unittest.TestCase):
	def setUp(self):
		pass
	def tearDown(self):
		pass
	def testReadDatabase(self):
		jar = firefox.readDatabase(os.path.join(test_common.PATH, "net", "login", "firefox.sqlite"));
		for cookie in jar:
			if cookie.name=="user_session" and cookie.domain==constant.COOKIE_DOMAIN:
				self.assertEqual("user_session_26735140_14681406081901241868", cookie.value);
				#self.assertTrue(util.isLoggedIn(jar));
				return
		self.fail("Failed to read fiurefox cookie!");


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()