#include "Highscore.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>

Highscore::Highscore(std::string const& filename, int const name_length)
	:	m_savefile(filename),
		m_name_length(name_length) {
	load(filename);
}

Highscore::~Highscore() {
	save(m_savefile);
}


void
Highscore::load(std::string const& fn) {
	std::ifstream in(fn.c_str());
	if( !in ) {
		// if file can not be opened, try to create it by saving the empty highscore
		save(fn);
		in.open(fn.c_str());
		if( !in )
			throw std::runtime_error("Could not open highscore for reading");
	}
	
	while( in ) {
		std::string buf;
		std::getline(in, buf, '\n');

		if( buf.size() > 0 ) {
			std::stringstream strm(buf);
			Entry entry;
			strm >> entry.name;
			strm >> entry.points;
			m_scores.push_back(entry);
		}
	}

	sort();
}


void
Highscore::save(std::string const& fn) {
	std::ofstream out(fn.c_str());
	if( !out  )
		throw std::runtime_error("Could not open highscore for saving.");

	for(std::vector<Entry>::const_iterator i = m_scores.begin();
			i != m_scores.end();
			++i ) {
		out << i->name << ' ' << i->points << '\n';
	}
}


void
Highscore::print() {
	std::cout << "HIGHSCORE:\n";
	for(std::vector<Entry>::const_iterator i = m_scores.begin();
			i != m_scores.end();
			++i ) {
		std::cout << i->name << ' ' << i->points << '\n';
	}	
	std::cout << std::endl;
}


void
Highscore::add(std::string const& name, int points) {
	Entry entry;
	entry.name = name;
	entry.points = points;
	m_scores.push_back(entry);
	sort();
}


void
Highscore::get_new_highscore(Renderer& renderer, int points) {
	SDL_Event ev;
	bool done = false;
	Entry e;
	size_t char_i = 0;

	e.name.resize(m_name_length, '-');
	e.points = points;

	if( SDL_EnableKeyRepeat(0, 0) == -1 ) {
		std::cerr << "disabling key repeat failed" << std::endl;
	}

	do {
		renderer.RenderTrack();
		renderer.RenderNewHighscore(e.name);
		renderer.Blit();

		if( SDL_PollEvent(&ev) != 0 ) {
			if( ev.type == SDL_KEYDOWN ) {
				e.name[char_i] = SDL_GetKeyName(ev.key.keysym.sym)[0];
				if( ++char_i == m_name_length )
					done = true;
			}
		}
	} while( !done );

	m_scores.push_back(e);
	sort();
}


void
Highscore::show_highscore(Renderer& renderer) {
	bool done = false;

	for(size_t pos=0; pos<std::min(10ul, m_scores.size()); ++pos) {
		renderer.RenderHighscoreEntry(pos,
				m_scores[pos].name, 
				m_scores[pos].points);
	}
	renderer.Blit();

	while( SDL_PollEvent(NULL) == 0 );
}


void
Highscore::sort() {
	std::sort(m_scores.begin(), m_scores.end(), compare_highscore_entry);
}
/* vim: set noet fenc= ff=unix sts=0 sw=4 ts=4 : */
