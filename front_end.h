#ifndef FRONT_END_H
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <unordered_map>
#include "recursive_descent.h"
#define FRONT_END_H
//#define p_pstrstr std::shared_ptr<std::pair<std::string,std::string>>
#define MAX_N (2048)
class scanner{
    private:
    int input,fence;
    std::string buffer;
    std::ifstream program;
    std::vector<std::pair<std::string,std::string>> first_take;
    //std::vector<std::vector<std::pair<std::string,std::string>>> second_take;
    protected:
    public:
    scanner(const char*name):program(name),input(0),fence(0){
        for (int i=0; i<MAX_N && !program.eof(); i++){
            char c;
            program>>std::noskipws>>c;
            if (!program.eof())
            buffer=buffer+c;
        }
        //std::cout<<buffer<<'\n';
    }
    int it=0;
    std::vector<std::pair<std::string,std::string>> scan;
    std::pair<std::string,std::string> next();
    std::pair<std::string,std::string> next_word();
    short rollback();
    char next_char();
    std::vector<std::pair<std::string,std::string>> execute();
    //std::vector<std::vector<std::pair<std::string,std::string>>> sep_lines();
};
#endif