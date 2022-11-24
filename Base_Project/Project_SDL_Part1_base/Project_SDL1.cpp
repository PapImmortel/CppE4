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
animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr, float positionX, float positionY)
{

    this->positionX_ = positionX;
    this->positionY_ = positionY;
    this->setSpeed(1);
    this->setVivant(true);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 2 * std::_Pi);

    this->setDirectionX(this->getSpeed() * cos(dist(gen)));
    this->setDirectionY(this->getSpeed() * sin(dist(gen)));
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> dist2(0, 1);
    this->setGenre(dist2(gen2));

    this->image_ptr_ = IMG_Load(file_path.c_str());
    if (!this->image_ptr_)
        throw std::runtime_error("Could not load image");
    this->window_surface_ptr_ = window_surface_ptr;
    if (!this->window_surface_ptr_)
        throw std::runtime_error(std::string(SDL_GetError()));

    this->rectangle_ = { (int)this->positionX_, (int)this->positionY_ ,30,30 };

}

animal::~animal()
{
    SDL_FreeSurface(this->window_surface_ptr_);
    SDL_FreeSurface(this->image_ptr_);
}
void animal::draw()
{
    if (this->getVivant())
    {
        this->rectangle_ = { (int)this->positionX_, (int)this->positionY_ ,30,30 };
        SDL_BlitScaled(this->image_ptr_, NULL, this->window_surface_ptr_, &this->rectangle_);
    }
    
}
void animal::Deplacement(float pX, float pY)
{
    this->positionX_ += pX;
    this->positionY_ += pY;

}
float animal::getPosX()
{
    return this->positionX_;
}
float animal::getPosY()
{
    return this->positionY_;
}


