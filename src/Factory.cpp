/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-noe.sellam
** File description:
** Factory
*/

#include "../include/Operand.hpp"

IOperand *Factory::createOperand(eOperandType type, const std::string& value)
{
    const std::function<IOperand*(std::string value)> arr[6] = {
    createInt8,
    createInt16,
    createInt32,
    createFloat,
    createDouble,
    createBigDecimal
    };
    return arr[type](value);
}

IOperand *Factory::createInt8(const std::string& value)
{
    if (std::stold(value) > 127) {
        throw OverflowException();
    }
    if (std::stold(value) < -128) {
        throw UnderflowException();
    }
    IOperand *ptr = new Operand<int8_t>(std::stoi(value), INT8);
    return ptr;
}

IOperand *Factory::createInt16(const std::string& value)
{
    if (std::stold(value) > 32767) {
        throw OverflowException();
    }
    if (std::stold(value) < -32768) {
        throw UnderflowException();
    }
    IOperand *ptr = new Operand<int16_t>(std::stoi(value), INT16);
    return ptr;
}

IOperand *Factory::createInt32(const std::string& value)
{
    if (std::stold(value) > 2147483647) {
        throw OverflowException();
    }
    if (std::stold(value) < -2147483648) {
        throw UnderflowException();
    }
    IOperand *ptr = new Operand<int32_t>(std::stol(value), INT32);
    return ptr;
}

IOperand *Factory::createFloat(const std::string& value)
{
    if (std::stold(value) > 340282346638528859811704183484516925440.0000000000000000) {
        throw OverflowException();
    }
    if (std::stold(value) < -340282346638528859811704183484516925440.0000000000000000) {
        throw UnderflowException();
    }
    IOperand *ptr = new Operand<float>(std::stof(value), FLOAT);
    return ptr;
}

IOperand *Factory::createDouble(const std::string& value)
{
    if (std::stold(value) > 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000) {
        throw OverflowException();
    }
    if (std::stold(value) < -179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000) {
        //std::cout << "VALUE IS :" << std::stold(value) << " MIN IS" << std::numeric_limits<double_t>::min() << std::endl;
        throw UnderflowException();
    }
    IOperand *ptr = new Operand<double>(std::stod(value), DOUBLE);
    return ptr;
}

IOperand *Factory::createBigDecimal(const std::string& value)
{
    if (std::stold(value) > 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000) {
        throw OverflowException();
    }
    if (std::stold(value) < -179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000) {
        throw UnderflowException();
    }
    IOperand *ptr = new Operand<long double>(std::stold(value), BIGDECIMAL);
    return ptr;
}