#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''
import unittest
from . import thread, play_info;
from . import login;
from .. import test_common;
from xml.dom import minidom;
import os;

class Test(unittest.TestCase):
	def setUp(self):
		VIDEO_ID="sm60"
		self.jar = login.login(test_common.TEST_USER, test_common.TEST_PASS, 'own')
		self.info = play_info.getPlayInfo(self.jar, VIDEO_ID)
		pass
	def tearDown(self):
		pass
	def testOfficialThread(self):
		pass
	def testGetNormalThread(self):
		fname = thread.downloadThread(self.jar, self.info, 'thread_id', 1000, os.path.join(test_common.PATH, "resources", "sm60_thread.xml"));
		self.assertTrue(os.path.exists(fname))
		self.assertTrue(os.path.isfile(fname))
		os.remove(fname)
	def testConstructCommand(self):
		payload = thread.constructCommand(self.info, 'thread_id', 1000)
		self.assertEqual(
			b'<?xml version="1.0" encoding="utf-8"?><packet><thread scores="1" thread="1173124005" user_id="26735140" version="20090904"/><thread_leaves scores="1" thread="1173124005" user_id="26735140">0-50:100,1000</thread_leaves><thread click_revision="-1" fork="1" res_from="-1000" scores="1" thread="1173124005" user_id="26735140" version="20061206"/></packet>',
			payload
			)
	def testConstructPacketPayload(self):
		th = minidom.Element("thread");
		th.setAttribute("thread", "1")
		lst = minidom.NodeList()
		lst.append(th);
		payload = thread.constructPacketPayload(lst);
		self.assertEqual(b'<?xml version="1.0" encoding="utf-8"?><packet><thread thread="1"/></packet>', payload)



if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()