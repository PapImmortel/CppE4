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
animal::animal()
{
    ;
}
animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr,SDL_Rect* rectangle)
{
    this->window_surface_ptr_ = window_surface_ptr;
    this->image_ptr_ = IMG_Load(file_path.c_str());
    this->rectangle_ = rectangle;

}
animal::~animal()
{
    SDL_FreeSurface(this->window_surface_ptr_);
    SDL_FreeSurface(this->image_ptr_);
    delete & rectangle_;
}
void animal::draw()
{
    SDL_BlitScaled(this->image_ptr_,NULL,this->window_surface_ptr_, this->rectangle_);
}

//class ground

sheep::sheep(const std::string& file_path, SDL_Surface* window_surface_ptr, SDL_Rect* rectangle, int positionX_, int positionY_) :animal(file_path, window_surface_ptr, rectangle)
{
    this->positionX = positionX_;
    this->positionY = positionY_;
}
sheep::~sheep() 
{
    SDL_FreeSurface(this->window_surface_ptr_);
    SDL_FreeSurface(this->image_ptr_);
    delete& rectangle_;
}

ground::ground() { ; }
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
void ground::add_animal(const std::string& file_path, SDL_Surface* window_surface_ptr,SDL_Rect* rectangle)
{
    animalList.push_back(&animal(file_path, window_surface_ptr,rectangle));
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
    
    return 0;
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
