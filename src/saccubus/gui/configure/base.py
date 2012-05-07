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
import os;

BACKEND_SEP='&'

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
	def toArgument(self):
		lstDic = {}
		for key in self.children:
			self.children[key].toArgument(lstDic);
		argList = [];
		print (lstDic)
		argList.extend( ('-f', 'saccubus') )
		argList.extend( lstDic['input-opt'] )
		argList.append("-sacc")
		argList.append( BACKEND_SEP.join(lstDic['sacc']) )
		argList.extend(lstDic['input'])
		return argList;
			
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
		conf[self.typeName][self.uniq] = self.cfgDump();
	def deserialize(self, conf):
		if not self.typeName in conf:
			conf[self.typeName] = dict()
		if self.typeName in conf and self.uniq in conf[self.typeName]:
			self.cfgLoad(conf[self.typeName][self.uniq]);
	def toArgument(self, lstDic):
		if not self.typeName in lstDic:
			lstDic[self.typeName] = []
		lstDic[self.typeName].extend(self.cfg2Arg())

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
		return (self.argname, str(self.val.get()))

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

