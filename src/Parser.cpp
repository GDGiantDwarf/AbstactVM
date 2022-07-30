/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-noe.sellam
** File description:
** Stack.cpp
*/

#include "../include/abstractVM.hpp"

Parser::Parser()
{
    this->map["^((push)[\\s](int8|int16|int32|float|double|bigdecimal)[\\s]*?(\\([\\s]*?((-?[0-9]+)|(-?[0-9]+\\.[0-9]+))[\\s]*?\\)))[\\s]*?[\n]"] = [this](std::string remainder) {  this->prep_push(remainder); return false; };
    this->map["^(pop)[\\s]*?[\n]"] = [this](std::string remainder) {  this->pop(); return false; };
    this->map["^(dump)[\\s]*?[\n]"] = [this](std::string remainder) {  this->dump(); return false; };
    this->map["^(clear)[\\s]*?[\n]"] = [this](std::string remainder) {  this->clear(); return false; };
    this->map["^(dup)[\\s]*?[\n]"] = [this](std::string remainder) {  this->dup(); return false; };
    this->map["^(swap)[\\s]*?[\n]"] = [this](std::string remainder) {  this->swap(); return false; };
    this->map["^((assert)[\\s](int8|int16|int32|float|double|bigdecimal)[\\s]*?(\\([\\s]*?((-?[0-9]+)|(-?[0-9]+\\.[0-9]+))[\\s]*?\\)))[\\s]*?[\n]"] = [this](std::string remainder) {  this->prep_assert(remainder); return false; };
    this->map["^(add)[\\s]*?[\n]"] = [this](std::string remainder) {  this->add(); return false; };
    this->map["^(sub)[\\s]*?[\n]"] = [this](std::string remainder) {  this->sub(); return false; };
    this->map["^(mul)[\\s]*?[\n]"] = [this](std::string remainder) {  this->mul(); return false; };
    this->map["^(div)[\\s]*?[\n]"] = [this](std::string remainder) {  this->div(); return false; };
    this->map["^(mod)[\\s]*?[\n]"] = [this](std::string remainder) {  this->mod(); return false; };
    this->map["^((load)[\\s](int8|int16|int32|float|double|bigdecimal)[\\s]*?(\\([\\s]*?((-?[0-9]+)|(-?[0-9]+\\.[0-9]+))[\\s]*?\\)))[\\s]*?[\n]"] = [this](std::string remainder) {  this->prep_load(remainder); return false; };
    this->map["^((store)[\\s](int8|int16|int32|float|double|bigdecimal)[\\s]*?(\\([\\s]*?((-?[0-9]+)|(-?[0-9]+\\.[0-9]+))[\\s]*?\\)))[\\s]*?[\n]"] = [this](std::string remainder) {  this->prep_store(remainder); return false; };
    this->map["^(print)[\\s]*?[\n]"] = [this](std::string remainder) {  this->print(); return false; };
    this->map["^(exit)[\\s]*?[\n]"] = [this](std::string remainder) { this->exit_exec(); return true; };
    this->map["^[\\s]*?;*?[\\s]*?[\n]"] = [this](std::string remainder) { return false; };


    this->typemap["int8"] = INT8;
    this->typemap["int16"] = INT16;
    this->typemap["int32"] = INT32;
    this->typemap["float"] = FLOAT;
    this->typemap["double"] = DOUBLE;
    this->typemap["bigdecimal"] = BIGDECIMAL;
}

void Parser::parse(std::string input)
{
    std::istringstream ss(input);
    std::string line;
    while (std::getline(ss,  line))
    {
        try {
        if (this->command(line)){
            return;
        }
        }
        catch(std::exception e) {
            this->exit_exec();
            throw;
        }
    }
    throw NoExitException();
}

bool Parser::command(std::string line)
{
    std::string token("");
    std::smatch cmd;
    line.append("\n");
    bool end;

    for (auto it = map.begin(); it != map.end(); ++it) {
        if (std::regex_search(line, cmd, std::regex(it->first))){
            token = cmd.str(2);
            if (token.empty())
                token = cmd.str(1);
            //std::cerr << "issued command: '" << token << "' (with:) " << line << std::endl;
            try {
            end = this->map[it->first](line);
            //std::cout << "STACK WAS :"<< std::endl;
            //this->dump();
            //std::cout << std::endl;
            return end;
            }
            catch (...) {
                throw;
            }
            return false;
        }
    }
    //std::cerr << "Line is [" << line << "] " << std::endl;
    throw NoSuchMethodException();
}

