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

class Test(unittest.TestCase):
	def setUp(self):
		VIDEO_ID="sm60"
		self.jar = login.login(test_common.TEST_USER, test_common.TEST_PASS, 'own')
		self.info = play_info.getPlayInfo(self.jar, VIDEO_ID)
		pass
	def tearDown(self):
		pass
	def testGetThread(self):
		fname = thread.downloadThread(self.jar, self.info, 'thread_id', 1000, '/dev/null');
		print(fname)
	def testConstructCommand(self):
		payload = thread.constructCommand(self.info, 'thread_id', 1000)
		self.assertEqual(
			b'<?xml version="1.0" encoding="utf-8"?><packet><thread scores="1" thread="1173124005" user_id="26735140" version="20090904"/><thread_leaves scores="1" thread="1173124005" user_id="26735140">0-50:100,1000</thread_leaves><thread click_revision="-1" fork="1" res_from="-1000" scores="1" thread="1173124005" user_id="26735140" version="20061206"/></packet>',
			payload,
			payload
			)
	def testConstructPacketPayload(self):
		th = minidom.Element("thread");
		th.setAttribute("thread", "1")
		lst = minidom.NodeList()
		lst.append(th);
		payload = thread.constructPacketPayload(lst);
		self.assertEqual(b'<?xml version="1.0" encoding="utf-8"?><packet><thread thread="1"/></packet>', payload)
	def testMerge(self):
		base = minidom.parseString('''<?xml version="1.0" encoding="UTF-8"?>
		<packet>
		<thread resultcode="0" thread="1302222473" last_res="900" ticket="1310831408" revision="1" fork="1" server_time="1332577325"/>
		<chat thread="1302222473" no="1" vpos="0" date="1310831408" premium="1" fork="1">test</chat>
		</packet>
		''')
		self.assertEqual(base.documentElement.nodeName, "packet")
		self.assertEqual(len(base.documentElement.getElementsByTagName('chat')), 1)
		appended = minidom.parseString('''<?xml version="1.0" encoding="UTF-8"?>
		<packet>
		<thread resultcode="0" thread="1302222473" last_res="900" ticket="1310831408" revision="1" fork="1" server_time="1332577325"/>
		<chat thread="1302222473" no="1" vpos="0" date="1310831408" premium="1" fork="1">test2</chat>
		</packet>
		''')
		merged = thread.mergeThread(base, appended);
		self.assertEqual(merged.documentElement.nodeName, "packet")
		self.assertEqual(len(merged.documentElement.getElementsByTagName('chat')), 2)
		pass


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testName']
	unittest.main()