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
from saccubus.gui.edit_menu import EditMenu
import tkinter.ttk
import tkinter.filedialog;
import pickle;
import os.path;


class ConfigurePanel(tkinter.ttk.Notebook):
	'''
	classdocs
	'''
	def __init__(self, master):
		'''
		Constructor
		'''
		tkinter.ttk.Notebook.__init__(self, master)
	def serialize(self):
		conf = {}
		for key in self.children:
			self.children[key].serialize(conf);
		return conf;
	def deserialize(self, conf):
		for key in self.children:
			self.children[key].deserialize(conf);
	def toArgument(self, videoId):
		raise Exception("Please implement");
			
	def load(self, filename):
		conf={}
		if os.path.exists(filename):
			with open(filename, "rb") as f:
				conf = pickle.load(f)
		self.deserialize(conf);
	def save(self, filename):
		with open(filename, "wb") as f:
			conf = self.serialize()
			pickle.dump(conf, f, pickle.HIGHEST_PROTOCOL)
			return conf;

class ConfigureSectionPanel(tkinter.Frame):
	'''
	classdocs
	'''
	def __init__(self, master, sectionTitle):
		'''
		'''
		tkinter.Frame.__init__(self, master)
		master.add(self, text=sectionTitle)
	def serialize(self, conf):
		for key in self.children:
			self.children[key].serialize(conf);
	def deserialize(self, conf):
		for key in self.children:
			self.children[key].deserialize(conf);
	def toArgument(self, lstDic):
		for key in self.children:
			self.children[key].toArgument(lstDic);

class BaseConfigurePanel(tkinter.Frame):
	def __init__(self, master, title, desc, typeName, uniq):
		tkinter.Frame.__init__(self, master)
		self.typeName = typeName;
		self.uniq = uniq
		tkinter.Label(self, text=title, font=tkinter.font.BOLD).pack(fill=tkinter.X, expand=tkinter.YES);
		tkinter.Label(self, text=desc).pack(fill=tkinter.X, expand=tkinter.YES);
	def deploy(self):
		self.pack(fill=tkinter.X, expand=tkinter.NO, side=tkinter.TOP)

	def serialize(self, conf):
		if not self.typeName in conf:
			conf[self.typeName] = dict()
		try:
			conf[self.typeName][self.uniq] = self.cfgDump();
		except Exception as e:
			print("Error while serializing configure: {0}", e);
	def deserialize(self, conf):
		if not self.typeName in conf:
			conf[self.typeName] = dict()
		if self.typeName in conf and self.uniq in conf[self.typeName]:
			try:
				self.cfgLoad(conf[self.typeName][self.uniq]);
			except Exception as e:
				print("Error while deserializing configure: ", e);
	def toArgument(self, lstDic):
		val = self.cfg2Arg()
		if not val:
			return
		if not self.typeName in lstDic:
			lstDic[self.typeName] = []
		lstDic[self.typeName].extend(val)

	def cfgDump(self):
		raise Exception("Please implement");
	def cfgLoad(self, obj):
		raise Exception("Please implement");
	def cfg2Arg(self):
		raise Exception("Please implement");

class StringConfigurePanel(BaseConfigurePanel):
	def __init__(self, master, title, desc, typeName, uniq, argname, default, **kw):
		BaseConfigurePanel.__init__(self, master, title, desc, typeName, uniq)
		self.argname=argname;
		self.val = tkinter.StringVar(self, default)
		e = tkinter.Entry(self, textvariable=self.val, **kw)
		e.pack(fill=tkinter.X, expand=tkinter.NO)
		EditMenu(e)
	def cfgDump(self):
		return self.val.get()
	def cfgLoad(self, obj):
		self.val.set(obj);
	def cfg2Arg(self):
		val = self.val.get()
		if val:
			return (self.argname, str(self.val.get()))
		else:
			return ()

class IntegerConfigurePanel(BaseConfigurePanel):
	def __init__(self, master, title, desc, typeName, uniq, argname, default, **kw):
		BaseConfigurePanel.__init__(self, master, title, desc, typeName, uniq)
		self.argname=argname;
		self.val = tkinter.IntVar(self, default)
		entry=tkinter.Entry(self, textvariable=self.val, **kw)
		entry.pack(fill=tkinter.X, expand=tkinter.NO)
		EditMenu(entry)
	def cfgDump(self):
		return self.val.get()
	def cfgLoad(self, obj):
		self.val.set(obj);
	def cfg2Arg(self):
		return (self.argname, str(self.val.get()))

