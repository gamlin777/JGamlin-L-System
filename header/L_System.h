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

	L_System(){
		DEFAULT_LENGTH = 2.0f;
		DEFAULT_ITERATIONS = 3;
		TURN_VALUE = 90.0f;
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