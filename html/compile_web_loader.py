#!/usr/bin/python

''' Open Source file '''
f =  open("web_loader.html", "r")

''' read file contents '''
buf = f.read()

''' Close file '''
f.close()

''' Open destination file '''
f = open("../fpga/sw_system/src/web_loader/web_loader_data.h", "w")

''' Prepare header '''
f.write("#ifndef _WEB_LOADER_DATA\n")
f.write("#define _WEB_LOADER_DATA\n")
f.write("\nconst char web_loader_data[] = {\n\t")

''' Fill array '''
k = 0
for c in buf:
	f.write("{0:d}, ".format(ord(c)))
	k = k + 1

	# Every 10 columns, next line
	if k == 10:
		# Write next line
		f.write("\n\t")

		# Reset counter
		k = 0

''' Close array and header'''
f.write("0\n\t};\n\n");
f.write("#endif /* _WEB_LOADER_DATA */\n")

''' Close destination file '''
f.close()


