#coding=UTF-8

#
# Copyright (c) 2023 AhDun
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


#
# 
#  @file git_python_tools.py
# 
#  @brief git图形化python脚本工具
# 
#  @note none
# 
# 

default_branch = 'master' #默认分支
touch_gitignore_file  = True #创建仓库时,自动新建.gitignore文件
touch_readme_file  = True #创建仓库时,自动新建readme文件



import os
import datetime
import subprocess 
import re
import sys

logo = '''
      ___                                   ___                                 ___           ___           ___     
     /  /\        ___           ___        /  /\        ___         ___        /__/\         /  /\         /__/\    
    /  /:/_      /  /\         /  /\      /  /::\      /__/|       /  /\       \  \:\       /  /::\        \  \:\   
   /  /:/ /\    /  /:/        /  /:/     /  /:/\:\    |  |:|      /  /:/        \__\:\     /  /:/\:\        \  \:\  
  /  /:/_/::\  /__/::\       /  /:/     /  /:/~/:/    |  |:|     /  /:/     ___ /  /::\   /  /:/  \:\   _____\__\:\ 
 /__/:/__\/\:\ \__\/\:\__   /  /::\    /__/:/ /:/   __|__|:|    /  /::\    /__/\  /:/\:\ /__/:/ \__\:\ /__/::::::::\\
 \  \:\ /~~/:/    \  \:\/\ /__/:/\:\   \  \:\/:/   /__/::::\   /__/:/\:\   \  \:\/:/__\/ \  \:\ /  /:/ \  \:\~~\~~\/
  \  \:\  /:/      \__\::/ \__\/  \:\   \  \::/       ~\~~\:\  \__\/  \:\   \  \::/       \  \:\  /:/   \  \:\  ~~~ 
   \  \:\/:/       /__/:/       \  \:\   \  \:\         \  \:\      \  \:\   \  \:\        \  \:\/:/     \  \:\     
    \  \::/        \__\/         \__\/    \  \:\         \__\/       \__\/    \  \:\        \  \::/       \  \:\    
     \__\/                                 \__\/                               \__\/         \__\/         \__\/     
'''






from tkinter import simpledialog
from tkinter import *
import tkinter.messagebox as messagebox
from tkinter import ttk

shell_exit = ""

root = Tk()
root.title("git_python_tools.py")
root.config(bg='#ffffff')
root.geometry('800x500+300+200')
root.resizable(0, 1)

shell_win_scroll = Scrollbar()

shell_win_scroll.pack(side=RIGHT, fill=Y)
shell_win = Text(root,font=("", 10),width=800,height=500)
shell_win.config(yscrollcommand=shell_win_scroll.set)
shell_win_scroll.config(command=shell_win.yview)


shell_win.tag_config('T1C',foreground="#000000", font=("", 20, "bold"),justify="center")
shell_win.tag_config('T2C',foreground="#000000", font=("", 15, "bold"),justify="center")
shell_win.tag_config('T2CG',foreground="#007000", font=("", 15, "bold"),justify="center")
shell_win.tag_config('T3C',foreground="#000000", font=("", 12, "bold"),justify="center")

shell_win.tag_config('T1',foreground="#000000", font=("", 20, "bold"))
shell_win.tag_config('T2',foreground="#000000", font=("", 15, "bold"))
shell_win.tag_config('T3',foreground="#000000", font=("", 12, "bold"))


shell_win.tag_config('error',foreground="red")
shell_win.tag_config('info',foreground="blue")
shell_win.tag_config('logo',foreground="#009000", font=("", 8, ""),justify="center")
shell_win.tag_config('welcome',foreground="#009000", font=("", 20, ""),justify="center")
shell_win.tag_config('log',foreground="#000090", font=("", 15, ""),justify="center")


shell_output = str()
shell_error  = str()

def shell_is_error():
    if len(shell_error) == 0:
        return 0
    else:
        return 1
    
def shell_win_insert_separator(text):
    text = '\n--------------------'+text+'-----------------------\n\n'
    shell_win.insert(END, text,'T2CG')
    shell_win.see(END)
    shell_win.update()
    
