#include "Errors.h"
#include "Board.h"
#include <iostream>
using namespace std;
// Space for implementing Board functions.

void Board::add_info(const Move& move){
    if(move.row == 'A'){
        row = 1;
    }
    else if(move.row == 'B'){
        row = 2;
    }
    else{
        row = 3;
    }
    if(arr[row][move.column] != 0){
        throw InvalidMove("this location is occupied");
    }
    arr[row][move.column] = move.player;
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
        throw InvalidMove("the number order is incorrect");
        //check the number order: 1, 2, 3, 4, 5.....
    }
    if(move.number == 1){
        first_player = move.player;
    }
    
    if(n%2 != 0){
        int x = 0;
        for(int i = 0; i < 3; ++i){
            for( int m = 0; m < 3; ++m){
                if(arr[i][m] == 'X'){
                    x += 1;
                }
            }
        }
        if(x > n/2){
            if(move.player == 'X'){
                throw InvalidMove("the next step should be O");
            }
            //cout << "Game in progress: O's turn." << endl;
            return '0';
        }
        else{
            if(move.player == 'O'){
                throw InvalidMove("the next step should be X");
            }
            //cout << "Game in progress: X's turn." << endl;
            return '1';
        }
    }
    else{
        if(first_player == 'X'){
            //cout << "Game in progress: X's turn." << endl;
            return '1';
        }
        else{
            //cout << "Game in progress: O's turn." << endl;
            return '0';
        }
    }
    //check the X or O order
}

char Board::check_win(){
    
    for(int i = 0; i < 3; ++i){
        if((arr[i][0] == arr[i][1]) && (arr[i][1] == arr[i][2]) && (arr[i][0] != 0)){
            if(arr[i][i] == 'X'){
                //cout << "Game over: X wins." << endl;
                return 'X';
            }
            else{
                //cout << "Game over: O wins." << endl;
                return 'O';
            }
        }
        else if((arr[0][i] == arr[1][i]) && (arr[1][i] == arr[2][i]) && (arr[0][i] != 0)){
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
    if((arr[0][0] == arr[1][1]) && (arr[1][1] == arr[2][2]) && (arr[0][0] != 0)){
        if(arr[1][1] == 'X'){
            //cout << "Game over: X wins." << endl;
            return 'X';
        }
        else{
            //cout << "Game over: O wins." << endl;
            return 'O';
        }
    }
    else if((arr[0][2] == arr[1][1]) && (arr[1][1] == arr[2][0]) && (arr[1][1] != 0)){
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
    return ((check_win() != 'X') && (check_win() != 'O'));
}

void Board::print_result(const Move& move) {
    char winner = check_win();
    if(winner != 'm') {
        cout << "Game over: " << winner << "wins.\n";
    }
    else if(check_draw()) {
        cout << "Game over: Draw.";
    }
    else if(check_over()){
        cout << "Game in progress: New game.";
    }
    else if(check_order(move)== '0'){
        cout << "Game in progress: O's turn.";
    }
    else if(check_order(move) == '1'){
        cout << "Game in progress: X's turn.";
    }
}
