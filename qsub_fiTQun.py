#!/usr/bin/python
import os, shutil

# Current directory
TOPDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC"
# Run directory
RUNDIR="/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/NQS_fiTQun"


# Clean up
files = os.listdir(RUNDIR)
for i in range(len(files)):
	file = files[i]
	script = "run_fiTQun" in file
	if(script==True):
		os.remove(os.path.join(RUNDIR,file))
		print("[###### fiTQun ######] Clean up is done.")
	else:
		print("[###### fiTQun ######] No script file")
print(" ")


#print("Existence: "+str(os.path.exists(os.path.join(TOPDIR,"run_fiTQun.sh"))))
for i in range(100):
	for j in range(3):
		for k in range(20):
			if (os.path.exists(os.path.join(RUNDIR,"run_fiTQun.XCount.Xpart.Xskip.sh"))==True):
				os.remove(os.path.join(RUNDIR,"run_fiTQun.XCount.Xpart.Xskip.sh"))

			if (os.path.exists(os.path.join(TOPDIR,"run_fiTQun.sh"))==True):
				shutil.copy(os.path.join(TOPDIR,"run_fiTQun.sh"),os.path.join(RUNDIR,"run_fiTQun.XCount.Xpart.Xskip.sh"))
				#print("[###### fiTQun ######] File copied: run_fiTQun.XCount.Xpart.Xskip.sh")

				if (i<10):
					filename = "run_fiTQun.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(50*k)+".sh"
					#print("[###### fiTQun ######] File: run_fiTQun.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(k)+".sh is created.")
				if (i>=10):
					filename = "run_fiTQun.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(50*k)+".sh"
					#print("[###### fiTQun ######] File: run_fiTQun.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(k)+".sh is created.")

				os.rename(os.path.join(RUNDIR,"run_fiTQun.XCount.Xpart.Xskip.sh"),os.path.join(RUNDIR,filename))
			
				if (i<10):
					shellscript = os.path.join(RUNDIR,"run_fiTQun.Count00"+str(i)+".part00"+str(j+1)+".skip"+str(50*k)+".sh")
				if (i>=10):
					shellscript = os.path.join(RUNDIR,"run_fiTQun.Count0"+str(i)+".part00"+str(j+1)+".skip"+str(50*k)+".sh")
				with open(shellscript,'r') as f:
					contents = f.read()
					contents = contents.replace("XCount",str(i))
					contents = contents.replace("Xpart",str(j+1))
					contents = contents.replace("Xskip",str(50*k))
				with open(shellscript,'w') as f:
					f.write(contents)


# Sumbission
#for i in range(100):
	#for j in range(3):
		#for k in range(10):
			#if (i>=0 and i<10):
				#cmd= '/usr/local/bin/qsub -e /disk02/usr6/sedi/fiTQun/NQSLog/err.Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(k)+'.log -o /disk02/usr6/sedi/fiTQun/NQSLog/Count00'+str(i)+'.part00'+str(j+1)+'.skip'+str(k)+'.log \"./NQS_fiTQun/run_fiTQun.Count00'+str(i)+".part00"+str(j+1)+'.skip'+str(k)+'.sh\"'
				#print("[###### fiTQun ######] Execution of "+cmd)
				#os.system(cmd)
			#if (i>=10):
				#cmd= '/usr/local/bin/qsub -e /disk02/usr6/sedi/fiTQun/NQSLog/err.Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(k)+'.log -o /disk02/usr6/sedi/fiTQun/NQSLog/Count0'+str(i)+'.part00'+str(j+1)+'.skip'+str(k)+'.log \"./NQS_fiTQun/run_fiTQun.Count0'+str(i)+".part00"+str(j+1)+'.skip'+str(k)+'.sh\"'
				#print("[###### fiTQun ######] Execution of "+cmd)
				#os.system(cmd)

#for i in range(4,10):
	#cmd= '/usr/local/bin/qsub -e /disk02/usr6/sedi/fiTQun/NQSLog/err.Count000.part003.skip'+str(i)+'.log -o /disk02/usr6/sedi/fiTQun/NQSLog/Count000.part003.skip'+str(i)+'.log \"./NQS_fiTQun/run_fiTQun.Count000.part003.skip'+str(i)+'.sh\"'
	#print("[###### fiTQun ######] Execution of "+cmd)
	#os.system(cmd)

for i in range(3):
	cmd= '/usr/local/bin/qsub -e /disk02/usr6/sedi/fiTQun/NQSLog/err.Count000.part001.skip'+str(50*i)+'.log -o /disk02/usr6/sedi/fiTQun/NQSLog/Count000.part001.skip'+str(50*i)+'.log \"./NQS_fiTQun/run_fiTQun.Count000.part001.skip'+str(50*i)+'.sh\"'
	print("[###### fiTQun ######] Execution of "+cmd)
	os.system(cmd)