def shell(cmd):
    #res = subprocess.Popen(cmd.split(),stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    #output, error = res.communicate(timeout=20)
    
    # global shell_output
    # global shell_error
    # shell_output = str(output.decode())
    # shell_error = str(error.decode())
    # print(shell_output)
    # print(shell_error)
    if sys.platform == "linux":
        res = subprocess.run(str(cmd).encode('utf-8'), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True,encoding='utf-8')
    else:
        res = subprocess.run(str(cmd).encode('utf-8').split(), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True,encoding='utf-8')
    global shell_output
    global shell_error
    shell_output = str(res.stdout)
    shell_error = str(res.stderr)

def shell_win_insert(cmd):
    shell(cmd)
    if shell_is_error() == 0:
        shell_win.insert(END, datetime.datetime.now().strftime("[%H:%M:%S]") + shell_output + '\n','info')
    else:
        shell_win.insert(END, datetime.datetime.now().strftime("[%H:%M:%S]") + shell_error + '\n','error')
    shell_win.see(END)
    root.update()


# def shell_win_insert(cmd):
#     shell_win_insert(res)
#     return res
def git_exist():
    if os.path.isdir(".git") == 0:
        messagebox.showwarning("错误", "还没有仓库，请新建或克隆仓库 ")
        return True
    else:
        return False

def git_create():
    shell_win_insert_separator('开始新建仓库')
    if touch_gitignore_file :
        file = open('.gitignore','a+')

        file.write('\ngit_python_tools.py\n')

        file.close()

    if touch_readme_file:
        file = open('readme.md','a+')

        file.close()
    

    res = shell_win_insert("git init")
    if shell_is_error() == 0:
        if (shell_output.find("Reinitialized existing Git repository")) != -1:
            messagebox.showerror("错误", "这里已经有仓库了")
            return
        else:
            messagebox.showinfo("成功", "仓库创建成功")
            
    else:
        messagebox.showerror("错误", "发生异常")
        return
    shell_win_insert_separator('新建仓库完成')

def git_remove():
    shell_win_insert_separator('开始删除仓库')
    if git_exist():
        return
    if messagebox.askyesno("警告！", "确定要删除仓库吗？") == False:
        return
    res = shell_win_insert("rm -rf .git")
    messagebox.showinfo("成功", "仓库删除成功")
    shell_win_insert_separator('删除仓库完成')

def git_reset():
    shell_win_insert_separator('开始重置仓库')
    if git_exist():
        return
    if messagebox.askyesno("警告！", "确定要重置仓库吗？") == False:
        return
    res = shell_win_insert("rm -rf .git")
    res = shell_win_insert("git init")
    messagebox.showinfo("成功", "仓库重置成功")
    shell_win_insert_separator('重置仓库完成')

def git_log():
    if git_exist():
        return
    cmd = 'git log'
    shell(cmd)
    sum = 0
    if shell_is_error() == 1:
         messagebox.showerror("错误", "查询错误")
    else:
        history = ''
        outputs = shell_output
        while True:
            commit = ''
            result = re.search(r'commit.*\n', outputs)
            if result:
                commit = result.group(0)
                commit = re.sub(r'commit', '节点: ', commit)
                commit = re.sub(r'\n', '', commit)

            author = ''
            result = re.search(r'Author.*\n', outputs)
            if result:
                author = result.group(0)
                author = re.sub(r'Author', '作者', author)
                author = re.sub(r'\n', '', author)


            date = ''
            result = re.search(r'Date.*\n', outputs)
            if result:
                date = result.group(0)
                date = re.sub(r'Date: ', '', date)
                date = re.sub(r'\n', '', date)
                date = datetime.datetime.strptime(date.strip(), "%a %b %d %H:%M:%S %Y %z")
                date = str(date)
                date = re.sub(r'\+[\d]{1,2}:[\d]{1,2}', '', date)
                date = '时间: ' + date


            note = ''
            result = re.search(r'\n\n.*\n', outputs)

            if result:
                note = result.group(0)

                note = re.sub(r'\n', '', note)
                note = re.sub(r' ', '', note)
                note = '注释: ' + note



       
                
            
            history  = history +   commit + '\n' + author + '\n' + date + '\n' + note + '\n\n'
            history  = history + '-------------------------------------------------------\n\n'
            sum = sum + 1
  
            outputs = outputs[int(result.span(0)[1]):]
            if len(outputs) < 10:
                break
    shell_win.insert(END, '\n')
    shell_win.see(END)
    shell_win.insert(END, '\n\n\n所有提交('+str(sum)+'次提交)\n\n','T2C')
    shell_win.insert(END, history,'log')
 
    root.update()

