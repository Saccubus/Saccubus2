#! python3
# -*- coding: utf-8 -*-

def test_succeed_dict(**kwarg):
	return {'result': int(kwarg['first'])+int(kwarg['second'])}
	
def test_not_equal(**kwarg):
	return int(kwarg['two_plus_two']) == int(kwarg['five']);

def test_run_fail(**kwarg):
	print(UNKNWON)

