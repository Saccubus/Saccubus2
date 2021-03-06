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

import tkinter.messagebox;
import subprocess;
import threading;
import saccubus.gui.configure.backend;
from saccubus.resource.resolve import meta_info
from saccubus.resource import rule
import os
import re
import tempfile

class TaskRunner(threading.Thread):
	def __init__(self, task):
		threading.Thread.__init__(self)
		self.task = task;
		self.setDaemon(True)
	def run(self):
		try:
			print("executing");
			arg = list(self.task.arg)
			val = {}
			val['ffmpeg-file'] = self.task.conf['ffmpeg']['ffmpeg-path'];
			val['saccubus-opts'] = subprocess.list2cmdline(arg)
			#FIXME: 動画情報だけ先に取得してしまう。見苦し。
			try:
				#FIXME: このとき、リソースフォルダがないとネットエラーなのにファイルエラーという悲惨なエラーになる、避けるべき
				_, metainfo = meta_info.downloadMetaInfo(self.task.videoId, self.task.conf['sacc']['resolve-resource-path']);
			except Exception as e:
				raise Exception("ネットへの接続に失敗しました。", e);
			val['out-file-base'] = rule.formatConvertedFilenameBase(self.task.videoId, metainfo['title'])
			val['resource-path'] = self.task.conf['sacc']['resolve-resource-path'];

			#レシピファイルに本当のコマンドを聞く
			try:
				cmdline = self.createCmdlineFromRecipe(val)
			except Exception as e:
				raise Exception("レシピファイルが不正です。", e);
			if os.name=='posix':
				self.launchPosix(cmdline);
			elif os.name=='nt':
				self.launchWin(cmdline)
			else:
				raise Exception("サポートしていないプラットフォーム：{}".format(os.name));
		except BaseException as e:
			self.task.onExecutingError(e)
		finally:
			self.task.onExecuted(self)
	def launchWin(self, ffarg):
		# TODO: shlex.quoteに相当するものがWindows版Pythonにないので再発明
		# http://up-cat.net/%25A5%25B3%25A5%25DE%25A5%25F3%25A5%25C9%25A5%25D7%25A5%25ED%25A5%25F3%25A5%25D7%25A5%25C8%25A4%25CE%25A5%25A8%25A5%25B9%25A5%25B1%25A1%25BC%25A5%25D7%25BB%25C5%25CD%25CD.html
		def quoteWin(arg):
			arg = "\\\\".join(arg.split("\\"))
			arg = "\\\"".join(arg.split("\""))
			return arg
		logfile = os.path.join(self.task.conf['sacc']['resolve-resource-path'], rule.formatLogFilename(self.task.videoId))
		logfile=quoteWin(logfile)
		cmdline = "{arg} 2>&1 | tee.exe -a {log}".format(arg=ffarg, log=logfile)
		tmp = tempfile.NamedTemporaryFile('w+b', suffix='.bat', delete=False)
		tmp.write(bytes("@echo executing... > {0}\r\n".format(logfile), 'CP932'))
		tmp.write(bytes("@echo {0} >> {1}\r\n".format(cmdline, logfile), 'CP932'))
		tmp.write(bytes("@echo result: >> {0}\r\n".format(logfile), 'CP932'))
		tmp.write(bytes(cmdline, 'CP932'));
		tmp.close()
		cmdline = "start /WAIT cmd.exe /C {0}".format(tmp.name)
		print("[{0}] executing => {1}".format(self.task.videoId, ffarg))
		p = subprocess.Popen(cmdline, shell=True)
		p.wait()
		if p.returncode != 0:
			raise Exception("動画{0}の変換に失敗しました。".format(self.task.videoId));
		print("[{0}] executed".format(self.task.videoId));
	def launchPosix(self, ffarg):
		import shlex
		logfile = os.path.join(self.task.conf['sacc']['resolve-resource-path'], rule.formatLogFilename(self.task.videoId))
		logfile=shlex.quote(logfile)
		cmdline = "{arg} 2>&1 | tee -a {log}".format(arg=ffarg, log=logfile)
		tmp = tempfile.NamedTemporaryFile('w+b', suffix='.sh', delete=False)
		
		tmp.write(bytes("echo executing... > {0}\n".format(logfile), 'utf-8'))
		tmp.write(bytes("echo \"{0}\" >> {1}\n".format(cmdline, logfile), 'utf-8'))
		tmp.write(bytes("echo result: >> {0}\n".format(logfile), 'utf-8'))
		tmp.write(bytes(cmdline, 'utf-8'));
		tmp.close()
		print("[{0}] executing => {1}".format(self.task.videoId, ffarg))
		p = subprocess.Popen("gnome-terminal --disable-factory --command \"sh {0}\"".format(tmp.name), shell='/bin/bash')
		p.wait()
		if p.returncode != 0:
			raise Exception("動画{0}の変換に失敗しました。".format(self.task.videoId));
		print("[{0}] executed".format(self.task.videoId));
	def createCmdlineFromRecipe(self, info):
		recipePath = os.path.join(*self.task.conf['ffmpeg']['recipe'])
		src = open(recipePath, encoding='utf-8').read()
		obj = compile(src, recipePath, 'exec')
		g = {}
		l = {}
		exec(obj, g, l)
		l['info'] = info;
		exec('__result__ = cmdline(info)', g, l)
		return l['__result__']

