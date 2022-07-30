/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-noe.sellam
** File description:
** main.c
*/

#include "../include/abstractVM.hpp"
#include "../include/Parser.hpp"
#include "../include/error.hpp"

std::string get_commands(char *av)
{
    std::ifstream file(av);

    if (!file) {
        throw NoSuchFileException();
        return (std::string(""));
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::string read_commands()
{
    std::string theline;
    std::string thelist;

    do {
        std::getline(std::cin, theline);
        thelist.append(theline);
        thelist.append("\n");
    } while  (theline != ";;");
    return (thelist);
}

int main(int ac, char *av[])
{
    std::string thelist;
    Parser parser;
    std::smatch cmd;

    try {
    if(ac > 2)
        throw BadArgException();
    if (ac == 1) {
        thelist = read_commands();
    } else {
        thelist = get_commands(av[1]);
    }
    thelist = std::regex_replace(thelist, std::regex(";[^;\\n].*\\n"), "\n");
    parser.parse(thelist);
    }
    catch(NoSuchFileException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(BadArgException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(RegistryException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(NoSuchMethodException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(WrongAssertion e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(NotPrintableException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(EmptyStackException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(MathErrorException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(OverflowException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(UnderflowException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }

    catch(NoExitException e)
    {
        std::cerr << "Caught exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}