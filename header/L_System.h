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
	char FORWARD_DRAW_F;
	char FORWARD_DRAW_X;
	char FORWARD_NO_DRAW_F;
	char FORWARD_NO_DRAW_X;
	char SYMBOL_TURN_LEFT;
	char SYMBOL_TURN_RIGHT;
	char SYMBOL_POP;
	char SYMBOL_PUSH;
	
float getLength() { return DEFAULT_LENGTH; }
float getTurnValue() { return TURN_VALUE; }
int getIterations() { return DEFAULT_ITERATIONS; }
string getRule() { return RULE; }
string getAxiom() { return AXIOM; }

	L_System(){
		DEFAULT_LENGTH = 0.05f;
		DEFAULT_ITERATIONS = 5;
		TURN_VALUE = 25.7f;
		RULE = "F[+F]F[-F]F";
		AXIOM = "F";
		FORWARD_DRAW_F = 'F';
		FORWARD_DRAW_X = 'X';
		FORWARD_NO_DRAW_F = 'f';
		FORWARD_NO_DRAW_X = 'x';
		SYMBOL_TURN_LEFT = '+';
		SYMBOL_TURN_RIGHT = '-';
		SYMBOL_POP = ']';
		SYMBOL_PUSH = '[';

		string rule;
	}
};