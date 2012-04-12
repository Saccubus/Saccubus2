def shouldCommentBeIgnored(*arg):
	com = dict(arg)
	print (repr(com))
	return int(com['thread']) == 1302222473 and float(com['vpos']) == 0 and int(com['date']) == 1310831408;
