#include "NtupleMaker.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void help();

int main(int argc, char **argv)
{
    char *infile = NULL;
    char *outfile = NULL;
    int maxevent = 999999;
    bool isMC = true;
    char c;
    bool verbose = false;

    opterr = 0;
     
    while ((c = getopt (argc, argv, "i:o:n:hv")) != -1)
        switch (c) {
        case 'i':
            infile = optarg;
            cout << "infile " << infile << endl;
            break;
        case 'o':
            outfile = optarg;
            cout << "outfile " << outfile << endl;
            break;
        case 'n':
            maxevent = atoi(optarg);
            cout << "nevents " << maxevent << endl;
            break;
        case 'v':
            verbose = true;
            break;
        case 'h':
            help();
            break;
        case '?':
            if (optopt == 'i' || optopt == 'o' || optopt == 'n')
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
          
    //for (index = optind; index < argc; index++)
    //    printf ("Non-option argument %s\n", argv[index]);


    if ( infile == NULL || outfile == NULL ) {
        help();
    }

    

    NtupleMaker *nt = new NtupleMaker();
    nt->OpenInfile(infile);
    nt->OpenOutfile(outfile);
    
    if (verbose) nt->SetVerbose();
    
    int nread = 0;
    for (int event = 0; event < maxevent; event++)
    {
	if ( ! nt->ReadNextEvent() ) break; //break end of file
        nt->SaveToTree();

	nread++;
	if ( nread % 100 == 0) cout << "Events scanned: " << nread << endl;
    }
    
    nt->Finish();

    cout << "Likelihood failures: " << nt->like_fail << "/" << nt->like_all << endl;

    cout << "Successfully finished. " << endl;
    
    return 0;
}


void help() 
{
    cout << "make_t2klowe_ntuple -i <infile> -o <outfile> [ -n <number of events ]" << endl;
    exit(1);
}
