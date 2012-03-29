#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
import unittest
from .error import LoginError;

class Test(unittest.TestCase):
	def testLoginErrorCatch(self):
		try:
			raise LoginError("Hey!")
		except LoginError as e:
			self.assertEqual("Hey!", str(e));
		except:
			self.fail("Failed to catch exception")


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()