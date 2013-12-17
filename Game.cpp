#include "Game.h"

#include <iostream>

Game::Game()
	:	m_lifes(max_lifes),
		m_points(0),
		m_has_won(false),
		m_mult_points(1) {
}

void
Game::win_track() {
	m_points += 100*m_mult_points;
	m_mult_points *= 2;
}

void
Game::fail_track() {
	m_points -= 20*(m_mult_points-1);
	m_lifes -= 1;
}

void
Game::win_game() {
	m_has_won = true;
	std::cout << "you have won" << std::endl;
}

bool
Game::check_game_over() {
	return m_lifes <= 0 || m_has_won;
}
