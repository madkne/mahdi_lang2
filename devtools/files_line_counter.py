
import sys
import os.path
import os
#----------------------------------------------------lambda for check a file in binary
textchars = bytearray({7,8,9,10,12,13,27} | set(range(0x20, 0x100)) - {0x7f})
is_binary_string = lambda bytes: bool(bytes.translate(None, textchars))
#----------------------------------------------------
print("\t Files Line Counter(V 1.9)")
filename=os.path.dirname(__file__)
if len(sys.argv)>1: filename=sys.argv[1]
path = os.path.abspath(os.path.join(filename))
print ("Searched path is: \""+path+"\"")
#----------------------------------------------------
dirs=[path]
i=0
line_counter=0
while i < len(dirs):
    # print("Dir:"+dirs[i],i,len(dirs))
    item=dirs[i]
    #del dirs[i]
    with os.scandir(item) as it:
        for entry in it:
            if entry.name.startswith('.'): continue
            path = os.path.join(item,entry.name)
            # is directory
            if entry.is_dir(): dirs.append(path)
            # if is file
            elif entry.is_file():
                # check if file is binary
                if is_binary_string(open(os.path.join(path), 'rb').read(1024)): 
                    continue
                co=0;    
                with open(os.path.join(path),"r",encoding="utf8") as f:
                    # print("###:"+item+"/"+entry.name)
                    line = f.readline()
                    while line:
                        is_code = True
                        line = line.strip()
                        if len(line) < 2: is_code = False
                        elif line[0]=='#': is_code = False
                        elif line[0]=='/' and line[1]=='/': is_code = False
                        elif line[0]=='/' and line[1]=='*': is_code = False
                        # increase line counter
                        if is_code: co += 1
                        line = f.readline()
                print("- File: {:<20s} => {} lines".format(entry.name[-20:],co))
                line_counter += co
    i+=1
#----------------------------------------------------
#print(str(dirs))
print("==========\n\t Total Counter:"+str(line_counter)+"\n==========")
        