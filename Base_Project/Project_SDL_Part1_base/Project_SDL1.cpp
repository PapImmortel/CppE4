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
animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr, int positionX, int positionY)
{

    this->positionX_ = positionX;
    this->positionY_ = positionY;

    this->image_ptr_ = IMG_Load(file_path.c_str());
    if (!this->image_ptr_)
        throw std::runtime_error("Could not load image");
    this->window_surface_ptr_ = window_surface_ptr;
    if (!this->window_surface_ptr_)
        throw std::runtime_error(std::string(SDL_GetError()));

    this->rectangle_ = { this->positionX_, this->positionY_ ,30,30 };

}
animal::~animal()
{
    /*SDL_FreeSurface(this->window_surface_ptr_);
    SDL_FreeSurface(this->image_ptr_);*/
}
void animal::draw()
{
    this->rectangle_ = { this->positionX_, this->positionY_ ,30,30 };
    SDL_BlitScaled(this->image_ptr_,NULL,this->window_surface_ptr_, &this->rectangle_);
}
void animal::Deplacement(int pX, int pY)
{
    this->positionX_ += pX;
    this->positionY_ += pY;

}
int animal::getPosX()
{
    return this->positionX_;
}
int animal::getPosY()
{
    return this->positionY_;
}

std::string animal::getImage()
{
    return this->image_;
}
void animal::setImage(std::string image)
{
    this->image_ = image;
}
void animal::setDirectionX(int directionX)
{
    this->directionX_ = directionX;
}
void animal::setDirectionY(int directionY)
{
    this->directionY_ = directionY;
}
int animal::getDirectionX()
{
    return this->directionX_;
}
int animal::getDirectionY()
{
    return this->directionY_;
}
void animal::setSpeed(int speed)
{
    this->speed_ = speed;
}
int animal::getSpeed()
{
    return this->speed_;
}
//class ground

sheep::sheep(SDL_Surface* window_surface_ptr, int positionX, int positionY) :animal("sheep.png", window_surface_ptr, positionX, positionY)
{
    this->setDirectionX(1 * this->getSpeed());
    this->setDirectionY(1 * this->getSpeed());
    setImage("sheep.png");
}
sheep::~sheep() 
{
}

void sheep::move()
{
    if (getDirectionX() + getPosX() <= 0 || getDirectionX() + getPosX() >= frame_width)
    {
        setDirectionX(-getDirectionX());
    }
    if (getDirectionY() + getPosY() <= 0 || getDirectionY() + getPosY() >= frame_height)
    {
        setDirectionY(-getDirectionY());
    }
    Deplacement(getDirectionX(), getDirectionY());
}
wolf::wolf(SDL_Surface* window_surface_ptr, int positionX, int positionY) : animal("wolf.png", window_surface_ptr, positionX, positionY)
{
    this->setDirectionX(1 * this->getSpeed());
    this->setDirectionY(1 * this->getSpeed());
    setImage("wolf.png");

}
wolf::~wolf()
{
}

void wolf::move()
{
    Deplacement(getDirectionX(), getDirectionY());
}


ground::ground(SDL_Surface* window_surface_ptr)
{
    this->window_surface_ptr_ = window_surface_ptr;
    if (!window_surface_ptr_)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
    this->color = SDL_MapRGB(this->window_surface_ptr_->format, 0, 255, 0);
    SDL_FillRect(window_surface_ptr_, NULL, color);
    this->rectangle = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,frame_width, frame_height };
    std::vector<std::shared_ptr<animal>> animalList = {};
    /*this->lou = wolf(this->window_surface_ptr_, 1000, 100);
    this->mout = sheep(this->window_surface_ptr_, 0, 100);*/

}
ground::~ground()
{
    SDL_FreeSurface(window_surface_ptr_);
   while (!animalList.empty())
    {
        delete &animalList.back();
        animalList.pop_back();
    }
}
void ground::add_animal(std::shared_ptr<animal> newAnimal)
{
    animalList.push_back(newAnimal);
}