class FileConfigurePanel(BaseConfigurePanel):
	OpenFile, SaveFile, Directory = range(3)
	def __init__(self, master, title, desc, typeName, uniq, openType, argname, default, **kw):
		BaseConfigurePanel.__init__(self, master, title, desc, typeName, uniq)
		self.argname=argname;
		self.val = tkinter.StringVar(self, default)
		self.openType = openType;

		frame = tkinter.Frame(self)
		entry=tkinter.Entry(frame, textvariable=self.val, state='readonly', **kw)
		entry.pack(fill=tkinter.X, expand=tkinter.YES, side=tkinter.LEFT)
		tkinter.Button(frame, text="参照", command=self.onClicked).pack(expand=tkinter.NO, side=tkinter.LEFT)
		frame.pack(expand=tkinter.YES, fill=tkinter.X)
		EditMenu(entry)
	def onClicked(self):
		val=None
		if self.openType == FileConfigurePanel.OpenFile:
			val = tkinter.filedialog.askopenfilename();
		elif self.openType == FileConfigurePanel.SaveFile:
			val = tkinter.filedialog.asksaveasfilename();
		elif self.openType == FileConfigurePanel.Directory:
			val = tkinter.filedialog.askdirectory()
		else:
			pass
		if val:
			self.val.set(val)
	def cfgDump(self):
		return self.val.get()
	def cfgLoad(self, obj):
		self.val.set(obj);
	def cfg2Arg(self):
		return (self.argname, str(self.val.get()))

class FileSelectConfigurePanel(BaseConfigurePanel):
	def __init__(self, master, title, desc, typeName, uniq, argname=None, defaultDir=None, **kw):
		BaseConfigurePanel.__init__(self, master, title, desc, typeName, uniq)
		self.argname = argname;

		self.dval = tkinter.StringVar(self, defaultDir)
		dframe = tkinter.Frame(self)
		dentry=tkinter.Entry(dframe, textvariable=self.dval, state='readonly', **kw)
		dentry.pack(fill=tkinter.X, expand=tkinter.YES, side=tkinter.LEFT)
		tkinter.Button(dframe, text="参照", command=self.onDirectorySelect).pack(expand=tkinter.NO, side=tkinter.LEFT)
		EditMenu(dentry)
		dframe.pack(expand=tkinter.YES, fill=tkinter.X)
		
		self.fval = tkinter.StringVar(self)
		fframe = tkinter.Frame(self)
		self.fbox = tkinter.ttk.Combobox(fframe, textvariable=self.fval, state='readonly', **kw)
		self.fbox.pack(fill=tkinter.X, expand=tkinter.YES, side=tkinter.LEFT)
		tkinter.Button(fframe, text="再読み込み", command=lambda *a:self.reloadDirectory()).pack(expand=tkinter.NO, side=tkinter.LEFT)
		fframe.pack(expand=tkinter.YES, fill=tkinter.X)
		self.reloadDirectory()
	def onDirectorySelect(self, *event):
		newDir = tkinter.filedialog.askdirectory();
		if not newDir:
			return
		if (not os.path.exists(newDir)) or (not os.path.isdir(newDir)):
			tkinter.messagebox.showerror('エラー', 'ディレクトリは存在しません')
			return
		self.dval.set(newDir)
		self.reloadDirectory()
	def reloadDirectory(self):
		if os.path.exists(self.dval.get()) and os.path.isdir(self.dval.get()):
			values = []
			for item in os.listdir(self.dval.get()):
				if os.path.isfile(os.path.join(self.dval.get(), item)):
					values.append(item)
			self.fbox['values'] = values
			f = os.path.join(self.dval.get(), self.fval.get())
			if not os.path.exists(f) or not os.path.isfile(f):
				if len(values) > 0:
					self.fbox.current(0)
				else:
					self.fval.set('')
		else:
			self.fbox['values'] = ("フォルダが存在しません。",)
			self.fbox.current(0)
	def cfgDump(self):
		return (self.dval.get(), self.fval.get())
	def cfgLoad(self, obj):
		d,f = obj;
		self.dval.set(d);
		self.fval.set(f);
		self.reloadDirectory()
	def cfg2Arg(self):
		fpath = os.path.join(self.dval.get(), self.fval.get());
		if self.argname and os.path.exists(fpath) and os.path.isfile(fpath):
			return (self.argname,  fpath)
		else:
			return ()

class SelectionConfigurePanel(BaseConfigurePanel):
	def __init__(self, master, title, desc, typeName, uniq, choices, default, **kw):
		BaseConfigurePanel.__init__(self, master, title, desc, typeName, uniq)
		self.val = tkinter.StringVar(self, default)

		box=tkinter.ttk.Combobox(self, textvariable=self.val, state='readonly', **kw)
		box.pack(fill=tkinter.X, expand=tkinter.NO)
		values=[]
		self.choices = {};
		idx=0;
		for i, choice in enumerate(choices):
			values.append(choice[0])
			self.choices[choice[0]] = choice[1:];
			if choice[0] == default:
				idx=i;
			i+=1
		box['values']=values;
		box.current(idx)
	def cfgDump(self):
		return self.val.get()
	def cfgLoad(self, obj):
		if obj in self.choices:
			self.val.set(obj);
	def cfg2Arg(self):
		return self.choices[self.val.get()]

