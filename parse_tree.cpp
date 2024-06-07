#include "parse_tree.h"
using namespace parse_tree_nodes;
void parse_tree::print()const{
    root->print();
}
void parse_node::print(){
    std::cout<<this->type()<<' ';
    for (int i=0; i<children.size(); i++){
        children[i]->print();
    }
    std::cout<<'\n';
}
std::vector<std::shared_ptr<parse_node>> parse_node::leafs(){
    return children;
}
void parse_node::add_child(std::shared_ptr<parse_node> a){
    //std::shared_ptr<parse_node> p(new parse_node);
    children.push_back(a);
}
std::string parse_node::type(){
    std::string s("null");
    return s;
}
std::string start::type(){
    return "start";
}
std::string command::type(){
        return "command";
}
std::string init::type(){
        return "init";
}
std::string read::type(){
        return "read";
}
std::string write::type(){
        return "write";
}
std::string attr::type(){
        return "attr";
}
std::string _if::type(){
        return "if";
}
std::string loop::type(){
        return "loop";
}
std::string end_line::type(){
        return "end_line";
}
std::string variable::type(){
    return "variable";
}
variable::variable(std::string a):name(a),parse_node(){}
std::string integer::type(){
    return "integer";
}
void variable::print(){
    std::cout<<this->type()<<' '<<this->name<<'\n'<<'\n';
}
integer::integer(std::string a):parse_node(){
    value=0;
    //std::cout<<a<<' ';
    for (int i=0; i<a.size(); i++){
        value=value*10+a[i]-'0';
    }
    //std::cout<<value<<'\n';
}
void integer::print(){
    std::cout<<this->type()<<' '<<value<<'\n'<<'\n';
}
std::string operand::type(){
    return "operand";
}
std::string expression::type(){
    return "expression";
}
std::string expression_extend::type(){
    return "expression_extend";
}
std::string term::type(){
    return "term";
}
std::string term_extend::type(){
    return "term_extend";
}
std::string keyword::type(){
    return "keyword";
}
keyword::keyword(std::string a):keyw(a),parse_node(){}
std::string bol_eq::type(){
    return "bol_eq";
}
void keyword::print(){
    std::cout<<this->type()<<' '<<keyw<<'\n'<<'\n';
}
std::string operator1::type(){
    return "operator1";
}
std::string operator1::sign(){
    return op;
}
operator1::operator1(std::string a):op(a),parse_node(){}
void operator1::print(){
    std::cout<<this->type()<<' '<<op<<'\n'<<'\n';
}
std::string operator2::type(){
    return "operator2";
}
std::string operator2::sign(){
    return op;
}
operator2::operator2(std::string b):op(b),parse_node(){}
void operator2::print(){
    std::cout<<this->type()<<' '<<op<<'\n'<<'\n';
}
bin_op::bin_op(std::string a):op(a),parse_node(){}
void bin_op::print(){
    std::cout<<this->type()<<' '<<op<<'\n'<<'\n';
}
std::string bin_op::sign(){
    return op;
}
std::string bin_op::type(){
    return "bin_op";
}