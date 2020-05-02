<p align="center" >
<img src="devdocs/assets/logo.png"  alt="Mahdi Programming Language" title="Mahdi Programming Language"> <br>
**MAHDI (BETA-0.1)**
</p>

![Build Status](devdocs/assets/passing.svg)

**Mahdi** is a small, lightweight, fast programming language written in C (c99) without any non-standard libraries that Assemble all the good features of programming languages.

**Mahdi** supports object-oriented programming and functional programming. Thanks to special built-in methods, it can also be used as a prototype-based programming language.

**Mahdi** Influenced by:
 > C,PHP,MPL,PYTHON,JAVA,GO,TYPESCRIPT


| **OS** | **Architecture** | **Build** | **Tested Host**|
|---|:---:|:---:|:---:|
| **macOS**   | x86_64 |PENDING      |-
| **Linux**   | x86_64 |**PROCESSING**  |Debian 10-4.9-amd64
| **Windows** | x86_64 |PENDING      |-




MAHDI Language Features
--------

- [ ] support utf8 strings 
- [ ] support radix numbers  
- [ ] support object oriented
- [ ] has built-in functions  
- [ ] all config of project is in source code
- [ ] type safed with auto detect data type by value
- [ ] inline string formatting
- [ ] support for stack tracing
- [ ] support for short condition (?:)
- [ ] using common loop(for,while,foreach)
- [ ] using modules(as dll,so) and packages(as user defined) in apps
- [ ] for run a program in program directory just type: mahdi myapp
- [ ] run lambda functions as new thread
- [ ] support method overloads (just by count and type of parameters)
- [ ] support for calculating huge numbers(with infinity digits)
- [ ] flexible exception handler with manage it or not!
- [ ] facility for swaping values of two variables
- [ ] support for built-in power operator for all numeric values
- [ ] support for infinity function parameters
- [ ] support for dynamic operators,indexes and ranges for classes
- [ ] using packaging model for source codes
- [ ] written on pure C programming language
- [ ] Support closures, anonymous functions (lambda)
- [ ] support multi dimensions arrays  
- [ ] support dictionary(map) data structure
- [ ] has built-in garbage collector(gc)  
- [ ] expandability by c,c++ modules  
- [ ] support built-in debugger
- [ ] support for built-in packager
- [ ] support call function by its parameter name
- [ ] support multi return values  
- [ ] support for getter and setter attributes of classes
- [ ] support call by reference vars  
- [ ] support short allocations for vars  
- [ ] support built-in encoder  
- [ ] support bit functions  
- [ ] support sqlite3 module  
- [ ] support browse arrays in loop  
- [ ] support switch condition equivalent  
- [ ] support module os syscalls
- [ ] support create executable file from program
- [ ] support cross-platform gui kit
- [ ] support for function recursions

MAHDI 'Hello World' Program
--------

    import mod:stdio
    /**
    * main function that boot app from Here!
    */
    func _bootup_(){
        f="سلام به دنیا \
        hello world!\n"
        stdio.print(f)
    }

MAHDI default structure directory (linux like!)
--------

    |__ bin
    |  |__ mahdi
    |  |__ mrm (mahdi repository manager)
    |
    |__ mods
    |  |__ os.so
    |  |__ math.so
    |  |__ thread.so
    |  |__ exception.so
    |  |__ sqlite3.so
    |  |__ stdio.so
    |  |__ time.so
    |  |__ mgui.so (mahdi cross-platform gui kit)
    |  |__ socket.so
    |
    |__ pkgs
    |  |__ encoding.mahpack (json,xml,base64,csv,...)
    |  |__ crypto.mahpack (aes,md5,sha1,...)
    |  |__ compress.mahpack (gzip,bzip2,zlib,tar,zip,...)
    |  |__ net.mahpack
    |  |__ mlearn.mahpack
    |
    |__ docs
    |
    |__ samples
    |
    |__ tmp
    |
    |__ LICENSE.txt

Programmers & Designers
--------

1. Mohammad Amin Delavar Khalafi [main developer,designer],[Iran],[amindelavar@hotmail.com]

MAHDI VERSIONS
--------

- [ ] MAHDI-BETA (0.0.0 - 0.9.9)
- [ ] MAHDI-RC (1.0.0 - 1.9.9)



MAHDI appreciates for your suggestions and the other :))
--------

> Contact with amindelavar@hotmail.com by "**mAh : devhelp**" title

License
--------

Mahdi is available under the **Creative Commons Attribution Share Alike 4.0**
