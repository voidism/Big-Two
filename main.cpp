#include"Deckofcards.h"
#include"Handcard.h"
#include"Ltexture.h"
#include"LButton.h"
#include"Four.h"
#include"Straight.h"
#include<sstream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include "SDL.h"

using namespace std;

vector<Card> gvector;
vector<int> gintvector;

//Screen dimension constants
const int SCREEN_WIDTH = 780;
const int SCREEN_HEIGHT = 480;

//The color of the words on the screen
SDL_Color textColor = { 255, 255, 255 };
SDL_Color textColor2 = { 255, 0, 0 };

//Three types of button constants
const int BUTTON_WIDTH = 60;
const int BUTTON_HEIGHT = 170;
const int BUTTON_WIDTH2 = 150;
const int BUTTON_HEIGHT2 = 56;
const int BUTTON_WIDTH3 = 100;
const int BUTTON_HEIGHT3 = 60;
const int BUTTON_WIDTH4 = 240;
const int BUTTON_HEIGHT4 = 28;
const int TOTAL_BUTTONS = 13;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(vector<Card> &);

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//The textures(photoes and words) putted on the screen
SDL_Rect CardButtons[ BUTTON_SPRITE_TOTAL ];
LTexture CardTexture[TOTAL_BUTTONS];
LTexture CardTexture2[TOTAL_BUTTONS];
LTexture BackgroundTexture;
LTexture goTexture;
LTexture passTexture;
LTexture playerTextTexture;
LTexture compTextTexture;
LTexture FinalTextTexture[2];
LTexture LeftCardTexture[3];
LTexture mcardTexture[5];
LTexture mcardTexture2[5];
LTexture whiteTexture[18];
LTexture errorTexture;
LTexture startTexture;

//Button objects
LButton gButtons[ TOTAL_BUTTONS ];
LButton goButton;
LButton passButton;
LButton startButton;

//The Fibonacci function, I use it to achieve program delay after the game is over.
int Fibonacci(int x)
{
    if(x==0 || x==1 || x==2)
    {
        return 1;
    }
    else
    {
        return Fibonacci(x-1)+Fibonacci(x-2);
    }
}

//The following defines each LTexture class member functions
LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

//The following defines each LButton class member functions
LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    clickCount=0;
}

void LButton::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e , int type)
{
    //If mouse event happened
    if( e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;
        int WIDTH=0;
        int HEIGHT=0;

        if(type==1)
        {
            WIDTH=BUTTON_WIDTH;
            HEIGHT=BUTTON_HEIGHT;
        }
        else if(type==2)
        {
            WIDTH=BUTTON_WIDTH2;
            HEIGHT=BUTTON_HEIGHT2;
        }
        else if(type==3)
        {
            WIDTH=BUTTON_WIDTH3;
            HEIGHT=BUTTON_HEIGHT3;
        }
        else if(type==4)
        {
            WIDTH=BUTTON_WIDTH4;
            HEIGHT=BUTTON_HEIGHT4;
        }

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + WIDTH )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + HEIGHT )
        {
            inside = false;
        }

        //Mouse is outside button
        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    clickCount++;
                    break;

                case SDL_MOUSEBUTTONUP:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void LButton::render(int i)
{
    //Show current button sprite
    CardTexture[i].render( mPosition.x, mPosition.y, &CardButtons[ i ] );
    CardTexture2[i].render( mPosition.x, mPosition.y, &CardButtons[ i ] );
}

