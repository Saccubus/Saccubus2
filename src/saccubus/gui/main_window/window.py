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
import re
from saccubus.gui.edit_menu import EditMenu;
from saccubus.gui.main_window.version_info import VersionInfoWindow;
from saccubus.gui.main_window.convert_list import ConvertList;

class MainWindow(object):
	'''
	メインウィンドウです。
	'''
	def __init__(self):
		'''
		Constructor
		'''
		master = tkinter.Tk();
		master.title("Saccubus");
		master.configure(menu=self.initMenu(master))
		
		mainFrame = tkinter.Frame(master);
		videoAddPanel = self.initVideoAddPanel(master)
		statusbar = self.initStatusBar(master);

		convertList = ConvertList(mainFrame);
		convertList.pack(fill=tkinter.BOTH, expand=tkinter.YES)

		#配置
		master.columnconfigure(0, weight=1)
		master.rowconfigure(1, weight=1)
		videoAddPanel.grid(column=0, row=0, sticky=tkinter.W+tkinter.E);
		mainFrame.grid(column=0, row=1, sticky=tkinter.W + tkinter.N+tkinter.E + tkinter.S);
		statusbar.grid(column=0, row=2, sticky=tkinter.W);

		
		#self.convertList = convertList;
		self.statusbar = statusbar;
		self.master = master;
		self.setStatus("Initialized.")
	
	def setStatus(self, msg):
		self.statusbar['text']=msg;
	
	def initVideoAddPanel(self, master):
		panel = tkinter.Frame(master)
		panel.columnconfigure(1, weight=1)
		tkinter.Label(panel, text="動画を変換：").grid(column=0, row=0)
		videoIdText=tkinter.Text(panel, height=3)
		videoIdText.grid(column=1, row=0, sticky=tkinter.W + tkinter.E)
		EditMenu(videoIdText)
		tkinter.Button(panel, text="変換", command=lambda: self.onConvertButtonClicked(videoIdText.get(1.0, tkinter.END))).grid(column=2, row=0)
		return panel;
	
	def initStatusBar(self, master):
		statusbar = tkinter.Label(master);
		statusbar['text']="status"
		return statusbar;
	
	def initMenu(self, master):
		menuRoot = tkinter.Menu(master);
		
		menuFile = tkinter.Menu(menuRoot);
		menuRoot.add_cascade(label="ファイル", menu=menuFile);
		menuFile.add_command(label="終了", command=exit)
		
		menuConfig = tkinter.Menu(menuRoot)
		menuRoot.add_cascade(label="設定", menu=menuConfig);
		menuConfig.add_command(label="フロントエンド設定", command=self.onFrontendConfigMenuClicked)
		menuConfig.add_command(label="バックエンド設定", command=None)
		
		menuHelp = tkinter.Menu(menuRoot)
		menuRoot.add_cascade(label="ヘルプ", menu=menuHelp)
		menuHelp.add_command(label="バージョン情報", command=self.onVersionInfoMenuClicked)
		
		return menuRoot;
	def onFrontendConfigMenuClicked(self):
		exit()
	def onVersionInfoMenuClicked(self):
		self.master.wait_window(VersionInfoWindow(self.master));
	def onConvertButtonClicked(self, videoIds):
		print(re.split("[\n\r]*", videoIds.strip()))
	def mainLoop(self):
		self.master.mainloop();


if __name__ == "__main__":
	MainWindow().mainLoop()
