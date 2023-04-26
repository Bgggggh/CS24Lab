#include "Errors.h"
#include "Board.h"
#include <iostream>
using namespace std;
// Space for implementing Board functions.

Board::Board()
{
    for(int i = 0; i < 3; ++i){
        for(int m = 0; m < 3; m++){
            arr[i][m] = ' ';
        }
    }
        this->n=0;
        this -> first_player = ' ';
        this -> previous_player = ' ';
}
void Board::add_info(const Move& move){
    if(move.row == 'A'){
        row = 0;
    }
    else if(move.row == 'B'){
        row = 1;
    }
    else{
        row = 2;
    }
    if(arr[row][move.column - 1] != ' '){
        
        throw InvalidMove("this location is occupied");
    }
    arr[row][move.column - 1] = move.player;
    n += 1;
    
}

bool Board::check_over(){
    if(n == 0){
        //cout << "Game in progress: New game." << endl;
        return true;
    } else {
        return false;
    }
    
}

char Board::check_order(const Move& move){
    if((n + 1) != move.number){
        cout << n <<' ' << move.number << endl;
        throw InvalidMove("the number order is incorrect");
        //check the number order: 1, 2, 3, 4, 5.....
    }
    if(move.number == 1){
        first_player = move.player;
    }
    
    if(previous_player == move.player){
        throw InvalidMove("it is an incorrect order");
    }
    
    previous_player = move.player;
    if(previous_player == 'X'){
        return '1';
    }
    else{
        return '0';
    }
    //check the X or O order
}

char Board::check_win(){
    
    for(int i = 0; i < 3; ++i){
        if((arr[i][0] == arr[i][1]) && (arr[i][1] == arr[i][2]) && (arr[i][0] != ' ')){
            if(arr[i][i] == 'X'){
                //cout << "Game over: X wins." << endl;
                return 'X';
            }
            else{
                //cout << "Game over: O wins." << endl;
                return 'O';
            }
        }
        else if((arr[0][i] == arr[1][i]) && (arr[1][i] == arr[2][i]) && (arr[0][i] != ' ')){
            if(arr[i][i] == 'X'){
                //cout << "Game over: X wins." << endl;
                return 'X';
            }
            else{
                //cout << "Game over: O wins." << endl;
                return 'O';
            }
        }
    }
    if((arr[0][0] == arr[1][1]) && (arr[1][1] == arr[2][2]) && (arr[0][0] != ' ')){
        if(arr[1][1] == 'X'){
            //cout << "Game over: X wins." << endl;
            return 'X';
        }
        else{
            //cout << "Game over: O wins." << endl;
            return 'O';
        }
    }
    else if((arr[0][2] == arr[1][1]) && (arr[1][1] == arr[2][0]) && (arr[1][1] != ' ')){
        if(arr[1][1] == 'X'){
            //cout << "Game over: X wins." << endl;
            return 'X';
        }
        else{
            //cout << "Game over: O wins." << endl;
            return 'O';
        }
    }
    return 'm';
}

bool Board::check_draw(){
    //check it when arr.size() == 9
    return ((check_win() != 'X') && (check_win() != 'O') && (n == 9));
}

void Board::print_result(const Move& move) {
    char winner = check_win();
    if(winner != 'm') {
        cout << "Game over: " << winner << " wins.\n";
    }
    else if(check_draw()) {
        cout << "Game over: Draw.\n";
    }
    else if(check_over()){
        cout << "Game in progress: New game.\n";
    }
    else if(check_order(move)== '0'){
        cout << "Game in progress: O's turn.\n";
    }
    else if(check_order(move) == '1'){
        cout << "Game in progress: X's turn.\n";
    }
}

