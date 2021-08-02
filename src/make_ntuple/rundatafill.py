#!/usr/bin/env python
import os,sys,string, stat
from glob import glob

def main():
    #t2kskrun={1:[66251,66945],2:[67877,68208],3:[69511,69753],4:[70524,71245]}
    t2kskrun={4:[70524,71245]}
    
    pwddir = os.getcwd()
    scriptdir = "%s/script" %(pwddir)

    if os.path.exists(scriptdir):
        print "scriptdir is %s" %(scriptdir)
    else :
        cmd = "mkdir %s" %(scriptdir)
        print cmd
        os.system(cmd)
        print "scriptdir is %s" %(scriptdir)

    pdir="/disk/usr4/cnantais/lowedata"
        
    idir="%s/lowfit/" %(pdir)
    ofdir="%s/ntuple/" %(pdir)
 
    if os.path.exists(ofdir):
        print "ofdir is %s" %(ofdir)
    else :
        cmd = "mkdir %s" %(ofdir)
        print cmd
        os.system(cmd)
        print "ofdir is %s" %(ofdir)
    
    outdir="%s/out/" %(ofdir)
    errdir="%s/err/" %(ofdir)

    if os.path.exists(outdir):
        print "outdir is %s" %(outdir)
    else :
        cmd = "mkdir %s" %(outdir)
        print cmd
        os.system(cmd)
        print "outdir is %s" %(outdir)

    if os.path.exists(errdir):
        print "outdir is %s" %(errdir)
    else :
        cmd = "mkdir %s" %(errdir)
        print cmd
        os.system(cmd)
        print "outdir is %s" %(errdir)

    subfile = "nqs_list_alldata"
    fsub = open(subfile,'w')

    permission = stat.S_IRWXU | stat.S_IRGRP | stat.S_IXGRP
    #start to creat script file if there are no script file there
    for t2krun in t2kskrun.keys():
        print "T2K Run %d analysis............" %(t2krun)
        startskrun = t2kskrun[t2krun][0]
        endskrun   = t2kskrun[t2krun][1]
        for skRun in range(startskrun,endskrun+1):
            run4 = int(skRun/100)
            reducdir = "%s/run%d" %(idir, skRun)
            ntupledir = "%s/run%d" %(ofdir, skRun)
            if os.path.exists(reducdir):
                print "SK Run %d.... dir is %s" %(skRun, reducdir)
                if os.path.exists(ntupledir):
                    print "Out %d.... dir is %s" %(skRun, ntupledir)
                else :
                    cmd ="mkdir %s" %(ntupledir)
                    print cmd
                    os.system(cmd)
                    print "Out %d.... dir is %s" %(skRun, ntupledir)
            else :
                continue
            
            for subrun in range(2000):
                if subrun%200==0:
                    
                    cshnum = int(subrun/200)
                    cshnum += 1
                    cshfname = "%s/sample_%06d_%d.csh" % (scriptdir,skRun, cshnum)
                    
                    csfile = open(cshfname, "w")
                    csfile.write("#!/bin/csh -f\n")
                    csfile.write("\n")

                    #writestr = "source ~ahimmel/skenv.csh\n"
                    #writestr = "source /home/huangkx/t2k/alex/ncgamma/alexenv.csh\n"
                    writestr = "source /home/cnantais/ncgamma/alexenv.csh\n"
                    csfile.write(writestr)
               
                    #csfile.write("cd /home/huangkx/t2k/alex/ncgamma/make_ntuple \n")
                    csfile.write("cd /home/cnantais/ncgamma/make_ntuple \n")
                    csfile.write("\n")
                    
                    csfile.write("echo $PWD")
                    csfile.write("\n")

                infname = "%s/data.lowfit.%d.%d.root" %(reducdir, skRun, subrun)
                if os.path.exists(infname)==True :
                    outfname = "%s/data.%d.%d.root" %(ntupledir, skRun, subrun)
                    tmpstr = "%s/RunNtupleMaker.sh %s %s\n" %(pwddir, infname, outfname)
                    csfile.write(tmpstr)
                    
                icount = subrun+1
                if icount%200==0:
                    csfile.close()
                    cshnum = icount/200
            
                    outname = "%s/out/out_%d_%d" %(ofdir,skRun, cshnum) 
                    errname = "%s/err/err_%d_%d" %(ofdir,skRun, cshnum)
                
                    cmd = "chmod 755 %s" %(cshfname)
                    print cmd
                    os.system(cmd)

                
                    
                    print >>fsub, "qsub  -q all -o %s -e %s %s" %(outname, errname, cshfname)

    fsub.close()
            
    cmd = "chmod 751 %s" %(subfile) 
    os.system(cmd)
    print "Finish......"
    return

if __name__=='__main__':
    main() 