class Task(object):
	def __init__(self, parent, videoId, conf, arg):
		self.videoId = videoId;
		self.parent = parent;
		self.taskRunner = None;
		self.conf = conf
		self.arg = arg
	def execute(self):
		if self.taskRunner:
			raise Exception("task already running.");
		self.taskRunner = TaskRunner(self)
		self.taskRunner.start()
	def taskRepr(self):
		status = '予約中'
		if self.running():
			status = '実行中'
		return "動画ID:[{videoId:>15}] 状態:[{status:>10}]".format(videoId = self.videoId, status=status)
	def running(self):
		return self.taskRunner != None;
	def onExecuted(self, taskRunner):
		if self.taskRunner != taskRunner:
			raise Exception("[BUG] Invalid task");
		self.taskRunner = None;
		self.parent.after_idle(lambda *a: self.parent.unregistTask(self))
	def onExecutingError(self, e):
		self.parent.after_idle(lambda *a: self.parent.onExecutingError(e))

class ConvertListMenu(tkinter.Menu):
	def __init__(self, master):
		tkinter.Menu.__init__(self, master)
		self.add_cascade(label="実行取り消し", command=self.onDeleteTask)
		master.bind('<Button-3>', self.onClick)
	def onClick(self, *event):
		event=event[0]
		if len(self.master.curselection()) > 0:
			self.post(event.x_root,event.y_root)
	def onDeleteTask(self, *event):
		if len(self.master.curselection()) > 0:
			for sel in self.master.curselection():
				self.master.cancelTaskFromUser(int(sel))

class ConvertList(tkinter.Listbox):
	'''
	変換タスクの管理と、その表示を担う。見苦しいけどこれで工数削減。
	'''
	def __init__(self, masterWindow, master, conf, cnf={}, **kw):
		'''
		UIと、タスクリストの初期化を行う
		'''
		cnf['font']=("monospace", )
		cnf['activestyle']='none'
		tkinter.Listbox.__init__(self, master, cnf, **kw)
		self.masterWindow = masterWindow;
		self.taskList = [];
		ConvertListMenu(self)
		self.reloadConfig(conf);
	def registTasksFromUser(self, videoIds):
		for videoId in videoIds:
			conf, arg = saccubus.gui.configure.backend.BackendConfigureWindow(self.masterWindow, videoId).show()
			if arg is None:
				print("task {0} cancelled".format(videoId));
				continue
			self.registTask(videoId, conf, arg);

	def cancelTaskFromUser(self, index):
		task = self.taskList[index]
		if task.running():
			tkinter.messagebox.showerror('エラー', 'タスクは実行中です。')
			self.select_clear(0, tkinter.END)
			return
		self.taskList.remove(task)
		self.update()
	def registTask(self, videoId, conf, arg):
		self.taskList.append(Task(self, videoId, conf, arg))
		self.consumeQueue()
	def unregistTask(self, task):
		if task.running():
			raise Exception("[BUG] Task is still running!!");
		self.taskList.remove(task)
		self.consumeQueue()
	def onExecutingError(self, e):
		tkinter.dialog.messagebox.showerror("変換エラー", "変換エラーが発生しました。\n{0}".format(str(e)))

	def consumeQueue(self):
		runningTasks = len([t for t in self.taskList if t.running()])
		left = self.taskLimit - runningTasks
		if left > 0:
			for _ in range(0, left):
				for task in self.taskList:
					if not task.running():
						task.execute()
						break;
		self.update()
	def update(self):
		sel = None
		self.delete(0, tkinter.END)
		if len(self.curselection()) > 0:
			sel = self.taskList[int(self.curselection()[0])];
		for task in self.taskList:
			self.insert(tkinter.END, task.taskRepr())
			if task.running():
				self.itemconfigure(tkinter.END, foreground='white', background='red')
		if sel:
			self.select_set(self.taskList.index(sel))
		tkinter.Listbox.update(self);

	def reloadConfig(self, conf):
		self.taskLimit = int(conf.get('frontend', {}).get("task-limit", 1))
		self.consumeQueue()
