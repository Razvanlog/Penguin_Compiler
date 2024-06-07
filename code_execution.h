#ifndef CODE_EXECUTION_H
#define CODE_EXECUTION_H
#include "parse_tree.h"
#include <map>
#include <string>
#include<iostream>
class execute{
    private:
    std::map<std::string,int> value_table;
    public:
    int execute_value;
    std::string error_message;
    void start(std::shared_ptr<parse_node>);
    void command(std::shared_ptr<parse_node>);
    void read(std::shared_ptr<parse_node>);
    void write(std::shared_ptr<parse_node>);
    void attr(std::shared_ptr<parse_node>);
    void loop(std::shared_ptr<parse_node>);
    void _if(std::shared_ptr<parse_node>);
    void init(std::shared_ptr<parse_node>);
    int expression(std::shared_ptr<parse_node>);
    int expression_extend(std::shared_ptr<parse_node>);
    double term(std::shared_ptr<parse_node>);
    double term_extend(std::shared_ptr<parse_node>);
    int operand(std::shared_ptr<parse_node>);
    int variable(std::shared_ptr<parse_node>);
    int integer(std::shared_ptr<parse_node>);
    int bool_eq(std::shared_ptr<parse_node>);
    execute (parse_tree);
};
#endif