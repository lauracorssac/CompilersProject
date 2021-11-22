import os
import subprocess
import sys

os.system("cd etapa7 && make --silent")
failed = []

def executeAux(fileName, optimized, expectedExitCode):

    optimizedString = "Optimized" if optimized else "Normal"
    print()
    print()
    print(optimizedString, "Exec")
    print()
    outputFileName = "saida" + optimizedString + ".s"
    
    command = "./etapa7/etapa7 "
    if optimized:
        command += "-O "
    
    command += (" < " + fileName + " > " + outputFileName)
    
    exitCode = subprocess.call(command, shell=True)
    print("ExitCode = ", str(exitCode))
    
    command = "gcc " + outputFileName + " -o ex3"
    exitCode = subprocess.call(command, shell=True)
    print("ExitCode = ", str(exitCode))
    
    command = "./ex3"
    exitCode = subprocess.call(command, shell=True)
    print("ExitCode = ", str(exitCode))
    
    if exitCode != expectedExitCode:
        failed.append(fileName)
        print("FALHOU!")
    else:
        print("Esse aqui PASSOU!")
    

def execute(fileName):
    print("FileName = ", fileName)
    if not os.path.exists(fileName):
        print("File not found")
        return
    f = open(fileName, "r")
    line = f.readline().strip()
    expectedExitCode = int(line[2:])
    print("Expected = ", expectedExitCode)
    executeAux(fileName, True, expectedExitCode)
    executeAux(fileName, False, expectedExitCode)


if len(sys.argv) == 2:
    fileName = "testeE7/" + sys.argv[1]
    execute(fileName)
else:
    for i in range(0,33):
        fileName = "testeE56/ijk"
        if i < 10:
            fileName += "0"
        fileName += str(i)
        execute(fileName)
    
print("TESTS THAT FAILED:", failed)


        
    
    
        

