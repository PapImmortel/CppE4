#include "Project_SDL1.h"
#include <stdio.h>
#include <string>

int main(int argc, char* argv[]) {

  std::cout << "Starting up the application" << std::endl;

  if (argc != 4)
    throw std::runtime_error("Need three arguments - "
                             "number of sheep, number of wolves, "
                             "simulation time\n");*/

  init();

  std::cout << "Done with initilization" << std::endl;

  application my_app(std::stoul(argv[1]), std::stoul(argv[2]));
  //application my_app(4,4);

  std::cout << "Created window" << std::endl;

  int retval = my_app.loop(std::stoul(argv[3]));
  //int retval = my_app.loop(20000);

  std::cout << "Exiting application with code " << retval << std::endl;

  SDL_Quit();

  return retval;
}