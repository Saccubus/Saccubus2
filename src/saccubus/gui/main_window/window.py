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
from saccubus.gui.main_window.version_info import VersionInfoWindow;

class MainWindow(object):
	'''
	メインウィンドウです。
	'''
	def __init__(self):
		'''
		Constructor
		'''
		self.master = tkinter.Tk();
		self.master.title("Saccubus");
		self.initMenu();
		self.mainFrame = tkinter.Frame(self.master, width=640, height=480);
		self.statusbar = tkinter.Label(self.master);
		self.statusbar['text']="status"
		self.mainFrame.grid(column=1, row=1, sticky=tkinter.W + tkinter.S);
		self.statusbar.grid(column=1, row=2, sticky=tkinter.W);
	def initMenu(self):
		self.menuRoot = tkinter.Menu(self.master);
		self.master.configure(menu=self.menuRoot);
		
		self.menuFile = tkinter.Menu(self.menuRoot);
		self.menuRoot.add_cascade(label="ファイル", menu=self.menuFile);
		self.menuFile.add_command(label="終了", command=exit)
		
		self.menuConfig = tkinter.Menu(self.menuRoot)
		self.menuRoot.add_cascade(label="設定", menu=self.menuConfig);
		self.menuConfig.add_command(label="フロントエンド設定", command=self.onFrontendConfigMenuClicked)
		self.menuConfig.add_command(label="バックエンド設定", command=None)
		
		self.menuHelp = tkinter.Menu(self.menuRoot)
		self.menuRoot.add_cascade(label="ヘルプ", menu=self.menuHelp)
		self.menuHelp.add_command(label="バージョン情報", command=self.onVersionInfoMenuClicked)
	
	def onFrontendConfigMenuClicked(self):
		exit()
	
	def onVersionInfoMenuClicked(self):
		self.master.wait_window(VersionInfoWindow(self.master).getWindow());
		
	def mainLoop(self):
		self.master.mainloop();


if __name__ == "__main__":
	MainWindow().mainLoop()
