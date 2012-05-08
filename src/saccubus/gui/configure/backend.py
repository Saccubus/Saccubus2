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
from saccubus.gui.configure.base import\
	ConfigurePanel, ConfigureSectionPanel,\
	SelectionConfigurePanel, StringConfigurePanel,\
	FileConfigurePanel, IntegerConfigurePanel, FileSelectConfigurePanel
import saccubus.gui.dialog

class BackendConfigureWindow(saccubus.gui.dialog.Dialog):
	'''
	バックエンドの設定ダイアログです。
	'''
	def __init__(self, master, videoId=None):
		saccubus.gui.dialog.Dialog.__init__(self, master)
		self.saveFlag = tkinter.IntVar(self, 1)
		self.videoId = videoId;
		'''
		コンストラクタ
		'''
		self.geometry("360x480")
		self.protocol("WM_DELETE_WINDOW", lambda: self.destroy())
		if self.videoId:
			self.saveFlag.set(0)
			self.title("変換設定：{videoId}".format(videoId = self.videoId))
		else:
			self.title("バックエンド設定")
		
		'''
		具体的な設定項目
		'''
		confPanel = ConfigurePanel(self)
		generalSection = ConfigureSectionPanel(confPanel, "一般的な設定")
		FileConfigurePanel(generalSection, "アダプタファイル", "FFmpegフィルタの場所を指定します。", "input", "adapterfile", FileConfigurePanel.OpenFile, '-i', "ext/bin/Saccubus.dll").deploy()
		FileSelectConfigurePanel(generalSection, "変換レシピ", "変換に使うFFmpegオプションのレシピを指定します", "ffmpeg", "recipe", None, "./recipe").deploy()

		SelectionConfigurePanel(generalSection, "ログレベル", "出力ログのログレベルを設定します", "sacc", 'log-level',[
						("トレース", "--trace"),
						("詳細", "--verbose"),
						("デバッグ", "--trace"),
						("情報", "--info"),
						("警告", "--warning"),
						("エラー", "--error"),
						],'警告').deploy()
		
		resolveSection = ConfigureSectionPanel(confPanel, "ダウンローダ")
		SelectionConfigurePanel(resolveSection, "ログイン方法", "ニコニコ動画へのログイン方法を指定します。", 'sacc', 'resolve-cookie', [
						('ユーザーID＆パスワード', "--resolve-cookie", "own"),
						('Firefox', "--resolve-cookie", "firefox"),
						('Chrome', "--resolve-cookie", "chrome"),
						('InternetExplorer', "--resolve-cookie", "ie")], None).deploy()
		StringConfigurePanel(resolveSection, "ユーザーID", "上でブラウザを選択した場合は入力しなくて大丈夫です。", "sacc", "resolve-user", "--resolve-user", "udon@example.com").deploy()
		StringConfigurePanel(resolveSection, "パスワード", "上でブラウザを選択した場合は入力しなくて大丈夫です。", "sacc", "resolve-pass", "--resolve-pass", "udonudon", show="*").deploy()

		FileConfigurePanel(resolveSection, "ダウンロード先", "動画のダウンロード先を指定します","sacc", "resolve-resource-path", FileConfigurePanel.Directory, "--resolve-resource-path", "./conv_plugins").deploy()

		videoSection = ConfigureSectionPanel(confPanel, "動画設定")
		IntegerConfigurePanel(videoSection, "横幅", "この縦幅・横幅に短辺を合わせて拡大されます。", "input-opt", "width", "-width", 0).deploy()
		IntegerConfigurePanel(videoSection, "縦幅", "この縦幅・横幅に短辺を合わせて拡大されます。", "input-opt", "height", "-height", 0).deploy()
		IntegerConfigurePanel(videoSection, "最低FPS", "このFPS以上になるように出力されます。\nコメントがかくかくする場合などにお試し下さい。", "input-opt", "minfps", "-minfps", 25).deploy()
		SelectionConfigurePanel(videoSection, "TASモード", "TASのように変換中に１フレームずつ操作できます。\nスペースキーで次のフレームです。", 'sacc', 'controll-mode', [
					('TASモードにしない', ),
					('TASモードにする', "--enable-tas")],None).deploy()

		commentSection = ConfigureSectionPanel(confPanel, "コメント設定")
		IntegerConfigurePanel(commentSection, "コメント取得数", "コメント取得件数を指定します。", "sacc", "resolve-comment-back", "--resolve-comment-back", 500).deploy()
		FileSelectConfigurePanel(commentSection, "NGスクリプトファイル", "変換しないコメントを決定するスクリプトを指定します。","sacc", "ng-script", "--ng-script", "./ng-script").deploy()

		'''
		最後に配置
		'''
		confPanel.load(saccubus.gui.BackendConfigureFilename)
		confPanel.pack(expand=tkinter.YES, fill=tkinter.BOTH)
		self.confPanel = confPanel;
		self.initExitPanel()
		self.moveToCenter();
	
	def initExitPanel(self):
		if not self.videoId:
			vframe = tkinter.Frame(self)
			tkinter.Checkbutton(vframe, variable=self.saveFlag, text='これを以降のデフォルト設定にする').pack(expand=tkinter.NO, side=tkinter.LEFT)
			
			vframe.pack(expand=tkinter.NO, fill=tkinter.X)
		frame=tkinter.Frame(self)
		tkinter.Button(frame, text="　　OK　　", command=self.onOkButtonClicked).pack(expand=tkinter.YES, fill=tkinter.X, side=tkinter.LEFT)
		tkinter.Button(frame, text="キャンセル", command=lambda *a: self.destroy()).pack(expand=tkinter.YES, fill=tkinter.X, side=tkinter.LEFT)
		frame.pack(expand=tkinter.NO, fill=tkinter.X)
	
	def onOkButtonClicked(self):
		if self.saveFlag.get() != 0:
			self.confPanel.save(saccubus.gui.BackendConfigureFilename)
		argument = self.confPanel.toArgument()
		self.destroy()
		return argument;
