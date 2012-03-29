#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/28

@author: psi
'''
import unittest

#from ... import test_common;
#from . import ie, constant;
#import os;

class Test(unittest.TestCase):
	def testReadCookieTest(self):
		'''
		jar = ie.readCookieFile(os.path.join(test_common.path, "net", "login", "ie"))
		for cookie in jar:
			if cookie.name=="user_session" and cookie.domain==constant.COOKIE_DOMAIN:
				self.assertEqual("user_session_26735140_19439488701445715695", cookie.value);
				return
		self.fail("Failed to read IE cookie!");
		'''


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()