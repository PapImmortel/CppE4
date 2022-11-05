﻿// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

class animal {
private:
    SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
    SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
    SDL_Rect rectangle_;
    int positionX_;
    int positionY_;
    int speed = 1;
    // todo: Attribute(s) to define its position

public:
    animal(){};
    animal(const std::string& file_path, SDL_Surface* window_surface_ptr, int positionX, int positionY);
    // todo: The constructor has to load the sdl_surface that corresponds to the
    // texture
    void Deplacement(int px, int pY);
    int getPosX();
    int getPosY();
    virtual ~animal(); // todo: Use the destructor to release memory and "clean up
               // behind you"

    void draw(); // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

    virtual void move(){}; // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {
private:
    int directionX=1;
    int directionY=1;

public:
  // todo                                                                             
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
    sheep(){};
    sheep(SDL_Surface* window_surface_ptr, int positionX, int positionY);
    ~sheep();
    void move();
};


// Insert here:
// class wolf, derived from animal
class wolf : public animal {
private:

public: // todo
    wolf(SDL_Surface* window_surface_ptr, int positionX, int positionY);// Ctor
    wolf() {}
    ~wolf();
    //void move();
};


// Use only sheep at first. Once the application works
// for sheep you can add the wolves

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
    SDL_Surface* window_surface_ptr_;
    SDL_Rect rectangle;
    sheep mout;
    wolf lou;
    std::vector<std::shared_ptr<animal>> animalList;
    Uint32 color;
public:
    ground(){};

    ground(SDL_Surface* window_surface_ptr); // todo: Ctor
    ~ground(); // todo: Dtor, again for clean up (if necessary)
    void add_animal(std::shared_ptr<animal> newAnimal); // todo: Add an animal
    void update(); // todo: "refresh the screen": Move animals and draw them
    // Possibly other methods, depends on your implementation
};

// The application class, which is in charge of generating the window
class application {
private:
    // The following are OWNING ptrs
    SDL_Window* window_ptr_;
    SDL_Surface* window_surface_ptr_;
    SDL_Event window_event_;
    ground ground_;
    // Other attributes here, for example an instance of ground

public:
    application(unsigned n_sheep, unsigned n_wolf); // Ctor
    ~application();                                 // dtor

    int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};