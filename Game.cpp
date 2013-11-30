#include "Game.h"

Game::Game()
	:	m_lifes(max_lifes),
		m_points(0) {

}

void
Game::win_track() {
	m_points += 100;
}

void
Game::fail_track() {
	m_lifes -= 1;
}

bool
Game::check_game_over() {
	return m_lifes <= 0;
}
