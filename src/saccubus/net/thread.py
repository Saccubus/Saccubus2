#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/30

@author: psi
'''

from xml.dom import minidom;
import urllib

'''
コメントをDLします。
'''
def downloadThreads(jar, play_info, resDir, merge=True):
	pass

def downloadThread(jar, play_info, thread_id_key, backCnt, fname, merge=True):
	payload = constructCommand(play_info, thread_id_key, backCnt)
	resp = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar)).open(play_info['ms'], payload)
	return resp.read()

def constructCommand(play_info, thread_id_key, backCnt):
	lst = minidom.NodeList();
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
	if thread_id_key == 'thread_id':
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
コマンドのリストから、投稿用のPOSTデータを取得する
'''
def constructPacketPayload(commandNodes):
	doc = minidom.Document()
	packet = doc.createElement("packet");
	doc.appendChild(packet)
	for node in commandNodes:
		packet.appendChild(node)
	return doc.toxml('utf-8')

def mergeThread(base, appended):
	for chat in appended.documentElement.getElementsByTagName('chat'):
		base.documentElement.appendChild(chat)
	return base

