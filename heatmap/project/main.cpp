#include<iostream>

#include "Board.h"

int main(){

  Board game(11);
  game.fillRandom(50);


  std::cout<<game.getColor(Position(3, 4))<<"\n";

  return 0;
}
