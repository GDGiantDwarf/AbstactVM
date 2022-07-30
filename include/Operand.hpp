/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-noe.sellam
** File description:
** Operand
*/

#ifndef OPERAND_HPP_
#define OPERAND_HPP_

#include "Factory.hpp"
#include "abstractVM.hpp"
#include <sstream>
#include <cmath>

template <typename X>
class Operand : public IOperand
{
    private:
        int precision;
        eOperandType type;
        std::string _valstr;
        X _val;
        std::map<eOperandType, std::pair<std::string, std::string>> limit_map;
        std::map<eOperandType, int> precsionmap;

    public:

    Operand(X value, eOperandType type)
    {
        _valstr = std::to_string(value);
        _val = value;
        this->type = type;
    this->limit_map[INT8] = std::make_pair<std::string, std::string>("-128", "127");
    this->limit_map[INT16] = std::make_pair<std::string, std::string>("-32768", "32767");
    this->limit_map[INT32] = std::make_pair<std::string, std::string>("-2147483648", "2147483647");
    this->limit_map[FLOAT] = std::make_pair<std::string, std::string>("-340282346638528859811704183484516925440.0000000000000000", "340282346638528859811704183484516925440.0000000000000000");
    this->limit_map[DOUBLE] = std::make_pair<std::string, std::string>("-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000", "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000");
    this->limit_map[BIGDECIMAL] = std::make_pair<std::string, std::string>("-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000", "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000");
    
    precsionmap[INT8] = 1;
    precsionmap[INT16] = 1;
    precsionmap[INT32] = 1;
    precsionmap[FLOAT] = 7;
    precsionmap[DOUBLE] = 15;
    precsionmap[BIGDECIMAL] = 200;
    this->precision = precsionmap[type];
    }

    std::string const& toString() const
    {
        return _valstr;
    }

    IOperand* operator+(const IOperand &rhs ) const
    {
        double long firstval = std::stod(toString());
        double long secondval = std::stod(rhs.toString());

        eOperandType TheType = (eOperandType)std::max((int)this->type, (int)rhs.getType());
        std::string TheVal = std::to_string(firstval + secondval);

        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) > std::stold(limit_map.at(TheType).second)) {
            throw OverflowException();
        }
        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) < std::stold(limit_map.at(TheType).first)) {
            throw UnderflowException();
        }

        return Factory::createOperand(TheType, TheVal);
    }

    IOperand* operator-(const IOperand &rhs ) const
    {
        double long firstval = std::stod(toString());
        double long secondval = std::stod(rhs.toString());

        eOperandType TheType = (eOperandType)std::max((int)this->type, (int)rhs.getType());
        std::string TheVal = std::to_string(secondval - firstval);

        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) > std::stold(limit_map.at(TheType).second)) {
            throw OverflowException();
        }
        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) < std::stold(limit_map.at(TheType).first)) {
            throw UnderflowException();
        }

        return Factory::createOperand(TheType, TheVal);
    }

    IOperand* operator*(const IOperand &rhs ) const
    {
        double long firstval = std::stod(toString());
        double long secondval = std::stod(rhs.toString());

        eOperandType TheType = (eOperandType)std::max((int)this->type, (int)rhs.getType());
        std::string TheVal = std::to_string(firstval * secondval);

        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) > std::stold(limit_map.at(TheType).second)) {
            throw OverflowException();
        }
        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) < std::stold(limit_map.at(TheType).first)) {
            throw UnderflowException();
        }

        return Factory::createOperand(TheType, TheVal);
    }

    IOperand* operator/(const IOperand &rhs ) const
    {
        double long firstval = std::stod(this->toString());
        double long secondval = std::stod(rhs.toString());

        eOperandType TheType = (eOperandType)std::max((int)this->type, (int)rhs.getType());
        std::string TheVal = std::to_string(firstval / secondval);

        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) > std::stold(limit_map.at(TheType).second)) {
            throw OverflowException();
        }
        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) < std::stold(limit_map.at(TheType).first)) {
            throw UnderflowException();
        }

        return Factory::createOperand(TheType, TheVal);
    }

    IOperand* operator%(const IOperand &rhs ) const
    {
        double long firstval = std::stod(toString());
        double long secondval = std::stod(rhs.toString());

        eOperandType TheType = (eOperandType)std::max((int)this->type, (int)rhs.getType());
        std::string TheVal = std::to_string(fmod(firstval, secondval));

        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) > std::stold(limit_map.at(TheType).second)) {
            throw OverflowException();
        }
        if ((!limit_map.at(TheType).first.empty()) && std::stold(TheVal) < std::stold(limit_map.at(TheType).first)) {
            throw UnderflowException();
        }

        return Factory::createOperand(TheType, TheVal);
    }

    int getPrecision() const { return this->precision;}; // Renvoie la precision du type de l'instance
    eOperandType getType() const { return this->type;}; // Renvoie le type de l'instance
};
#endif /* !OPERAND_HPP_ */
