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

int main(int argc, char **argv)
{
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
     
    while ((c = getopt (argc, argv, "i:o:n:h:v:a:")) != -1) {
        switch (c) {
        case 'i':
            infile = optarg;
            cout << "infile     = " << infile << endl;
            break;
        case 'o':
            outfile = optarg;
            cout << "outfile    = " << outfile << endl;
            break;
        case 'n':
            maxevent = atoi(optarg);
            cout << "nevents    = " << maxevent << endl;
            break;
		case 'a':
			ambepos = optarg;
			cout << "ambepos    = " << ambepos << endl;
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
                 fprintf (stderr,
                          "Unknown option character `\\x%x'.\n",
                          optopt);
            return 1;
        default:
            abort ();
        }
    }
          
    //for (index = optind; index < argc; index++)
    //    printf ("Non-option argument %s\n", argv[index]);


    if ( infile == NULL || outfile == NULL ) {
        help();
    }

    

    NtupleMaker *nt = new NtupleMaker();
    nt->OpenInfile(infile);
    nt->OpenOutfile(outfile);
	nt->SetAmbePosition( ambepos ); // fiacob 2020/02/20
    //nt->OpenSbifile(sbifile);
    //nt->OpenInlogfile(inlogfile);
    //nt->OpenOutlogfile(outlogfile);
    read_runsum( rsfilename );

    if (verbose) nt->SetVerbose();
    
    int nread = 0;
    for (int event = 0; event < maxevent; event++) {
        fprintf( stderr, "*** GOING TO READ EVENT %d\n", nread );
        fprintf( stderr, "*** event numbering from 0\n" );
	    if (!nt->ReadNextEvent()) break; //break end of file
        if(inPMT) nt->SaveToTree();
        //nt->SaveToTree();
        std::cout << "nread: " << nread << std::endl;
	    nread++;
	    //if ( nread % 100 == 0) cout << "Events scanned: " << nread << endl;
    }
    
    nt->Finish();
    kill_runsum();

    cout << "Likelihood failures: " << nt->like_fail << "/" << nt->like_all << endl;

    cout << "Successfully finished. " << endl;
    
    return 0;
}


void help() 
{
    cout << "make_t2klowe_ntuple -i <infile.zbs> -o <outfile.root> [ -n <number of events> ] [ -a <ambe position> ]" << endl;
    exit(1);
}
