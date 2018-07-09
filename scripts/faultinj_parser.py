#!/usr/bin/env python3
import os
import re
import csv
from collections import Counter
import sys

varSDCList = list()
varSDCDetectList = list()
varCrashList = list()
flipList = list()
faultModelCrash = list()
faultModelSDC = list()
faultModelSDCDetect = list()

flipCount = 0
sdcCount = 0
sdcDetectCount = 0
crashCount = 0
sdcCrashCount = 0

sdcFilename = "sdc.csv"
crashFilename = "crash.csv"
summFilename = "summary.csv"

def processDirectory(dirName, fileList, app_name, out_folder):
    #print('Found directory: %s' % dirName)
    flipInfo = ""
    flip=False
    sdc=0
    sdcDetect=0
    crash=0
    var = ""
    varFile = ""
    varLine = ""
    faultTime = ""
    faultModel = ""
    signalTime = ""
    for fname in fileList:
        if re.search("carolfi-flipvalue",fname):
            (flip, flipInfo, var, varFile, varLine, faultTime, faultModel, signalTime) = getFlipInfo(dirName, fname)
            if re.search("sdcs",dirName):
                sdc = 1
                if re.search("sdcs-detected",dirName):
                    sdcDetect = 1
                else:
                    sdcDetect = 0
            else:
                sdc = 0
                sdcDetect = 0
            if re.search("hangs",dirName) or re.search("noOutputGenerated",dirName):
                crash = 1
            else:
                crash = 0
    if flip:
        global flipCount
        global sdcCount
        global sdcDetectCount
        global crashCount
        global sdcCrashCount
        if var != "":
            flipCount += 1
            varInfo = var+";"+varFile+";"+str(varLine)
            flipList.append(varInfo)
            if sdc == 1:
                sdcCount += 1
                if sdcDetect == 1:
                    sdcDetectCount += 1
                    varSDCDetectList.append(varInfo)
                    faultModelSDCDetect.append(faultModel)
                else:
                    varSDCList.append(varInfo)
                    faultModelSDC.append(faultModel)
                csvWFP = open(out_folder + "/" + app_name+"_"+sdcFilename, "a")
                writer = csv.writer(csvWFP, delimiter=';')
                writer.writerow([var,varFile,str(varLine),str(faultTime),str(signalTime),str(faultModel),str(sdcDetect)])
                csvWFP.close()
            if crash == 1:
                crashCount += 1
                varCrashList.append(varInfo)
                faultModelCrash.append(faultModel)
                csvWFP = open(out_folder + "/" + app_name+"_"+crashFilename, "a")
                writer = csv.writer(csvWFP, delimiter=';')
                writer.writerow([var,varFile,str(varLine),str(faultTime),str(signalTime),str(faultModel)])
                csvWFP.close()
            if sdc == 1 and crash == 1:
                sdcCrashCount += 1

def getSDCCrashInfo(dirName, fname):
    fp = open(dirName+"/"+fname, "r", errors="replace")
    content = fp.read()
    sdc = 0
    crash = 1
    if re.search("SDC", content):
        sdc = 1
    if re.search("END", content):
        crash = 0
    return (sdc, crash)

def getFlipInfo(dirName, fname):
    fp = open(dirName+"/"+fname, "r")
    content = fp.read()
    flip = False
    if re.search("Fault Injection Successful",content):
        flip = True
    if flip:
        fp.seek(0)
        btC = False
        bt = ""
        symbolName = ""
        symbolFilename = ""
        symbolLine = 0
        faultTime = -1
        faultModel=""
        initSignal=-1
        endSignal=-1
        for line in fp:
            if re.search("Backtrace BEGIN:",line):
                bt = "Backtrace BEGIN:\n"
                btC = True
            if re.search("Backtrace END", line):
                btC = False
                bt += "Backtrace END\n"
            if btC:
                bt += line
            m = re.match(".*(Memory content before bitflip:.*)",line)
            if m:
                bt += m.group(1)
            m = re.match(".*(Memory content after  bitflip:.*)",line)
            if m:
                bt += m.group(1)
            m = re.match(".*(frame name:.*)",line)
            if m:
                bt += m.group(1)
            m = re.match(".*(symbol name: )(.*)",line)
            if m:
                bt += m.group(1)+m.group(2)
                symbolName = m.group(2)
            m = re.match(".*(symbol filename: )(.*)",line)
            if m:
                bt += m.group(1)+m.group(2)
                symbolFilename = m.group(2)
            m = re.match(".*(Fault Model: )(.*)",line)
            if m:
                bt += m.group(1)+m.group(2)
                faultModel = m.group(2)
            #initSignal:0
            m = re.match(".*(initSignal:)(.*)",line)
            if m:
                bt += m.group(1)+m.group(2)
                initSignal = m.group(2)
            #endSignal:2
            m = re.match(".*(endSignal:)(.*)",line)
            if m:
                bt += m.group(1)+m.group(2)
                endSignal = m.group(2)
            m = re.match(".*(symbol line: )(.*)",line)
            if m:
                bt += m.group(1)+m.group(2)
                symbolLine = m.group(2)
                #Fault Injection Successful after 0.692039966583s
            m = re.match(".*(Fault Injection Successful after )(\d+.\d+)s",line)
            if m:
                bt += m.group(1)+m.group(2)+"s"
                faultTime = m.group(2)

        return (flip, bt, symbolName, symbolFilename, symbolLine, faultTime, faultModel,initSignal+"-"+endSignal)
    else:
        return (flip, "", "", "", "", "", "", "")

