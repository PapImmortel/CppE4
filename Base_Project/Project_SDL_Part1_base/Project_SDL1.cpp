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
    this->setSpeed(1);
    this->setVivant(true);
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
SDL_Rect animal::getRectangle()
{
    return this->rectangle_;
}
void animal::setVivant(bool vivant)
{
    this->vivant_ = vivant;
}
bool animal::getVivant()
{
    return vivant_;
}


sheep::sheep(SDL_Surface* window_surface_ptr, int positionX, int positionY) :animal("sheep.png", window_surface_ptr, positionX, positionY)
{
    this->setDirectionX(1 * this->getSpeed());
    this->setDirectionY(1 * this->getSpeed());
    this->cdCop = 0;
    this->Baby = false;

    setImage("sheep.png");
}
sheep::~sheep() 
{
}

void sheep::move()
{
    if (getDirectionX() + getPosX() <= 0 || getDirectionX() + getPosX() >= frame_width-30)
    {
        setDirectionX(-getDirectionX());
    }
    if (getDirectionY() + getPosY() <= 0 || getDirectionY() + getPosY() >= frame_height-30)
    {
        setDirectionY(-getDirectionY());
    }
    Deplacement(getDirectionX(), getDirectionY());
}
bool sheep::HasBaby()
{
    return this->Baby;
}
void sheep::changeBaby()
{
    this->Baby = !(this->Baby);
}
void sheep::BabyFalse()
{
    this->Baby = false;
}
void sheep::augmentCd(int n)
{
    if (n > 0)
    {
        this->cdCop += n;
    }
}
void sheep::copBaisse(int n)
{

    if (this->cdCop >= n)
    {
        this->cdCop -= n;
    }
    else if (this->cdCop > 0 && this->cdCop < n)
    {
        this->cdCop = 0;
    }
    if (this->cdCop == 0)
    {
        return;
    }

}
int sheep::getCdCop()
{

    return this->cdCop;
}
wolf::wolf(SDL_Surface* window_surface_ptr, int positionX, int positionY) : animal("wolf.png", window_surface_ptr, positionX, positionY)
{
    this->setDirectionX(1 * this->getSpeed());
    this->setDirectionY(1 * this->getSpeed());
    this->setFood(1500);
    this->setPeur(1);

    setImage("wolf.png");

}
wolf::~wolf()
{
}
void wolf::move()
{
    Deplacement(getDirectionX(), getDirectionY());
}
void wolf::setFood(int food)
{
    food_ = food;
}
int wolf::getFood()
{
    return food_;
}
void wolf::setPeur(int peur)
{
    this->peur_ = peur;
}
int wolf::getPeur()
{
    return this->peur_;
}
dog::dog(SDL_Surface* window_surface_ptr, int positionX, int positionY) : animal("doggo.png", window_surface_ptr, positionX, positionY)
{
    this->setDirectionX(1 * this->getSpeed());
    this->setDirectionY(1 * this->getSpeed());
    bool clicPress_ = false;
    int destinationX=-1;
    int destinationY=-1;
    setImage("doggo.png");

}
dog::~dog()
{
}

void dog::move()
{
    Deplacement(getDirectionX(), getDirectionY());
}

bool dog::getClicPress()
{
    return this->clicPress_;
}
void dog::setClicPress(bool clicPress)
{
    this->clicPress_ = clicPress;
}
void dog::setDestination(int destinationX, int destinationY)
{
    this->destinationX = destinationX;
    this->destinationY = destinationY;

}
int dog::getDestinationX()
{
    return this->destinationX;
}
int dog::getDestinationY()
{
    return this->destinationY;

}

