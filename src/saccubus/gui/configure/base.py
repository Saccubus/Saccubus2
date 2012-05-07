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
import tkinter;
import tkinter.ttk
import tkinter.filedialog;
import pickle;
import os;

class ConfigurePanel(tkinter.ttk.Notebook):
	'''
	classdocs
	'''
	def __init__(self, master):
		'''
		Constructor
		'''
		tkinter.ttk.Notebook.__init__(self, master)
	def crestore(self, conf):
		for key in self.children:
			self.children[key].crestore(conf)
	def cdump(self, conf):
		for key in self.children:
			self.children[key].cdump(conf)
		return conf;
	def carg(self, lst):
		for key in self.children:
			self.children[key].carg(lst)
		return lst;
	def load(self, filename):
		conf={}
		if os.path.exists(filename):
			with open(filename, "rb") as f:
				conf = pickle.load(f)
		self.crestore(conf)
	def save(self, filename):
		with open(filename, "wb") as f:
			conf={}
			self.cdump(conf)
			pickle.dump(conf, f, pickle.HIGHEST_PROTOCOL)
			return conf;

class ConfigureSectionPanel(tkinter.Frame):
	'''
	classdocs
	'''
	def __init__(self, master, sectionName):
		'''
		'''
		tkinter.Frame.__init__(self, master)
		master.add(self, text=sectionName)
		DummyConfigurePanel(self).pack(side=tkinter.BOTTOM, fill=tkinter.BOTH, expand=tkinter.YES)
	def crestore(self, conf):
		for key in self.children:
			self.children[key].crestore(conf)
	def cdump(self, conf):
		for key in self.children:
			self.children[key].cdump(conf)
		return conf;
	def carg(self, lst):
		for key in self.children:
			self.children[key].carg(lst)
		return lst;

class BaseConfigurePanel(tkinter.Frame):
	def __init__(self, master, cnf={}, **kw):
		tkinter.Frame.__init__(self, master, cnf, **kw)
	
	def deploy(self):
		self.pack(fill=tkinter.X, expand=tkinter.NO, side=tkinter.TOP)
	def crestore(self, conf):
		raise Exception("Please implement this method.");
	def cdump(self, conf):
		raise Exception("Please implement this method.");
	def carg(self, lst):
		raise Exception("Please implement this method.");

class DummyConfigurePanel(BaseConfigurePanel):
	def __init__(self, master, cnf={}, **kw):
		BaseConfigurePanel.__init__(self, master, cnf, **kw)
	def crestore(self, conf):
		pass
	def cdump(self, conf):
		pass
	def carg(self, lst):
		pass

class StringConfigurePanel(BaseConfigurePanel):
	def __init__(self, master, name, desc, optname, default=None, **kw):
		BaseConfigurePanel.__init__(self, master)
		self.optname=optname
		self.val = tkinter.StringVar(self, default)
		self.columnconfigure(0, weight=1)
		tkinter.Label(self, text=name, font=tkinter.font.BOLD).grid(column=0, row=0, sticky=tkinter.W);
		tkinter.Label(self, text=desc).grid(column=0, row=1, sticky=tkinter.W);
		entry=tkinter.Entry(self, textvariable=self.val, **kw)
		entry.grid(column=0, row=2, sticky=tkinter.W+tkinter.E);
		EditMenu(entry)
	def crestore(self, conf):
		if self.optname in conf:
			self.val.set(conf[self.optname])
	def cdump(self, conf):
		conf[self.optname]=self.val.get()
	def carg(self, lst):
		lst.append(self.optname)
		lst.append(self.val.get());
		return lst;

class IntegerConfigurePanel(BaseConfigurePanel):
	def __init__(self, master, name, desc, optname, default=None, **kw):
		BaseConfigurePanel.__init__(self, master)
		self.optname=optname
		self.val = tkinter.IntVar(self, default)
		self.columnconfigure(0, weight=1)
		tkinter.Label(self, text=name, font=tkinter.font.BOLD).grid(column=0, row=0, sticky=tkinter.W);
		tkinter.Label(self, text=desc).grid(column=0, row=1, sticky=tkinter.W);
		entry=tkinter.Entry(self, textvariable=self.val, **kw)
		entry.grid(column=0, row=2, sticky=tkinter.W+tkinter.E);
		EditMenu(entry)
	def crestore(self, conf):
		if self.optname in conf:
			self.val.set(int(conf[self.optname]))
	def cdump(self, conf):
		conf[self.optname]=str(self.val.get())
	def carg(self, lst):
		lst.append(self.optname)
		lst.append(self.val.get());
		return lst;

class FileConfigurePanel(BaseConfigurePanel):
	OpenFile, SaveFile, Directory = range(3)
	def __init__(self, master, name, desc, _type, optname, default=None, **kw):
		self.type=_type
		self.optname=optname
		BaseConfigurePanel.__init__(self, master)
		self.val = tkinter.StringVar(self, default)
		self.columnconfigure(0, weight=1)
		tkinter.Label(self, text=name, font=tkinter.font.BOLD).grid(column=0, row=0, columnspan=2, sticky=tkinter.W);
		tkinter.Label(self, text=desc).grid(column=0, row=1, columnspan=2, sticky=tkinter.W);
		entry=tkinter.Entry(self, textvariable=self.val, state='readonly', **kw)
		entry.grid(column=0, row=2, sticky=tkinter.W+tkinter.E);
		tkinter.Button(self, text="参照", command=self.onClicked).grid(column=1, row=2, sticky=tkinter.W+tkinter.E)
		EditMenu(entry)
	def crestore(self, conf):
		if self.optname in conf:
			self.val.set(conf[self.optname])
	def cdump(self, conf):
		conf[self.optname]=self.val.get()
	def carg(self, lst):
		lst.append(self.optname)
		lst.append(self.val.get());
		return lst;
	def onClicked(self):
		val=None
		if self.type == FileConfigurePanel.OpenFile:
			val = tkinter.filedialog.askopenfilename();
		elif self.type == FileConfigurePanel.SaveFile:
			val = tkinter.filedialog.asksaveasfilename();
		elif self.type == FileConfigurePanel.Directory:
			val = tkinter.filedialog.askdirectory()
		else:
			pass
		if val:
			self.val.set(val)

class SelectionConfigurePanel(BaseConfigurePanel):
	def __init__(self, master, name, desc, optkey, lists, default=None, **kw):
		BaseConfigurePanel.__init__(self, master)
		self.lists=lists;
		self.optkey=optkey
		self.val=tkinter.StringVar(self)
		self.columnconfigure(0, weight=1)
		tkinter.Label(self, text=name, font=tkinter.font.BOLD).grid(column=0, row=0, sticky=tkinter.W);
		tkinter.Label(self, text=desc).grid(column=0, row=1, sticky=tkinter.W);
		box=tkinter.ttk.Combobox(self, textvariable=self.val, state='readonly', **kw)
		box.grid(column=0, row=2, sticky=tkinter.W+tkinter.E);
		values=[]
		idx=0;
		for i, item in enumerate(lists):
			values.append(item[0])
			if item[0] == default:
				idx=i;
			i+=1
		box['values']=values;
		box.current(idx)
	def crestore(self, conf):
		if self.optkey in conf:
			self.val.set(conf[self.optkey])
	def cdump(self, conf):
		conf[self.optkey]=self.val.get()
	def carg(self, lst):
		for item in self.lists:
			if(item[0] == self.val.get()):
				lst.extend(item[1:])
				return lst;
		raise Exception("Unknwon opt: {0}".format(self.val.get()));
