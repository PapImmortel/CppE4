# CMakeList.txt : projet CMake pour cartesian_vector_param, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("cartesian_vector_param")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (main "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
