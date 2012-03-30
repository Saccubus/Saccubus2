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

OFFICIAL_VIDEO='1318394714' #よーあけーまえのーくらやみがー
VIDEO_ID="sm60"

class Test(unittest.TestCase):
	jar = None;
	defInfo = None;
	offInfo = None;
	def setUp(self):
		if Test.jar is None:
			Test.jar = login.login(test_common.TEST_USER, test_common.TEST_PASS, 'own')
		if Test.defInfo is None:
			Test.defInfo = play_info.getPlayInfo(Test.jar, VIDEO_ID)
		if Test.offInfo is None:
			Test.offInfo = play_info.getPlayInfo(Test.jar, OFFICIAL_VIDEO)
	def tearDown(self):
		pass
	def testDownloadThread(self):
		files = thread.downloadThreads(Test.jar, OFFICIAL_VIDEO, Test.offInfo, 1000, test_common.RESOURCE_DL_PATH)
		for f in files:
			self.assertTrue(os.path.exists(f))
			self.assertTrue(os.path.isfile(f))
			os.remove(f)
		
	def testOfficialThread(self):
		fname = thread.downloadThread(Test.jar, OFFICIAL_VIDEO, Test.offInfo, 'thread_id', 1000, test_common.RESOURCE_DL_PATH);
		self.assertTrue(os.path.exists(fname))
		self.assertTrue(os.path.isfile(fname))
		os.remove(fname)
	def testGetThreadKey(self):
		key_dict = thread.getThreadKey(Test.jar, OFFICIAL_VIDEO);
		self.assertIsNotNone(key_dict['threadkey'])
		self.assertNotEquals(key_dict['threadkey'], '')
	def testGetNormalThread(self):
		fname = thread.downloadThread(Test.jar, VIDEO_ID, Test.defInfo, 'thread_id', 1000, test_common.RESOURCE_DL_PATH);
		self.assertTrue(os.path.exists(fname))
		self.assertTrue(os.path.isfile(fname))
		os.remove(fname)
	def testConstructCommand(self):
		payload = thread.constructCommand(Test.jar, Test.defInfo, 'thread_id', 1000)
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