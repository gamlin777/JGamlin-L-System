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

	int lsFileKey;
	int DEFAULT_ITERATIONS;
	float TURN_VALUE;
	string RULE;
	string AXIOM;
	string NODE;
	string NODE_RULE;

	// the following strings are used to to record the data from the config files.
	string ex6_line1_it;
	string ex6_line2_ang;
	string ex6_line3_ax;
	string ex6_line4_r1;
	string ex6_line5_n;
	string ex6_line6_r2;

	string ex5_line1_it;
	string ex5_line2_ang;
	string ex5_line3_ax;
	string ex5_line4_r1;
	string ex5_line5_n;
	string ex5_line6_r2;
	
	string ex4_line1_it;
	string ex4_line2_ang;
	string ex4_line3_ax;
	string ex4_line4_r1;
	string ex4_line5_n;
	string ex4_line6_r2;

	string ex3_line1_it;
	string ex3_line2_ang;
	string ex3_line3_ax;
	string ex3_line4_r1;
	string ex3_line5_n;
	string ex3_line6_r2;

	string ex2_line1_it;
	string ex2_line2_ang;
	string ex2_line3_ax;
	string ex2_line4_r1;
	string ex2_line5_n;
	string ex2_line6_r2;

	string ex1_line1_it;
	string ex1_line2_ang;
	string ex1_line3_ax;
	string ex1_line4_r1;
	string ex1_line5_n;
	string ex1_line6_r2;


float getTurnValue() { return TURN_VALUE; }
int getIterations() { return DEFAULT_ITERATIONS; }
string getRule() { return RULE; }
string getAxiom() { return AXIOM; }
string getNode() { return NODE; }
string getNodeRule() { return NODE_RULE; }
	
L_System(){ //Contructor
	ifstream ifile;

			//Collects all the data from the config files
			ifile.open("config/example1.txt");

			getline(ifile, ex1_line1_it);
			getline(ifile, ex1_line2_ang);
			getline(ifile, ex1_line3_ax);
			getline(ifile, ex1_line4_r1);
			getline(ifile, ex1_line5_n);
			getline(ifile, ex1_line6_r2);
			
			ifile.close();

			ifile.open("config/example2.txt");

			getline(ifile, ex2_line1_it);
			getline(ifile, ex2_line2_ang);
			getline(ifile, ex2_line3_ax);
			getline(ifile, ex2_line4_r1);
			getline(ifile, ex2_line5_n);
			getline(ifile, ex2_line6_r2);
			
			ifile.close();

			ifile.open("config/example3.txt");

			getline(ifile, ex3_line1_it);
			getline(ifile, ex3_line2_ang);
			getline(ifile, ex3_line3_ax);
			getline(ifile, ex3_line4_r1);
			getline(ifile, ex3_line5_n);
			getline(ifile, ex3_line6_r2);

			ifile.close();

			ifile.open("config/example4.txt");

			getline(ifile, ex4_line1_it);
			getline(ifile, ex4_line2_ang);
			getline(ifile, ex4_line3_ax);
			getline(ifile, ex4_line4_r1);
			getline(ifile, ex4_line5_n);
			getline(ifile, ex4_line6_r2);

			ifile.close();

			ifile.open("config/example5.txt");

			getline(ifile, ex5_line1_it);
			getline(ifile, ex5_line2_ang);
			getline(ifile, ex5_line3_ax);
			getline(ifile, ex5_line4_r1);
			getline(ifile, ex5_line5_n);
			getline(ifile, ex5_line6_r2);
			
			ifile.close();

			ifile.open("config/example6.txt");

			getline(ifile, ex6_line1_it);
			getline(ifile, ex6_line2_ang);
			getline(ifile, ex6_line3_ax);
			getline(ifile, ex6_line4_r1);
			getline(ifile, ex6_line5_n);
			getline(ifile, ex6_line6_r2);

			ifile.close();
	load(1);
	};

	void load(int lsFile)
	{
		lsFileKey = lsFile;
	// depending on the current F-Key pressed, it will change the lsystem
			if (lsFileKey == 1){
				DEFAULT_ITERATIONS = ::atoi(ex1_line1_it.c_str());
				TURN_VALUE = ::atof(ex1_line2_ang.c_str());
				RULE = ex1_line4_r1;
				AXIOM = ex1_line3_ax;
				NODE = ex1_line5_n;
				NODE_RULE = ex1_line6_r2;
			} else if(lsFileKey == 2) {
				DEFAULT_ITERATIONS = ::atoi(ex2_line1_it.c_str());
				TURN_VALUE = ::atof(ex2_line2_ang.c_str());
				RULE = ex2_line4_r1;
				AXIOM = ex2_line3_ax;
				NODE = ex2_line5_n;
				NODE_RULE = ex2_line6_r2;
			} else if(lsFileKey == 3) {
				DEFAULT_ITERATIONS = ::atoi(ex3_line1_it.c_str());
				TURN_VALUE = ::atof(ex3_line2_ang.c_str());
				RULE = ex3_line4_r1;
				AXIOM = ex3_line3_ax;
				NODE = ex3_line5_n;
				NODE_RULE = ex3_line6_r2;
			} else if(lsFileKey == 4) {
				DEFAULT_ITERATIONS = ::atoi(ex4_line1_it.c_str());
				TURN_VALUE = ::atof(ex4_line2_ang.c_str());
				RULE = ex4_line4_r1;
				AXIOM = ex4_line3_ax;
				NODE = ex4_line5_n;
				NODE_RULE = ex4_line6_r2;
			} else if(lsFileKey == 5) {
				DEFAULT_ITERATIONS = ::atoi(ex5_line1_it.c_str());
				TURN_VALUE = ::atof(ex5_line2_ang.c_str());
				RULE = ex5_line4_r1;
				AXIOM = ex5_line3_ax;
				NODE = ex5_line5_n;
				NODE_RULE = ex5_line6_r2;
			} else if(lsFileKey == 6) {
				DEFAULT_ITERATIONS = ::atoi(ex6_line1_it.c_str());
				TURN_VALUE = ::atof(ex6_line2_ang.c_str());
				RULE = ex6_line4_r1;
				AXIOM = ex6_line3_ax;
				NODE = ex6_line5_n;
				NODE_RULE = ex6_line6_r2;
			}
	}
};