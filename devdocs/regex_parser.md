
- [attrs* ] : means that get multiple (0..) words as 'attrs' list that split by ' '
- [name] : means that get a word as 'name' string
- [section1?] : means that if not exist, then ignore it and continue!
- special chars : ", [ * ? ]"
--------------------------
- package statement
> package[name]

- class header:
> class[name]([parent?])

- function header:
> [attrs* ]func[name]([params*,])

- block header:
> [name]([params?])

- import statement:
> import[type]:[name*,]:[objects*,]

- config statement
> config[name]=[value]

- instruction statement
> [instruction];




- variable declaration
	* samples
	- x:num,e,u=45
	- y:num 
	- GG=(45*2)+5
	- exp:exception=exception()
	- z1,z2:bool,z3:str=3,true and true,"hello"
	- B:bool=true
	- v:num[]=list1[1:3];
	- lam:lambda=(&g:num)=>{g++;return 'hi';}
> [names*,]=[values*,]

- loop header content
	* samples
	- loop(i=0,u='';i<10,u!="Hello";i++)
	- loop(;i<5)
	- loop(j=0;j:u)
> [section1?];[section2];[section3?]

- call function
	* samples
	- sam1(jj="er",j=7,656)
	- pkg,main()
	- f("g",6,8)[1]
	- encoding,json,encode([4,6])
> [package?].[class?].[function].([params*,])\[[index?]\]









