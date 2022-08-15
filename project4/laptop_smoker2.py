import random

"""
Note from Joey:
Hi! Thanks using my tester to generate a test file. To use this program to generate a file, you need to have python installed on your computer.

To Run Call:
python3 test_maker.py  (python test_maker.py also works)

This will generate a test file called python_test.txt with
Run this file as an arguement of ./a.out file by running

./a.out python_test.txt 

"""

f = open("python_test.txt", "w+")
random.seed(a=None, version=2)
FileNameBASE = ["FILE", "A_FILE", "B_FILE", "C_FILE", "D_FILE", "E_FILE", "F_FILE", "G_FILE", "H_FILE", "I_FILE", "J_FILE", "K_FILE", "L_FILE", "M_FILE", "N_FILE", "O_FILE", "P_FILE", "Q_FILE", "R_FILE", "S_FILE", "T_FILE", "U_FILE", "V_FILE", "W_FILE", "X_FILE", "Y_FILE", "Z_FILE"]
FileNameList = []
DependencyNameBase = ["iostream", "fstream", "ostream", "cmath", "lmath", "cmath.h", "cassert", "stdio", "Joey.h", "Zefei.h", "Zian.h", "Tester.h", "Depper.h"]


def make_include(FileNameNumber):
    IncludeList = []
    a = random.randint(0,2000)
    for i in range(a):
        b = random.randint(0,9)
        if (b <= 2):
            if (FileNameNumber>10):
                c = random.randint(0,FileNameNumber-1)
                IncludeList.append("#include <"+FileNameList[c]+">\n")
        else:
            d = random.randint(0,len(DependencyNameBase)-1)
            c = random.randint(1, 1000)
            IncludeList.append("#include <"+str(c)+DependencyNameBase[d]+">\n")
    for x in IncludeList:
        f.write(x)

        

for i in range(10000):
    a = random.randint(0,len(FileNameBASE)-1)
    b = random.randint(0,100000)
    FileNameList.append(FileNameBASE[a]+str(b))


FileNameList = list(dict.fromkeys(FileNameList))

for x in range(len(FileNameList)):
    f.write(FileNameList[x]+"\n")
    make_include(x)