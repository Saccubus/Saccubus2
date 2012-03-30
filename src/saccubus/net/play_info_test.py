#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''
import unittest
from .login import own, util;
from . import play_info;

class Test(unittest.TestCase):

	def setUp(self):
		self.jar = own.login("saccubus@gmail.com", "test1234")
		self.assertTrue(util.isLoggedIn(self.jar));


	def tearDown(self):
		pass


	def testBasic(self):
		dic = play_info.getPlayInfo(self.jar, 'sm60')
		self.assertEquals(dic['thread_id'], '1173124005')
		self.assertEquals(dic['l'], '50')
		pass


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()