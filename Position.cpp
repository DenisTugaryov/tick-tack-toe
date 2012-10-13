#include "Position.h"

#include <iostream>

#include "Data_base.h"

double BEGIN_WEIGHT = 0.5;

CPosition::CPosition()
{
 for (int i = 0; i < board_width; ++i)
    for (int j = 0; j < board_height; ++j)
    {
      game_field[i][j].state = EMPTY;
      game_field[i][j].weight = BEGIN_WEIGHT;
    }
}

CPosition::CPosition(const CPosition & position, const CCell_state state, int x_coord, int y_coord)
{
  for (int i = 0; i < board_width; ++i)
    for (int j = 0; j < board_height; ++j)
    {
      game_field[i][j].state = position.game_field[i][j].state;
      game_field[i][j].weight = position.game_field[i][j].weight;
    }
	game_field[x_coord][y_coord].state = state;
	game_field[x_coord][y_coord].weight = 0;
}

CPosition::CPosition(const std::vector<CCell_state> states, const std::vector<double> weights)
{
	for (int i = 0; i < board_width; ++i)
		for (int j = 0; j < board_height; ++j)
		{
			game_field[i][j].state = states[i * board_width + board_height];
			game_field[i][j].weight = weights[i * board_width + board_height];
		}
}


bool CPosition::is_won(const CPosition & position, const CCell_state state, const int x_coord, const int y_coord) const
{
  int right_neighbour = 0;
  int left_neighbour = 0;
  int up_neighbour = 0;
  int down_neighbour = 0;
  int up_right_neighbour = 0;
  int up_left_neighbour = 0;
  int down_right_neighbour = 0;
  int down_left_neighbour = 0;

  for (int i = y_coord + 1; i < board_width; ++i)
    if(game_field[x_coord][i].state == state)
      ++right_neighbour;
    else break;
  for (int i = y_coord - 1; i >= 0; --i)
    if(game_field[x_coord][i].state == state)
      ++left_neighbour;
    else break;
  for (int i = x_coord + 1; i < board_width; ++i)
    if(game_field[i][y_coord].state == state)
      ++up_neighbour;
    else break;
  for (int i = x_coord - 1; i >= 0; --i)
    if(game_field[i][y_coord].state == state)
      ++down_neighbour;
    else break;

  while (x_coord + up_right_neighbour + 1 < board_width && y_coord + up_right_neighbour + 1 < board_height)
  {
  if(game_field[x_coord + up_right_neighbour + 1][y_coord + up_right_neighbour + 1].state == state)
    ++up_right_neighbour;
  else break;
  }

  while (x_coord - down_left_neighbour - 1 >= 0 && y_coord - down_left_neighbour - 1 >= 0)
  {
  if(game_field[x_coord - down_left_neighbour - 1][y_coord - down_left_neighbour - 1].state == state)
    ++down_left_neighbour;
  else break;
  }

  while (x_coord - down_right_neighbour - 1 >= 0 && y_coord + down_right_neighbour + 1 < board_width)
  {
  if(game_field[x_coord - down_right_neighbour - 1][y_coord + down_right_neighbour + 1].state == state)
    ++down_right_neighbour;
  else break;
  }

  while (x_coord + up_left_neighbour + 1 < board_width && y_coord - up_left_neighbour - 1 >= 0)
  {
  if(game_field[x_coord + up_left_neighbour + 1][y_coord - up_left_neighbour - 1].state == state)
    ++up_left_neighbour;
  else break;
  }
  // std::cout<< "i == " << x_coord << "; j == " << y_coord << std::endl;
  // std::cout<< "right_neighbour == " << right_neighbour << std::endl;
  // std::cout<< "left_neighbour == " << left_neighbour << std::endl;
  // std::cout<< "up_neighbour == " << up_neighbour << std::endl;
  // std::cout<< "down_neighbour == " << down_neighbour << std::endl;
  // std::cout<< "up_right_neighbour == " << up_right_neighbour << std::endl;
  // std::cout<< "down_left_neighbour == " << down_left_neighbour << std::endl;
  // std::cout<< "up_left_neighbour == " << up_left_neighbour << std::endl;
  // std::cout<< "down_right_neighbour == " << down_right_neighbour << std::endl;
  // std::cout<<std::endl;

  return (right_neighbour + left_neighbour + 1 >= simbols_quantity_for_victory ||
    up_neighbour + down_neighbour + 1 >= simbols_quantity_for_victory ||
    up_right_neighbour + down_left_neighbour + 1 >= simbols_quantity_for_victory ||
    up_left_neighbour + down_right_neighbour + 1 >= simbols_quantity_for_victory);
}

bool CPosition::is_won_for_x() const
{
  for (int i = 0; i < board_width; ++i)
    for (int j = 0; j < board_height; ++j)
      if(game_field[i][j].state == X && is_won(*this, X, i, j))
        return true;
  return false;
}

bool CPosition::is_won_for_o() const
{
  for (int i = 0; i < board_width; ++i)
    for (int j = 0; j < board_height; ++j)
      if(game_field[i][j].state == O && is_won(*this, O, i, j))
        return true;
  return false;
}

void CPosition::print() const
{
  for (int i = board_height - 1; i >= 0; --i)
  {
    for (int j = 0; j < board_width; ++j)
      switch(game_field[i][j].state)
      {
        case EMPTY :
        {
          std::cout << "_";
          break;
        }
        case X :
        {
          std::cout << "X";
          break;
        }
        case O :
        {
          std::cout << "O";
          break;
        }
      };
    std::cout << std::endl;
  }
}

bool CPosition::is_equal(const CPosition & pos) const
{
  for (int i = 0; i < board_width; ++i)
    for (int j = 0; j < board_height; ++j)
      if (pos.game_field[i][j].state != this->game_field[i][j].state)
        return false;
  return true;
}

