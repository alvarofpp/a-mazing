#include "player.h"
#include <functional> //<! std::hash


std::vector<Direction> directions = 
{
	Direction(-1, 0), //north
	Direction(1, 0),  //south
	Direction(0, -1), //east
	Direction(0, 1)   //west
};

std::vector<direction_t> movements =
{
	direction_t::NORTH,
	direction_t::SOUTH,
	direction_t::EAST,
	direction_t::WEST
};

//Functor para a dispersão
struct KeyHash {
    std::size_t operator()( const Position & k_ ) const
    {

    return (std::hash < int >()( k_.roll )  xor
        std::hash < int >()( k_.col )) ;
    }
};

//Functor para a comparação
struct KeyEqual{
    bool operator()( const Position &lhs, const Position &rhs) const{
        return (lhs.roll == rhs.roll and lhs.col == rhs.col);
    }
};

direction_t Player::next_move()
{
	if( not m_solution.empty() ){
		auto dir = m_solution.front();
		m_solution.erase(m_solution.begin());
		return dir;
	}
	return direction_t::NONE;
}


Player::Player()
{
    std::vector<direction_t> sol;
    m_solution = sol;
  
}

bool Player::find_solution ( std::vector<std::string> & map )
{
	Level lvl;
	lvl.load( map );
	auto start = lvl.get_start_position(); //<! posição inicial da cobra

	//<! Declarar movimento inicial
	Move inicial;
	inicial.pos = start;
	inicial.dir.push_back(direction_t::STATIC);

	//<! pilha para a possível sólução
	std::stack< Move > possible_sol;

	//<! tabela hash para posições visitadas
	HashTbl<Position, Move, KeyHash, KeyEqual> pos_visit(23);

	Move x;
	//<! pilha inicia com a posição inicial
	possible_sol.push( inicial );

	//<! possível solução na tabela hash
	pos_visit.insert( inicial.pos, inicial);	

	while (  not possible_sol.empty() )
	{	
		// desempilha uma possível solução
		x = possible_sol.top();
		possible_sol.pop();

		///<! verifica se é a solução
		if ( lvl.is_solution( x.pos ) )
		{	
			m_solution = x.dir;		

			return true;
		}
		//<! verifica se já foi visitada e já insere uma possível solução
		else if ( (not pos_visit.insert( x.pos, x)) and (x.pos != inicial.pos))
		{
			/*próximo ciclo*/
			
		} else
		{
			
			for ( auto d  = (int) direction_t::NORTH; d != (int) direction_t::WEST +1; ++d )
			{
				//direction_t index = static_cast<direction_t>(dir);
				Direction de = directions[ d ];

				Position direc;
				direc.roll = de.height + x.pos.roll;
				direc.col  = de.weight  + x.pos.col;

				Move mv;
				//<! verificar se não é bloqueado
				if ( !lvl.is_blocked( direc ) and not pos_visit.retrieve( direc, mv) )
				{

					Move ins;
					ins.pos = direc; //de onde veio
					ins.dir = x.dir;
					ins.dir.push_back(movements[ d ]); //direção que tomou
					possible_sol.push( ins ); //adiciona move
					
				}   	
			}
		}
	}
	return false;
}

void Player::print ()
{
	std::cout << ">>>SOLUTION<<<\n";
	auto cont(0);
	for ( auto i = m_solution.begin(); i != m_solution.end(); ++i)
	{
		if ( *i == direction_t::NORTH ) std::cout << cont << " NORTH\n";
		else if ( *i == direction_t::SOUTH ) std::cout << cont << " SOUTH\n";
		else if ( *i == direction_t::EAST ) std::cout << cont << " EAST\n";
		else if ( *i == direction_t::WEST ) std::cout << cont << " WEST\n";
		else if ( *i == direction_t::STATIC ) std::cout << cont << " Inicio\n";

		cont++;
	}
	std::cout << ">>>FIM DA SOLUÇÂO<<<\n";
}