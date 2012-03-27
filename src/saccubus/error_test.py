#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
import unittest
from saccubus.error import SaccubusError;

class Test(unittest.TestCase):
	def setUp(self):
		pass
	def tearDown(self):
		pass
	def testThrow(self):
		try:
			raise SaccubusError("Test");
		except SaccubusError as e:
			self.assertEqual(str(e), "Test", "Error messages must be equal.");
		except:
			self.fail("Unkown exception caught.")
		else:
			self.fail("No exception caught.")
	def testFormat(self):
		try:
			raise SaccubusError("Test {0}", "FMT");
		except SaccubusError as e:
			self.assertEqual(str(e), "Test FMT", "Error messages must be equal.");
		except:
			self.fail("Unkown exception caught.")
		else:
			self.fail("No exception caught.")


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()