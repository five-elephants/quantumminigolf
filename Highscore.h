#pragma once

#include <string>
#include <vector>

#include "Renderer.h"

class Highscore {
	public:
		struct Entry {
			std::string name;
			int points;
		};
		
		Highscore(std::string const& filename, int const name_length=5);
		~Highscore();

		void load(std::string const& filename);
		void save(std::string const& filename);
		void print();
		void add(std::string const& name, int points);
		void get_new_highscore(Renderer& renderer, int points);
		void show_highscore(Renderer& renderer);

	private:
		std::vector<Entry> m_scores;	
		std::string m_savefile;
		int const m_name_length;

		void sort();

};

inline bool compare_highscore_entry(Highscore::Entry const& a,
		Highscore::Entry const& b) {
	return a.points > b.points;
}

/* vim: set noet fenc= ff=unix sts=0 sw=4 ts=4 : */
