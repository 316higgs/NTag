#!/usr/bin/python
import os, shutil, time

# Current directory
TOPDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC"
# Run directory
RUNDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/NQS_LENtuple"

#'''
# Clean up
files = os.listdir(RUNDIR)
for i in range(len(files)):
	file = files[i]
	script = "run_lentuple" in file
	if(script==True):
		os.remove(os.path.join(RUNDIR,file))
		print("[###### LENtuple ######] Clean up is done.")
	else:
		print("[###### LENtuple ######] No script file")
print(" ")

for i in range(100):
	for j in range(3):
		for k in range(10):
			if (os.path.exists(os.path.join(RUNDIR,"run_lentuple.XCount.Xpart.Xskip.sh"))==True):
				os.remove(os.path.join(RUNDIR,"run_lentuple.XCount.Xpart.Xskip.sh"))

			if (os.path.exists(os.path.join(TOPDIR,"run_lentuple.sh"))==True):
				shutil.copy(os.path.join(TOPDIR,"run_lentuple.sh"),os.path.join(RUNDIR,"run_lentuple.XCount.Xpart.Xskip.sh"))

				if (i<10):
					filename = "run_lentuple.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh"
				if (i>=10):
					filename = "run_lentuple.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh"

				os.rename(os.path.join(RUNDIR,"run_lentuple.XCount.Xpart.Xskip.sh"),os.path.join(RUNDIR,filename))

				if (i<10):
					shellscript = os.path.join(RUNDIR,"run_lentuple.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh")
				if (i>=10):
					shellscript = os.path.join(RUNDIR,"run_lentuple.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh")
				with open(shellscript,'r') as f:
					contents = f.read()
					contents = contents.replace("XCount",str(i))
					contents = contents.replace("Xpart",str(j+1))
					contents = contents.replace("Xskip",str(100*k))
				with open(shellscript,'w') as f:
					f.write(contents)
#'''

'''
for i in range(75, 100):
	for j in range(3):
		for k in range(10):
			#if (i==0 and j==0):
			#if (i>=0 and i<10):
				#cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/LENtuple/NQSLog/err.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log -o /disk02/usr6/sedi/LENtuple/NQSLog/Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log \"./NQS_LENtuple/run_lentuple.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.sh\"'
				#print("[###### LENtuple ######] Execution of "+cmd)
				#os.system(cmd)
			#if (i>=71):
			cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/LENtuple/NQSLog/err.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log -o /disk02/usr6/sedi/LENtuple/NQSLog/Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log \"./NQS_LENtuple/run_lentuple.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.sh\"'
			print("[###### LENtuple ######] Execution of "+cmd)
			os.system(cmd)
		time.sleep(15)
	time.sleep(15)
'''

#for i in range(100):
for i in range(84, 100):
	for j in range(3):
		for k in range(10):
			if (i>=0 and i<10):
				#if (i==0 and j==2 and k>3):
					#break
				#if (i==0 and j==0 and k<1):
					cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/LENtuple/NQSLog/err.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(k*100)+'.log -o /disk02/usr6/sedi/LENtuple/NQSLog/Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(k*100)+'.log \"./NQS_LENtuple/run_lentuple.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(k*100)+'.sh\"'
					#cmd = '/usr/local/bin/qsub \"./NQS_LENtuple/run_lentuple.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(k)+'.sh\"'
					print("[###### LENtuple ######] Execution of "+cmd)
					os.system(cmd)
					time.sleep(1)
			#'''
			if (i>=10):
				cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/LENtuple/NQSLog/err.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(k*100)+'.log -o /disk02/usr6/sedi/LENtuple/NQSLog/Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(k*100)+'.log \"./NQS_LENtuple/run_lentuple.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(k*100)+'.sh\"'
				#cmd = '/usr/local/bin/qsub -n \"./NQS_LENtuple/run_lentuple.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(k)+'.sh\"'
				print("[###### LENtuple ######] Execution of "+cmd)
				os.system(cmd)
				time.sleep(1)
			#'''
