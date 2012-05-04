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
from saccubus.gui.configure.base import ConfigurePanel, ConfigureSectionPanel,\
	IntegerConfigurePanel, FileConfigurePanel, SelectionConfigurePanel

class BackendConfigureWindow(tkinter.Toplevel):
	'''
	バックエンドの設定ダイアログです。
	'''
	def __init__(self, master):
		'''
		コンストラクタ
		'''
		tkinter.Toplevel.__init__(self, master)
		self.geometry("360x480")
		self.protocol("WM_DELETE_WINDOW", lambda: self.destroy())
		self.title("バックエンド設定")
		self.focus_set()
		self.grab_set()
		
		'''
		具体的な設定項目
		'''
		confPanel = ConfigurePanel(self)
		generalSection = ConfigureSectionPanel(confPanel, "一般的な設定")
		SelectionConfigurePanel(generalSection, "ログレベル", "出力ログのログレベルを設定します", 'loglevel', [
							("トレース", "--trace"),
							("詳細", "--verbose"),
							("デバッグ", "--trace"),
							("情報", "--info"),
							("警告", "--warning"),
							("エラー", "--error"),
							],'警告').deploy()
		
		
		'''
		最後に配置
		'''
		confPanel.pack(expand=tkinter.YES, fill=tkinter.BOTH)
		self.initExitPanel()
	
	def initExitPanel(self):
		frame=tkinter.Frame(self)
		tkinter.Button(frame, text="　　OK　　", command=self.onOkButtonClicked).pack(expand=tkinter.YES, fill=tkinter.X, side=tkinter.LEFT)
		tkinter.Button(frame, text="キャンセル", command=lambda *a: self.destroy()).pack(expand=tkinter.YES, fill=tkinter.X, side=tkinter.LEFT)
		frame.pack(expand=tkinter.NO, fill=tkinter.X)
	
	def onOkButtonClicked(self):
		pass