
#include "Position.h"
#include "Data_base.h"
#include "Cell.h"


#include <random>
#include <stack>
#include <iostream>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_01.hpp>

const int GAME_COUNT = 1000000;
const int EPSILON = 1;
const int ALPHA = 0.5;

void x_step(CPosition & position, CData_base & base, std::stack<int> & coords_stack)
{
	int empty_counter = 0;
	int max_i = -1;
	int max_j = -1;
	int max_element = 0;
	for (int i = 0; i < board_width; ++i)
	    for (int j = 0; j < board_height; ++j)
	      if (position.game_field[i][j].state == EMPTY)
	      {
	      	++empty_counter;
	      	if(position.game_field[i][j].weight > max_element)
	      	{
	      		max_i = i;
	      		max_j = j;
	      		max_element = position.game_field[max_i][max_j].weight;
	      	}
	      		
	      }

	std::random_device rg;
	boost::mt19937 gen (rg);
	boost::uniform_int<> uniform (EPSILON, 50);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > gener(gen, uniform);

	if(gener() == 1)
	{
		// std::cout<< "eps" << std::endl;
		boost::uniform_int<> new_uniform (1, empty_counter);
		boost::variate_generator<boost::mt19937&, boost::uniform_int<> > new_gener(gen, new_uniform);

		int random_free_value = new_gener();
		empty_counter = 0;
		for (int i = 0; i < board_width; ++i)
		    for (int j = 0; j < board_height; ++j)
		      if (position.game_field[i][j].state == EMPTY)
		      {
		      	++empty_counter;
		      	if(empty_counter == random_free_value)
		      	{
		      		CPosition new_position = CPosition(position, X, i, j);
		      		coords_stack.push(i);
		      		coords_stack.push(j);
		      		in_base(new_position, base);
		      		std::vector<CPosition>::iterator iterator = in_base(new_position, base);
		      		if(iterator != base.data.end())
		      			position = *iterator;
		      		else
		      		{
		      			base.add_position(new_position);
		      			position = *(base.data.end() - 1);
		      		}
		   		break;
		      	}
		      }
	}
	else
	{
		// std::cout<< "no" << std::endl;
		// for (int i = 0; i < board_width; ++i)
		//     for (int j = 0; j < board_height; ++j)
		//       if (position.game_field[i][j].weight == max_element && position.game_field[i][j].state == EMPTY)
		//       {
		      		CPosition new_position = CPosition(position, X, max_i, max_j);
		      		coords_stack.push(max_i);
		      		coords_stack.push(max_j);
		      		std::vector<CPosition>::iterator iterator = in_base(new_position, base);
		      		if(iterator != base.data.end())
		      			position = *iterator;
		      		else
		      		{
		      			base.add_position(new_position);
		      			position = *(base.data.end() - 1);
		      		}
		      		// break;
		      // }
	}
}

void o_step(CPosition & position, CData_base & base, std::stack<int> & coords_stack)
{
	int empty_counter = 0;
	for (int i = 0; i < board_width; ++i)
	    for (int j = 0; j < board_height; ++j)
	      if (position.game_field[i][j].state == EMPTY)
	      	++empty_counter;
	      // std::cout<< "empty_counter == " << empty_counter << std::endl;
	std::random_device rg;
	boost::mt19937 gen (rg);
	boost::uniform_int<> uniform (1, empty_counter);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > gener(gen, uniform);

	int random_free_value = gener();
	empty_counter = 0;
	for (int i = 0; i < board_width; ++i)
	    for (int j = 0; j < board_height; ++j)
	      if (position.game_field[i][j].state == EMPTY)
	      {
	      	++empty_counter;
	      	if(empty_counter == random_free_value)
	      	{
	      		CPosition new_position = CPosition(position, O, i, j);
	      		coords_stack.push(i);
	      		coords_stack.push(j);
	      		std::vector<CPosition>::iterator iterator = in_base(new_position, base);
	      		if(iterator != base.data.end())
	      			position = *iterator;
	      		else
	      		{
	      			base.add_position(new_position);
	      			position = new_position;
	      		}
	   		break;
	      	}
	      }
}

int game(CData_base & base)
{
	CPosition* position = new CPosition();
	std::stack<CPosition> game_stack;
	std::stack<int> coords_stack;
	game_stack.push(*position);
	base.add_position(*position);
	int step_counter = 0;
	const int SUP_OF_STEP = board_width * board_height;
	while(!(position->is_won_for_x()) && !(position->is_won_for_o()) && step_counter < SUP_OF_STEP)
	{
		x_step(*position, base, coords_stack);
		// position->print();
		// std::cout<< std::endl;
		game_stack.push(*position);
		++step_counter;
		if(!position->is_won_for_x() && step_counter < SUP_OF_STEP)
		{
			o_step(*position, base, coords_stack);
			// position->print();
			// std::cout<< std::endl;
			game_stack.push(*position);

			++step_counter;
		}
	}
	int result = 0;
	double prize = 0;
	if(position->is_won_for_x())
	{
		prize = 0.001;
		result = 1;
	}
	else //if(position->is_won_for_o())
	{
		prize = -0.001;
		//result = -1;
	}
	game_stack.pop();
	int current_value = 1;

	while(!game_stack.empty())
	{
		bool flag = true;
		int y = coords_stack.top();
		coords_stack.pop();

		int x = coords_stack.top();
		coords_stack.pop();
		std::vector<CPosition>::iterator iterator = in_base(game_stack.top(), base);
		if(flag && result == 1)
		{
			// if(result == 1)
			{
				iterator->game_field[x][y].weight = 1;
				current_value = 1;
			}
			// else
			// {
			// 	iterator->game_field[x][y].weight = 0;
			// 	current_value = 0;
			// }
			flag = false;
		}
		else if(result == 1)
		{
			double old_value = iterator->game_field[x][y].weight;
			double new_value = ALPHA * (current_value - old_value);
			iterator->game_field[x][y].weight += new_value;
			current_value = old_value + new_value;
			// iterator->game_field[x][y].weight += ALPHA * (current_value - iterator->game_field[x][y].weight);
			// current_value = iterator->game_field[x][y].weight;
		}
		else
			iterator->game_field[x][y].weight += prize;
		game_stack.pop();
	}
	delete position;
	return result;
}


int main()
{
	CData_base base;
	// base.load();
	
	int wins_counter = 0;
	for (int i = 1; i <= GAME_COUNT; ++i)
	{
		
		wins_counter += game(base);
		if(i % 1000 == 0)
		{
			std::cout<< i << ") wins_counter == " << wins_counter << std::endl;
			wins_counter = 0;
		}

		// std::cout<< i << ") wins_counter == " << wins_counter << std::endl;
	}

	 base.save();
	return 0;
}