void animal::setDirectionX(float directionX)
{
    this->directionX_ = directionX;
}
void animal::setDirectionY(float directionY)
{
    this->directionY_ = directionY;
}
float animal::getDirectionX()
{
    return this->directionX_;
}
float animal::getDirectionY()
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
void animal::setGenre(bool genre)
{
    this->genre_ = genre;
}
bool animal::getGenre()
{
    return this->genre_;
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

sheep::sheep(SDL_Surface* window_surface_ptr, float positionX, float positionY) :animal("sheep.png", window_surface_ptr, positionX, positionY)
{

    this->cdCop = 0;
    this->Baby = false;
    this->addFlag("prey");
    this->addFlag("sheep");
    this->setRandomMove(100);
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
void sheep::setRandomMove(int randomMove)
{
    this->randomMove_ = randomMove;
}
int sheep::getRandomMove()
{
    return this->randomMove_;
}

wolf::wolf(SDL_Surface* window_surface_ptr, float positionX, float positionY) : animal("wolf.png", window_surface_ptr, positionX, positionY)
{

    this->setFood(3000);
    this->setPeur(1);
    this->addFlag("predator");
    this->addFlag("wolf");
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
dog::dog(SDL_Surface* window_surface_ptr, float positionX, float positionY) : animal("doggo.png", window_surface_ptr, positionX, positionY)
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

void dog::setDestination(float destinationX, float destinationY)
{
    this->destinationX = destinationX;
    this->destinationY = destinationY;

}
float dog::getDestinationX()
{
    return this->destinationX;
}
float dog::getDestinationY()
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
    if (getDirectionX() + getPosX() <= 60 || getDirectionX() + getPosX() >= frame_width - 90)
    {
        setDirectionX(0);
    }
    if (getDirectionY() + getPosY() <= 60 || getDirectionY() + getPosY() >= frame_height - 90)
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

Score::Score(SDL_Surface* window_surface_ptr,int nbMoutonAlive)
{
    this->image_ptr_ = IMG_Load("score.png");
    if (!this->image_ptr_)
        throw std::runtime_error("Could not load image");
    this->window_surface_ptr_ = window_surface_ptr;
    if (!this->window_surface_ptr_)
        throw std::runtime_error(std::string(SDL_GetError()));

    this->rectangle_ = { frame_width/3 +50, 0 ,70,60 };
    this->setNbMoutonAlive(nbMoutonAlive);

}
void Score::setNbMoutonAlive(int nbMoutonAlive)
{
    this->nbMoutonALive_ = nbMoutonAlive ;
}
int Score::getNbMoutonAlive()
{
    return this->nbMoutonALive_;
}
void Score::draw()
{
    SDL_BlitScaled(this->image_ptr_, NULL, this->window_surface_ptr_, &this->rectangle_);
    int valeur = this->getNbMoutonAlive();
    int position=250;
    if (valeur == 0)
    {
        SDL_Rect newRect = { frame_width / 3 + position,10,40,40 };
        SDL_BlitScaled(IMG_Load("0.png"), NULL, this->window_surface_ptr_, &newRect);

    }
    else
    {
        while (valeur > 0)
        {
            SDL_Rect newRect = { frame_width / 3 + position,10,40,40 };
            position -= 50;
            int newVal = valeur % 10;
            if (newVal == 0)
            {
                SDL_BlitScaled(IMG_Load("0.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 1)
            {
                SDL_BlitScaled(IMG_Load("1.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 2)
            {
                SDL_BlitScaled(IMG_Load("2.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 3)
            {
                SDL_BlitScaled(IMG_Load("3.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 4)
            {
                SDL_BlitScaled(IMG_Load("4.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 5)
            {
                SDL_BlitScaled(IMG_Load("5.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 6)
            {
                SDL_BlitScaled(IMG_Load("6.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 7)
            {
                SDL_BlitScaled(IMG_Load("7.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 8)
            {
                SDL_BlitScaled(IMG_Load("8.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            else if (newVal == 9)
            {
                SDL_BlitScaled(IMG_Load("9.png"), NULL, this->window_surface_ptr_, &newRect);
            }
            valeur /= 10;

        }
    }
    
    
   
}


ground::ground(SDL_Surface* window_surface_ptr, int nbScore)
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
    this->player = Humain(this->window_surface_ptr_, frame_width/2, frame_height/2);
    this->score_ = Score(this->window_surface_ptr_,nbScore);

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
    this->score_.draw();

    for (auto&& animal_ : animalList)
    {
        compteur += 1;


        if (animal_->hasFlag("prey") && animal_->getVivant())
        {
            
            //
            animal_->BabyFalse();
            float procheX = 101;
            float procheY = 101;
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
                else if (animal_->getCdCop() == 0 && animal_->getGenre()==0)
                {
                    if (SDL_HasIntersection(&animal_->getRectangle(), &partenaire_->getRectangle()) && partenaire_ != animal_ && partenaire_->getVivant())
                    {
                        if (partenaire_->hasFlag("sheep") && partenaire_->getGenre()==1)
                        {
                            if (partenaire_->getCdCop() == 0)
                            {
                                animal_->changeBaby();
                                animal_->augmentCd(500);

                            }


                        }
                    }
                }    
            }
            animal_->copBaisse(1);
            if (procheX < 101 && procheY < 101)
            {
                float diagonale = sqrt(procheX * procheX + procheY * procheY);
                animal_->setSpeed(3);
                animal_->setDirectionX(- (procheX / diagonale)* animal_->getSpeed());
                animal_->setDirectionY(-(procheY / diagonale)  * animal_->getSpeed());
            }
            
            else
            {
                if (animal_->getSpeed() > 1)
                {
                    animal_->setDirectionX(animal_->getDirectionX() / animal_->getSpeed());
                    animal_->setDirectionY(animal_->getDirectionY() / animal_->getSpeed());

                    animal_->setSpeed(1);
                }
                if (animal_->getRandomMove() <= 0)
                {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_real_distribution<> dist(0, 2*std::_Pi);

                    animal_->setDirectionX(animal_->getSpeed() * cos(dist(gen)));
                    animal_->setDirectionY(animal_->getSpeed() * sin(dist(gen)));
                    
                    animal_->setRandomMove(100);

                }
                else
                {
                    animal_->setRandomMove(animal_->getRandomMove() - 1);

                }
            }

        }
        else if (animal_->hasFlag("predator") && animal_->getVivant())
        {
            int procheX = frame_width;
            int procheY = frame_height;
            for (auto&& partenaire_ : animalList)
            {
                if (partenaire_->hasFlag("prey") && partenaire_->getVivant())
                {
                    if (SDL_HasIntersection(&animal_->getRectangle(), &partenaire_->getRectangle()))
                    {
                        partenaire_->setVivant(false);
                        this->score_.setNbMoutonAlive(this->score_.getNbMoutonAlive() - 1);
                        animal_->setFood(3000);
                    }
                    else if ((abs(partenaire_->getPosX() - animal_->getPosX()) + abs(partenaire_->getPosY() - animal_->getPosY()) <= abs(procheX) + abs(procheY)) && animal_->getPeur() == 1)
                    {
                        procheX = partenaire_->getPosX() - animal_->getPosX();
                        procheY = partenaire_->getPosY() - animal_->getPosY();
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
            float diagonale = sqrt(procheX * procheX + procheY * procheY);
            animal_->setDirectionX((procheX / diagonale)  * animal_->getSpeed() * animal_->getPeur());
            animal_->setDirectionY((procheY / diagonale) * animal_->getSpeed() * animal_->getPeur());

            
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

            float cheminX;
            float cheminY;
            if (animal_->getDestinationX() >= 0 && animal_->getDestinationY() >= 0 )
            {
                cheminX = animal_->getDestinationX() - animal_->getPosX();
                cheminY = animal_->getDestinationY() - animal_->getPosY();
                float diagonale = sqrt(cheminX * cheminX + cheminY * cheminY);
                animal_->setDirectionX((cheminX / diagonale) * animal_->getSpeed());
                animal_->setDirectionY((cheminY / diagonale)* animal_->getSpeed());


                SDL_Point destination = { animal_->getDestinationX(), animal_->getDestinationY() };
                if (SDL_PointInRect(&destination,&animal_->getRectangle() ))
                {
                    animal_->setDestination(-1,-1);
                }
                

            }
            else if (animal_->getDestinationX() == -1 && animal_->getDestinationY() == -1)
            {
                         
                
                cheminX = this->player.getPosX() - animal_->getPosX();
                cheminY = this->player.getPosY() - animal_->getPosY();

                float diagonale = sqrt(cheminX * cheminX + cheminY * cheminY);
                if (abs(cheminX) + abs(cheminY) > 60 )
                {
                    animal_->setDirectionX((cheminX / diagonale)  * animal_->getSpeed());
                    animal_->setDirectionY((cheminY / diagonale)* animal_->getSpeed());
                }
                else if (abs(cheminX) + abs(cheminY) < 50)
                {
                    animal_->setDirectionX(-(cheminX / diagonale)* animal_->getSpeed());
                    animal_->setDirectionY(-(cheminY / diagonale)* animal_->getSpeed());
                }
                else
                {
                    animal_->setDirectionX(0);
                    animal_->setDirectionY(0);

                    float timedelta = (SDL_GetTicks() / 4) % 360;
                    int positionX = (cos((timedelta * 2 * std::_Pi) / 360))*100;
                    int positionY = (sin((timedelta * 2 * std::_Pi) / 360))*100;
                    float diagonale = sqrt(cheminX * cheminX + cheminY * cheminY);
                    int actualX = (-cheminX / diagonale) * 100;
                    int actualY = (-cheminY / diagonale) * 100;


                    if (abs(actualX - positionX)<5 && abs(actualY - positionY)<5)
                    {
                        animal_->setDestination(-2, -2);
                    }
                }

                
                
                
            }
            else if (animal_->getDestinationX() == -2 && animal_->getDestinationY() == -2)
            {
                float timedelta = (SDL_GetTicks()/4) % 360;
                float positionX = cos((timedelta * 2 * std::_Pi) / 360) * 60 + this->player.getPosX();
                float positionY = sin((timedelta * 2 * std::_Pi) / 360) * 60 + this->player.getPosY();
                animal_->Deplacement(positionX - animal_->getPosX(), positionY - animal_->getPosY());
            }
            
            

        }
        animal_->move();
        animal_->draw();

            
        
        

    }

    
    int pCompteur = 0;

    int animalMort=-1;
    for (auto&& animal_ : animalList)
    {
        if (!animal_->getVivant())
        {
            animalMort=pCompteur;
            break;
        }
        pCompteur += 1;
    }
    if (animalMort!=-1)
    {
        animalList.erase(animalList.begin() + animalMort);
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
        this->score_.setNbMoutonAlive(this->score_.getNbMoutonAlive() + 1);

    }
    while (!animauxNai.empty())
    {
        animauxNai.pop_back();
    }

    this->player.draw();

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
    ground_ = ground(window_surface_ptr_,n_sheep);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, frame_width - 30);
    std::uniform_int_distribution<> distY(0, frame_height - 30);

    for (int i = 0; i < n_sheep; i++)
    {
        ground_.add_animal(std::make_shared<sheep>(window_surface_ptr_, distX(gen), distY(gen)));

    }
    for (int i = 0; i < n_wolf; i++)
    {
        ground_.add_animal(std::make_shared<wolf>(window_surface_ptr_, distX(gen), distY(gen)));



    }

    ground_.add_animal(std::make_shared<dog>(window_surface_ptr_, distX(gen), distY(gen)));
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
