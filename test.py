import os

pid_main = input("PID_main: ")
pid_bonus = input("PID_bonus: ")
client_main = "./client "
client_bonus = "./client_bonus "
f = open('Test.txt', 'r')

for i in range(69):
    os.system(client_main + pid_main + ' "' + f.readline().rstrip('\n') + '"')
f.close()
f = open('Test.txt', 'r')
for i in range(69):
    os.system(client_bonus + pid_bonus + ' "' + f.readline().rstrip('\n') + '"')
f.close()
