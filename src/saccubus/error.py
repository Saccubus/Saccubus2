#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/27

@author: psi
'''

class SaccubusError(BaseException):
	'''
	さきゅばす内で使うエラー
	'''


	def __init__(self, fmt, *args):
		'''
		エラーを構築します
		'''
		self.msg = fmt.format(*args)
	def __str__(self):
		return self.msg;
	