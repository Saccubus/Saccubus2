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

import tkinter
from saccubus.gui.configure.panel import ConfigurePanel
class FrontEndConfigureWindow(tkinter.Toplevel):
	'''
	フロントエンドの設定です。変換手順を決定するオプションファイルの指定などを行います。
	'''
	def __init__(self, master):
		'''
		コンストラクタ
		'''
		tkinter.Toplevel.__init__(self, master)
		self.protocol("WM_DELETE_WINDOW", lambda: self.destroy())
		self.title("フロントエンド設定")
		self.focus_set()
		self.grab_set()
		ConfigurePanel(self).pack(expand=tkinter.YES, fill=tkinter.BOTH)
