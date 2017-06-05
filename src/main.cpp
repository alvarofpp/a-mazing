#include <iostream>
#include <cassert>
#include "maze.h"



 bool solve_maze( const Maze& mz, const Maze::Position pos){
 	//Recupera
 	const Maze::Position initial = mz.get_start_position();

 	if( not mz.is_blocked())

 }

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

	pos.col+=1;
	pos.roll-=1;

	mz.mark_cell(pos);

	mz.render();

	Maze::Position p;
	p.roll = 0;
	p.col = 2;

	Maze::Direction d;
	d.height = 0;
	d.weight = 0;

	assert ( mz.is_blocked(p, d));

	pos.roll-=1;
	pos.col+=1;
	mz.mark_cell(pos);

	assert( mz.is_marked(pos) == false);

	mz.unmark_cell(pos);

	assert( mz.is_marked(pos) == false);

	return 0;
}