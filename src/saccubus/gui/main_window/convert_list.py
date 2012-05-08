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

import tkinter;
import subprocess;
import threading;

class TaskRunner(threading.Thread):
	pass

class Task(object):
	def __init__(self, videoId):
		self.videoId = videoId;
		pass
	def execute(self):
		pass
	def __str__(self, *args, **kwargs):
		status = '予約中'
		if self.running():
			status = '実行中'
		return "動画ID:[{videoId:>15}] 状態:[{status:>10}]".format(videoId = self.videoId, status=status)
		return self.videoId;
	def running(self):
		return False;

class ConvertListMenu(tkinter.Menu):
	def __init__(self, master):
		tkinter.Menu.__init__(self, master)
		self.add_cascade(label="削除", command=self.onDeleteTask)
		master.bind('<Button-3>', self.onClick)
	def onClick(self, *event):
		event=event[0]
		if len(self.master.curselection()) > 0:
			self.post(event.x_root,event.y_root)
	def onDeleteTask(self, *event):
		if len(self.master.curselection()) > 0:
			for sel in self.master.curselection():
				self.master.unregistTaskFromUser(int(sel))

class ConvertList(tkinter.Listbox):
	'''
	変換タスクの管理と、その表示を担う。見苦しいけどこれで工数削減。
	'''
	def __init__(self, master=None, cnf={}, **kw):
		'''
		UIと、タスクリストの初期化を行う
		'''
		cnf['font']="Monospace"
		cnf['activestyle']='none'
		tkinter.Listbox.__init__(self, master, cnf, **kw)
		self.taskList = [];
		ConvertListMenu(self)
	def registTask(self, videoId):
		self.taskList.append(Task(videoId))
		self.update()
	def unregistTask(self, task):
		if task.running():
			raise Exception("[BUG] Task is still running!!");
		self.taskList.remove(task)
		self.update()
	def unregistTaskFromUser(self, index):
		task = self.taskList[index]
		if task.running():
			tkinter.messagebox.showerror('エラー', 'タスクは実行中です。')
			return
		self.unregistTask(task);
		
	def update(self):
		sel = None
		self.delete(0, tkinter.END)
		if len(self.curselection()) > 0:
			sel = self.taskList[int(self.curselection()[0])];
		for task in self.taskList:
			self.insert(tkinter.END, str(task))
			if task.running():
				self.itemconfigure(tkinter.END, foreground='white', background='red')
		if sel:
			self.select_set(self.taskList.index(sel))
		tkinter.Listbox.update(self);
