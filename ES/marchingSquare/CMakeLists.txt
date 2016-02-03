 
# Ajustez en fonction de votre version de CMake

cmake_minimum_required (VERSION 2.8)


# Nom du projet

project (marchingSquare)


find_package (OpenCV REQUIRED)


# Exécutable "hello", compilé à partir du fichier helloworld.cpp

add_executable (marchingSquare marchingSquare.cpp)


# Hello sera linké avec les bibliothèques d'OpenCV

target_link_libraries (marchingSquare ${OpenCV_LIBS})