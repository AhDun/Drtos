@echo off
echo ���ڴ���ģ��....
md MDK-ARM_New
cd MDK-ARM_New
md Doc MDK-ARM Readme Src Tools 
cd Src
md App Drive Func  OS  User
cd ..
cd MDK-ARM
md Listings Objects

::echo  listing		-keil5��Ϣ(.M51 .lst��) > Readme.md
::echo  Objects		-Ŀ���ļ�(.Hex .obj��) >> Readme.md
::echo  DebugConfig                  -��������Ϣ(.dbgconf) >> Readme.md
::echo  Uvproj                            -keil5�����ļ�(.uvproj . uvport��) >> Readme.md
::echo  User  		-�û��� 	-��Ҫ��������Main.c�ļ� >> Readme.md
::echo  App   		-Ӧ�ò� 	-�û��Լ�������ͨ��ϵͳ�����еĳ��� >> Readme.md
::echo  OS    		-����ϵͳ�� -Ϊ����ϵͳ����  >> Readme.md
::echo  Func  		-���ܲ� 	-ͨ���������Ӳ�����ٻ�������Ӳ��ϣ�ʵ��һЩ���ܵĳ��� >> Readme.md
::echo  Drive 		-������ 	-ֱ������Ӳ��(�Ĵ�����IO�ڵ�)�ĳ���>> Readme.md

echo �������!
pause 