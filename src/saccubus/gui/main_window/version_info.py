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

class VersionInfoWindow(object):
	'''
	バージョン情報などを表示します。
	'''


	def __init__(self, master):
		self.master = tkinter.Toplevel(master, width=240, height=320)
		self.master.title("バージョン情報")
		self.master.protocol("WM_DELETE_WINDOW", lambda: self.master.destroy())
		self.titleLabel = tkinter.Label(self.master, text="さきゅばす", font=tkinter.font.Font(size=36,weight="bold"));
		self.versionLabel = tkinter.Label(self.master, text="version: 2.0");
		self.authorLabel = tkinter.Label(self.master, text="""Developed by
PSI 2007〜
orz 2011〜""");
		self.titleLabel.grid(column=0, row=0, sticky=tkinter.W+tkinter.E);
		self.versionLabel.grid(column=0, row=1, sticky=tkinter.W+tkinter.E);
		self.authorLabel.grid(column=0, row=2, sticky=tkinter.W+tkinter.E);
	
	def getWindow(self):
		return self.master;
	