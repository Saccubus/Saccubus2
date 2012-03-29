#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''
import unittest
from . import filename;

class Test(unittest.TestCase):


	def setUp(self):
		pass


	def tearDown(self):
		pass


	def testName(self):
		self.assertEqual("abc", filename.escapeFilename("abc"));
		self.assertEqual("__", filename.escapeFilename("_♥_"));
		self.assertEqual("_＼_", filename.escapeFilename('_\_'));
		self.assertEqual(filename.FILENAME_TO, filename.escapeFilename(filename.FILENAME_FROM));


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()