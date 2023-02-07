import os


def shell(cmd):
    print(cmd)
    res = os.popen(cmd).read()
    print(res.encode("gbk"))
    return res


def init():
    cmd = "git init"
    return cmd


def add():
    cmd = "git add ."
    return cmd


def commit(s):
    cmd = "git commit -m" + "'" + s + "'"
    return cmd


def remoteadd(s):
    cmd = "git remote add origin " + s
    return cmd


def remoterm():
    cmd = "git remote rm origin "
    return cmd


def push():
    cmd = "git push -f origin master"
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




def git():
    print("---------------")
    print(" 自动git脚本")
    print("---------------")
    print("1.首次提交 ")
    print("2.本地提交")
    print("3.仓库推送")
    print("4.回滚上一个版本")
    print("5.回滚到指定版本")
    print("6.查看所有版本")
    print("R.删除本地git")
    print("S.更改仓库地址")
    print("---------------")
    print("按shift+c退出程序")
    print("---------------")

    i = input("请输入:")

    if i == "1":
        shell(init())
        shell(add())
        shell(commit(input("\n请输入,提交备注：")))
        shell(remoteadd(input("\n请输入,仓库地址：")))
        shell(push())
    elif i == "2":
        shell(add())
        shell(commit(input("\n请输入,提交备注：")))
    elif i == "3":
        shell(push())
    elif i == "4":
        shell(reseth())
    elif i == "5":
        shell(resets(input("\n请输入,指定版本哈希：")))
    elif i == "R":
        shell(rm())
    elif i == "S":
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
        print("已退出")
        break