int LButton::getenum()
{
    return mCurrentSprite;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(Handcard &player)
{
    /*for(int i=0; i<13; i++)
    {
        CardTexture[i].free();
        CardTexture2[i].free();
    }*/

    //Loading success flag
    bool success = true;

    //Load text
    gFont = TTF_OpenFont( "timesbd.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        playerTextTexture.setBlendMode( SDL_BLENDMODE_BLEND );
        compTextTexture.setBlendMode( SDL_BLENDMODE_BLEND );
        FinalTextTexture[0].setBlendMode(SDL_BLENDMODE_BLEND);
        FinalTextTexture[1].setBlendMode(SDL_BLENDMODE_BLEND);
        LeftCardTexture[0].setBlendMode(SDL_BLENDMODE_BLEND);
        LeftCardTexture[1].setBlendMode(SDL_BLENDMODE_BLEND);
        LeftCardTexture[2].setBlendMode(SDL_BLENDMODE_BLEND);
        errorTexture.setBlendMode(SDL_BLENDMODE_BLEND);
        errorTexture.loadFromRenderedText( "ERROR!", textColor2 );
        startTexture.setBlendMode(SDL_BLENDMODE_BLEND);
        startTexture.loadFromRenderedText("Click here to start", textColor);
        if( !playerTextTexture.loadFromRenderedText( "It's your turn!", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !compTextTexture.loadFromRenderedText( "It's computer's turn!", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !FinalTextTexture[0].loadFromRenderedText( "You Win!", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !FinalTextTexture[1].loadFromRenderedText( "You Lose!", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    //Load sprites
    for(size_t i=0; i<player.hand.size(); i++)
    {
        CardButtons[ i ].x = i*60;
        CardButtons[ i ].y = 290;
        CardButtons[ i ].w = BUTTON_WIDTH;
        CardButtons[ i ].h = BUTTON_HEIGHT;

        stringstream a;
        a.str("");
        a << player.hand[i].getsuit() << "s.png";
        stringstream b;
        b.str("");
        b << player.hand[i].getface()+2 << ".png";
        if( !CardTexture[i].loadFromFile( a.str().c_str() ) )
        {
            printf( "Failed to load button sprite texture!\n" );
            success = false;
        }
        else
        {
            CardTexture[i].setBlendMode( SDL_BLENDMODE_BLEND );
        }
        if( !CardTexture2[i].loadFromFile( b.str().c_str() ) )
        {
            printf( "Failed to load button sprite texture!\n" );
            success = false;
        }
        else
        {
                CardTexture2[i].setBlendMode( SDL_BLENDMODE_BLEND );
        }
    }
    for(int i=0; i<13; i++)
    {
        whiteTexture[i].setBlendMode(SDL_BLENDMODE_BLEND);
        whiteTexture[i].loadFromFile("white.png");
    }
    if( !BackgroundTexture.loadFromFile( "title.png" ) )
    {
        printf( "Failed to load button sprite texture!\n" );
        success = false;
    }
    else
    {
        //blank
    }
    if( !goTexture.loadFromFile( "go.png" ) )
    {
        printf( "Failed to load button sprite texture!\n" );
        success = false;
    }
    else
    {
        goTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
    if( !passTexture.loadFromFile( "pass.png" ) )
    {
        printf( "Failed to load button sprite texture!\n" );
        success = false;
    }
    else
    {
        passTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
    return success;
}

//A simplified type of the loadMedia function
bool loadMedia2(Handcard &player)
{
    /*for(int i=0; i<13; i++)
    {
        CardTexture[i].free();
        CardTexture2[i].free();
    }*/

    //Loading success flag
    bool success = true;

    //Load sprites
    for(size_t i=0; i<player.hand.size(); i++)
    {
        stringstream a;
        a.str("");
        a << player.hand[i].getsuit() << "s.png";
        stringstream b;
        b.str("");
        b << player.hand[i].getface()+2 << ".png";
        CardTexture[i].loadFromFile( a.str().c_str() );
        CardTexture2[i].loadFromFile( b.str().c_str() );
    }
    for(int i=0; i<13; i++)
    {
        whiteTexture[i].loadFromFile("white.png");
    }

    return success;
}

//The third type of loadMedia function
bool loadMedia3(vector<Card> &gvector)
{
    for(int i=0; i<5; i++)
    {
        mcardTexture[i].free();
        mcardTexture2[i].free();
    }
    bool success = true;
    if(gvector.size()==0)
    {
        mcardTexture[0].setBlendMode(SDL_BLENDMODE_BLEND);
        mcardTexture[0].loadFromRenderedText("PASS!", textColor);
    }
    else
    {
        for(size_t i=0; i<gvector.size(); i++)
        {
            stringstream a;
            a.str("");
            a << gvector[i].getsuit() << "s.png";
            stringstream b;
            b.str("");
            b << gvector[i].getface()+2 << ".png";
            mcardTexture[i].setBlendMode( SDL_BLENDMODE_BLEND );
            mcardTexture2[i].setBlendMode( SDL_BLENDMODE_BLEND );
            mcardTexture[i].loadFromFile( a.str().c_str() );
            mcardTexture2[i].loadFromFile( b.str().c_str() );
        }
    }
    for(int i=13; i<18; i++)
    {
        whiteTexture[i].loadFromFile("white.png");
        whiteTexture[i].setBlendMode(SDL_BLENDMODE_BLEND);
    }

    return success;
}

void close()
{
    //Free loaded images(textures)
    for(int i=0; i<13; i++)
    {
        CardTexture[i].free();
        CardTexture2[i].free();
    }
    for(int i=0; i<5; i++)
    {
        mcardTexture2[i].free();
        mcardTexture[i].free();
    }
    for(int i=0; i<18; i++)
    {
        whiteTexture[i].free();
    }
    startTexture.free();
    BackgroundTexture.free();
    goTexture.free();
    passTexture.free();
    playerTextTexture.free();
    compTextTexture.free();
    FinalTextTexture[1].free();
    FinalTextTexture[0].free();
    LeftCardTexture[0].free();
    LeftCardTexture[1].free();
    LeftCardTexture[2].free();
    errorTexture.free();

    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void selectionSort(vector<Card> &, int);
void whatdoyouhave(vector<Card> &, int &);

int main(int argc, char *argv[])/*In this program, I use selection sort to simplify the determination of the type of cards
		    each person has.*/
{
    srand(time(0));
    cout<<"Before playing this game, please read the PDF file first."<<endl;
    cout<<"The PDF file is the tutorial of this game."<<endl;
    system("PAUSE");
    //Definition of some constants that will be used to control the program
    int whoturn=0;
    int whowin=0;
    int countpr1=0, countpr2=0, countpr3=0, countuser=0;
    bool stop=0;
    bool error=0;

    //Construction of a complete deck of cards
    Deckofcards test2;
    test2.shuffle();

    //Construction of four sets of cards. Three sets are for computers, one for the player.
    Handcard pr1,pr2,pr3,user;
    for(int i=0;i<13;i++)
    {
        pr1.hand.push_back(test2.dealCard());
    }
    for(int i=0;i<13;i++){
        pr2.hand.push_back(test2.dealCard());
    }
    for(int i=0;i<13;i++){
        pr3.hand.push_back(test2.dealCard());
    }
    for(int i=0;i<13;i++){
        user.hand.push_back(test2.dealCard());
    }

    //Some initialization works for the four sets of cards, make them easier to compute
    pr1.sort();
    pr1.classify();
    pr1.printall();
    pr2.sort();
    pr2.classify();
    pr2.printall();
    pr3.sort();
    pr3.classify();
    pr3.printall();
    user.sort();
    user.classify();
    user.printall();

    cout<<"start game";

    //Parameters for the play card AI(artificial intelligence)
    int inn=0;
    Play i;

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia(user) )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Initialize buttons
            for(int i=0; i<user.hand.size();i++)
            {
                gButtons[i].setPosition(i*60, 290);
            }
            goButton.setPosition(620, 100);
            passButton.setPosition(620, 160);
            startButton.setPosition(260, 230);

            //While application is running

            //This while loop represents the start page
            while(!quit)
            {
                Uint8 x=255;
                while(x>6)
                {
                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );
                    x-=5;
                    BackgroundTexture.render(0, 0);
                    startTexture.setAlpha(x);
                    startTexture.render(260, 230);
                    //Update screen
                    SDL_RenderPresent( gRenderer );
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        startButton.handleEvent(&e, 4);
                    }
                    if(startButton.clickCount!=0)
                    {
                        break;
                    }
                }
                if(startButton.clickCount!=0)
                {
                    break;
                }
                while(x<249)
                {
                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );
                    x+=5;
                    BackgroundTexture.render(0, 0);
                    startTexture.setAlpha(x);
                    startTexture.render(260, 230);
                    //Update screen
                    SDL_RenderPresent( gRenderer );
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        startButton.handleEvent(&e, 4);
                    }
                    if(startButton.clickCount!=0)
                    {
                        break;
                    }
                }
                if(startButton.clickCount!=0)
                {
                    break;
                }
            }

            //This while loop represents the "fade in" special effect
            while(!quit)
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }
                static Uint8 x=0;
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render background
                BackgroundTexture.setAlpha(x);
                BackgroundTexture.render( 0, 0 );

                //Render front blended
                goTexture.setAlpha(x);
                goTexture.render(620, 100);
                passTexture.setAlpha(x);
                passTexture.render(620, 160);
                compTextTexture.setAlpha(x);
                compTextTexture.render(20, 30);
                stringstream text[3];
                text[0] << "Computer 1 have " << pr1.hand.size() << " cards left.";
                text[1] << "Computer 2 have " << pr2.hand.size() << " cards left.";
                text[2] << "Computer 3 have " << pr3.hand.size() << " cards left.";
                for(int i=0; i<3; i++)
                {
                    LeftCardTexture[i].loadFromRenderedText( text[i].str().c_str(), textColor );
                    LeftCardTexture[i].setAlpha(x);
                    LeftCardTexture[i].render(340, i*30);
                }

                for(int i=0; i<13; i++)
                {
                    whiteTexture[i].setAlpha(x-20>0?x:0);
                    CardTexture[i].setAlpha(x);
                    CardTexture2[i].setAlpha(x);
                    whiteTexture[i].render(i*60-5, 340);
                    CardTexture[i].render( i*60, 360 );
                    CardTexture2[i].render( i*60+6, 410 );
                }
                //Update screen
                SDL_RenderPresent( gRenderer );
                x+=2;
                if(x>=253)
                {
                    break;
                }
            }

            //This is the main while loop to control everything during playing the game
            while( !quit )
            {

                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    //Handle button events
                    goButton.handleEvent(&e, 2);
                    passButton.handleEvent(&e, 2);

                    for( int i = 0; i < TOTAL_BUTTONS; ++i )
                    {
                        gButtons[ i ].handleEvent( &e, 1 );
                    }
                }

                stringstream text[3];

                //The AI works here
                if(countpr1==0 && stop==0 && (inn!=0||pr1.club3()))
                {
                    cout<<"player1's turn\n";whoturn=0;
                    i=pr1.playcardAI(i, inn, gvector);
                    loadMedia3(gvector);
                    pr1.popout();
                    inn++;
                }
                else if(countpr2==50 && stop==0 && (inn!=0||pr2.club3()))
                {
                    cout<<"player2's turn\n";whoturn=0;
                    i=pr2.playcardAI(i, inn, gvector);
                    loadMedia3(gvector);
                    pr2.popout();
                    inn++;
                }
                else if(countpr3==100 && stop==0 && (inn!=0||pr3.club3()))
                {
                    cout<<"player3's turn\n";whoturn=0;
                    i=pr3.playcardAI(i, inn, gvector);
                    loadMedia3(gvector);
                    pr3.popout();
                    stop=1;
                    inn++;
                }
                if(inn!=0||user.club3())
                {
                    static int hehe=0;
                    if(user.club3() && hehe==0)
                    {
                        stop=1;
                        hehe=1;
                    }
                    if(stop==1)
                    {
                        //cout<<"user's turn\n";
                        whoturn=1;
                        gintvector.clear();
                        if(goButton.clickCount!=0 || passButton.clickCount!=0)
                        {
                            user.sort();
                            user.userclassify();
                            for(int k=0; k<user.hand.size(); k++)
                            {
                                if(gButtons[k].clickCount%2==1 && passButton.clickCount==0)
                                {
                                    gintvector.push_back(k);
                                }
                            }
                            if(user.judgecard(i,inn,gintvector)==0 || (goButton.clickCount!=0 && gintvector.size()==0))
                            {
                                error=1;
                                gintvector.clear();
                                goButton.clickCount=0;
                                passButton.clickCount=0;
                                for(int i=0; i<user.hand.size(); i++)
                                {
                                    gButtons[i].clickCount=0;
                                }
                            }
                            else
                            {
                                error=0;
                                i=user.userplaycard(i, gintvector, gvector);
                                loadMedia3(gvector);
                                user.popout();
                                loadMedia2(user);
                                countpr1=-50;
                                countpr2=-50;
                                countpr3=-50;
                                countuser=-50;
                                goButton.clickCount=0;
                                passButton.clickCount=0;
                                for(int i=0; i<user.hand.size(); i++)
                                {
                                    gButtons[i].clickCount=0;
                                }
                                stop=0;
                                inn++;
                            }
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render background
                BackgroundTexture.render( 0, 0 );

                //Render front blended
                goTexture.setAlpha(goButton.getenum() == 2 ? 0 : 255);
                goTexture.render(620, 100);
                passTexture.setAlpha(passButton.getenum() == 2 ? 0 : 255);
                passTexture.render(620, 160);
                playerTextTexture.setAlpha(whoturn==1?255:0);
                playerTextTexture.render(20, 30);
                compTextTexture.setAlpha(whoturn==0?255:0);
                compTextTexture.render(20, 30);
                errorTexture.setAlpha(error==0?0:255);
                errorTexture.render(100, 180);

                text[0] << "Computer 1 have " << pr1.hand.size() << " cards left.";
                text[1] << "Computer 2 have " << pr2.hand.size() << " cards left.";
                text[2] << "Computer 3 have " << pr3.hand.size() << " cards left.";
                for(int i=0; i<3; i++)
                {
                    LeftCardTexture[i].loadFromRenderedText( text[i].str().c_str(), textColor );
                    LeftCardTexture[i].render(340, i*30);
                }

                for(int i=0;i<user.hand.size();i++)
                {
                    if(gButtons[i].clickCount%2==0)
                    {
                        whiteTexture[i].render(i*60-5, 340);
                        CardTexture[i].render( i*60, 360 );
                        CardTexture2[i].render( i*60+6, 410 );
                    }
                    else
                    {
                        whiteTexture[i].render(i*60-5, 290);
                        CardTexture[i].render( i*60, 310 );
                        CardTexture2[i].render( i*60+6, 360 );
                    }
                }
                if(gvector.size()==0)
                {
                    mcardTexture[0].render(300, 170);
                }
                else
                {
                    for(int i=0; i<gvector.size(); i++)
                    {
                        whiteTexture[i+13].render(300+i*60-5, 150);
                        mcardTexture[i].render(300+i*60, 170);
                        mcardTexture2[i].render(306+i*60, 220);
                    }
                }

                //Update screen
                SDL_RenderPresent( gRenderer );

                //Control some integers
                countpr1++;
                countpr2++;
                countpr3++;
                countuser++;

                //Determine whether the game is over.(Someone has no card in his hands)
                if(pr1.hand.size()==0)
                {
                    cout << "pr1 wins" << endl;
                    whowin=1;
                    break;
                }
                else if(pr2.hand.size()==0)
                {
                    cout << "pr2 wins" << endl;
                    whowin=1;
                    break;
                }
                else if(pr3.hand.size()==0)
                {
                    cout << "pr3 wins" << endl;
                    whowin=1;
                    break;
                }
                else if(user.hand.size()==0)
                {
                    cout << "user wins" << endl;
                    whowin=0;
                    break;
                }
            }
        }
    }
    //The last time to refresh the screen
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    //Render background
    BackgroundTexture.render( 0, 0 );

    //Render front blended
    goTexture.setAlpha(goButton.getenum() == 2 ? 0 : 255);
    goTexture.render(620, 100);
    passTexture.setAlpha(passButton.getenum() == 2 ? 0 : 255);
    passTexture.render(620, 160);
    playerTextTexture.setAlpha(whoturn==1?255:0);
    playerTextTexture.render(20, 30);
    compTextTexture.setAlpha(whoturn==0?255:0);
    compTextTexture.render(20, 30);

    stringstream text[3];
    text[0] << "Computer 1 have " << pr1.hand.size() << " cards left.";
    text[1] << "Computer 2 have " << pr2.hand.size() << " cards left.";
    text[2] << "Computer 3 have " << pr3.hand.size() << " cards left.";
    for(int i=0; i<3; i++)
    {
        LeftCardTexture[i].loadFromRenderedText( text[i].str().c_str(), textColor );
        LeftCardTexture[i].render(340, i*30);
    }
    for(int i=0;i<user.hand.size();i++)
    {
        if(gButtons[i].clickCount%2==0)
        {
            whiteTexture[i].render(i*60-5, 340);
            CardTexture[i].render( i*60, 360 );
            CardTexture2[i].render( i*60+6, 410 );
        }
        else
        {
            whiteTexture[i].render(i*60-5, 290);
            CardTexture[i].render( i*60, 310 );
            CardTexture2[i].render( i*60+6, 360 );
        }
    }
    if(gvector.size()==0)
    {
        mcardTexture[0].render(300, 170);
    }
    else
    {
        for(int i=0; i<gvector.size(); i++)
        {
            whiteTexture[i+13].render(300+i*60-5, 150);
            mcardTexture[i].render(300+i*60, 170);
            mcardTexture2[i].render(306+i*60, 220);
        }
    }

    //Print the "You Win!" or "You Lose!" message before the end of the program
    FinalTextTexture[0].setAlpha(whowin==0?255:0);
    FinalTextTexture[1].setAlpha(whowin==1?255:0);
    FinalTextTexture[0].render(100, 100);
    FinalTextTexture[1].render(100, 100);
    SDL_RenderPresent( gRenderer );

    //I use Fibonacci function(recursive type) to achieve program delay of the final screen.
    for(int k=1; k<42; k++)
    {
        Fibonacci(k);
    }

    //Free resources and close SDL
    close();
}


void whatdoyouhave(vector<Card> &array1, int &score)
{
    for(size_t i=0; i<10; i++)
    {
        if(array1[i].getface()==array1[i+1].getface()&&array1[i+1].getface()==array1[i+2].getface()&&array1[i+2].getface()==array1[i+3].getface())
        {
            cout << "A four of a kind!" << endl;score+=6;
        }
    }
    for(size_t i=0; i<11; i++)
    {
        if(array1[i].getface()==array1[i+1].getface())
        {
            cout << "A pair!" << endl;score+=1;
            for(size_t j=0; j<12; j++)
            {
                if(array1[j].getface()==array1[j+1].getface()&&array1[j+1].getface()==array1[j+2].getface())
                {
                    if(array1[i].getface()!=array1[j].getface())
                    {
                        cout << "A Fullhouse!" << endl;score+=3;
                    }
                }
            }
        }
    }
    for(size_t i=0; i<9; i++)
    {
        int x;
        x=array1[i].getface();
        for(size_t j=i+1; j<10; j++)
            {
                if(array1[j].getface()==x+1)
                {
                    for(size_t k=j+1; k<11; k++)
                    {
                        if(array1[k].getface()==x+2)
                        {
                            for(size_t l=k+1; l<12; l++)
                            {
                                if(array1[l].getface()==x+3)
                                {
                                    for(size_t m=0; m<13; m++)
                                    {
                                        if(array1[m].getface()==x+4)
                                        {
                                            if(array1[i].getsuit()==array1[j].getsuit()&&
                                               array1[j].getsuit()==array1[k].getsuit()&&
                                               array1[k].getsuit()==array1[l].getsuit()&&
                                               array1[l].getsuit()==array1[m].getsuit())
                                            {
                                                cout << "A straight flush!" << endl;score+=10;
                                            }
                                            else
                                            {
                                                cout << "A straight!" << endl;score+=5;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
    }
    for(size_t i=0; i<4; i++)
    {
        if(array1[i].getface()==1)
        {
            for(size_t j=i+1; j<13; j++)
            {
                if(array1[j].getface()==10)
                {
                    for(size_t k=j+1; k<13; k++)
                    {
                        if(array1[k].getface()==11)
                        {
                            for(size_t l=k+1; l<13; l++)
                            {
                                if(array1[l].getface()==12)
                                {
                                    for(size_t m=0; m<13; m++)
                                    {
                                        if(array1[m].getface()==13)
                                        {
                                            if(array1[i].getsuit()==array1[j].getsuit()&&
                                               array1[j].getsuit()==array1[k].getsuit()&&
                                               array1[k].getsuit()==array1[l].getsuit()&&
                                               array1[l].getsuit()==array1[m].getsuit())
                                            {
                                                cout << "A straight flush!" << endl;score+=10;
                                            }
                                            else
                                            {
                                                cout << "A straight!" << endl;score+=5;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(score==0)
	{
		cout << "Nothing special!" << endl;
	}
}


void selectionSort(vector<Card> &aarray, int aanswer)
{
	static int n=12;
	int minimum=aarray[n].getface();
	int minindex=n;

	if(aanswer==1)
	{
		//cout << "\nThe array after sorting: \n" << aarray[0] << endl;
	}
	else
	{
		for(int i=n-1; i>=0; i--) // Want to find an integer to sort.
		{
			if(aarray[i].getface()<minimum)
			{
				minimum=aarray[i].getface();
				minindex=i;
			}
		}

		Card change(1,1); // Interchanging the value, performing sorting action.
		change=aarray[minindex];
		aarray.erase(aarray.begin()+minindex);
		aarray.push_back(change);

		n--;

		/*cout << "\nAfter " << n << " times of sorting, the array becomes: \n";
		for(int i=0; i<aanswer; i++)
		{
			cout << aarray[i] << "  ";
		}
		cout << endl;*/

		if(n!=0)
		{
			selectionSort(aarray, aanswer); // Recursive. Call "selectionSort" again.
		}
		else
		{
            n=12;
            Card ouch=aarray[0];
            aarray.erase(aarray.begin());
            aarray.push_back(ouch);
			/*cout << "\nThe array after sorting: \n";
			for(int i=0; i<aanswer; i++)
			{
				cout << aarray[i] << "  ";
			}*/
		}
	}
}
