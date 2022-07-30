/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-noe.sellam
** File description:
** error.hpp
*/


#ifndef ERROR_TYPES
#define ERROR_TYPES

#include "abstractVM.hpp"

class NoSuchFileException : public std::exception {
    public:
    char * what () {
        return (char *) "NoSuchFileException";
    }
};

class BadArgException : public std::exception {
    public:
    char * what () {
        return (char *) "BadArgException";
    }
};

class RegistryException : public std::exception {
    public:
    char * what () {
        return (char *) "RegistryException";
    }
};

class NoSuchMethodException : public std::exception {
    public:
    char * what () {
        return (char *) "NoSuchMethodException";
    }
};

class WrongAssertion : public std::exception {
    public:
    char * what () {
        return (char *) "WrongAssertionException";
    }
};

class NotPrintableException : public std::exception {
    public:
    char * what () {
        return (char *) "NotPrintableException";
    }
};

class EmptyStackException : public std::exception {
    public:
    char * what () {
        return (char *) "EmptyStackException";
    }
};

class MathErrorException : public std::exception {
    public:
    char * what () {
        return (char *) "MathErrorException";
    }
};

class OverflowException : public std::exception {
    public:
    char * what () {
        return (char *) "OverflowException";
    }
};

class UnderflowException : public std::exception {
    public:
    char * what () {
        return (char *) "UnderflowException";
    }
};

class NoExitException : public std::exception {
    public:

    char * what () {
        return (char *) "NoExitException";
    }
};


#endif