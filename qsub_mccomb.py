#!/usr/bin/python
import os, shutil

# Current directory
TOPDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC"
# Run directory
RUNDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/NQS_MCcomb"

'''
# Clean up
files = os.listdir(RUNDIR)
for i in range(len(files)):
	file = files[i]
	script = "run_mccomb" in file
	if(script==True):
		os.remove(os.path.join(RUNDIR,file))
		print("[###### MCcomb ######] Clean up is done.")
	else:
		print("[###### MCcomb ######] No script file")
print(" ")

for i in range(100):
	for j in range(3):
		for k in range(10):
			if (os.path.exists(os.path.join(RUNDIR,"run_mccomb.XCount.Xpart.Xskip.sh"))==True):
				os.remove(os.path.join(RUNDIR,"run_mccomb.XCount.Xpart.Xskip.sh"))

			if (os.path.exists(os.path.join(TOPDIR,"run_mccomb.sh"))==True):
				shutil.copy(os.path.join(TOPDIR,"run_mccomb.sh"),os.path.join(RUNDIR,"run_mccomb.XCount.Xpart.Xskip.sh"))

				if (i<10):
					filename = "run_mccomb.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh"
				if (i>=10):
					filename = "run_mccomb.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh"

				os.rename(os.path.join(RUNDIR,"run_mccomb.XCount.Xpart.Xskip.sh"),os.path.join(RUNDIR,filename))

				if (i<10):
					shellscript = os.path.join(RUNDIR,"run_mccomb.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh")
				if (i>=10):
					shellscript = os.path.join(RUNDIR,"run_mccomb.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(100*k)+".sh")
				with open(shellscript,'r') as f:
					contents = f.read()
					contents = contents.replace("XCount",str(i))
					contents = contents.replace("Xpart",str(j+1))
					contents = contents.replace("Xskip",str(100*k))
					contents = contents.replace("Xindex",str(i))
				with open(shellscript,'w') as f:
					f.write(contents)
'''


#part, skip fixed
#count loop
# Check List
# !!!! Note: Index file should be corresponded to Count for coherent job running (The same index file must not be referenced from some jobs)
#part001.skip0, part002.skip0, part003.skip0 (300files x 2files(.sbi + .root) = 600files) done
#part001.skip100, part002.skip100, part003.skip100 (1200files) done
#part001.skip200, part002.skip200, part003.skip200 (1800files) done
#part001.skip300, part002.skip300, part003.skip300 (2400files) done
#part001.skip400, part002.skip400, part003.skip400 (3000files) done
#part001.skip500, part002.skip500, part003.skip500 (3600files) done
#part001.skip600, part002.skip600, part003.skip600 (4200files) done
#part001.skip700, part002.skip700, part003.skip700 (4800files) done
#part001.skip800, part002.skip800, part003.skip800 (5400files) done
#part001.skip900, part002.skip900, part003.skip900 (6000files) done

part = 3
skip = 900
#'''
for i in range(100):
	if (i>=0 and i<10):
		cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/MCcomb/NQSLog/err.Count00'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.log -o /disk02/usr6/sedi/MCcomb/NQSLog/Count00'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.log \"./NQS_MCcomb/run_mccomb.Count00'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.sh\"'
		print("[###### MCcomb ######] Execution of "+cmd)
		os.system(cmd)
	if (i>=10):
		cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/MCcomb/NQSLog/err.Count0'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.log -o /disk02/usr6/sedi/MCcomb/NQSLog/Count0'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.log \"./NQS_MCcomb/run_mccomb.Count0'+str(i)+'.part00'+str(part)+'.skip'+str(skip)+'.sh\"'
		print("[###### MCcomb ######] Execution of "+cmd)
		os.system(cmd)
#'''


#for i in range(100):
	#for j in range(3):
		#for k in range(10):
			#if (i==0 and j==0 and k==0):
			#if (i>=0 and i<10):
				#cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/MCcomb/NQSLog/err.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log -o /disk02/usr6/sedi/MCcomb/NQSLog/Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log \"./NQS_MCcomb/run_mccomb.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.sh\"'
				#print("[###### MCcomb ######] Execution of "+cmd)
				#os.system(cmd)
			#if (i>=10):
				#cmd = '/usr/local/bin/qsub -e /disk02/usr6/sedi/MCcomb/NQSLog/err.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log -o /disk02/usr6/sedi/MCcomb/NQSLog/Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.log \"./NQS_MCcomb/run_mccomb.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(100*k)+'.sh\"'
				#print("[###### MCcomb ######] Execution of "+cmd)
				#os.system(cmd)

