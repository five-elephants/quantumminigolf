/*	Quantum Minigolf, a computer game illustrating quantum mechanics
	Copyright (C) 2007 Friedemann Reinhard <friedemann.reinhard@gmail.com>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include "QuantumSimulator.h"
#include "ClassicSimulator.h"
#include "Renderer.h"
#include "SoftwareTracker.h"
#include "GameTrackSelector.h"
#include "Highscore.h"
#include "Game.h"
#include "quantumminigolf.h"

#include <iostream>
#include <limits>
#include <cstdlib>

#ifdef VR
#include "WebcamTracker.h"
#endif //VR

#ifdef LINUX
#include <sys/time.h>
#endif

#ifdef DUMP_VIDEO
char fname[80];
#endif

// dimensions of the playing field
#define WIDTH 640
#define HEIGHT 320


// main
// put it all together...
#ifdef WIN32  // no comment...
int wmain(int argc, char *argv[]){
#endif
#ifdef LINUX
int main(int argc, char **argv){
#endif

	int ix=550, iy=160; // initial ball position
	int rball = 5;		// ball radius
	int holex=100; int holey=160; int holer=30; // hole position and radius

	int posx, posy; // result of the final position measurement;

	int res;        // success of the user: win / lose
	int ypos;		// position of the win / lose indicator

	float rphi; // angle of the racket relative to x axis
	float rv; // velocity of the racket
	float rvmax = 40; // maximum club speed

	float dt = 0.0001; // hard-coded increment for the quantum propagation

	float norm=1; //total shrink during a position space propagation
				  // used to enforce normalization of psi
	float normlast = 1; //shrink during last iteration, used to enforce 
						//normalization
	float nsq = WIDTH*HEIGHT;

	int frames = 0;
	float framerate;

	Uint32 sdlclock, frameclock;

	bool quantum=true;  // quantum or classical mode ?
	bool exit_request = false;

	SDL_Event dummyevent;

	// seed the random number generator
#ifdef WIN32
	srand(time(NULL));
#endif 
#ifdef LINUX
	struct timeval tv;
	gettimeofday(&tv,0);
	srand(tv.tv_sec + tv.tv_usec);
	srandom(tv.tv_sec + tv.tv_usec);
#endif

#ifndef VR
	SoftwareTracker stracker(WIDTH, HEIGHT, ix, iy, rball, rvmax, NULL);
	Tracker& tracker = stracker;
	Renderer renderer(WIDTH, HEIGHT, SDL_HWSURFACE /*| SDL_FULLSCREEN*/, holex, holey, holer, rball);// | SDL_FULLSCREEN);
#endif
#ifdef VR
	WebcamTracker wctracker(WIDTH, HEIGHT, ix, iy, rball, rvmax, NULL);
	Tracker& tracker = wctracker;
	printf("adjust your webcam and press <ENTER> to start\n");
	getc(stdin);
	Renderer renderer(WIDTH, HEIGHT, SDL_HWSURFACE /*  | SDL_FULLSCREEN */, holex, holey, holer, rball);// | SDL_FULLSCREEN);
