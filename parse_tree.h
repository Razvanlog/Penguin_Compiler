#ifndef PARSE_TREE_H
#define PARSE_TREE_H
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "parse_tree.h"
class parse_node{
    private:
    std::vector<std::shared_ptr<parse_node>> children;
    public:
    void add_child(std::shared_ptr<parse_node>);
    virtual std::string type();
    virtual void print();
    std::vector<std::shared_ptr<parse_node>> leafs();
};
namespace parse_tree_nodes
{
class start:public parse_node{
    public:
    std::string type();
    //void print();
};
class command:public parse_node{
    public:
    std::string type();
    //void print();
};
class init:public parse_node{
    public:
    std::string type();
    //void print();
};
class read:public parse_node{
    public:
    std::string type();
    //void print();
};
class write:public parse_node{
    public:
    std::string type();
    //void print();
};
class attr:public parse_node{
    public:
    std::string type();
    //void print();
};
class _if :public parse_node{
    public:
    std::string type();
    //void print();
};
class loop:public parse_node{
    public:
    std::string type();
    //void print();
};
class end_line: public parse_node{
    public:
    std::string type();
    //void print();
};
class operand: public parse_node{
    public:
    std::string type();
    //void print();
};
class expression: public parse_node{
    public:
    std::string type();
    //void print();
};
class expression_extend: public parse_node{
    public:
    std::string type();
    //void print();
};
class term: public parse_node{
    public:
    std::string type();
    //void print();
};
class term_extend: public parse_node{
    public:
    std::string type();
    //void print();
};
class keyword: public parse_node{
    private:
    std::string keyw;
    public:
    std::string type();
    keyword(std::string);
    void print();
};
class bol_eq: public parse_node{
    private:
    public:
    std::string type();
    //void print();
};
class operator1: public parse_node{
    private:
    std::string op;
    public:
    std::string type();
    operator1(std::string);
    std::string sign();
    void print();
};
class operator2: public parse_node{
    private:
    std::string op;
    public:
    std::string type();
    std::string sign();
    operator2(std::string);
    void print();
};
class variable: public parse_node{
    public:
    std::string name;
    std::string type();
    variable(std::string);
    void print();
};
class integer: public parse_node{
    public:
    int value;
    std::string type();
    integer(std::string);
    void print();
};
class bin_op: public parse_node{
    public:
    std::string op;
    std::string type();
    bin_op(std::string);
    std::string sign();
    void print();
};
}
class parse_tree{
    private:
    std::shared_ptr<parse_node> root;
    public:
    void print()const;
    parse_tree():root(new parse_tree_nodes::start){}
    std::shared_ptr<parse_node> base(){
        return root;
    }
};
#endif