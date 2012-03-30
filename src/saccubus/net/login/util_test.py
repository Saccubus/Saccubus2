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


	def testReadSession(self):
		# TODO: お使いの環境のクッキーがありそうな場所を指定してください。
		jar = util.searchNicoSessionFrom(
			"/home/psi/.mozilla/firefox",
			"C:/Users/psi/AppData/Roaming/Mozilla/Firefox/Profiles/bdlmkjhm.default",
			);
		self.assertIsNotNone(jar);
		self.assertTrue(util.isLoggedIn(jar))

if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()