#endif //VR

	ClassicSimulator csimulator(WIDTH, HEIGHT, &renderer, holex, holey, holer);
	QuantumSimulator simulator(WIDTH, HEIGHT, dt);
	GameTrackSelector trackselector(&renderer, &csimulator);
	Highscore highscore("highscore.dat");
		
	trackselector.load_configuration("tracks/game_tracks.cfg");
	tracker.setRenderer(&renderer);

	quantum = true;

	while( !exit_request ) {
		highscore.show_highscore(renderer,
				std::numeric_limits<unsigned int>::max());

		Game game;
		tracker.setGame(game);
		trackselector.back_to_start();
		do {
			// menu loop - have the user select a track and play
			if( !trackselector.GetTrack(&quantum) ) {
				exit_request = true;
				break;
			}
				
			// for each new track, we have to rebuild the position propagator
			if(quantum)
				simulator.BuildPositionPropagator(renderer.V);

			// have the user kick the ball
			tracker.GetHit(&rv, &rphi);
			Uint32 hitclock = SDL_GetTicks();

			// now that the user has decided about the initial values, 
			// prepare the wave packet		
			if(quantum){
				// commented out for uncertainty movie 070519
				simulator.GenGauss( ix, iy,
					-2*rv*M_PI/2 * cos(rphi)/2, 
					-2*rv*M_PI/2 * sin(rphi)/2, 
					10);    
				// hack for uncertainty movie 070519
	//  			simulator.GenGauss( 200, iy,
	//  				-.4, 
	//  				0, 
	//  				15);    
	//  			simulator.GenGauss( 400, iy,
	//  				-.4, 
	//  				0, 
	//  				6);    		    
	//  			simulator.GenGauss( 600, iy,
	//  				-.4, 
	//  				0, 
	//  				3);    		    
			}
			else{
				csimulator.setPosition((float)ix, (float)iy);
				csimulator.setVelocity(-2*rv*M_PI/2 * cos(rphi), -2*rv*M_PI/2 * sin(rphi));
			}
			
			//kick it like Beckham
			tracker.AnimateHit(1000, rv, rphi);

			SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);  
			sdlclock = SDL_GetTicks();
			frameclock = SDL_GetTicks();
			frames=0;

			// ***** MAIN LOOP *****//
			//
			// while the user is watching (no event emitted), propagate the 
			// wave function in the potential
			while (SDL_PollEvent(&dummyevent)==0)    
			{              			
				renderer.RenderTrack();

				if(quantum){
					// propagate in momentum space
					simulator.PropagateMomentum();
					// propagate in position space
					normlast = simulator.PropagatePosition(1/nsq/sqrt(normlast));	
					// finally, show the result
					renderer.RenderWave(simulator.psi);
				}
				else{
					if(csimulator.propagate(SDL_GetTicks()-frameclock)) break;
					renderer.RenderBall(csimulator.pos[0], csimulator.pos[1]);
				}

				renderer.RenderHud(game.lifes(), Game::max_lifes, game.score());
				renderer.Blit();
#ifdef DUMP_VIDEO
				snprintf(fname, 80, "video/%d.bmp", frames);
				renderer.SaveFrame(fname);
#endif

				// some bookkeeping
				frames++;
				frameclock = SDL_GetTicks();
			}

			framerate = frames / (float)(SDL_GetTicks() - sdlclock)*1000;

			while (SDL_PollEvent(&dummyevent)==1){} // clear event buffer 

			// render a flash to show the position measurement
			renderer.RenderFlash();
			renderer.Blit();
			frames++;
#ifdef DUMP_VIDEO
			snprintf(fname, 80, "video/%d.bmp", frames);
			renderer.SaveFrame(fname);
#endif

			// a button has been pressed, measure the ball position!
			if(quantum)
				simulator.PositionMeasurement(&posx, &posy);
			else{
				posx = (int)(csimulator.pos[0]);
				posy = (int)(csimulator.pos[1]);
			}

			// render the extro. Show the (now classical) ball and inform the user about his success
			if((posx-holex)*(posx-holex) + (posy-holey)*(posy-holey) < holer*holer) {
				res = QMG_WIN;
				game.win_track();
				if( !trackselector.tier_up() ) {
					game.win_game();
				}
			} else {
				res = QMG_LOSE;
				game.fail_track();
			}
			trackselector.next_track();

			sdlclock = SDL_GetTicks();
			//while (SDL_PollEvent(NULL)==0)                    
			while ( (SDL_GetTicks() - sdlclock) < 2000 )  // show for 2 sec                   
			{              
				ypos = - 300 + (int)((float)(SDL_GetTicks() - sdlclock)/500*HEIGHT/2);

				renderer.RenderTrack();
				renderer.RenderBall(posx, posy);
				renderer.RenderHud(game.lifes(), Game::max_lifes, game.score());
				renderer.RenderExtro(res, ypos);
				
				renderer.Blit();
				frames++;
#ifdef DUMP_VIDEO
				snprintf(fname, 80, "video/%d.bmp", frames);
				renderer.SaveFrame(fname);
#endif
			}

	//		printf("rendered %d frames, quantum part framerate %2.1f fps. Goodbye\n", frames, framerate);
			simulator.ClearWave();

			SDL_Event evdummy;
			SDL_PollEvent(&evdummy);
		} while( !game.check_game_over() );

		if( !exit_request ) {
			unsigned int hi_id = std::numeric_limits<unsigned int>::max();
			// show highscore
			if( highscore.is_new_highscore(game.score()) ) {
				hi_id = highscore.get_new_highscore(renderer, game.score());
			}
			//renderer.RenderTrack();
			renderer.RenderBlank();
			highscore.show_highscore(renderer, hi_id);
		}
	}

	return 0;
}


/* vim: set noet fenc=utf-8 ff=unix sts=0 sw=4 ts=4 : */
