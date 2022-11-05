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


    this->image_ptr_ = IMG_Load(file_path.c_str());
    if (!this->image_ptr_)
        throw std::runtime_error("Could not load image");
    this->window_surface_ptr_ = window_surface_ptr;
    if (!this->window_surface_ptr_)
        throw std::runtime_error(std::string(SDL_GetError()));

    this->rectangle_ = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED ,30,30 };
    int IMG_Blit = SDL_BlitScaled(this->image_ptr_, NULL, this->window_surface_ptr_, &this->rectangle_);
    if (IMG_Blit != 0)
        throw std::runtime_error("Blitzing error! "
            "SDL_image Error: " +
            std::string(SDL_GetError()));
}
animal::~animal()
{
    SDL_FreeSurface(this->window_surface_ptr_);
    SDL_FreeSurface(this->image_ptr_);
    delete & rectangle_;
}
void animal::draw()
{
    SDL_BlitScaled(this->image_ptr_,NULL,this->window_surface_ptr_, &this->rectangle_);
}

//class ground

sheep::sheep(const std::string& file_path, SDL_Surface* window_surface_ptr, int positionX_, int positionY_) :animal(file_path, window_surface_ptr)
{
    this->positionX = positionX_;
    this->positionY = positionY_;
}
sheep::~sheep() 
{
}

ground::ground(SDL_Surface* window_surface_ptr)
{
    this->window_surface_ptr_ = window_surface_ptr;
    Uint32 color = SDL_MapRGB(this->window_surface_ptr_->format, 0, 255, 0);
    SDL_FillRect(window_surface_ptr_, NULL, color);
    this->rectangle = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,frame_width, frame_height };
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
    window_ptr_ = SDL_CreateWindow("fenetre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, frame_width, frame_height, SDL_WINDOW_SHOWN);
    if (!window_ptr_)
        throw std::runtime_error(std::string(SDL_GetError()));
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
    if (!window_surface_ptr_)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
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
    /*auto currentTime = SDL_GetTicks();
    while (currentTime < period)
    {
        SDL_Delay(20);
        SDL_UpdateWindowSurface(window_ptr_);
    }
    
    return 0;*/
    this->ground_.update();

    SDL_UpdateWindowSurface(window_ptr_);

    auto start = SDL_GetTicks();

    SDL_Event e;
    bool quit = false;
    while (!quit && (SDL_GetTicks() - start < period)) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
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
