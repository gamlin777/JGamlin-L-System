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
	
float length() { return DEFAULT_LENGTH; }
	
	L_System(){
		DEFAULT_LENGTH = 4.0f;
		DEFAULT_ITERATIONS = 3;
		TURN_VALUE = 90.0f;
		FORWARD_DRAW_F = 'F';
		FORWARD_DRAW_X = 'X';
		FORWARD_NO_DRAW_F = 'f';
		FORWARD_NO_DRAW_X = 'x';
		SYMBOL_TURN_LEFT = '+';
		SYMBOL_TURN_RIGHT = '-';

		string rule;
	}
};