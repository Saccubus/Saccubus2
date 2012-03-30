#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''
import unittest
import os;
from ... import test_common;
from . import chrome, constant;

class Test(unittest.TestCase):


	def setUp(self):
		pass


	def tearDown(self):
		pass


	def testDatabase(self):
		jar = chrome.readDatabase(os.path.join(test_common.PATH, "net", "login", "Cookies.chrome"))
		for cookie in jar:
			if cookie.name=="user_session" and cookie.domain==constant.COOKIE_DOMAIN:
				self.assertEqual("user_session_26735140_19721752331154494149", cookie.value);
				#self.assertTrue(util.isLoggedIn(jar))
				return
		self.fail("Failed to read Chrome cookie!");


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()