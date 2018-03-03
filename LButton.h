#ifndef LButton_h
#define LButton_h
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

//Set the enumeration of the states of the buttons
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 13
};

class LButton
{
public:
    //Initializes internal variables
    LButton();

    //Sets top left position
    void setPosition( int x, int y );

    //Handles mouse event
    void handleEvent( SDL_Event* e, int );

    //Shows button sprite
    void render(int);

    int getenum();
    int clickCount;

private:
    //Top left position
    SDL_Point mPosition;

    //Currently used global sprite
    LButtonSprite mCurrentSprite;
};

#endif /* LButton_h */
