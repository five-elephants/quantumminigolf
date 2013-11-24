#include "Highscore.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <sstream>

Highscore::Highscore(std::string const& filename)
	:	m_savefile(filename) {
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
}

/* vim: set noet fenc= ff=unix sts=0 sw=4 ts=4 : */
