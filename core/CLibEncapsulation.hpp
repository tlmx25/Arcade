/*
** EPITECH PROJECT, 2024
** bsarcarde
** File description:
** CLibEncapsulation
*/

#pragma once

#include <dlfcn.h>
#include <iostream>

class CLibEncapsulation {
    public:
        CLibEncapsulation();
        CLibEncapsulation(std::string &libPath);
        ~CLibEncapsulation();
        void openLib(std::string const libPath);
        void closeLib();
        void *getLib();
        bool isGameLib();
        bool isDisplayLib();
        void *getFunction(std::string const &functionName);
        /**
         * @brief Get an element from the library.
         *
         * @tparam T The type of the element to get.
         * @param elementName The name of the element to get.
         * @return T The element.
         */
        template<class T>
        T getElement(std::string const elementName) {
            void *(*element)() = (void * (*)())dlsym(this->lib, elementName.c_str());
            if (!element) {
                this->setError(dlerror());
                return nullptr;
            }
            std::cout << "2" << std::endl;
            T elementPtr = (T)element();
            std::cout << "3" << std::endl;
            if (!elementPtr) {
                this->setError(dlerror());
                return nullptr;
            }
            std::cout << "sortie de getElement" << std::endl;
            return elementPtr;
        }
        std::string getError();

    public:
        bool isLibOpen = false;

    private:
        void *lib = nullptr;
        std::string libPath;
        void setError(std::string const &error);
        bool failed = false;
        std::string _error;

public:
    class LibException : public std::exception {
        public:
            LibException(std::string const &message) throw() : _message(message) {}
            const char *what() const throw() { return _message.c_str(); }
            ~LibException() throw() {}
        private:
            std::string _message;
    };
};
