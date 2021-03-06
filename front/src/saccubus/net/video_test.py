#! python3
# -*- coding: utf-8 -*-
'''
  Copyright (C) 2012 psi

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
'''
import unittest
if __name__ == "__main__":
	import sys
	import os
	abs = os.path.abspath(os.path.join(os.path.dirname(__file__), "..",".."))
	sys.path.append(abs)
from saccubus.net import meta_info;
from saccubus.net import play_info;
from saccubus.net import login;
from saccubus import test_common;
from saccubus.net import video;
import os;

TEST_VIDEO_ID='1339405721' #ニャル子さん。テスト時に変えたほうが良いかもしれぬ

class Test(unittest.TestCase):
	def setUp(self):
		self.jar = login.login(test_common.TEST_USER, test_common.TEST_PASS, 'own')
		_, self.meta_info = meta_info.downloadMetaInfo(TEST_VIDEO_ID, test_common.RESOURCE_DL_PATH);
		_, self.play_info = play_info.downloadPlayInfo(self.jar, TEST_VIDEO_ID, test_common.RESOURCE_DL_PATH)
	def tearDown(self):
		pass
	def testNormalVideoDownloading(self):
		fname = video.downloadVideo(self.jar, self.play_info, self.meta_info, test_common.RESOURCE_DL_PATH)
		self.assertTrue(os.path.exists(fname))
		self.assertTrue(os.path.isfile(fname))
		os.remove(fname)
	def testTouchingOfficialVideo(self):
		video.touchWatchPage(self.jar, TEST_VIDEO_ID)


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()