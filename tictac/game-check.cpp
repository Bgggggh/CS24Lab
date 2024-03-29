#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>

int main(int argc, char** argv) {
  bool verbose = false;
  Board board;

  if(argc == 2 && std::string(argv[1]) == "-v") {
    verbose = true;
  }

  if(verbose) {
    std::cout << "> ";
  }

  std::string line;

  try {
      //Board board;
      Move move2;

      while(std::getline(std::cin, line)){
          Move move(line);
          move2 = move;
          
          board.add_info(move);
          board.check_over();
          
          board.check_win();
          
          board.check_order(move);
          
          board.check_draw();
          
          //board.add_info(move);
          
          
      }
      
    board.print_result(move2);
    return 0;
  }
  catch(const ParseError& e) {
    if(verbose) {
      std::cout << "Parse error: " << e.what() << '\n';
    }
    else {
      std::cout << "Parse error.\n";
    }
  

    return 1;
  }
    catch(const InvalidMove& f){
        if(verbose){
            std::cout << "Invalid move: " << f.what() << '\n';
        }
        else{
            std::cout << "Invalid move.\n";
        }
        return 2;
        
    }
   
}
