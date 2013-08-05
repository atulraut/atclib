///////////////////////////////////////////////////////////////////////////////////////////
//	This program can determin very accurately the nature of the user input,
//	it detects whether it is an integer, a float, a number in scientific notation
//	or simply an invalid input. To be capable of doing this the program uses a simple FSM
//	(FINITE STATE MACHINE) to represent the possible states of the input.( INT, FLOAT,.. )
//	author: Gonzales Cenelia
///////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using std::cin;
using std::endl;
using std::cout;

//===========================================================================
//		the list of all the possible states for the current FSM
//===========================================================================
enum STATE{ START, INT, FLOAT, SCIENTIFIC, EXPONENT, S1, S2, INVALID } state;

STATE Transition( char *str );
void PrintState( STATE state );

int main() {
	// declaring buffer variable
	char buffer[32] = {0}; 
	// geting input from the user
	cout << "\nPlease enter a number: ";
	cin.getline( buffer, 32 );
	// compute final state
	STATE FINAL_STATE = Transition(buffer);
	// prints the final state
	PrintState(FINAL_STATE);
	return 0;
}

//================================================
// makes the transition from one state to another
//================================================
STATE Transition( char *str ) {
	int NEXT_SYMBOL;
	cout << "state = " << state <<endl;		
	for( ; *str && state != INVALID; str++ ) {
		NEXT_SYMBOL = *str;
		cout << "str = " << str <<endl;		
		switch(state) {
		case START:
			if(isdigit(NEXT_SYMBOL)) {
				state = INT;
			}
			else if( NEXT_SYMBOL == '+' || NEXT_SYMBOL == '-' ) {
				state = S1;
			}
			else if( NEXT_SYMBOL == '.' ) {
				state = FLOAT;
			}
			else {
				state = INVALID;
			}
			break;
		case S1:
			if(isdigit(NEXT_SYMBOL)) {
				state = INT;
			}
			else if( NEXT_SYMBOL == '.' ) {
				state = FLOAT;
			}
			else if(!isdigit(NEXT_SYMBOL)) {
				state = INVALID;
			}
			break;
		case INT:
			if( NEXT_SYMBOL == '.' ) {
				state = FLOAT;
			}
			else if(!isdigit(NEXT_SYMBOL)) {
				state = INVALID;
			}
			break;
		case FLOAT:
			if( NEXT_SYMBOL == 'E' || NEXT_SYMBOL == 'e' ) {
				state = S2;
			}
			else if(!isdigit(NEXT_SYMBOL)) {
				state = INVALID;
			}
			break;
		case S2:
			if( NEXT_SYMBOL == '+' || NEXT_SYMBOL == '-' ) {
				state = EXPONENT;
			}
			else {
				state = INVALID;
			}
			break;
		case EXPONENT:
			if(isdigit(NEXT_SYMBOL)) {
				state = SCIENTIFIC;
			}
			else {
				state = INVALID;
			}
			break;
		case SCIENTIFIC:
			if(!isdigit(NEXT_SYMBOL)) {
				state = INVALID;
			}
			break;
		}
	}
	return state;
}

//=====================================
// prints the current state of the FSM
//=====================================
void PrintState( STATE state ) {
	cout << "\nFSM state: ";
	switch(state) {
	case INT:
		cout << "INT \n";
		break;
	case FLOAT:
		cout << "FLOAT \n";
		break;
	case SCIENTIFIC:
		cout << "SCIENTIFIC \n";
		break;
	case INVALID:
		cout << "INVALID \n";
		break;
	}
	cout << "\n";
}







