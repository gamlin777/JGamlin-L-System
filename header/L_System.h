////////////////////////////////////////////////////////////////////////////////////////////////
// L-System Class
// By James Gamlin
////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
using namespace std;
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

class L_System
{
public:

	float DEFAULT_LENGTH;
	int DEFAULT_ITERATIONS;
	float TURN_VALUE;
	string RULE;
	string AXIOM;
	string NODE;
	string NODE_RULE;
	
float getLength() { return DEFAULT_LENGTH; }
float getTurnValue() { return TURN_VALUE; }
int getIterations() { return DEFAULT_ITERATIONS; }
string getRule() { return RULE; }
string getAxiom() { return AXIOM; }
string getNode() { return NODE; }
string getNodeRule() { return NODE_RULE; }

	L_System(){

			ifstream ifile;
			ifile.open("config/example1.txt"); // create an if statement and a counter that is cycleable to iterate files.
			string line1_it;
			string line2_ang;
			string line3_ax;
			string line4_r1;
			string line5_n;
			string line6_r2;


			getline(ifile, line1_it);
			getline(ifile, line2_ang);
			getline(ifile, line3_ax);
			getline(ifile, line4_r1);
			getline(ifile, line5_n);
			getline(ifile, line6_r2);
			
			ifile.close();

			DEFAULT_LENGTH = 0.5f;
			DEFAULT_ITERATIONS = ::atoi(line1_it.c_str());
			TURN_VALUE = ::atof(line2_ang.c_str());
			RULE = line4_r1;
			AXIOM = line3_ax;
			NODE = line5_n;
			NODE_RULE = line6_r2;

	}
};