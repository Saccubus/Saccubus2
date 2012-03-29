#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''
from saccubus.error import SaccubusError;
class LoadError(SaccubusError):
	def __init__(self, fmt, *args):
		SaccubusError.__init__(self, fmt, *args)

