# ----------------------init
import os
from os import path
import glob
import sys
import shutil
#from subprocess import call

# -----------------------------
# python3 build_win32_migw64.py
# -----------------------------
# -----------------------------functions--------------------------------


def copy_dir(src, dst, folder, just_contents):
    dirs = [folder]
    i = 0
    line_counter = 0
    while True:
        if(i == len(dirs)):
            break
        # print("Dir:"+dirs[i],i,len(dirs),src,dst)
        item = dirs[i]
        #del dirs[i]
        with os.scandir(src+"/"+item) as it:
            for entry in it:
                if entry.is_file():
                    new_dst = dst+"/"+item+"/"+entry.name
                    if item == folder:
                        new_dst = dst+"/"+entry.name
                    # print("Cfile:",src+"/"+item+"/"+entry.name,new_dst);
                    if os.path.exists(new_dst):
                        os.remove(new_dst)
                    ret = shutil.copyfile(src+"/"+item+"/"+entry.name, new_dst)
                    # print("\nCOpy",ret)
                    #if len(ret)<2 : print("Not copy :(");
                elif entry.is_dir():
                    # print("Cdir:",dst+"/"+item+"/"+entry.name);
                    if not os.path.exists(dst+"/"+item+"/"+entry.name):
                        os.makedirs(dst+"/"+item+"/"+entry.name)
                    dirs.append(item+"/"+entry.name)
        i += 1


# -----------------------------functions--------------------------------

os.system("clear")
# os.system("echo -e \"Default \e[34mBlue\"")
os.system("tput setaf 5") #set foreground pink
# ----------------------define vars
# enable warnings :  -Wall -Wextra
cflags = "-I ../include -std=c99 -fmax-errors=2 -c " #-m32:for 32bits
build_folder = "../linux32-release"
obj_folder = "../tmp"
src_folder = "../src"
compiler = "gcc "
is_error = 0
logfile = "build_linux32_gcc_list.txt"
compfiles = []
writefiles = []
mahdi_exec = os.path.join(build_folder,"bin","mahdi")
# ----------------------open build_linux32_gcc_list.txt
if os.path.exists(logfile):
    f = open(logfile, "r")
    compfiles = f.readlines()
    f.close()
# for j in compfiles:
#	print(compfiles)
# ----------------------
print("\t~~~~~MAHDI Build Tool (BY Python3) V 4.5~~~~~")
print("=== Start Building linux32 release of MAHDI Interpreter using GCC (C99) ....")
# ----------------------init dirs
# -----create docs dir
if not os.path.exists(build_folder+"/docs"):
    os.makedirs(build_folder+"/docs")
# copy_dir("../", build_folder, "docs", False)
# -----create bin dir
if not os.path.exists(build_folder+"/bin"):
    os.makedirs(build_folder+"/bin")
# -----create modules dir
if not os.path.exists(build_folder+"/mods"):
    os.makedirs(build_folder+"/mods")
# -----create packages dir
if not os.path.exists(build_folder+"/pkgs"):
    os.makedirs(build_folder+"/pkgs")
# -----create samples dir
if not os.path.exists(build_folder+"/samples"):
    os.makedirs(build_folder+"/samples")
# -----delete all obj/.*o
# if os.path.exists(obj_folder):
 #   objs=os.listdir(obj_folder);
  #  for ob in objs:
   #     os.remove("obj/"+ob);
# -----create obj file
if not os.path.exists(obj_folder):
    os.makedirs(obj_folder)

# -----delete mahdi executable
if os.path.exists(mahdi_exec):
    os.remove(mahdi_exec)

