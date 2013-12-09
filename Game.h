#pragma once

class Game {
	public:
		static int const max_lifes = 3;

		Game();

		void win_track();
		void fail_track();
		void win_game();
		bool check_game_over();

		int lifes() const { return m_lifes; }
		int score() const { return m_points; }

	private:
		int m_mult_points;
		int m_lifes;
		int m_points;
		bool m_has_won;
};
