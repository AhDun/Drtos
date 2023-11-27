import os

filename = "filestruct.txt"



def dirswalk(listx,t):
    dirslist = []
    dirsname = ""
    flag = 0
    filetab = ""
    dirtab = ""
    if len(listx) > 0:
        for x in range(t):
            filetab = filetab + " "
        for x in range(t-2):
            dirtab = dirtab + " "
        for x in listx:
            if x.count("\\") == 1:
                if dirsname != x[:x.find("\\")]:
                    dirsname = x[:x.find("\\")]
                    if flag > 0:
                        dirswalk(dirslist,t+2)
                        dirslist.clear()
                    else:
                        flag = 1
                    f.write(dirtab+"|- "+dirsname+"\n")
                f.write(filetab+"|-- "+x[x.rfind('\\')+1:]+"\n")
            else:
                dirslist.append(x[x.find("\\")+1:])
        dirswalk(dirslist,t+2)
                
print("将当前目录下的所有文件与文件夹结构，输出到当前目录下的：" + filename + "文件中")
filelist = []#所有文件列表
for root,dirs,files in os.walk("./"):#遍历当前文件夹所有文件夹与文件
    for file in files:
        filelist.append(os.path.join(root,file))

dirs = []#文件夹列表
files = []#文件列表
for x in filelist:#
    if x.find('\\') >= 0:#如果这个字符串内有\符号，就说明这是个文件夹
        dirs.append(x[2:])#添加到文件夹列表中
    else:#否则就是文件
        files.append(x[2:])#添加到文件列表中

f = open(filename,"w")#打开文件
f.write(os.path.abspath('')+'\n')#将当前路径写入到文件中
for x in files:
    f.write("|-- "+x+"\n")#将文件名写入到文件中
dirswalk(dirs,2)
f.close()#关闭这个文件

print("完成输出")
