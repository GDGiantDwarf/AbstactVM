/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-noe.sellam
** File description:
** IOperand
*/

#ifndef IOPERAND_HPP
#define IOPERAND_HPP
#include <iostream>

enum eOperandType
    {
        INT8,
        INT16,
        INT32,
        FLOAT,
        DOUBLE,
        BIGDECIMAL
    };

class IOperand
{
public:
    virtual std::string const & toString() const = 0;

    virtual int getPrecision() const = 0; // Renvoie la precision du type de l'instance
    virtual eOperandType getType() const = 0; // Renvoie le type de l'instance

    virtual IOperand *operator+(const IOperand &rhs) const = 0;
    virtual IOperand *operator-(const IOperand &rhs) const = 0;
    virtual IOperand *operator*(const IOperand &rhs) const = 0;
    virtual IOperand *operator/(const IOperand &rhs) const = 0;
    virtual IOperand *operator%(const IOperand &rhs) const = 0;

    virtual ~IOperand() {}
};

#endif