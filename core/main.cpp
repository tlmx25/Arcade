/*
** EPITECH PROJECT, 2024
** PRIVATE_arcade
** File description:
** main
*/

#include <iostream>
#include "Core.hpp"

void print_help()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./arcade path_to_graphical_library" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tpath_to_graphical_library\tThe path to the graphical library you want to use" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        print_help();
        return 84;
    }
    if (std::string(av[1]) == "-h") {
        print_help();
        return 0;
    }
    try {
        Core core(av[1]);
        core.mainLoop();
    } catch (Core::InvalidStartLibException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (CLibEncapsulation::LibException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
