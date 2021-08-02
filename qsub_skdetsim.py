#!/usr/bin/python
import os, shutil

# Current directory
TOPDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC"
# Run directory
RUNDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/NQS_SKDETSIM"


# Clean up
files = os.listdir(RUNDIR)
for i in range(len(files)):
	file = files[i]
	script = "run_skdetsim" in file
	if(script==True):
		os.remove(os.path.join(RUNDIR,file))
		print("[###### SKDETSIM ######] Clean up is done.")
	else:
		print("[###### SKDETSIM ######] No script file")
print(" ")


# Generate 10 shell scripts
# fhc.num.VECTcount0XY.part00Z.dat (10 corresponds to X. Y runs to 0 to 9 and Z runs 1 to 3 in original script)
# i runs 0 to 9
for i in range(100):
	for j in range(3):
		# If copy source file already exists, remove it
		if (os.path.exists(os.path.join(RUNDIR,"run_skdetsim.XCount.Xpart.sh"))==True):
		os.remove(os.path.join(RUNDIR,"run_skdetsim.XCount.Xpart.sh"))
		# make copy source file
		# make 10 files by replacing XCount into appropriate numbers.
		if (os.path.exists(os.path.join(TOPDIR,"run_skdetsim.sh"))==True):
			shutil.copy(os.path.join(TOPDIR,"run_skdetsim.sh"),os.path.join(RUNDIR,"run_skdetsim.XCount.Xpart.sh"))
			#print("[###### SKDETSIM ######] File copied: run_skdetsim.XCount.sh")

		if (i<10):
			filename = "run_lentuple.Count00"+str(i)+".part00"+str(j+1)+".sh"
		if (i>=10):
			filename = "run_lentuple.Count0"+str(i)+".part00"+str(j+1)+".sh"

        os.rename(os.path.join(RUNDIR,"run_skdetsim.XCount.Xpart.sh"),os.path.join(RUNDIR,filename))
    	# File format: run_skdetsim.CountX.sh (X runs 0 to 9)
		#filename = "run_skdetsim.Count"+str(i)+".sh"
		#os.rename(os.path.join(RUNDIR,"run_skdetsim.XCount.sh"),os.path.join(RUNDIR,filename))
		#print("[###### SKDETSIM ######] File: run_skdetsim.Count"+str(i)+".sh is created.")

		# Rewrite XCount in file into appropriate numbers
		if (i<10):
			shellscript = os.path.join(RUNDIR,"run_lentuple.Count00"+str(i)+".part00"+str(j+1)+".sh")
		if (i>=10):
			shellscript = os.path.join(RUNDIR,"run_lentuple.Count0"+str(i)+".part00"+str(j+1)+".sh")
		#shellscript = os.path.join(RUNDIR,"run_skdetsim.Count"+str(i)+".sh")
		with open(shellscript,'r') as f:
			contents = f.read()
			contents = contents.replace("XCount",str(i))
			contents = contents.replace("Xpart",str(j+1))
		with open(shellscript,'w') as f:
			f.write(contents)
		print(" ")


# Sumbission
for i in range(100):
	for j in range(3):
		if (i>=0 and i<10):
			cmd= '/usr/local/bin/qsub -e /disk02/usr6/sedi/LENtuple/NQSLog/err.Count00'+str(i)+'.part00'+str(j+1)+'.skip.log -o /disk02/usr6/sedi/LENtuple/NQSLog/Count00'+str(i)+'.part00'+str(j+1)+'.log \"./NQS_SKDETSIM/run_skdetsim.Count00'+str(i)+'.part00'+str(j+1)+'.sh\"'
			print("[### SKDETSIM ###] Execution of "+cmd)
			#os.system(cmd)
			time.sleep(1)
		if (i>=10):
			cmd= '/usr/local/bin/qsub -e /disk02/usr6/sedi/LENtuple/NQSLog/err.Count0'+str(i)+'.part00'+str(j+1)+'.skip.log -o /disk02/usr6/sedi/LENtuple/NQSLog/Count0'+str(i)+'.part00'+str(j+1)+'.log \"./NQS_SKDETSIM/run_skdetsim.Count0'+str(i)+'.part00'+str(j+1)+'.sh\"'
			print("[### SKDETSIM ###] Execution of "+cmd)
			#os.system(cmd)
			time.sleep(1)

#cmd= '/usr/local/bin/qsub \"./NQS_SKDETSIM/run_skdetsim.Count0.sh\"'
#print("[###### SKDETSIM ######] Execution of "+cmd)
#os.system(cmd)