def parse(app_name, logs_folder, out_folder):
    csvWFP = open(out_folder + "/" + app_name+"_"+sdcFilename, "w")
    writer = csv.writer(csvWFP, delimiter=';')
    writer.writerow(["Variable Name","Variable File","Variable Line","Fault Injection Time(s)","Injection Time Interval","Fault Model","Detected"])
    csvWFP.close()
    csvWFP = open(out_folder + "/" + app_name+"_"+crashFilename, "w")
    writer = csv.writer(csvWFP, delimiter=';')
    writer.writerow(["Variable Name","Variable File","Variable Line","Fault Injection Time(s)","Injection Time Interval","Fault Model"])
    csvWFP.close()

    for dirName, subdirList, fileList in os.walk(logs_folder):
        processDirectory(dirName, fileList, app_name, out_folder)

    fp = open(out_folder + "/" + app_name+"_"+summFilename, "w")
    fp.write("bitflips:;"+str(flipCount))
    fp.write("\nTotal SDCs:;"+str(sdcCount))
    fp.write("\nDetected SDCs:;"+str(sdcDetectCount))
    fp.write("\nCrashes:;"+str(crashCount))
    fp.write("\nSimultaneous SDCs and Crashes:;"+str(sdcCrashCount))
    fp.write("\n\n")

    flips = Counter(flipList)

    fp.write("FaultModels Undetected SDCs:")
    fp.write("\nFaultModel ;#SDCs; percentage")
    for k,v in Counter(faultModelSDC).most_common():
        per = float(v)/float(sdcCount) * 100
        fp.write("\n"+str(k)+";"+str(v)+";"+str(per))

    fp.write("\n\n")
    fp.write("FaultModels Detected SDCs:")
    fp.write("\nFaultModel ;#SDCs Detected; percentage")
    for k,v in Counter(faultModelSDCDetect).most_common():
        per = float(v)/float(sdcCount) * 100
        fp.write("\n"+str(k)+";"+str(v)+";"+str(per))

    fp.write("\n\n")
    fp.write("FaultModels Crashes:")
    fp.write("\nFaultModel ;#Crashes; percentage")
    for k,v in Counter(faultModelCrash).most_common():
        per = float(v)/float(sdcCount) * 100
        fp.write("\n"+str(k)+";"+str(v)+";"+str(per))

    fp.write("\n\n")
    fp.write("Variables that caused Undetected SDCs:")
    fp.write("\nPVF ;#flips ;#SDCs ;Var name ;file ;line number")
    for k,v in Counter(varSDCList).most_common():
        pvf = float(v)/float(flips[k]) * 100
        fp.write("\n"+str(pvf)+";"+str(flips[k])+";"+str(v)+";"+k)

    fp.write("\n\n")
    fp.write("Variables that caused Detected SDCs:")
    fp.write("\nPVF ;#flips ;#SDCs ;Var name ;file ;line number")
    for k,v in Counter(varSDCDetectList).most_common():
        pvf = float(v)/float(flips[k]) * 100
        fp.write("\n"+str(pvf)+";"+str(flips[k])+";"+str(v)+";"+k)

    fp.write("\n")
    fp.write("\nVariables that caused Crash:")
    fp.write("\nPVF ;#flips ;#SDCs ;Var name ;file ;line number")
    for k,v in Counter(varCrashList).most_common():
        pvf = float(v)/float(flips[k]) * 100
        fp.write("\n"+str(pvf)+";"+str(flips[k])+";"+str(v)+";"+k)

    fp.close()

if(__name__ == "__main__"):
    if(len(sys.argv) != 3):
        print("Arguments: app. name, app. logs folder path")
    else:
        parse(sys.argv[1], sys.argv[2], "./")
