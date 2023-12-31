#
# Copyright (c) 2022-2023 AhDun
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

import os


def shell(cmd):
    #print(cmd)
    res = os.popen(cmd).read()
    #print(res.encode("gbk"))
    return res


def init():
    cmd = "git init"
    return cmd


def add():
    cmd = "git add ."
    return cmd


def commit(s):
    cmd = "git commit -m" + s
    return cmd


def remoteadd(s):
    cmd = "git remote add origin " + s
    return cmd


def remoterm():
    cmd = "git remote rm origin "
    return cmd


def push():
    cmd = "git push origin master"
    return cmd


def reseth():
    cmd = "git reset --hard HEAD^"
    return cmd


def resets(s):
    cmd = "git reset --soft " + s
    return cmd


def rm():
    cmd = "rm -rf .git"
    return cmd

def pull():
    cmd = "pull "
    return cmd




def git():
    print("---------------------------")
    print("git-python自动脚本")
    print("---------------------------\n")
    if os.path.isdir(".git") == 0:
        print(" 1.首次提交与仓库推送")
    else:
        print(" 2.本地提交并仓库推送")
        print(" 3.本地提交")
        print(" 4.仓库推送")
        print("---------------")
        print(" 6.下载到本地")
        print("---------------")
        print(" 7.回滚上一个版本")
        print(" 8.回滚到指定版本")
        # print(" 9.删除本地git")
        print(" 0.更改仓库地址")
    print("\n---------------")
    i = input(" 请输入:")

    if i == "1":
        shell(init())
        shell(add())
        shell(commit(input("\n请输入,提交备注：")))
        shell(remoteadd(input("\n请输入,仓库地址：")))
        shell(push())
    elif i == "2":
        shell(add())
        shell(commit(input("\n请输入,提交备注：")))
        shell(push())
    elif i == "3":
        shell(add())
        shell(commit(input("\n请输入,提交备注：")))
    elif i == "4":
        shell(push())
    elif i == "6":
        shell(pull())
    elif i == "7":
        shell(reseth())
    elif i == "8":
        shell(resets(input("\n请输入,指定版本哈希：")))
    # elif i == "9":
    #     shell(rm())
    elif i == "0":
        shell(remoterm())
        shell(remoteadd(input("\n请输入,仓库地址：")))
    print("\n\n")
    print("---------------")
    print("已完成")
    print("---------------")
    print("\n")

while True:
    try:
        git()
    except:
        print("error")
