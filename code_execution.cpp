#include "code_execution.h"
execute::execute(parse_tree a){
    execute_value=0;
    start(a.base());
}
void execute::start(std::shared_ptr<parse_node> focus){
    if (focus->type()=="start"){
        std::vector<std::shared_ptr<parse_node>> leafs=focus->leafs();
        if (leafs.size()==1 || leafs.size()==0){
            return;
        }
        command(leafs[0]);
        if (!execute_value)
        start(leafs[1]);
    }
    else execute_value=1;
}
void execute::command(std::shared_ptr<parse_node> focus){
    if (focus->type()=="command"){
        std::vector<std::shared_ptr<parse_node>> leafs=focus->leafs();
        if (leafs[0]->type()=="read"){
            read(leafs[0]);
        }
        if (leafs[0]->type()=="init"){
            init(leafs[0]);
        }
        if (leafs[0]->type()=="write"){
            write(leafs[0]);
        }
        if (leafs[0]->type()=="attr"){
            attr(leafs[0]);
        }
        if (leafs[0]->type()=="if"){
            _if(leafs[0]);
        }
        if (leafs[0]->type()=="loop"){
            loop(leafs[0]);
        }
    }
}
void execute::init(std::shared_ptr<parse_node> focus){
    std::shared_ptr<parse_tree_nodes::variable>p(std::dynamic_pointer_cast<parse_tree_nodes::variable>(focus->leafs()[1]));
    if (value_table.find(p->name)==value_table.end()){
        value_table[p->name]=0;
    }
    else {execute_value=1;
    error_message="variable "+p->name+" already initialized";
    }
}
void execute::read(std::shared_ptr<parse_node>focus){
    std::shared_ptr<parse_tree_nodes::variable>p(std::dynamic_pointer_cast<parse_tree_nodes::variable>(focus->leafs()[1]));
    if (value_table.find(p->name)==value_table.end()){
        execute_value=1;
        error_message="variable not initialized: "+p->name;
    }
    else{
        std::string s;
        int temp=0;
        std::cin>>s;
        for (int i=0; i<s.size(); i++){
            if (s[i]>='0' && s[i]<='9')
            temp=temp*10+s[i]-'0';
            else {
                execute_value=1;
                error_message="inputted value is not an integer: "+s;
                return ;
            }
        }
        value_table[p->name]=temp;
    }
}
void execute::write(std::shared_ptr<parse_node>focus){
    std::shared_ptr<parse_tree_nodes::variable>p(std::dynamic_pointer_cast<parse_tree_nodes::variable>(focus->leafs()[1]));
    if (value_table.find(p->name)==value_table.end()){
        execute_value=1;
        error_message="variable not initialized: "+p->name;
    }
    else{
        std::cout<<value_table[p->name]<<'\n';
    }
}
void execute::attr(std::shared_ptr<parse_node>focus){
    //std::vector<std::shared_ptr<parse_node>>leafs=focus->leafs();
    std::shared_ptr<parse_tree_nodes::variable>p(std::dynamic_pointer_cast<parse_tree_nodes::variable>(focus->leafs()[0]));
    std::shared_ptr<parse_tree_nodes::expression>exp(std::dynamic_pointer_cast<parse_tree_nodes::expression>(focus->leafs()[2]));
    if (value_table.find(p->name)==value_table.end()){
        execute_value=1;
        error_message="variable not initialized: "+p->name;
        return;
    }
    value_table[p->name]=expression(exp);
}
void execute::loop(std::shared_ptr<parse_node>focus){
    std::shared_ptr<parse_tree_nodes::bol_eq>p(std::dynamic_pointer_cast<parse_tree_nodes::bol_eq>(focus->leafs()[1]));
    int condition=bool_eq(p);
    if (!execute_value)
    while (condition){
       // std::cout<<condition<<'\n';
        std::shared_ptr<parse_tree_nodes::start>pp(std::dynamic_pointer_cast<parse_tree_nodes::start>(focus->leafs()[3]));
        if (!execute_value)
        start(pp);
        if (!execute_value)
        condition=bool_eq(p);
    }
    return;
}
void execute::_if(std::shared_ptr<parse_node>focus){
    std::shared_ptr<parse_tree_nodes::bol_eq>p(std::dynamic_pointer_cast<parse_tree_nodes::bol_eq>(focus->leafs()[1]));
    int condition=bool_eq(p);
    if (!execute_value)
    if (condition){
        std::shared_ptr<parse_tree_nodes::start>pp(std::dynamic_pointer_cast<parse_tree_nodes::start>(focus->leafs()[3]));
        if (!execute_value)
        start(pp);
        //if (!execute_value)
        //condition=bool_eq(p);
    }
    return;
}
int execute::expression(std::shared_ptr<parse_node>focus){
    int value=term(focus->leafs()[0]);
    value+=expression_extend(focus->leafs()[1]);
    return value;
}
int execute::expression_extend(std::shared_ptr<parse_node>focus){
    if (focus->leafs().size()){
    int value=0;
    std::shared_ptr<parse_tree_nodes::operator1>p(std::dynamic_pointer_cast<parse_tree_nodes::operator1>(focus->leafs()[0]));
    std::shared_ptr<parse_tree_nodes::term>pp(std::dynamic_pointer_cast<parse_tree_nodes::term>(focus->leafs()[1]));
    if (p->sign()=="+"){
        value+=term(pp);
    }
    else value-=term(pp);
    value+=expression_extend(focus->leafs()[2]);
    return value;
    }
    else return 0;
}
double execute::term(std::shared_ptr<parse_node>focus){
    int value=operand(focus->leafs()[0]);
    value*=term_extend(focus->leafs()[1]);
    return value;
}
double execute::term_extend(std::shared_ptr<parse_node>focus){
    if (focus->leafs().empty())
    return 1;
    std::shared_ptr<parse_tree_nodes::operator2>p(std::dynamic_pointer_cast<parse_tree_nodes::operator2>(focus->leafs()[0]));
    std::shared_ptr<parse_tree_nodes::operand>pp(std::dynamic_pointer_cast<parse_tree_nodes::operand>(focus->leafs()[1]));
    double value=1;
    if (p->sign()=="*"){
        value=value*operand(pp);
    }
    else value=value/operand(pp);
    value*=term_extend(focus->leafs()[2]);
    return value;
}
int execute::operand(std::shared_ptr<parse_node>focus){
    int value=0;
    if (focus->leafs()[0]->type()=="variable"){
        return variable(focus->leafs()[0]);
        //return value;
    }
    if (focus->leafs()[0]->type()=="integer"){
        return integer(focus->leafs()[0]);
        //return value;
    }
    return expression(focus->leafs()[1]);
}
int execute::variable(std::shared_ptr<parse_node>focus){
    std::shared_ptr<parse_tree_nodes::variable>p(std::dynamic_pointer_cast<parse_tree_nodes::variable>(focus));
    if (value_table.find(p->name)==value_table.end())
    {
        execute_value=1;
        error_message="variable not initialized: "+p->name;
        return 0;
    }
    return value_table[p->name];
}
int execute::integer(std::shared_ptr<parse_node>focus){
    std::shared_ptr<parse_tree_nodes::integer>p(std::dynamic_pointer_cast<parse_tree_nodes::integer>(focus));
    //std::cout<<focus->type()<<' '<<p->value<<'\n';
    return p->value;
    //std::cout<<focus->leafs().size()<<'\n';
    //return 0;
}
int execute::bool_eq(std::shared_ptr<parse_node>focus){
    int value_a=expression(focus->leafs()[0]),value_b=expression(focus->leafs()[2]);
    std::shared_ptr<parse_tree_nodes::bin_op>p(std::dynamic_pointer_cast<parse_tree_nodes::bin_op>(focus->leafs()[1]));
    std::string bin_op=p->op;
    if (bin_op=="!="){
        if (value_a!=value_b)
            return 1;
    }
    else if (bin_op=="=="){
        if (value_a==value_b)
            return 1;
    }
    else if (bin_op=="<"){
        if (value_a<value_b)
        return 1;
    }
    else if (bin_op=="<="){
        if (value_a<=value_b)
        return 1;
    }
    else if (bin_op==">"){
        if (value_a>value_b)
        return 1;
    }
    else if (bin_op==">="){
        if (value_a>=value_b)
        return 1;
    }
    return 0;
}