void ground::update()
{
    SDL_FillRect(window_surface_ptr_, NULL, this->color);

    for (auto&& animal_ : animalList)
    {
        if (animal_->getImage() == "sheep.png")
        {
            int procheX = 101;
            int procheY = 101;
            for (auto&& animal2_ : animalList)
            {
                if (animal2_->getImage() == "wolf.png")
                {
                    if (abs(animal2_->getPosX() - animal_->getPosX()) <=  100)
                    {
                        if (abs(animal2_->getPosY() - animal_->getPosY()) <= 100) 
                        {
                            if (abs(animal2_->getPosX() - animal_->getPosX()) <= abs(procheX))
                            {
                                procheX = animal2_->getPosX() - animal_->getPosX();
                            }
                            if (abs(animal2_->getPosY() - animal_->getPosY()) <= abs(procheY))
                            {
                                procheY = animal2_->getPosY() - animal_->getPosY();
                            }

                        }
                    }
                }
            }
            if (procheX < 0)
            {
                animal_->setSpeed(3);
                animal_->setDirectionX(1*animal_->getSpeed());
            }
            else if(procheX < 101 && procheX > 0)
            {
                animal_->setSpeed(3);
                animal_->setDirectionX(-1 * animal_->getSpeed());
            }
            else if(procheX==0)
            {
                animal_->setSpeed(3);
                animal_->setDirectionX(0);
            }
            if (procheY < 0)
            {
                animal_->setSpeed(3);
                animal_->setDirectionY(1 * animal_->getSpeed());
            }
            else if (procheY < 101 && procheY > 0)
            {
                animal_->setSpeed(3);
                animal_->setDirectionY(-1 * animal_->getSpeed());
            }
            else if (procheY == 0)
            {
                animal_->setSpeed(3);
                animal_->setDirectionY(0);
            }
            if (procheX >= 101 && procheY >= 101)
            {
                if (animal_->getSpeed() > 1)
                {
                    animal_->setDirectionX(animal_->getDirectionX()/ animal_->getSpeed());
                    animal_->setDirectionY(animal_->getDirectionY() / animal_->getSpeed());

                    animal_->setSpeed(1);

                }
            }
        }
        else if (animal_->getImage() == "wolf.png")
        {
            int procheX = frame_width;
            int procheY = frame_height;
            for (auto&& animal2_ : animalList)
            {
                if (animal2_->getImage() == "sheep.png")
                {
                    if (abs(animal2_->getPosX() - animal_->getPosX()) + abs(animal2_->getPosY() - animal_->getPosY()) <= abs(procheX) + abs(procheY))
                    {
                        procheX = animal2_->getPosX() - animal_->getPosX();
                        procheY = animal2_->getPosY() - animal_->getPosY();
                    }


                }
            }
            if (abs(procheX) > abs(procheY))
            {
                animal_->setDirectionY(0);
                if (procheX < 0)
                {
                    animal_->setDirectionX(-1 * animal_->getSpeed());
                }
                else if (procheX > 0)
                {
                    animal_->setDirectionX(1 * animal_->getSpeed());
                }
            }
            else if (abs(procheX) < abs(procheY))
            {
                animal_->setDirectionX(0);

                if (procheY < 0)
                {
                    animal_->setDirectionY(-1 * animal_->getSpeed());
                }
                else if (procheY > 0)
                {
                    animal_->setDirectionY(1 * animal_->getSpeed());
                }
            }
            else
            {
                if (procheX < 0)
                {
                    animal_->setDirectionX(-1 * animal_->getSpeed());
                }
                else if (procheX > 0)
                {
                    animal_->setDirectionX(1 * animal_->getSpeed());
                }
                if (procheY < 0)
                {
                    animal_->setDirectionY(-1 * animal_->getSpeed());
                }
                else if (procheY > 0)
                {
                    animal_->setDirectionY(1 * animal_->getSpeed());
                }
            }


        }

        animal_->move();
        animal_->draw();

    }
    

    /*this->mout.move();
    this->lou.Deplacement(-1, 1);
    this->lou.draw();

    this->mout.draw();*/
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
    ground_.add_animal(std::make_shared<sheep>(window_surface_ptr_, 0, 100));
    ground_.add_animal(std::make_shared<sheep>(window_surface_ptr_, 500, 100));

    ground_.add_animal(std::make_shared<wolf>(window_surface_ptr_, 1000, 100));

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
        ground_.update();
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