std::string Parser::valcheck(std::string type, std::string val, std::smatch cmd)
{
    if (!val.empty())
        return val;
    if (type != "float" && type != "double" && type != "bigdecimal")
        throw BadArgException();
    return cmd.str(7);
}

void Parser::prep_push(std::string str)
{
    std::string val;
    std::string type;
    std::smatch cmd;
    std::regex_search(str, cmd, std::regex("((push)[\\s](int8|int16|int32|float|double|bigdecimal)[\\s]*?(\\([\\s]*?((-?[0-9]+)|(-?[0-9]+\\.[0-9]+))[\\s]*?\\)))[\n]"));
    type = cmd.str(3);
    val = cmd.str(6);
    val = this->valcheck(type, val, cmd);
    //std::cout << "PUSHING :[" << val << "] WITH TYPE :" << type << std::endl;

    this->push(Factory::createOperand(typemap[type], val));
}

void Parser::push(IOperand *val)
{
    this->stack.push_front(val);
}

void Parser::pop()
{
    if(this->stack.size() < 1)
        throw EmptyStackException();
    IOperand *topvalue = stack.front();
    stack.pop_front();
    delete topvalue;
}

void Parser::dump()
{
    for (auto i = stack.begin(); i != stack.end(); i++) {
        std::cout << (*i)->toString() << std::endl;
    }
}

void Parser::clear()
{
    while (stack.size()) {
        IOperand *val = stack.front();
        stack.pop_front();
        delete val;
    }
}

void Parser::dup()
{
    if(this->stack.size() < 1)
        throw EmptyStackException();
    stack.push_front(
        Factory::createOperand(
            stack.front()->getType(),
            stack.front()->toString()
        )
    );
}

void Parser::swap()
{
    if(this->stack.size() < 2)
        throw EmptyStackException();
    IOperand *topvalue = stack.front();
    stack.pop_front();
    IOperand *beforevalue = stack.front();
    stack.pop_front();
    stack.push_front(topvalue);
    stack.push_front(beforevalue);
}

void Parser::prep_assert(std::string str)
{
    std::string val;
    std::string type;
    std::smatch cmd;
    if (stack.empty())
        throw EmptyStackException();
    std::regex_search(str, cmd, std::regex("((assert)[\\s](int8|int16|int32|float|double|bigdecimal)[\\s]*?(\\([\\s]*?((-?[0-9]+)|(-?[0-9]+\\.[0-9]+))[\\s]*?\\)))[\n]"));
    val = cmd.str(6);
    type = cmd.str(3);
    val = this->valcheck(type, val, cmd);
    this->assert(Factory::createOperand(typemap[type], val));
}

void Parser::assert(IOperand *val)
{
    IOperand *topvalue = stack.front();
    if (val->toString() != topvalue->toString() || val->getType() != topvalue->getType()) {
        //std::cerr << val->toString() << " VS " << topvalue->toString() <<
        //std::endl << "&&" << std::endl <<
        //val->getType() << " VS " <<topvalue->getType() << std::endl;
        delete val;
        throw WrongAssertion();
    }
    delete val;
}

void Parser::add()
{
    if(this->stack.size() < 2)
        throw EmptyStackException();
    IOperand *topvalue = stack.front();
    stack.pop_front();
    IOperand *beforevalue = stack.front();
    stack.push_front(topvalue);
    IOperand *newval = *beforevalue + *topvalue;
    stack.pop_front();
    stack.pop_front();
    delete beforevalue;
    delete topvalue;
    stack.push_front(newval);
}

void Parser::sub()
{
    if(this->stack.size() < 2)
        throw EmptyStackException();
    IOperand *topvalue = stack.front();
    stack.pop_front();
    IOperand *beforevalue = stack.front();
    stack.push_front(topvalue);
    IOperand *newval = *topvalue - *beforevalue;
    stack.pop_front();
    stack.pop_front();
    delete beforevalue;
    delete topvalue;
    stack.push_front(newval);
}

