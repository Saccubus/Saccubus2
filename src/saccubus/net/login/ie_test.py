#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/28

@author: psi
'''
import unittest
from . import ie;

class Test(unittest.TestCase):


	def testName(self):
		ie.login(None, None)
		pass


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()