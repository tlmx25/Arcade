##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

NAME = arcade


clean:
	@rm -rf "build"
	@ rm -rf "cmake-build-debug"

fclean: clean
	@rm -f $(NAME)
	@rm -fr lib
