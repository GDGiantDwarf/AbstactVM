/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-noe.sellam
** File description:
** stack.hpp
*/

#ifndef STACK_HPP_
#define STACK_HPP_

#include <stdio.h>
#include <array>
#include <string>
#include <list>
#include "Factory.hpp"

#include <regex>
#include <map>
#include <unordered_map>
#include <functional>

class Parser
{
    public:
        Parser();
        ~Parser();

        void parse(std::string input);
        bool command(std::string command);

        std::string valcheck(std::string val, std::string type, std::smatch cmd);
        void prep_push(std::string remainder);
        void push(IOperand *value);
        void pop();
        void dump();
        void clear();
        void dup();
        void swap();
        void prep_assert(std::string remainder);
        void assert(IOperand *vlaue);
        void add();
        void sub();
        void mul();
        void div();
        void mod();
        void prep_load(std::string remainder);
        void load(int reg);
        void prep_store(std::string remainder);
        void store(int reg);
        void print();
        void exit_exec();

    private:
        std::list<IOperand*> stack;
        std::unordered_map<std::string, std::function <bool(const std::string remainder)>> map;
        std::map<int, IOperand*> registered;
        std::map<std::string, eOperandType> typemap;
};

#endif /* !STACK_HPP_ */

