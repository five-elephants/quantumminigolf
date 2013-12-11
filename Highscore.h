#pragma once

#include <string>
#include <vector>

#include "Renderer.h"

class Highscore {
	public:
		struct Entry {
			unsigned int id;
			std::string name;
			int points;
		};
		
		Highscore(std::string const& filename,
				int const name_length=5,
				int const top_ranks=10);
		~Highscore();

		void load(std::string const& filename);
		void save(std::string const& filename);
		void print();
		void add(std::string const& name, int points);
		bool is_new_highscore(int points);
		unsigned int get_new_highscore(Renderer& renderer, int points);
		void show_highscore(Renderer& renderer, unsigned int highlight);

	private:
		std::vector<Entry> m_scores;	
		std::string m_savefile;
		int const m_name_length;
		int const m_top_ranks;
		unsigned int m_last_index;

		void sort();

};

inline bool compare_highscore_entry(Highscore::Entry const& a,
		Highscore::Entry const& b) {
	return a.points > b.points;
}

/* vim: set noet fenc= ff=unix sts=0 sw=4 ts=4 : */
