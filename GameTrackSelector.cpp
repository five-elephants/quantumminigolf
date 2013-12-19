#include "GameTrackSelector.h"

#include <cstdlib>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

GameTrackSelector::GameTrackSelector(Renderer* renderer, ClassicSimulator* csim)
	:	TrackSelector(renderer, csim) {
	this->renderer = renderer;
	this->csimulator = csimulator;
	this->width = renderer->width;
	this->height = renderer->height;
	help = true; // ???
}

GameTrackSelector::~GameTrackSelector() {
}

int
GameTrackSelector::GetTrack(bool* quantum) {
	SDL_Event ev;

	*quantum = true;

	renderer->V = (*trackiterator)->V;
	csimulator->hard = (*trackiterator)->hard;
	csimulator->soft = (*trackiterator)->soft;
	renderer->RenderTrack();
	renderer->RenderClubMark();
	renderer->Blit();

	SDL_WaitEvent(&ev);

	if( (ev.type == SDL_KEYDOWN) && (ev.key.keysym.sym == SDLK_ESCAPE) )
		return 0;

	return 1;
}

void
GameTrackSelector::next_track() {
	if( cur_tier->empty() )
		return;
	size_t chose = random() % cur_tier->size();
	trackiterator = cur_tier->begin() + chose;
}

bool
GameTrackSelector::tier_up() {
	if( ++cur_tier != tiers.end() ) {
		trackiterator = cur_tier->begin();
		return true;
	}
	return false;
}

void
GameTrackSelector::back_to_start() {
	cur_tier = tiers.begin();
	trackiterator = cur_tier->begin();
}

void
GameTrackSelector::load_configuration(std::string const& filename) {
	using boost::property_tree::ptree;

	ptree pt;	

	read_json(filename, pt);

	ptree const& game_tracks = pt.get_child("game");
	for(ptree::const_iterator track = game_tracks.begin();
			track != game_tracks.end();
			++track) {
		ptree const& st = track->second;
		std::cout << "found track '" << st.get<std::string>("img") << "'" << std::endl;

		trackrecord* rec = new trackrecord;
		rec->V = load_bmp(st.get<std::string>("img"));
		rec->hard = load_bmp(st.get<std::string>("hard"), true);
		rec->soft = load_bmp(st.get<std::string>("soft"), true);

		int const& tier = st.get<int>("tier");
		if( tier < 0 || tier > tier_limit )
			throw std::runtime_error("tier out of range (0 <= tier <= 20)");

		if( tier >= tiers.size() )
			tiers.resize(tier+1);

		tiers[tier].push_back(rec);
		std::cout << "pushin to tier " << tier << std::endl;
	}

	cur_tier = tiers.begin();
	trackiterator = cur_tier->begin();

	renderer->V = (*trackiterator)->V;
	csimulator->hard = (*trackiterator)->hard;
	csimulator->soft = (*trackiterator)->soft;
	renderer->RenderTrack();
	renderer->Blit();
}

SDL_Surface*
GameTrackSelector::load_bmp(std::string const& fn,
		bool optional) {
	std::string path("tracks/");

	SDL_Surface* surf = SDL_LoadBMP((path + fn).c_str());

	if( surf == NULL || surf->w != width || surf->h != height ) {
		SDL_FreeSurface(surf);
		
		if( !optional ) {
			throw std::runtime_error(
					std::string("Loading bitmap ")
					+ path
					+ fn
					+ std::string(" failed")
			);
		} else {
			surf = BlackTrack();	
		}
	}

	return SDL_ConvertSurface(surf, renderer->screen->format, SDL_SWSURFACE);
}

