#! python3
# -*- coding: utf-8 -*-

def test_succeed_dict(*args):
	dic = dict(args);
	result = int(dic['first'])+int(dic['second']);
	return {'result': result}
	
def test_not_equal(*args):
	dic = dict(args);
	return int(dic['two_plus_two']) == int(dic['five']);

def test_run_fail(**kwarg):
	print(UNKNWON)

