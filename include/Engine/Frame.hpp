/**
    @file Frame.hpp
    @brief Manages the frame of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __FRAME__
#define __FRAME__

#include "Engine/sdl2include.hpp"
#include "Customs/Exception.hpp"

class Frame {
	public:
	    Frame(int positionX, int positionY, int width, int height);
		~Frame();
	    SDL_Rect *GetRect();

	private:
	    // Rectangular area of the frame
	    SDL_Rect originOfRectangle = {
	    	0, 0, 0, 0
	    };
};

#endif
