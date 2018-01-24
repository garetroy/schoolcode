#include <stdio.h>
#include "PNMwriterCPP.h"
using namespace std;
void
PNMwriter::Write(char *filename){
	ofstream outfile (filename);
	outfile << imagein1->GetMagicNum() << endl;
	outfile << imagein1->GetWidth() << ' ' << imagein1->GetHeight() << endl;
	outfile << imagein1->GetMaxVal() << endl;
	int size = imagein1->GetWidth() * imagein1->GetHeight();
    outfile.write((reinterpret_cast<char *>)(imagein1->GetPixels()),size*3);
    outfile.close();
}

