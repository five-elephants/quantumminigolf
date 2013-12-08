#include "GameTrackSelector.h"

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

GameTrackSelector::GameTrackSelector(Renderer* renderer, ClassicSimulator* csim)
	:	TrackSelector(renderer, csim) {
	load_configuration("tracks/game_tracks.cfg");
}

GameTrackSelector::~GameTrackSelector() {
}

int
GameTrackSelector::GetTrack(bool* quantum) {
	SDL_Event ev;

	*quantum = true;

	renderer->V = (*trackiterator)->V;
	renderer->RenderTrack();
	renderer->Blit();

	SDL_WaitEvent(&ev);

	if( (ev.type == SDL_KEYDOWN) && (ev.key.keysym.sym == SDLK_ESCAPE) )
		return 0;

	return 1;
}

void
GameTrackSelector::next_track() {
	if( ++trackiterator == tracks.end() ) {
		trackiterator = tracks.begin();
	}
}

void
GameTrackSelector::load_configuration(std::string const& filename) {
	using boost::property_tree::ptree;

	ptree pt;	

	read_json(filename, pt);

	for(ptree::iterator track = pt.begin(); track != pt.end(); ++track) {
		std::cout << "found track '" << track->first << "'" << std::endl;
	}
}
