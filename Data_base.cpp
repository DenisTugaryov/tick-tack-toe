#include "Data_base.h"

#include <vector>
#include <fstream>
#include <iostream>


#include "Position.h"
#include "Cell.h"



  void CData_base::add_position(CPosition & pos)
  {
    data.push_back(pos);
  }

  void CData_base::save() const
  {
    std::ofstream data_file("data_base.txt");
    for (std::vector<CPosition>::const_iterator it = data.begin(); it != data.end(); ++it)
    {
      for (int i = 0; i < board_width; ++i)
      	for (int j = 0; j < board_height; ++j)
      	  data_file << it->game_field[i][j].state << " " << it->game_field[i][j].weight << "\t";
      data_file << std::endl;
    }
  }

  void CData_base::load()
  {
    std::ifstream data_file("data_base.txt");
    while (!data_file.eof())
    {
      std::vector<CCell_state> states;
      std::vector<double> weights;
      char symbol = ' ';
      double tmp_weight = 0;
      for (int i = 0; i < board_width * board_height; ++i)
      {
        std::cin >> symbol;
        switch(symbol)
        {
          case 'E':
          {
            states.push_back(EMPTY);
            break;
          }
          case 'X':
          {
            states.push_back(X);
            break;
          }
          case 'O':
          {
            states.push_back(O);
            break;
          }
        };
        std::cin >> tmp_weight;
        weights.push_back(tmp_weight);
      }
      data.push_back(CPosition(states, weights));
      states.clear();
      weights.clear();
    }
  }

std::vector<CPosition>::iterator in_base( CPosition & position,  CData_base & base)
{
  for(std::vector<CPosition>::iterator it = base.data.begin(); it != base.data.end(); ++it)
    if(position.is_equal(*it))
      return it;
  return base.data.end();
}