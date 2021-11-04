import os
import subprocess
import sys

os.system("cd etapa6 && make --silent")

def execute(fileName):
    print("FileName = ", fileName)
    if not os.path.exists(fileName):
        print("File not found")
        return
    f = open(fileName, "r")
    line = f.readline().strip()

    command = "./etapa6/etapa6 < " + fileName + " > saida.s"
    exitCode = subprocess.call(command, shell=True)
    print("ExitCode = ", str(exitCode))
    
    command = "gcc saida.s -o ex3"
    exitCode = subprocess.call(command, shell=True)
    print("ExitCode = ", str(exitCode))
    
    command = "./ex3"
    exitCode = subprocess.call(command, shell=True)
    print("ExitCode = ", str(exitCode))

fileName = "testeE6Lau/" + sys.argv[1]
execute(fileName)


        
    
    
        

