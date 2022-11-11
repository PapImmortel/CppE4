// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>
#include <time.h>
#include <random>

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

    int nbAlea[3] = { -1, 0, 1 };
    std::random_device rd{};
    bool mouvement = false;
    while (!mouvement)
    {
        mouvement = true;
        this->setDirectionX(1 * this->getSpeed() * nbAlea[(rd() % 3)]);
        this->setDirectionY(1 * this->getSpeed() * nbAlea[(rd() % 3)]);
        if (getDirectionX() == 0 && getDirectionY() == 0)
        {
            mouvement = false;
        }
    }
    

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
void animal::addFlag(std::string flag)
{
    this->flags_.push_back(flag);
}
bool animal::hasFlag(std::string flag)
{
    for (std::string f : this->flags_)
    {
        if (flag == f)
        {
            return true;
        }

    }
    return false;
}

sheep::sheep(SDL_Surface* window_surface_ptr, int positionX, int positionY) :animal("sheep.png", window_surface_ptr, positionX, positionY)
{

    this->cdCop = 0;
    this->Baby = false;
    this->addFlag("prey");
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

    this->setFood(1500);
    this->setPeur(1);
    this->addFlag("predator");
}
wolf::~wolf()
{
}
void wolf::move()
{
    if (getDirectionX() + getPosX() <= 0 || getDirectionX() + getPosX() >= frame_width - 30)
    {
        setDirectionX(0);
    }
    if (getDirectionY() + getPosY() <= 0 || getDirectionY() + getPosY() >= frame_height - 30)
    {
        setDirectionY(0);
    }
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
    this->setDestination(-1, -1);
    this->addFlag("dog");
}

dog::~dog()
{
}