# ----------------------compile mahdi sources
print("=== Start compiling source files [mahdi]...")
sources = [
    "main.c",
    "tests.c",
    # [scr_folder+"/builder.c",scr_folder+"/builder.c -o "+obj_folder+"/builder.o"],
    "mahdi_help.c",
    # [scr_folder+"/mahdi_module.c",scr_folder+"/mahdi_module.c -o "+obj_folder+"/mahdi_module.o"],
    "data_defined.c",
    "exceptions.c",
    # [scr_folder+"/mahdi_debugger.c",scr_folder+"/mahdi_debugger.c -o "+obj_folder+"/mahdi_debugger.o"],
    "mahdi_builtin.c",
    "tools/common_funcs.c",
    "tools/console.c",
    "tools/strings.c",
    "tools/chars.c",
    "tools/lists.c",
    # [scr_folder+"/tools/encoder.c", scr_folder +  "/tools/encoder.c -o "+obj_folder+"/encoder.o"],
    "tools/utf8.c",
    "tools/syscalls.c",
    # [scr_folder+"/core/runkit.c",scr_folder+"/core/runkit.c -o "+obj_folder+"/runkit.o"],
    "core/parser.c",
    "core/importer.c",
    # [scr_folder+"/core/inheritance.c",scr_folder+"/core/inheritance.c -o "+obj_folder+"/inheritance.o"],    [scr_folder+"/core/starter.c",scr_folder+"/core/starter.c -o "+obj_folder+"/starter.o"],
    # [scr_folder+"/core/runmgr.c",scr_folder+"/core/runmgr.c -o "+obj_folder+"/runmgr.o"],
    "core/memory.c",
    # [scr_folder+"/built_in/mpl_builtin.c",scr_folder+"/built_in/mpl_builtin.c -o "+obj_folder+"/mpl_builtin.o"],
    # [scr_folder+"/built_in/os_builtin.c",scr_folder+"/built_in/os_builtin.c -o "+obj_folder+"/os_builtin.o"],
    # [scr_folder+"/built_in/data_builtin.c",scr_folder+"/built_in/data_builtin.c -o "+obj_folder+"/data_builtin.o"],
    # [scr_folder+"/built_in/fs_builtin.c",scr_folder+"/built_in/fs_builtin.c -o "+obj_folder+"/fs_builtin.o"],

]
for i in range(0, len(sources), 1):
    # init vars
    src_path = os.path.join(src_folder,sources[i])
    obj_command = src_path + " -o " + os.path.join(obj_folder,os.path.basename(src_path).split('.')[0] + ".o")
    mtime = os.path.getmtime(src_path)
    if len(compfiles)==len(sources) and float(compfiles[i]) == mtime:
        print("=> Before Compiled: "+src_path)
    else:
        # print(mtime,compfiles[i]);
        is_error = os.system(compiler + cflags + obj_command)
        os.system("tput setaf 5") #set foreground pink
        print("=> Compiled: "+src_path)
        # print('compile:',is_error)
        if is_error != 0:
            os.system("tput setaf 1") #set foreground red
            print("*** Failed Compiling! ***")
            exit(1)

    writefiles.append(mtime)
# ----------------------save modified date of source files
fi = open(logfile, "w+")
for kl in writefiles:
    # print(kl)
    fi.write(str(kl)+"\n")
fi.close()

# ----------------------link object files
print("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_")
print("=== Start linking object files [mahdi]...")

# if os.path.exists("win32rc.res"):
#    os.remove("win32rc.res")
# is_error=os.system("windres win32_resources.rc -O coff -o win32rc.res")
# if is_error==1:os.system("color C0"); exit(1);
obj_files = glob.glob(obj_folder+"/*.o")
all_files = ' '.join(obj_files)
#print("gcc .\win32rc.res "+all_files+" -o "+build_folder+"/mpl.exe")
# is_error=os.system("gcc win32rc.res "+all_files+" -o "+build_folder+"/mpl.exe")
is_error = os.system("gcc -fPIC -ldl "+all_files+" -o "+mahdi_exec)
# print('link:',is_error)
# ----------------------finish
if is_error != 0:
    os.system("tput setaf 1") #set foreground red
    print("*** Failed Linking! ***")
    # ----------------------pause
    # os.system("pause");
else:
    os.system("tput setaf 2") #set foreground green
    print("=== Finish Building! All Done in "+build_folder+" folder")
    # ----------------------build modules, if user wants
    if len(sys.argv)>1 and sys.argv[1]=='build_mods':
        os.system("python3 modules_build_linux32_gcc.py")
    # ----------------------run gdb
    #print("=== Running GDB ...");
    #os.system("gdb "+build_folder+"/bin/mpl.exe main.mpl");
    # ----------------------run mahdi
    print("=== Running mahdi executable ...")
    print("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_")
    os.system("tput sgr0") #reset colors
    # os.system("../linux32-release/bin/mahdi -h")
    os.chdir("../samples/myapp1")
    os.system("../../linux32-release/bin/mahdi myapp1")
    os.chdir("../../devtools")
    #os.system("../win32-release/mpl.exe ../mprog.mpl init my_project");
    #os.system("../win32-release/mpl.exe -h keywords null");
    # os.system("dir");
    # os.system("pause");
