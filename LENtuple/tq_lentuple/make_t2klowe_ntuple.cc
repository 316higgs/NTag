#include "NtupleMaker.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "apmueC.h"
#include "runsummanager.h"
#include "prm.h"

#define dbg( x )   std::cerr << "DBG " << x << '\n'
#define dump( x )  std::cerr << x << '\n'
#define watch( x ) std::cerr << (#x) << " = " << x << '\n'

using namespace std;

void help();

int main(int argc, char **argv) {
    char *infile = NULL;
    char *outfile = NULL;
    char *sbifile = NULL;
    char *inlogfile = NULL;
    char *outlogfile = NULL;
    string rsfilename = "/disk02/usr6/fiacob/ncneut/tq_lentuple/runsum";
    int maxevent = 999999;
	char *ambepos = NULL;
    bool isMC = true;
    char c;
    bool verbose = false;

    opterr = 0;
    
    //Input file names and other info from arguments in command
    while ((c=getopt(argc, argv, "i:o:n:h:v:a:")) != -1) {
        switch (c) {
        case 'i':
            infile = optarg;
            cout << "infile  = " << infile << endl;
            break;
        case 'o':
            outfile = optarg;
            cout << "outfile = " << outfile << endl;
            break;
        case 'n':
            maxevent = atoi(optarg);
            cout << "nevents = " << maxevent << endl;
            break;
		case 'a':
			ambepos = optarg;
			cout << "ambepos = " << ambepos << endl;
			break;
        case 'v':
            verbose = true;
            break;
        case 'h':
            help();
            break;
        case '?':
            if (optopt == 'i' || optopt == 'o' || optopt == 'n' || optopt == 's' || optopt == 'l' || optopt == 'L' )
                 fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
                 fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
                 fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default:
            abort ();
        }
    }//argument while

          
    //for (index = optind; index < argc; index++)
    //    printf ("Non-option argument %s\n", argv[index]);

    //No any arguments, show help
    if (infile == NULL || outfile == NULL) {
        help();
    }

    //create NtupleMaker object
    NtupleMaker *nt = new NtupleMaker();
    //Open input file with given argument(infile) (See NtupleMaker.cc)
    nt->OpenInfile(infile);

    //create output file name with given argument(outfile) and TTree named h1 (See NtupleMaker.cc)
    nt->OpenOutfile(outfile);

    //Display given configuration of AmBe data(ambepos) (See NtupleMaker.cc)
	nt->SetAmbePosition(ambepos); // fiacob 2020/02/20

    //nt->OpenSbifile(sbifile);
    //nt->OpenInlogfile(inlogfile);
    //nt->OpenOutlogfile(outlogfile);
    read_runsum(rsfilename);

    if (verbose) nt->SetVerbose(); //See NtupleMaker.h
    
    int nread = 0; //event counter
    for (int event=0; event<maxevent; event++) {
        fprintf(stderr, "[##### make_t2klowe_ntuple #####]  *** GOING TO READ EVENT %d\n", nread);
        fprintf(stderr, "[##### make_t2klowe_ntuple #####]  *** event numbering from 0\n");

        //bool NtupleMaker::ReadNextEvent() (See NtupleMaker.cc)
        //If ReadNextEvent returns false, break.
        //In ReadNextEvent, ReadMCEvent is called and BONSAI or fiTQun vertex is input in this function.
	    if (!nt->ReadNextEvent()) break; //break end of file

        //Fill TTree(named h1) of output file
        nt->SaveToTree();
	    nread++;

	    //if ( nread % 100 == 0) cout << "Events scanned: " << nread << endl;
    }//event loop
    
    //Write TTree in output file (See NtupleMaker.cc)
    nt->Finish();

    kill_runsum();

    cout << "[##### make_t2klowe_ntuple #####]  Likelihood failures(Fail/All): " << nt->like_fail << "/" << nt->like_all << endl;

    cout << "[##### make_t2klowe_ntuple #####]  Successfully finished. " << endl;
    
    return 0;
}//main()


void help() {
    std::cout << "Command format is: " << std::endl;
    cout << "make_t2klowe_ntuple -i <infile.zbs> -o <outfile.root> [ -n <number of events> ] [ -a <ambe position> ]" << endl;
    exit(1);
}
