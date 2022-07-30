/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-noe.sellam
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "../include/IOperand.hpp"
#include <functional>

class Factory {
    public:
        static IOperand* createOperand(eOperandType type, const std::string& value);

    protected:
    private:
    static IOperand* createInt8(const std::string& value);
    static IOperand* createInt16(const std::string& value);
    static IOperand* createInt32(const std::string& value);
    static IOperand* createFloat(const std::string& value);
    static IOperand* createDouble(const std::string& value);
    static IOperand* createBigDecimal(const std::string& value);
};

#endif /* !FACTORY_HPP_ */
