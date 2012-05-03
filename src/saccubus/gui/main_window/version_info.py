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

class VersionInfoWindow(tkinter.Toplevel):
	'''
	バージョン情報などを表示します。
	'''


	def __init__(self, master, cnf={}, **kw):
		tkinter.Toplevel.__init__(self, master, cnf={}, **kw)
		self.title("バージョン情報")
		self.protocol("WM_DELETE_WINDOW", lambda: self.destroy())
		self.panel = tkinter.Frame(self)
		self.initPanel(self.panel)
		self.resizable(False, False)
		self.panel.pack(fill=tkinter.BOTH, expand=tkinter.YES)
	
	def initPanel(self, panel):
		titleLabel = tkinter.Label(panel, text="さきゅばす", font=tkinter.font.Font(size=36,weight="bold"));
		versionLabel = tkinter.Label(panel, text="version: 2.0");
		authorLabel = tkinter.Label(panel, text="""Developed by
PSI 2007〜
orz 2011〜""");
		panel.columnconfigure(0, weight=1)
		titleLabel.grid(column=0, row=0, sticky=tkinter.W+tkinter.E);
		versionLabel.grid(column=0, row=1, sticky=tkinter.W+tkinter.E);
		authorLabel.grid(column=0, row=2, sticky=tkinter.W+tkinter.E);
	