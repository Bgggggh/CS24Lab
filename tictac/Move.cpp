#include "Errors.h"
#include "Move.h"
#include <iostream>
using namespace std;
#include <sstream>
// Space for implementing Move functions.

Move::Move(){
    number = 1;
    player = 'X';
    row = 'A';
    column = 1;
}

Move::Move(const std::string& input) {
    if(input.length() < 6){
        throw ParseError("length is less than 6.");
    }
    istringstream is (input);
    
    string num;
    char num1;
    is >> num;
    if(num.length() != 1){
        throw ParseError("Digit error.");
    }
    else{
        num1 = num.at(0);
    }
    if((!(isdigit(num1))) || (!(((int)(num1) > 48) && ((int)(num1) < 58))) || (num1 != input[0])){
        throw ParseError("digit error");
    }
    else{
        number = (int)(num1) - 48;
        //define number
    }
    
    string play;
    char nplay;
    is >> play;
    if(play.length() != 1){
        throw ParseError("not X or O");
    }
    else{
        nplay = play.at(0);
    }
    if((nplay != 'X') && (nplay != 'x') && (nplay != 'O') && (nplay != 'o')){
        throw ParseError("The second element is not a X or O");
    }
    else{
        player = toupper(nplay);
        //define player
    }
    
    string square;
    is >> square;
    if(square.length() != 2){
        throw ParseError("location problems");
    }
    else{
        if((square.at(0) != 'A') && (square.at(0) != 'a') && (square.at(0) != 'B') && (square.at(0) != 'b') && (square.at(0) != 'C') && (square.at(0) != 'c')){
            throw ParseError("row problem");
        }
        else{
            row = toupper(square.at(0));
            //define row
        }
        if(square.at(1) != '1' && square.at(1) != '2' && square.at(1) != '3'){
            throw ParseError("column problem");
        }
        else{
            column = (int)(square.at(1)) - 48;
            //define column
        }
    }
    
    string comment;
    is >> comment;
    if(comment.length() != 0){
        if (comment.at(0) != '#'){
            throw ParseError("comments need #");
        }
    }
}

std::ostream& operator << (std::ostream& stream, const Move& move) {
    stream << move.number << " "<< move.player << " " << move.row << move.column;
    return stream;
}
