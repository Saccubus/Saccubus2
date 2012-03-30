#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''

from xml.dom import minidom;
import os;
import shutil;
import urllib

'''
コメントをDLします。
'''
def downloadThreads(jar, play_info, resDir):
	pass

def downloadThread(jar, play_info, thread_id_key, backCnt, fname):
	payload = constructCommand(play_info, thread_id_key, backCnt)
	resp = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar)).open(play_info['ms'], payload)
	if os.path.exists(fname):
		os.remove(fname)
	with open(fname, 'wb') as f, resp:
		shutil.copyfileobj(resp, f)
	return fname;

def constructCommand(play_info, thread_id_key, backCnt):
	lst = minidom.NodeList();
	#デフォルトコメント
	th = minidom.Element('thread')
	th.setAttribute('thread', play_info[thread_id_key])
	th.setAttribute('version', '20090904')
	th.setAttribute('user_id', play_info['user_id'])
	th.setAttribute('scores', '1')
	lst.append(th)
	leave = minidom.Element('thread_leaves')
	leave.setAttribute('thread', play_info[thread_id_key])
	leave.setAttribute('user_id', play_info['user_id'])
	leave.setAttribute('scores', '1')
	txt=minidom.Text();
	txt.data = "0-{to}:100,{back}".format(back=backCnt, to=(int(play_info['l'])+59//60))
	leave.appendChild(txt)
	lst.append(leave)
	#投稿者コメント
	fth = minidom.Element('thread')
	fth.setAttribute('thread', play_info[thread_id_key])
	fth.setAttribute('version', '20061206')
	fth.setAttribute('res_from', '-1000')
	fth.setAttribute('fork', '1')
	fth.setAttribute('user_id', play_info['user_id'])
	fth.setAttribute('scores', '1')
	fth.setAttribute('click_revision', '-1')
	lst.append(fth)
	return constructPacketPayload(lst)

'''
コマンドのリストから、取得用のPOSTデータを取得する
'''
def constructPacketPayload(commandNodes):
	doc = minidom.Document()
	packet = doc.createElement("packet");
	doc.appendChild(packet)
	for node in commandNodes:
		packet.appendChild(node)
	return doc.toxml('utf-8')

