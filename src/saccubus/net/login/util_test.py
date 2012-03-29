#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''
import unittest
from . import util;

class Test(unittest.TestCase):


	def setUp(self):
		pass


	def tearDown(self):
		pass


	def testName(self):
		path="C:/Users/psi/AppData/Roaming/Mozilla/Firefox/Profiles/bdlmkjhm.default"
		jar = util.searchNicoSessionFrom(path);
		self.assertIsNotNone(jar);
		self.assertTrue(util.isLoggedIn(jar))

if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()