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
import tkinter.font;
import subprocess;

class Task(object):
	def __init__(self):
		pass
	def execute(self):
		pass

class ConvertListMenu(tkinter.Menu):
	def __init__(self, master):
		tkinter.Menu.__init__(self, master)
		self.add_cascade(label="削除", command=None)
		master.bind('<Button-3>', self.onClick)
	
	def onClick(self, event):
		if len(self.master.curselection()) > 0:
			self.post(self, event.x_root,event.y_root)

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
		print(videoId);
	def update(self):
		sel = int(self.curselection()[0])
		self.select_set(sel)
		tkinter.Listbox.update(self);
