// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}


//class animal
animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr)
{
    window_surface_ptr_ = window_surface_ptr;
    image_ptr_ = load_surface_for(file_path,window_surface_ptr);

}
animal::~animal()
{
    SDL_FreeSurface(window_surface_ptr_);
    delete image_ptr_;

}
void animal::draw()
{
    SDL_Surface(window_surface_ptr_);
}

//class ground

ground::ground(SDL_Surface* window_surface_ptr)
{
    window_surface_ptr_ = window_surface_ptr;
    std::vector<animal*> animalList = {};


}
ground::~ground()
{
    SDL_FreeSurface(window_surface_ptr_);
    delete & animalList;
}
void ground::add_animal(const std::string& file_path, SDL_Surface* window_surface_ptr)
{
    animalList.push_back(&animal(file_path, window_surface_ptr));
}
void ground::update()
{
}
application::application(unsigned n_sheep, unsigned n_wolf)
{
    ground_ = ground(window_surface_ptr_);

}

application::~application()
{
    SDL_FreeSurface(window_surface_ptr_);
    SDL_DestroyWindow(window_ptr_);
    delete &window_event_;
    delete &ground_;

}
int application::loop(unsigned period)
{
    auto currentTime = SDL_GetTicks();
    while (currentTime < period)
    {
        SDL_Delay(20);
        SDL_UpdateWindowSurface(window_ptr_);
    }
    

}

namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

    SDL_Surface* load_surface_for(const std::string& path,
                              SDL_Surface* window_surface_ptr) 
    {

    // Helper function to load a png for a specific surface
    // See SDL_ConvertSurface
    }
} // namespace
