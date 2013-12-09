#pragma once

#include "TrackSelector.h"

#include <vector>
#include <string>

class GameTrackSelector : public TrackSelector {
	public:
	GameTrackSelector(Renderer* renderer, ClassicSimulator* csimulator);
	~GameTrackSelector();

	int GetTrack(bool* quantum);
	void next_track();
	bool tier_up();
	void back_to_start();

	void load_configuration(std::string const& filename);

	protected:
	std::vector<std::vector<trackrecord*> > tiers;
	//std::size_t cur_tier;
	std::vector<std::vector<trackrecord*> >::iterator cur_tier;
	static std::size_t const tier_limit = 20;

	SDL_Surface* load_bmp(std::string const& fn, bool optional = false);
};

/* vim: set noet fenc= ff=unix sts=0 sw=4 ts=4 : */