def git_remote_url_check():

    cmd = 'git remote -v'
    shell(cmd)

    if shell_is_error() == 1:
        config_url()
        return
    if len(shell_output) < 2:
        config_url()
        return
        

def git_add_commit_push():
    shell_win_insert_separator('开始本地提交并仓库推送')
    if git_exist():
        return
    res = shell_win_insert("git add .")
    if shell_is_error() == 1:
        if shell_error.find("warning") == -1:
            messagebox.showerror("错误", "添加失败")
            return
    commit = simpledialog.askstring(title='',prompt='输入提交注释')
    if commit  == None:
        return
    res = shell_win_insert("git commit -m" + commit)
    if shell_is_error() == 1:
        messagebox.showerror("错误", "提交失败")
        return
    else:
        messagebox.showinfo("成功", "提交成功")
    
    switch = simpledialog.askstring(title='',prompt='输入提交分支(不输入默认'+default_branch+')')
    git_remote_url_check()
    if switch  == None:
        return
    if len(switch) == 0:
        switch = default_branch
        
    shell_win_insert_separator('开始仓库推送')
    res = shell_win_insert("git push origin " + switch)
    text = shell_error
    print(text)
    if text.find(default_branch + ' ->') != -1:
        messagebox.showinfo("成功", "推送成功")
        shell_win_insert_separator('开始本地提交并仓库推送完成')
        return
    if text.find('Everything up-to-date') != -1:
        messagebox.showwarning("警告", "远程仓库已是最新的")
        return
    messagebox.showerror("错误", "推送失败")
   
    

def git_add_commit():
    shell_win_insert_separator('开始仓库提交')
    if git_exist():
        return
    res = shell_win_insert("git add .")
    if shell_is_error() == 1:
        if shell_error.find("warning") == -1:
            messagebox.showerror("错误", "添加失败")
            return
    commit = simpledialog.askstring(title='',prompt='输入提交注释')
    if commit  == None:
        return
    res = shell_win_insert("git commit -m" + commit)
    if shell_is_error() == 1:
        messagebox.showerror("错误", "提交失败")
        return
    else:
        messagebox.showinfo("成功", "提交成功")
    shell_win_insert_separator('仓库提交完成')

    
def git_push():
    shell_win_insert_separator('开始仓库推送')

    if git_exist():
        return
    switch = simpledialog.askstring(title='',prompt='输入提交分支(不输入默认'+default_branch+')')
    git_remote_url_check()
    if switch  == None:
        return
    if len(switch) == 0:
        switch = default_branch
    res = shell_win_insert("git push origin " + switch)

    text = shell_error
    print(text)
    if text.find(default_branch + ' ->') != -1:
        messagebox.showinfo("成功", "推送成功")
        shell_win_insert_separator('仓库推送完成')
        return
        
    if text.find('Everything up-to-date') != -1:
        messagebox.showwarning("警告", "远程仓库已是最新的")
        return
    messagebox.showerror("错误", "推送失败")
    
    
    
def git_clone():
    shell_win_insert_separator('开始克隆仓库')
    url = simpledialog.askstring(title='',prompt='输入克隆地址')
    if url  == None:
        return
    res = shell_win_insert("git clone " + url)
    text = shell_error
    if text.find('Cloning into') != -1:
        messagebox.showinfo("成功", "克隆成功")
        
    else:
        messagebox.showerror("错误", "克隆异常")
        return
    shell_win_insert_separator('克隆仓库完成')
 
    
def git_pull():
    shell_win_insert_separator('开始拉取仓库')
    if git_exist():
        return
    res = shell_win_insert("git pull")
    if shell_is_error() == 1:
        messagebox.showerror("错误", "拉取失败")
        return
    text = shell_output
    if text.find('Already up to date.') != -1:
        messagebox.showwarning("警告", "本地仓库已经是最新的")
        
    shell_win_insert_separator('拉取仓库完成')
    
