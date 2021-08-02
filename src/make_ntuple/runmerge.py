#!/usr/bin/env python
import os,sys,string, stat
from glob import glob

def main():
    #t2kskrun={1:[66251,66945],2:[67877,68208],3:[69511,69753],4:[70524,71245]}
    t2kskrun={4:[70524,71245]}
    
    pwddir = os.getcwd()
    scriptdir = "%s/script" %(pwddir)
 
  
    rootfdir="/disk/usr4/cnantais/lowedata/ntuple"
 
    
    subfile = "nqs_list_merge"
    fsub = open(subfile,'w')

    permission = stat.S_IRWXU | stat.S_IRGRP | stat.S_IXGRP
    #start to creat script file if there are no script file there
    for t2krun in t2kskrun.keys():
        print "T2K Run %d analysis............" %(t2krun)
        startskrun = t2kskrun[t2krun][0]
        endskrun   = t2kskrun[t2krun][1]
        for skRun in range(startskrun,endskrun+1):
            
            ntupledir = "%s/run%d" %(rootfdir, skRun)
            if os.path.exists(ntupledir):
                
                print "Out %d.... dir is %s" %(skRun, ntupledir)
                cshfname = "%s/merge_%06d.csh" % (scriptdir,skRun)
                csfile = open(cshfname, "w")
                csfile.write("#!/bin/csh -f\n")
                csfile.write("\n")
                    
                writestr = "source ~ahimmel/skenv.csh\n"
                csfile.write(writestr)
                
                writestr = "cd %s \n" %(pwddir)
                csfile.write(writestr)
                csfile.write("\n")
                
                csfile.write("echo $PWD")
                csfile.write("\n")
                
                

                rootform = "%s/data.%d.*.root" %(ntupledir, skRun)
                rootlist = glob(rootform)
                rootlist.sort()
                numroot = len(rootlist)
                nummerge = 1 + int(numroot/200.0)
                merfname =[]
                merexe =[]
                for im in range(nummerge):
                    substr="%s/data.lowfit.run%d.submerge%d.root" %(ntupledir, skRun, im)
                    if os.path.exists(substr):
                        cmd = "rm %s" %(substr)
                        print cmd
                        os.system(cmd)
                        
                    merfname.append(substr)
                    tmpstr = "hadd -f %s " %( substr)
                    merexe.append(tmpstr)
                    
                    
                #mergername = "data.lowfit.run%d.merge.root" %(skRun, )
                #tmpstr = "hadd -f %s " %(mergername)
                
                for ir in range(numroot):
                    icount = int(ir/200.0)
                    tmpstr =  merexe[icount] +" "+rootlist[ir]
                    merexe[icount] =tmpstr
                    

                for ime in range(nummerge):
                    tmpstr = merexe[ime] +"\n"
                    merexe[ime] = tmpstr
                    csfile.write(merexe[ime])
                    
                tmpstr = "\n"
                csfile.write(tmpstr)

                fmername = "%s/data.lowfit.%d.merge.root" %(rootfdir,skRun)
                if os.path.exists(fmername):
                    cmd = "rm %s" %(fmername)
                    print cmd
                    os.system(cmd)
                    
                exestr = "hadd -f %s " %(fmername)
                for ime in range(nummerge):
                    tmpstr = exestr + " " +merfname[ime]
                    exestr = tmpstr
                     

                tmpstr = exestr+"\n"
                csfile.write(tmpstr)
            
                csfile.close()
                
                    
                outname = "%s/out/out_merge%d" %(rootfdir, skRun) 
                errname = "%s/err/err_merge%d" %(rootfdir ,skRun)
                    
                cmd = "chmod 755 %s" %(cshfname)
                print cmd
                os.system(cmd)
                    
                
                    
                print >>fsub, "qsub -q lowe -o %s -e %s %s" %(outname, errname, cshfname)

    fsub.close()

    cmd = "chmod 751 %s" %(subfile)
    os.system(cmd)            
                
    print "Finish......"
    return

if __name__=='__main__':
    main() 
