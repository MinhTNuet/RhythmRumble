#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <bits/stdc++.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;

TTF_Font* font = NULL;

Mix_Music* music = NULL;

bool init()
{
    bool success = true;
    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
    {
        cout << "Init error SDL ERROR: " << SDL_GetError();
        success = false;
    }
    else
    {
        window=SDL_CreateWindow("Rhythm Rumble",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            cout<< "Could not create window SDL Error: " << SDL_GetError();
            success = false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer==NULL)
            {
                cout<< "Could not create renderer SDL Error: " << SDL_GetError();
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer,0,0,0,0);
                int flags = IMG_INIT_PNG;
                if(!IMG_Init(flags)&flags)
                {
                    cout << "Could not init img IMG error: " << IMG_GetError();
                    success = false;
                }

                if(TTF_Init() == -1)
                {
                    cout << "Could not init ttf TTF error: " << TTF_GetError();
                    success = false;
                }

                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
                {
                    cout<<"Could not init mix MIX error: " << Mix_GetError();
                    success = false;
                }
            }
        }
    }
    return success;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

void render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int w = SCREEN_WIDTH;
    int h = SCREEN_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderDrawLine(renderer, w/4, 0, w/4, h);
    SDL_RenderDrawLine(renderer, 2*w/4, 0, 2*w/4, h);
    SDL_RenderDrawLine(renderer, 3*w/4, 0, 3*w/4, h);
    SDL_RenderDrawLine(renderer, 0, 4*h/5, w, 4*h/5);

    SDL_RenderPresent(renderer);
}

int main( int argc, char* args[])
{
    if(!init()){
        cout<<"Failed to initialize"<<endl;
    }
    else
    {
        bool quit = false;
        SDL_Event e;
        while(!quit)
        {
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    quit = true;
                }
                render(renderer);
            }
        }

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    close();
}
