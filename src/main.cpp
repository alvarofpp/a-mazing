#include <iostream>
#include <cassert>
#include "maze.h"

struct Position{
	std::size_t row;
	std::size_t col;
};

// bool solve_maze( const Maze& mz, const Position pos){

// }

int main(int arcg, char** argv){

	Maze mz;

	//Validar argumentos

	//Caregar labirinto
	mz.load(argv[1]);
	//if(solve_maze( mz, mz.get_start_position() ) ){
		//soluçao encontrada
	//}
	auto pos = mz.get_start_position();
	std::cout << pos.roll << std::endl;
	std::cout << pos.col << std::endl;

	mz.render();

	Maze::Position p;
	p.roll = 0;
	p.col = 2;

	Maze::Direction d;
	d.height = 0;
	d.weight = 0;

	assert ( mz.is_blocked(p, d));
	return 0;
}