#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.
class Board{
    
private:
    char arr[3][3];
    int n;
    int row;
    char first_player;
    
    
public:
    Board();
    bool check_over();
    char check_order(const Move& move);
    char check_win();
    bool check_draw();
    
    //helper function
    void add_info(const Move& move);
    
    void print_result(const Move& move);
};



#endif
