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

class EditMenu(tkinter.Menu):
	'''
	classdocs
	'''
	def __init__(self, master):
		'''
		Constructor
		'''
		tkinter.Menu.__init__(self, master, tearoff=False);
		self.add_cascade(label="切り取り (Ctrl+X)", command=self.cut)
		self.add_cascade(label="コピー(Ctrl+C)", command=self.copy)
		self.add_cascade(label="貼り付け (Ctrl+V)", command=self.paste)
		master.bind('<Button-3>', lambda event: self.post(event.x_root,event.y_root))
	
	def paste(self):
		text = self.master.selection_get(selection='CLIPBOARD')
		if text:
			self.master.insert(tkinter.INSERT, text)
			self.master.tag_remove(tkinter.SEL, '1.0', tkinter.END) 
			self.master.see(tkinter.INSERT)
	
	def copy(self):
		if self.master.tag_ranges(tkinter.SEL):
			text = self.master.get(tkinter.SEL_FIRST, tkinter.SEL_LAST)
			self.master.clipboard_clear()
			self.master.clipboard_append(text)
	
	def cut(self):
		if self.master.tag_ranges(tkinter.SEL):
			text = self.master.get(tkinter.SEL_FIRST, tkinter.SEL_LAST)
			self.master.clipboard_clear()
			self.master.clipboard_append(text)
			self.master.delete(tkinter.SEL_FIRST, tkinter.SEL_LAST)
