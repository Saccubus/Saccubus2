#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''
import unittest
from . import meta_info;
from . import play_info;
from . import login;
from .. import test_common;
from . import video;
import os;

TEST_VIDEO_ID="sm60" #安心と信頼のsm60

class Test(unittest.TestCase):
	def setUp(self):
		self.resDir = os.path.join(test_common.PATH, 'resources');
		self.jar = login.login(test_common.TEST_USER, test_common.TEST_PASS, 'own')
		self.meta_info = meta_info.getMetaInfo('sm60');
		self.play_info = play_info.getPlayInfo(self.jar, 'sm60')
		pass
	def tearDown(self):
		pass
	def testName(self):
		video.downloadVideo(self.jar, self.play_info, self.meta_info, self.resDir)
		pass


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()