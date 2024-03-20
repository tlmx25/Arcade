##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

NAME = arcade

build:
	@mkdir "build"
	@cd "build"
	@cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
	@cmake --build .
	@cd ..

clean:
	@rm -rf "build"
	@ rm -rf "cmake-build-debug"

fclean: clean
	@rm -f $(NAME)

re: fclean build
