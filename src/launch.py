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

'''
他のプログラムを発見したりする際にのベースとなるディレクトリをSACCUBUS_PATHに設定すること。
'''
SACCUBUS_PATH='SACCUBUS_PATH'
SACCUBUS_INCLUDE_PATH=[
	'saccubus'
]

import os;
import sys;

def appendPath():
	saccubus_path = os.getenv(SACCUBUS_PATH);
	for path in SACCUBUS_INCLUDE_PATH:
		sys.path.insert(0, os.path.join(saccubus_path, path))

if __name__ == '__main__':
	print("launched")
	if os.getenv(SACCUBUS_PATH) == None:
		os.putenv(SACCUBUS_PATH, os.path.abspath(__file__));
	appendPath();
	