Humain::Humain(SDL_Surface* window_surface_ptr, int positionX, int positionY)
{
    this->positionX_ = positionX;
    this->positionY_ = positionY;
    this->setSpeed(3);

    this->image_ptr_ = IMG_Load("paysan.png");
    if (!this->image_ptr_)
        throw std::runtime_error("Could not load image");
    this->window_surface_ptr_ = window_surface_ptr;
    if (!this->window_surface_ptr_)
        throw std::runtime_error(std::string(SDL_GetError()));

    this->rectangle_ = { this->positionX_, this->positionY_ ,30,50 };
}
void Humain::move()
{
    directionY_ = 0;
    directionX_ = 0;
    while (SDL_PollEvent(&touche)) {
        if (touche.type = SDL_KEYDOWN)
        {
            if (touche.key.keysym.sym == SDLK_s) {
                directionY_ = 1;

            }
            if (touche.key.keysym.sym == SDLK_z) {
                directionY_ = -1;

            }
            if (touche.key.keysym.sym == SDLK_q) {
                directionX_ = -1;

            }
            if (touche.key.keysym.sym == SDLK_d) {
                directionX_ = 1;

            }
        }
    }
    positionX_ += directionX_ * getSpeed();
    positionY_ += directionY_ * getSpeed();
}
void Humain::draw()
{
    this->rectangle_ = { this->positionX_, this->positionY_ ,30,50 };
    SDL_BlitScaled(this->image_ptr_, NULL, this->window_surface_ptr_, &this->rectangle_);
}
int Humain::getPosX()
{
    return this->positionX_;
}
int Humain::getPosY()
{
    return this->positionY_;
}
void Humain::setDirectionX(int directionX)
{
    this->directionX_ = directionX;
}
void Humain::setDirectionY(int directionY)
{
    this->directionY_ = directionY;
}
int Humain::getDirectionX()
{
    return this->directionX_;
}
int Humain::getDirectionY()
{
    return this->directionY_;
}
void Humain::setSpeed(int speed)
{
    this->speed_ = speed;
}
int Humain::getSpeed()
{
    return this->speed_;
}
SDL_Rect Humain::getRectangle()
{
    return this->rectangle_;
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
    this->player = Humain(this->window_surface_ptr_, 0, 0);

    /*this->lou = wolf(this->window_surface_ptr_, 1000, 100);
    this->mout = sheep(this->window_surface_ptr_, 0, 100);*/

}
ground::~ground()
{
    SDL_FreeSurface(window_surface_ptr_);
   while (!animalList.empty())
    {
       
       animalList.erase(animalList.begin());
       
    }
}
void ground::add_animal(std::shared_ptr<animal> newAnimal)
{
    animalList.push_back(newAnimal);
}

