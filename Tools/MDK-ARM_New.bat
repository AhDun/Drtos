@echo off
echo 正在创建模板....
md MDK-ARM_New
cd MDK-ARM_New
md Doc MDK-ARM Readme Src Tools 
cd Src
md App Drive Func  OS  User
cd ..
cd MDK-ARM
md Listings Objects

::echo  listing		-keil5信息(.M51 .lst等) > Readme.md
::echo  Objects		-目标文件(.Hex .obj等) >> Readme.md
::echo  DebugConfig                  -调试器信息(.dbgconf) >> Readme.md
::echo  Uvproj                            -keil5工程文件(.uvproj . uvport等) >> Readme.md
::echo  User  		-用户层 	-主要用来放置Main.c文件 >> Readme.md
::echo  App   		-应用层 	-用户自己开发的通过系统来运行的程序 >> Readme.md
::echo  OS    		-操作系统层 -为操作系统程序  >> Readme.md
::echo  Func  		-功能层 	-通过软件或者硬件（再或者是软硬结合）实现一些功能的程序 >> Readme.md
::echo  Drive 		-驱动层 	-直接驱动硬件(寄存器、IO口等)的程序>> Readme.md

echo 创建完成!
pause 