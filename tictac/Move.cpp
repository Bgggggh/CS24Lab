#include "Errors.h"
#include "Move.h"
#include <iostream>
using namespace std;
#include <sstream>
// Space for implementing Move functions.

Move::Move(const std::string& input) {
    if(input.length() < 6){
        throw ParseError("length is less than 6.");
    }
    istringstream is (input);
    string num;
    is >> num;
    if(num.length() != 1){
        throw ParseError("Digit error.");
    }
    else{
        num = num.at(0);
    }
    if((!(isdigit(number))) || (!((number > 0) && (number < 10)))){
        throw ParseError("digit error");
    }
    else{
        number = stoi(num);
        //define number
    }
    
    string play, nplay;
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
        player = nplay;
        //define player
    }
    
    string square;
    is >> square;
    if(square.length() != 2){
        throw ParseError("location problems");
    }
    else{
        if((square.at(0) != 'A') && (square.at(0) != 'a') && (square.at(0) != 'B') && (square.at(0) != 'b') && (square.at(0) != 'C') && (square.at(0) != 'c')){
            throw ParseError("location problem1");
        }
        else{
            row = square.at(0);
            //define row
        }
        if(!isdigit(square.at(1))){
            throw ParseError("location problem2");
        }
        else{
            column = stoi(square.at(1));
            //define column
        }
    }
    
    if(input.find("#") > 0){
        if(!isspace(input[input.find("#") - 1])){
            throw ParseError("the former of # should be a whitespace");
        }
    }
    
    
}

std::ostream& operator << (std::ostream& stream, const Move& move) {
    stream << move.number << " "<< move.player << " " << move.row << move.column << std::endl;
    return stream;
}