void ground::update()
{
    SDL_FillRect(window_surface_ptr_, NULL, this->color);
    int compteur = 0;

    for (auto&& animal_ : animalList)
    {
        compteur += 1;


        if (animal_->getImage() == "sheep.png" && animal_->getVivant())
        {
            
            //
            animal_->BabyFalse();
            int procheX = 101;
            int procheY = 101;
            for (auto&& partenaire_ : animalList)
            {
                if (partenaire_->getImage() == "wolf.png" && partenaire_->getVivant())
                {
                    if (abs(partenaire_->getPosX() - animal_->getPosX()) <= 100)
                    {
                        if (abs(partenaire_->getPosY() - animal_->getPosY()) <= 100)
                        {
                            if (abs(partenaire_->getPosX() - animal_->getPosX()) <= abs(procheX))
                            {
                                procheX = partenaire_->getPosX() - animal_->getPosX();
                            }
                            if (abs(partenaire_->getPosY() - animal_->getPosY()) <= abs(procheY))
                            {
                                procheY = partenaire_->getPosY() - animal_->getPosY();
                            }

                        }
                    }
                }
                else if (animal_->getCdCop() == 0)
                {
                    if (SDL_HasIntersection(&animal_->getRectangle(), &partenaire_->getRectangle()) && partenaire_ != animal_)
                    {
                        if (partenaire_->getImage() == "sheep.png" && partenaire_->getVivant())
                        {
                            if (partenaire_->getCdCop() == 0)
                            {
                                animal_->changeBaby();
                                animal_->augmentCd(181);
                                partenaire_->augmentCd(181);

                            }


                        }
                    }
                }
            }
            animal_->copBaisse(1);
            
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
        else if (animal_->getImage() == "wolf.png" && animal_->getVivant())
        {
            int procheX = frame_width;
            int procheY = frame_height;
            for (auto&& partenaire_ : animalList)
            {
                if (partenaire_->getImage() == "sheep.png" && partenaire_->getVivant() && animal_->getPeur()==1)
                {
                    if (SDL_HasIntersection(&animal_->getRectangle(), &partenaire_->getRectangle()))
                    {
                        partenaire_->setVivant(false);
                        animal_->setFood(1500);
                    }
                    else
                    {
                        if (abs(partenaire_->getPosX() - animal_->getPosX()) + abs(partenaire_->getPosY() - animal_->getPosY()) <= abs(procheX) + abs(procheY))
                        {
                            procheX = partenaire_->getPosX() - animal_->getPosX();
                            procheY = partenaire_->getPosY() - animal_->getPosY();
                        }
                    }


                }
                else if (partenaire_->getImage() == "doggo.png" && partenaire_->getVivant())
                {
                    if (abs(partenaire_->getPosX() - animal_->getPosX()) <= 100)
                    {
                        if (abs(partenaire_->getPosY() - animal_->getPosY()) <= 100)
                        {
                            animal_->setPeur(-1);
                            if (abs(partenaire_->getPosX() - animal_->getPosX()) <= abs(procheX))
                            {
                                procheX = partenaire_->getPosX() - animal_->getPosX();
                            }
                            if (abs(partenaire_->getPosY() - animal_->getPosY()) <= abs(procheY))
                            {
                                procheY = partenaire_->getPosY() - animal_->getPosY();
                            }

                        }
                    }
                }
            }
            if (abs(procheX) > abs(procheY))
            {
                animal_->setDirectionY(0);
                if (procheX < 0)
                {
                    animal_->setDirectionX(-1 * animal_->getSpeed()* animal_->getPeur());
                }
                else if (procheX > 0)
                {
                    animal_->setDirectionX(1 * animal_->getSpeed() * animal_->getPeur());
                }
            }
            else if (abs(procheX) < abs(procheY))
            {
                animal_->setDirectionX(0);

                if (procheY < 0)
                {
                    animal_->setDirectionY(-1 * animal_->getSpeed() * animal_->getPeur());
                }
                else if (procheY > 0)
                {
                    animal_->setDirectionY(1 * animal_->getSpeed() * animal_->getPeur());
                }
            }
            else
            {
                if (procheX < 0)
                {
                    animal_->setDirectionX(-1 * animal_->getSpeed() * animal_->getPeur());
                }
                else if (procheX > 0)
                {
                    animal_->setDirectionX(1 * animal_->getSpeed() * animal_->getPeur());
                }
                if (procheY < 0)
                {
                    animal_->setDirectionY(-1 * animal_->getSpeed() * animal_->getPeur());
                }
                else if (procheY > 0)
                {
                    animal_->setDirectionY(1 * animal_->getSpeed() * animal_->getPeur());
                }
            }
            animal_->setFood(animal_->getFood() - 1);
            if (animal_->getFood() <= 0)
            {
                animal_->setVivant(false);
            }
            if (animal_->getPeur() != 1)
            {
                animal_->setPeur(1);
            }

        }
        else if (animal_->getImage() == "doggo.png" && animal_->getVivant())
        {
            //SDL_Event event;
            ////while (SDL_PollEvent(&e)) {
            ////    std::cout << "PUT";
            ////    switch (e.type) {
            ////    case SDL_MouseButtonEvent:
            ////        std::cout << "?";
            ////        animal_->setClicPress(false);
            ////        int sourisX;
            ////        int sourisY;
            ////        //SDL_GetMouseState(&sourisX, &sourisY);
            ////        
            ////        animal_->setDestination(e.button.x, e.button.y);
            ////        break;
            ////    case SDL_QUIT:
            ////        break;
            ////    //case SDL_MOUSEBUTTONDOWN:
            ////    //    //do whatever you want to do after a mouse button was pressed,
            ////    //    // e.g.:
            ////    //    animal_->setClicPress(true);
            ////    //    break;
            ////    }
            ////}
            //while (SDL_PollEvent(&event)) {
            //    if (event.type == SDL_MOUSEBUTTONDOWN)
            //    {
            //        std::cout << "YESN?";

            //    }
            //}
            //


            
            int cheminX;
            int cheminY;
            if (animal_->getDestinationX() >= 0 && animal_->getDestinationY() >= 0 )
            {
                SDL_Point destination = { animal_->getDestinationX(), animal_->getDestinationY() };
                if (SDL_PointInRect(&destination,&animal_->getRectangle() ))
                {
                    animal_->setDestination(-1,-1);
                }
                cheminX = animal_->getDestinationX();
                cheminY = animal_->getDestinationY();

            }
            else
            {
                cheminX = this->player.getPosX();
                cheminY = this->player.getPosY();
            }
            if (cheminX > animal_->getPosX())
            {
                animal_->setDirectionX(1 * animal_->getSpeed());

            }
            else if (cheminX < animal_->getPosX())
            {
                animal_->setDirectionX(-1 * animal_->getSpeed());

            }
            else
            {
                animal_->setDirectionX(0);
            }
            if (cheminY > animal_->getPosY())
            {
                animal_->setDirectionY(1 * animal_->getSpeed());

            }
            else if (cheminY < animal_->getPosY())
            {
                animal_->setDirectionY(-1 * animal_->getSpeed());

            }
            else
            {
                animal_->setDirectionY(0);
            }
            

        }

        animal_->move();
        animal_->draw();

            
        
        

    }
    //morts des animaux
    std::vector<int> animauxMorts;

    
    int pCompteur = 0;
    for (auto&& animal_ : animalList)
    {
        if (!animal_->getVivant())
        {
            animauxMorts.push_back(pCompteur);

        }
        pCompteur += 1;
    }
    if (size(animauxMorts) != 0)
    {
        std::cout << size(animauxMorts)<<"hey"<<size(animalList)<<"vrai taille";
        std::cout << "CEST PARTI";
        for (auto&& animal2_ : animauxMorts)
        {
            std::cout << animal2_<<"p";
        }
    }
    for (int i = 0; i < size(animauxMorts); i++)
    {
        std::cout << animauxMorts[i] - i<<"la position";
        std::cout << size(animalList) << "la positionTAillle";
        for (auto&& animal_ : animalList)
        {
            std::cout << "UnePlace";
        }

        animalList.erase(animalList.begin() + animauxMorts[i] - i);
        std::cout << "bug";
        
       
    }

    while (!animauxMorts.empty())
    {
        animauxMorts.pop_back();
        std::cout << animauxMorts.size() << "PUT";

    }

    //reproduction
    
    int cpoComp = 0;
    std::vector<int> animauxNai;
    for (auto&& animal_ : animalList)
    {
        if (animal_->HasBaby())
        {
            animauxNai.push_back(cpoComp);

        }
        cpoComp += 1;
    }


    for (int i = 0; i < size(animauxNai); i++)
    {
        std::cout << "BAISE";
        add_animal((std::make_shared<sheep>(window_surface_ptr_, animalList[animauxNai[i]]->getPosX(), animalList[animauxNai[i]]->getPosY())));
    }
    while (!animauxNai.empty())
    {
        animauxNai.pop_back();
    }

    player.move();
    player.draw();
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
    //ground_.add_animal(std::make_shared<sheep>(window_surface_ptr_, 500, 100));




    ground_.add_animal(std::make_shared<wolf>(window_surface_ptr_, 1000, 100));
    ground_.add_animal(std::make_shared<dog>(window_surface_ptr_, 1100, 600));


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