def git_back():
    shell_win_insert_separator('开始回滚到上次提交点')
    if messagebox.askyesno("警告！", "确定要回滚到上次提交点吗？") == False:
        return


    res = shell_win_insert("git reset --hard HEAD~")
    if shell_is_error() == 1:
        messagebox.showerror("错误", "回滚失败")
        return
    else:
        messagebox.showinfo("成功", "回滚成功")
        
    shell_win_insert_separator('回滚到上次提交点完成')
    
def git_back_commit():
    shell_win_insert_separator('开始回滚到上次提交点')
    if messagebox.askyesno("警告！", "确定要回滚指定提交点吗？") == False:
        return
    commit = simpledialog.askstring(title='',prompt='输入提交的节点值')

    if commit  == None:
        return
    res = shell_win_insert("git reset --hard "+commit)
    if shell_is_error() == 1:
        messagebox.showerror("错误", "回滚失败")
        return
    else:
        messagebox.showinfo("成功", "回滚成功")
        
    shell_win_insert_separator('回滚指定提交点完成')

def start():
    shell_win.insert(END, logo,'logo')
    shell_win.insert(END, '\n\n\n\n','logo')
    shell_win.insert(END, '欢迎使用Git-Python工具\n\n','welcome')
    cmd = 'git log'
    shell(cmd)


    if os.path.isdir(".git") == 0:
        shell_win.insert(END, '还没有仓库，请新建或克隆仓库 \n\n','T2C')
        shell_win.insert(END, '菜单栏->仓库->新建/克隆 \n\n\n','T2C')
        root.update()
        return 

    if shell_is_error() == 1:
        shell_win.insert(END, '这里没有提交记录 \n\n','T2C')
        shell_win.insert(END, '菜单栏->推送->本地提交\n\n\n','T2C')
        root.update()
        return
    else:
        outputs = shell_output
        commit = ''
        result = re.search(r'commit.*\n', outputs)
        if result:
            commit = result.group(0)
            commit = re.sub(r'commit', '节点: ', commit)
            commit = re.sub(r'\n', '', commit)

        author = ''

        result = re.search(r'Author.*\n', outputs)
        if result:
            author = result.group(0)
            author = re.sub(r'Author', '作者', author)
            author = re.sub(r'\n', '', author)


        date = ''
        result = re.search(r'Date.*\n', outputs)
        if result:
            date = result.group(0)
            date = re.sub(r'Date: ', '', date)
            date = re.sub(r'\n', '', date)
            date = datetime.datetime.strptime(date.strip(), "%a %b %d %H:%M:%S %Y %z")
            date = str(date)
            date = re.sub(r'\+[\d]{1,2}:[\d]{1,2}', '', date)
            date = '时间: ' + date


        note = ''
        result = re.search(r'\n\n.*\n', outputs)
        if result:
            note = result.group(0)
            note = re.sub(r'\n', '', note)
            note = re.sub(r' ', '', note)
            note = '注释: ' + note



  
        shell_win.insert(END, '您的上一次提交: \n\n','T2C')
        late  =   commit + '\n' + author + '\n' + date + '\n' + note + '\n\n'

        shell_win.insert(END, late,'log')
        root.update()
        return

    
    

def about():
    win = Tk()
    win.title("关于")
    win.geometry("350x230")
    win.resizable(0, 0)

    w_label0 = Label(win, height=2)
    w_label0.pack()

    w_label0 = Label(win, text="Git图形化Python脚本工具", font=("", 20))   
    w_label0.pack()

    w_sep0 = ttk.Separator(win, orient='horizontal')
    w_sep0.pack(fill='x', padx=10, pady=10)

    
    w_label = Label(win, text="作者: AhDun(DunHongWei)", font=("", 12))
    w_label.pack()

    w_sep = ttk.Separator(win, orient='horizontal')
    w_sep.pack(fill='x', padx=10, pady=10)

    w_label1 = Label(win, text="版本:v1.0(2024-1-8)", font=("", 12))
    w_label1.pack()

    w_sep1 = ttk.Separator(win, orient='horizontal')
    w_sep1.pack(fill='x', padx=10, pady=10)

    w_label2 = Label(win, text="开源协议:LICENSE-2.0(详情见源码)", font=("", 12))
    w_label2.pack()
    