void dog::move()
{
    if (getDirectionX() + getPosX() <= 0 || getDirectionX() + getPosX() >= frame_width - 30)
    {
        setDirectionX(0);
    }
    if (getDirectionY() + getPosY() <= 0 || getDirectionY() + getPosY() >= frame_height - 30)
    {
        setDirectionY(0);
    }
    Deplacement(getDirectionX(), getDirectionY());
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
    this->setSpeed(5);

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
    setDirectionX(0);
    setDirectionY(0);

    if (this->touche.type = SDL_KEYDOWN)
    {
        if (this->touche.key.keysym.sym == SDLK_s) {
            setDirectionY(1);

        }
        if (this->touche.key.keysym.sym == SDLK_z) {
            setDirectionY(-1);

        }
        if (this->touche.key.keysym.sym == SDLK_q) {
            setDirectionX(-1);

        }
        if (this->touche.key.keysym.sym == SDLK_d) {
            setDirectionX(1);

        }
    }
    if (getDirectionX() + getPosX() <= 0 || getDirectionX() + getPosX() >= frame_width - 30)
    {
        setDirectionX(0);
    }
    if (getDirectionY() + getPosY() <= 0 || getDirectionY() + getPosY() >= frame_height - 50)
    {
        setDirectionY(0);

    }
    positionX_ += getDirectionX() * getSpeed();
    positionY_ += getDirectionY() * getSpeed();
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
void Humain::setevent(SDL_Event  ev)
{
    this->touche = ev;
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


        if (animal_->hasFlag("prey") && animal_->getVivant())
        {
            
            //
            animal_->BabyFalse();
            int procheX = 101;
            int procheY = 101;
            for (auto&& partenaire_ : animalList)
            {
                if (partenaire_->hasFlag("predator") && partenaire_->getVivant())
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
                        if (partenaire_->hasFlag("prey") && partenaire_->getVivant())
                        {
                            if (partenaire_->getCdCop() == 0)
                            {
                                animal_->changeBaby();
                                animal_->augmentCd(181);
                                partenaire_->augmentCd(181);
                                animal_->setDirectionX(-animal_->getSpeed());
                                animal_->setDirectionY(-animal_->getSpeed());


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
        else if (animal_->hasFlag("predator") && animal_->getVivant())
        {
            int procheX = frame_width;
            int procheY = frame_height;
            for (auto&& partenaire_ : animalList)
            {
                if (partenaire_->hasFlag("prey") && partenaire_->getVivant() && animal_->getPeur()==1)
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
                else if (partenaire_->hasFlag("dog") && partenaire_->getVivant())
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
        else if (animal_->hasFlag("dog") && animal_->getVivant())
        {

            int cheminX;
            int cheminY;
            if (animal_->getDestinationX() >= 0 && animal_->getDestinationY() >= 0 )
            {
                cheminX = animal_->getDestinationX();
                cheminY = animal_->getDestinationY();
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

                SDL_Point destination = { animal_->getDestinationX(), animal_->getDestinationY() };
                if (SDL_PointInRect(&destination,&animal_->getRectangle() ))
                {
                    animal_->setDestination(-1,-1);
                }
                

            }
            else
            {
                cheminX = this->player.getPosX();
                cheminY = this->player.getPosY();
                if ((cheminX > animal_->getPosX() + 30) || (animal_->getPosX() - cheminX>=0 && animal_->getPosX() - cheminX <30))
                {
                    animal_->setDirectionX(1 * animal_->getSpeed());

                }
                else if (cheminX < animal_->getPosX() - 30 || (cheminX  - animal_->getPosX() >= 0 && cheminX - animal_->getPosX() < 30))
                {
                    animal_->setDirectionX(-1 * animal_->getSpeed());

                }
                else
                {
                    animal_->setDirectionX(0);
                }
                if (cheminY > animal_->getPosY() + 30 || (animal_->getPosY() - cheminY >= 0 && animal_->getPosY() - cheminY < 30))
                {
                    animal_->setDirectionY(1 * animal_->getSpeed());

                }
                else if (cheminY < animal_->getPosY() - 30 || (cheminY - animal_->getPosY() >= 0 && cheminY - animal_->getPosY() < 30))
                {
                    animal_->setDirectionY(-1 * animal_->getSpeed());

                }
                else
                {
                    animal_->setDirectionY(0);
                }
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

    for (int i = 0; i < size(animauxMorts); i++)
    {
        animalList.erase(animalList.begin() + animauxMorts[i] - i);
        
       
    }

    while (!animauxMorts.empty())
    {
        animauxMorts.pop_back();

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
        add_animal((std::make_shared<sheep>(window_surface_ptr_, animalList[animauxNai[i]]->getPosX(), animalList[animauxNai[i]]->getPosY())));
    }
    while (!animauxNai.empty())
    {
        animauxNai.pop_back();
    }

    player.draw();
}
void ground::updatePlayer(SDL_Event ev)
{
    this->player.setevent(ev);
    this->player.move();
}
void ground::updateDogs(SDL_Event ev)
{
    for (auto&& animal_ : this->animalList)
    {
        if (animal_->hasFlag("dog") && animal_->getVivant())
        {
            animal_->setDestination(ev.button.x, ev.button.y);
        }
    }
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

    //ground_.add_animal(std::make_shared<sheep>(window_surface_ptr_, 0, 100));
    //ground_.add_animal(std::make_shared<sheep>(window_surface_ptr_, 500, 100));
    //ground_.add_animal(std::make_shared<sheep>(window_surface_ptr_, 500, 100));
    std::random_device rd{};

    for (int i = 0; i < n_sheep; i++)
    {
        ground_.add_animal(std::make_shared<sheep>(window_surface_ptr_, rd() % (frame_width - 29), rd() % (frame_height - 29)));

    }
    for (int i = 0; i < n_wolf; i++)
    {
        ground_.add_animal(std::make_shared<wolf>(window_surface_ptr_, rd() % (frame_width - 29), rd() % (frame_height - 29)));



    }

    //ground_.add_animal(std::make_shared<wolf>(window_surface_ptr_, 1000, 100));
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
            if (e.type == SDL_KEYDOWN)
            {
                this->ground_.updatePlayer(e);
                break;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                this->ground_.updateDogs(e);
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
