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
    if(arr.size() == 0){
        //cout << "Game in progress: New game." << endl;
        return true;
    }
}

char Board::check_order(const Move& move){
    if(n != move.number){
        throw InvalidMove("the number order is incorrect");
        //check the number order: 1, 2, 3, 4, 5.....
    }
    if(move.number == 1){
        first_player = move.player;
    }
    
    if((arr.size())%2 != 0){
        int x = 0;
        for(int i = 1; i < 4; ++i){
            for(int i; int m = 1; i < 4; ++m){
                if(arr[i][m] == 'X'){
                    x += 1;
                }
            }
        }
        if(x > arr.size()/2){
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
    
    for(int i = 1; i < 4; ++i){
        if(arr[i][1] == arr[i][2] == arr[i][3]){
            if(arr[i][i] == 'X'){
                //cout << "Game over: X wins." << endl;
                return 'X';
            }
            else{
                //cout << "Game over: O wins." << endl;
                return 'O';
            }
        }
        else if(arr[1][i] == arr[2][i] == arr[3][i]){
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
    if(arr[1][1] == arr[2][2] == arr[3][3]){
        if(arr[2][2] == 'X'){
            //cout << "Game over: X wins." << endl;
            return 'X';
        }
        else{
            //cout << "Game over: O wins." << endl;
            return 'O';
        }
    }
    else if(arr[1][3] == arr[2][2] == arr[3][1]){
        if(arr[2][2] == 'X'){
            //cout << "Game over: X wins." << endl;
            return 'X';
        }
        else{
            //cout << "Game over: O wins." << endl;
            return 'O';
        }
    }
}

bool Board::check_draw(){
    //check it when arr.size() == 9
    if((void Board::check_win() != "Game over: X wins.") && (void Board::check_win() != "Game over: O wins.")){
        //cout << "Game over: Draw." << endl;
        return true;
    }
}

void Board::print_result() {
    char winner = Board::check_win();
    if(winner != ' ') {
        cout << "Game over: " << winner << "wins.\n";
    }
    else if(check_draw()) {
        cout << "Game over: Draw.";
    }
    else if(check_over()){
        cout << cout << "Game in progress: New game.";
    }
    else if(check_order() == '0'){
        cout << "Game in progress: O's turn.";
    }
    else if(check_order() == '1'){
        cout << "Game in progress: X's turn.";
    }
}