void Parser::mul()
{
    if(this->stack.size() < 2)
        throw EmptyStackException();
    IOperand *topvalue = stack.front();
    stack.pop_front();
    IOperand *beforevalue = stack.front();
    stack.push_front(topvalue);
    IOperand *newval = *beforevalue * *topvalue;
    stack.pop_front();
    stack.pop_front();
    delete beforevalue;
    delete topvalue;
    stack.push_front(newval);
}

void Parser::div()
{
    if(this->stack.size() < 2)
        throw EmptyStackException();
    if(std::stold(this->stack.front()->toString()) == 0.0f)
        throw MathErrorException();
    IOperand *topvalue = stack.front();
    stack.pop_front();
    IOperand *beforevalue = stack.front();
    stack.push_front(topvalue);
    IOperand *newval = *beforevalue / *topvalue;
    stack.pop_front();
    stack.pop_front();
    delete beforevalue;
    delete topvalue;
    stack.push_front(newval);
}

void Parser::mod()
{
    if(this->stack.size() < 2)
        throw EmptyStackException();
    if(std::stold(this->stack.front()->toString()) == 0.0f)
        throw MathErrorException();
    IOperand *topvalue = stack.front();
    stack.pop_front();
    IOperand *beforevalue = stack.front();
    stack.push_front(topvalue);
    IOperand *newval = *beforevalue % *topvalue;
    stack.pop_front();
    stack.pop_front();
    delete beforevalue;
    delete topvalue;
    stack.push_front(newval);
}

void Parser::prep_load(std::string str)
{
    std::string val;
    std::smatch cmd;
    std::string type;
    std::regex_search(str, cmd, std::regex("((load)[\\s](int8|int16|int32|float|double|bigdecimal)[\\s]*?(\\([\\s]*?((-?[0-9]+)|(-?[0-9]+\\.[0-9]+))[\\s]*?\\)))[\n]"));
    val = cmd.str(6);
    type = cmd.str(3);
    val = this->valcheck(type, val, cmd);
    if (std::stold(val) != std::round(std::stold(val)) || std::stold(val) > 15 || std::stold(val) < 0)
        throw BadArgException();

    this->load(std::stoi(val));
}

void Parser::load(int reg)
{
    if (this->registered.count(reg) == 0)
        throw RegistryException();
    IOperand *op = this->registered[reg];
    stack.push_front(op);
    this->registered.erase(reg);
}

void Parser::prep_store(std::string str)
{
    std::string val;
    std::smatch cmd;
    std::string type;
    if (stack.empty())
        throw EmptyStackException();
    std::regex_search(str, cmd, std::regex("((store)[\\s](int8|int16|int32|float|double|bigdecimal)[\\s]*?(\\([\\s]*?((-?[0-9]+)|(-?[0-9]+\\.[0-9]+))[\\s]*?\\)))[\n]"));
    val = cmd.str(6);
    type = cmd.str(3);
    val = this->valcheck(type, val, cmd);
    if (std::stold(val) != std::round(std::stold(val)) || std::stold(val) > 15 || std::stold(val) < 0) {
        throw BadArgException();
    }
    this->store(std::stoi(val));
}

void Parser::store(int reg)
{
    IOperand *op = this->stack.front();
    if(this->registered.count(reg)) {
        delete this->registered[reg];
        this->registered.erase(reg);
    }
    this->registered[reg] = op;
    stack.pop_front();
}

void Parser::print()
{
    if(this->stack.size() < 1)
        throw EmptyStackException();
    if (stack.front()->getType() != INT8)
        throw NotPrintableException();
    std::string val = stack.front()->toString();
    char print = (char) std::stoi(val);
    std::cout << print << std::endl;
}

void Parser::exit_exec()
{
    while(this->stack.size()) {
        IOperand *op = this->stack.front();
        this->stack.pop_front();
        delete op;
    }
    for(int i = 0; i < 16; i++){
        if(this->registered.count(i))
            delete this->registered[i];
            this->registered.erase(i);
    }
    this->dump();
}

Parser::~Parser()
{

}