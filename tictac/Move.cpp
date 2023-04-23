#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.

Move::Move(const std::string& input) {
    if(input.length() < 6){
        throw ParseError("length is less than 6.");
    }
    if((!(isdigit(input[0]))) || (input[0] == 0)){
        throw ParseError("The first element is not a digit.");
    }
    if(!(isspace(input[1]))){
        throw ParseError("The second element is not a whitespace");
    }
    if((input[2] != 'X') && (input[2] != 'x') && (input[2] != 'O') && (input[2] != 'o')){
        throw ParseError("The third element is not a X or O");
    }
    if(!(isspace(input[3]))){
        throw ParseError("The fourth element is not a whitespace.");
    }
    if((input[4] != 'A') && (input[4] != 'a') && (input[4] != 'B') && (input[4] != 'b') && (input[4] != 'C') && (input[4] != 'c')){
        throw ParseError("The fifth element is not A or B or C.");
    }
    if(!isdigit(input[5])){
        throw ParseError("The sixth element is not a digit.");
    }
    
    if((input.find("#")) && (!(isspace(input[6])))){
        throw ParseError("The seventh element is not a whitespace.");
    }
    if((input.length() > 7) && (input[7] != '#')){
        throw ParseError("The eighth elment is not a #");
    }
    
    number = stoi(input.substr(0,1));
    player = toupper(input[2]);
    row = toupper(input[4]);
    column = stoi(input.substr(5, 1));
    
    
}

std::ostream& operator << (std::ostream& stream, const Move& move) {
    stream << move.number << " "<< move.player << " " << move.row << move.column << std::endl;
    return stream;
}
