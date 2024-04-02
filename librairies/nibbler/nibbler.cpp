/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** nibbler
*/

#include "nibbler.hpp"

nibbler::nibbler()
{
    initMap();
}

void nibbler::initMap()
{
    std::ifstream file("librairies/assets/nibbler/map1.txt"); // replace with your file path
    if (!file) {
        std::cerr << "Unable to open file\n";
        return; // return with error code
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        std::cout << "line size: " << line.size() << std::endl;
    }

    file.close();
    return;
}