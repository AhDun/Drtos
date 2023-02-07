import os

cmd = "git add ."
print(cmd)
print(os.popen(cmd).read())


i = input("推送内容:")
cmd = " git commit -m " + '"' + i + '"'
print(cmd)
print(os.popen(cmd).read())


cmd = "git push origin"
print(cmd)
print(os.popen(cmd).read())
