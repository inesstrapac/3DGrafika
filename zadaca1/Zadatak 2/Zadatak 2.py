import math

outF = open("cilindar.obj", "w")

def x_koordinata (kut):
    return round(math.cos(kut*math.pi / 180 ),6)

def y_koordinata (kut):
    return round(math.sin(kut*math.pi / 180 ),6)

n = 24 #broj točaka za stvaranje kružnice (što je više točaka kružnica je pravilnija)
kut = 0

for i in range(n):
    outF.write("v " + str(x_koordinata(kut)) + " 0 " + str(y_koordinata(kut)) + "\n")
    kut= kut+360/n 

for i in range(n):
    outF.write("v " + str(x_koordinata(kut)) + " 2 " + str(y_koordinata(kut)) + "\n")
    kut= kut+360/n 

for i in range(n):
    outF.write("vn " + str(x_koordinata(kut)) + " 0 " + str(y_koordinata(kut)) + " \n")
    kut= kut+360/n     

outF.write("vn 0 -1 0 \n")
outF.write("vn 0 1 0  \n")

for i in range(n-2):
    outF.write("f 1//1 " + str(i+2) + "//" + str(i+2) + " " + str(i+3) + "//" + str(i+3) + "\n")

for i in range(n-2):
    outF.write("f 25//1 " + str(i+2+n) + "//" + str(i+2) + " " + str(i+3+n) + "//" + str(i+3) + "\n")


for i in range(n-1):
    outF.write("f " + str(i+1) + "//" + str(i+1) + " " + str(i+1+n) + "//" + str(i+1) + " " + str(i+2) + "//" + str(i+2) + "\n")

outF.write("f " + str(n) + "//" + str(n) + " " + str(2*n) + "//" + str(n) + " 1//1 \n")


for i in range(n-1):
    outF.write("f " + str(i+1+n) + "//" + str(i+1) + " " + str(i+2+n) + "//" + str(i+2) + " " + str(i+2) + "//" + str(i+2) + "\n")

outF.write("f " + str(2*n) + "//" + str(n) + " " + str(n+1) + "//1 1//1 \n")


for i in range(n-2):
    outF.write("f " + str(i+1) + "//25 " + str(i+2) + "//25 " + str(i+3) + "//25 \n")

outF.write("f " + str(n) + "//25 1//25 2//25 \n")

for i in range(n-2):
    outF.write("f " + str(i+1+n) + "//26 " + str(i+2+n) + "//26 " + str(i+3+n) + "//26 \n")

outF.write("f " + str(2*n - 1) + "//26 " + str(2*n) + "//26 " + str(n) + "//26 \n")
