import os
import subprocess
import sys

os.system("cd etapa5 && make --silent")

fileName = "testeE6Lau/" + sys.argv[1]
command = "./etapa5/etapa5 < " + fileName + " > saida"
exitCode = subprocess.call(command, shell=True)

#ilocCommand = "python3 ilocsim.py -x -t -s --data 500 --stack 1024 saida"
#subprocess.call(ilocCommand, shell=True)
