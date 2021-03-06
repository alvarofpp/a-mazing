/**
 * @file snake.cpp
 * @authors Gabriel Araújo de Souza e Mayra Dantas de Azevedo
 * @date 21 Junho 2017
 * @brief Arquivo contendo as implementações da classe Snake.
 */

#include "snake.h"

//<! faz a cobra acessar um level
void Snake::bind_level( Level & l_ )
{
    lvl = &l_;
}

//<! pega a posião da cabeça da cobra
Position Snake::get_position( void) 
{
    return body.front();
}

//<! faz a cobra se mover para um posição enviada
void Snake::move( Position pos)
{
    //!< Retira a cauda
    body.pop_back();

    //!< Cobra vai para a frente
    body.push_front(pos);
}

//<! Recupera simbolo da cabeça da cobra
std::string Snake::get_head() const{
    return head;
}

//<! define os simbolos possíveis para a cabeça da cobra
void Snake::set_head( direction_t dir){
    //cima \u02c4
    //baixo \u02c5
    //direita \u02c3
    //esq \u02c2

    //!< Atualiza cabeça da cobra
    switch( dir ){
        case direction_t::NORTH:
            head = "\u1404";
            break;
        case direction_t::SOUTH:
            head = "\u1401";
            break;
        case direction_t::WEST :
            head = "\u1413";
            break;
        case direction_t::EAST:
            head = "\u1417";
            break;
        default:
            head = "\u0A66";
            break;
    }
}

//<! Atualiza a cobra após a maçã ser comida
void Snake::grow( Position pos){
    //!< Quando a cobra comer a maçã, a maçã vira a cabeça da cobra
    body.push_front(pos);
}

//<! Consulta o estado da cobra
Snake::SnakeState Snake::get_state( void ) const 
{
    return state;
}

//<! Atualiza Atualiza o estado da cobra
void Snake::update_state( Snake::SnakeState new_state)
{
    state = new_state;
}

//<! Retorna corpo da cobra
std::deque < Position > Snake::get_body( ) const{
    return body;
}

//<! Recupera tamanho da cobra
std::size_t Snake::size() const{
    return body.size();
}

//<! recupera a quantidade de vidas restantes
int Snake::get_lifes() const{
	return m_lifes;
}

//<! faz a cobra morrer
void Snake::die(){
	m_lifes--;
}

//<! verifica se em uma dada posição há alguma parte da cobra
bool Snake::is_snake( const Position & pos )
{
    auto it = body.begin();
    auto end = body.end();
    auto res = std::find( it, end-1, pos);

    if (res != end-1 and res != it) return true;
    else return false;
}

//<! atualiza um novo coorpo para a snake
void Snake::set_body(  std::deque < Position > & newBody )
{
    body = newBody;
}
