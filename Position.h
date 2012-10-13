#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include "Cell.h"

const int board_width = 3;
const int board_height = 3;
const int simbols_quantity_for_victory = 3;


struct CPosition
{
  CCell game_field[board_height][board_width];

  CPosition();
  CPosition(const CPosition & position, const CCell_state state, int x_coord, int y_coord);
  CPosition(const std::vector<CCell_state> states, const std::vector<double> weights);
  bool is_won_for_x() const;
  bool is_won_for_o() const;
  void print() const;
  bool is_equal(const CPosition & pos) const;

 private:
 	bool is_won(const CPosition & position, const CCell_state state, const int x_coord, const int y_coord) const;

};



// struct CPosition_cmp
// {
//   bool operator()(const CPosition & pos1, const CPosition & pos2) const;
// };

// template <int n, int m>
// class A
// {cp
// int array[n][m];

// };

// A<3,3> a;
#endif //POSITION_H