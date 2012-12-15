// L-System Class
// by James Gamlin

#include <string>
using namespace std;

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
		DEFAULT_LENGTH = 0.1f;
		DEFAULT_ITERATIONS = 5;
		TURN_VALUE = 22.5f;
		RULE = "F-[[X]+X]+F[+FX]-X";
		AXIOM = "X";
		NODE = "F";
		NODE_RULE = "FF";

		string rule;
	}
};