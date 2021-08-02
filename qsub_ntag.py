#!/usr/bin/python
import os, shutil

# Current directory
TOPDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC"
# Run directory
RUNDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/NQS_Ntag"

'''
# Clean up
files = os.listdir(RUNDIR)
for i in range(len(files)):
	file = files[i]
	script = "run_ntag" in file
	if(script==True):
		os.remove(os.path.join(RUNDIR,file))
		print("[###### n-tagging ######] Clean up is done.")
	else:
		print("[###### n-tagging ######] No script file")
print(" ")

for i in range(100):
	for j in range(3):
		for k in range(10):
			if (os.path.exists(os.path.join(RUNDIR,"run_ntag.XCount.Xpart.Xskip.sh"))==True):
				os.remove(os.path.join(RUNDIR,"run_ntag.XCount.Xpart.Xskip.sh"))

			if (os.path.exists(os.path.join(TOPDIR,"run_ntag.sh"))==True):
				shutil.copy(os.path.join(TOPDIR,"run_ntag.sh"),os.path.join(RUNDIR,"run_ntag.XCount.Xpart.Xskip.sh"))

				if (i<10):
					filename = "run_ntag.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh"
				if (i>=10):
					filename = "run_ntag.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh"

				os.rename(os.path.join(RUNDIR,"run_ntag.XCount.Xpart.Xskip.sh"),os.path.join(RUNDIR,filename))

				if (i<10):
					shellscript = os.path.join(RUNDIR,"run_ntag.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh")
				if (i>=10):
					shellscript = os.path.join(RUNDIR,"run_ntag.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh")
				with open(shellscript,'r') as f:
					contents = f.read()
					contents = contents.replace("XCount",str(i))
					contents = contents.replace("Xpart",str(j+1))
					contents = contents.replace("Xskip",str(100*k))
				with open(shellscript,'w') as f:
					f.write(contents)
'''

# Check List
# count000-009.part001.skip0 (10files x 3files(all+sig+bkg) = 30files) done
# count010-019.part001.skip0 (60files) done
# count020-029.part001.skip0 (90files) done
# count030-039.part001.skip0 (120files) done
# count040-049.part001.skip0 (150files) done
# count050-059.part001.skip0 (180files) done
# count060-069.part001.skip0 (210files) done

part = 1
skip = 0

for i in range(70, 80):
	if (i>=0 and i<10):
		cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/Ntag/NQSLog/err.Count00'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.log -o /disk02/usr6/sedi/Ntag/NQSLog/Count00'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.log \"./NQS_Ntag/run_ntag.Count00'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.sh\"'
		print("[###### LENtuple ######] Execution of "+cmd)
		os.system(cmd)
	if (i>=10):
		cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/Ntag/NQSLog/err.Count0'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.log -o /disk02/usr6/sedi/Ntag/NQSLog/Count0'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.log \"./NQS_Ntag/run_ntag.Count0'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.sh\"'
		print("[###### LENtuple ######] Execution of "+cmd)
		os.system(cmd)

'''
for i in range(100):
	for j in range(3):
		for k in range(10):
			#if (i==0 and j==0):
			if (i>=0 and i<10):
				cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/Ntag/NQSLog/err.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log -o /disk02/usr6/sedi/Ntag/NQSLog/Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log \"./NQS_Ntag/run_ntag.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.sh\"'
				print("[###### LENtuple ######] Execution of "+cmd)
				os.system(cmd)
			if (i>=10):
				cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/Ntag/NQSLog/err.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log -o /disk02/usr6/sedi/Ntag/NQSLog/Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log \"./NQS_Ntag/run_ntag.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.sh\"'
				print("[###### LENtuple ######] Execution of "+cmd)
				os.system(cmd)
'''

