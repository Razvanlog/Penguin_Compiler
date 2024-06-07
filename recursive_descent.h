#ifndef RECURSIVE_DESCENT_H
#define RECURSIVE_DESCENT_H
#include <vector>
#include <string>
#include <iostream>
#include "parse_tree.h"
class rd_parser{
    private:
    short start(std::shared_ptr<parse_node>);
    short command(std::shared_ptr<parse_node>);
    short init(std::shared_ptr<parse_node>);
    short read(std::shared_ptr<parse_node>);
    short write(std::shared_ptr<parse_node>);
    short attr(std::shared_ptr<parse_node>);
    short _if(std::shared_ptr<parse_node>);
    short loop(std::shared_ptr<parse_node>);
    short expression(std::shared_ptr<parse_node>);
    short term(std::shared_ptr<parse_node>);
    short expression_extend(std::shared_ptr<parse_node>);
    short term_extend(std::shared_ptr<parse_node>);
    short bool_eq(std::shared_ptr<parse_node>);
    short operand(std::shared_ptr<parse_node>);
    short FAIL(std::shared_ptr<parse_node>);
    //parse_node focus;
    std::vector<std::pair<std::string,std::string>>scan;
    int it=0;
    std::pair<std::string,std::string> *cur_word;
    std::pair<std::string,std::string> next_word();
    public:
    parse_tree parse_tree;
    void print(){
        parse_tree.print();
    }
    rd_parser(std::vector<std::pair<std::string,std::string>> a):scan(a){}
    short execute(){
        cur_word=new std::pair<std::string,std::string>;
        *cur_word=next_word();
        if (start(parse_tree.base())){
            if (cur_word->first=="eof"){
                return 1;
            }
        }
        return FAIL(parse_tree.base());
    }
};
#endif