def config_url():
    if git_exist():
        return
    url = simpledialog.askstring(title='',prompt='输入远程仓库地址 (http/https/git)')
    if url == None:
        return
    shell_win_insert("git remote rm origin ")
    shell_win_insert("git remote add origin " + url)
    if shell_is_error() == 1:
        messagebox.showwarning("错误", "远程仓库地址配置失败")
        return
    messagebox.showinfo("成功", "远程仓库地址配置成功")
    
    
def config_user_and_mail():
    user = simpledialog.askstring(title='',prompt='输入用户名')
    if user == None:
        return
    shell_win_insert("git config --global user.name " + user) 
    if shell_is_error() == 1:
        messagebox.showwarning("错误", "用户名配置失败")
        return
    mail = simpledialog.askstring(title='',prompt='输入邮箱')
    if mail == None:
        return
    shell_win_insert("git config --global user.email " + mail)
    if shell_is_error( ) == 1:
        messagebox.showwarning("错误", "用户名配置失败")
        return
    messagebox.showinfo("成功", "用户名配置成功")
     

def git_url():
    cmd = 'git remote -v'
    shell(cmd)
    text = shell_output
    text = re.sub('origin', '地址: ', text)
    text = re.sub('\(fetch\)', '', text)
    text = re.sub('\(push\)', '', text)
    shell_win.insert(END,'-------------------------------------------------------\n\n','log')
    shell_win.insert(END,text,'log')
    shell_win.insert(END,'\n-------------------------------------------------------\n\n','log')
    shell_win.see(END)
    shell_win.update()

def git_user_mail_info():
    cmd = 'git config user.name'
    shell(cmd)
 
    username = shell_output

    cmd = 'git config user.email'
    shell(cmd)
    mail = shell_output
    shell_win.insert(END,'-------------------------------------------------------\n\n','log')
    shell_win.insert(END,'用户名: ' + username,'log')
    shell_win.insert(END,'邮箱: ' + mail,'log')
    shell_win.insert(END,'\n-------------------------------------------------------\n\n','log')
    shell_win.see(END)
    shell_win.update()

    


main_menu = Menu(root,font=("", 15))


push_menu = Menu(main_menu, tearoff=0)
push_menu.add_command (label="本地提交并仓库推送 (F5)",command=git_add_commit_push)
root.bind("<F5>",lambda event:git_add_commit_push())
push_menu.add_command (label="本地提交",command=git_add_commit)
push_menu.add_command (label="仓库推送",command=git_push)
main_menu.add_cascade (label="推送", menu=push_menu)


# pull_menu = Menu(main_menu, tearoff=0)
# pull_menu.add_command (label="线上")
# main_menu.add_cascade (label="拉取", menu=pull_menu)

back_menu = Menu(main_menu, tearoff=0)

back_menu.add_command (label="上次提交",command=git_back)
back_menu.add_command (label="指定提交",command=git_back_commit)
main_menu.add_cascade (label="回滚", menu=back_menu)


store_menu = Menu(main_menu, tearoff=0)
store_menu.add_command (label="新建" ,command=git_create)
store_menu.add_command (label="克隆" ,command=git_clone)
store_menu.add_command (label="拉取",command=git_pull)
store_menu.add_command (label="重置" ,command=git_reset)
store_menu.add_command (label="删除" ,command=git_remove)

main_menu.add_cascade (label="仓库", menu=store_menu)

query_menu = Menu(main_menu, tearoff=0)
query_menu.add_command (label="所有提交",command=git_log)
query_menu.add_command (label="用户名和邮箱",command=git_user_mail_info)
query_menu.add_command (label="仓库地址",command=git_url)
main_menu.add_cascade (label="查询", menu=query_menu)

confing_menu = Menu(main_menu, tearoff=0)
confing_menu.add_command (label="仓库地址",command=config_url)
confing_menu.add_command (label="用户名和邮箱",command=config_user_and_mail)
main_menu.add_cascade (label="配置", menu=confing_menu)




main_menu.add_command (label="关于", command=about)



shell_win.insert(INSERT, shell_exit)

shell_win.pack()

start()


root.config(menu=main_menu)
root.mainloop()









