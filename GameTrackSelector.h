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

	private:
	std::vector<std::vector<trackrecord*> > tiers;
	std::size_t cur_tier;

	void load_configuration(std::string const& filename);
};

/* vim: set noet fenc= ff=unix sts=0 sw=4 ts=4 : */
