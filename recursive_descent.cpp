#include "recursive_descent.h"
std::pair<std::string,std::string> rd_parser::next_word(){
    if (it<scan.size()){
        it++;
        return scan[it-1];
    }
    else return std::make_pair("eof","eof");
}
short rd_parser::start(std::shared_ptr<parse_node> focus){
   // if (){
        if ((cur_word->first=="variable" || cur_word->first=="end_line")||(cur_word->first=="keyword"&&(cur_word->second=="int" || cur_word->second=="read" || cur_word->second=="print" || cur_word->second=="if" || cur_word->second=="while"))){
            std::shared_ptr<parse_node>p(new parse_tree_nodes::command);
            focus->add_child(p);
            if (command(p)){
                std::shared_ptr<parse_node>pp(new parse_tree_nodes::start);
                focus->add_child(pp); 
                return start(pp);
            }
        }
    //}
    else if (cur_word->first=="end_program"){
            std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("end_program"));
            focus->add_child(p);
            *cur_word=next_word();
            return 1;
    }
    /*else if (){
        if (command()){
            std::shared_ptr<parse_node>p(new parse_tree_nodes::command);
            focus->add_child(p);
            return start();
        }
    }*/
    else if (cur_word->first=="scope_end"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("scope_end"));
        return true;
    }
    //std::shared_ptr<parse_node>p(new parse_tree_nodes::)
    return FAIL(focus);
}
short rd_parser::command(std::shared_ptr<parse_node> focus){
    if (cur_word->first=="keyword"){
        if (cur_word->second=="int"){
            std::shared_ptr<parse_node>p(new parse_tree_nodes::init);
            focus->add_child(p);
            return init(p);
            }
        if (cur_word->second=="read"){
            std::shared_ptr<parse_node>p(new parse_tree_nodes::read);
            focus->add_child(p);
            return read(p);
            }
        if (cur_word->second=="print"){
            std::shared_ptr<parse_node>p(new parse_tree_nodes::write);
            focus->add_child(p);
            return write(p);
            }
        if (cur_word->second=="if"){
            std::shared_ptr<parse_node>p(new parse_tree_nodes::_if);
            focus->add_child(p);
            return _if(p);
            }
        if (cur_word->second=="while"){
            std::shared_ptr<parse_node>p(new parse_tree_nodes::loop);
            focus->add_child(p);
            return loop(p);
        }
    }
    if (cur_word->first=="end_line"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("end_line"));
        focus->add_child(p);
        *cur_word=next_word();
        return 1;
    }
    if (cur_word->first=="end_program"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("end_program"));
        focus->add_child(p);
        *cur_word=next_word();
        return 1;
    }
    if (cur_word->first=="variable"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::attr);
        focus->add_child(p);
        return attr(p);
    }
    return FAIL(focus);
    //return 1;
}
short rd_parser::init(std::shared_ptr<parse_node> focus){
    if (cur_word->first=="keyword" && cur_word->second=="int")
    {
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("int"));
        focus->add_child(p);
        *cur_word=next_word();
        if (cur_word->first=="variable"){
            std::shared_ptr<parse_node>pp(new parse_tree_nodes::variable(cur_word->second));
            focus->add_child(pp);
            *cur_word=next_word();
            if (cur_word->first=="end_line"){
                std::shared_ptr<parse_node>ppp(new parse_tree_nodes::keyword("end_line"));
                focus->add_child(ppp);
                *cur_word=next_word();
                return true;
                }
        }
    }
    return FAIL(focus);
    //return 1;
}
short rd_parser::read(std::shared_ptr<parse_node> focus){
    if (cur_word->first=="keyword" && cur_word->second=="read")
    {
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("read"));
        focus->add_child(p);
        *cur_word=next_word();
        if (cur_word->first=="variable"){
            std::shared_ptr<parse_node>pp(new parse_tree_nodes::variable(cur_word->second));
            *cur_word=next_word();
            focus->add_child(pp);
            if (cur_word->first=="end_line"){
                std::shared_ptr<parse_node>ppp(new parse_tree_nodes::keyword("end_line"));
                focus->add_child(ppp);
                *cur_word=next_word();
                return true;
                }
        }
    }
    return FAIL(focus);
}
short rd_parser::write(std::shared_ptr<parse_node> focus){
    if (cur_word->first=="keyword" && cur_word->second=="print")
    {
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("print"));
        focus->add_child(p);
        *cur_word=next_word();
        if (cur_word->first=="variable"){
            std::shared_ptr<parse_node>pp(new parse_tree_nodes::variable(cur_word->second));
            focus->add_child(pp);
            *cur_word=next_word();
            if (cur_word->first=="end_line"){
                std::shared_ptr<parse_node>ppp(new parse_tree_nodes::keyword("end_line"));
                focus->add_child(ppp);
                *cur_word=next_word();
                return true;
                }
        }
    }
    return FAIL(focus);
    //return 1;
}
short rd_parser::attr(std::shared_ptr<parse_node> focus){
   // std::cout<<cur_word->first<<' '<<cur_word->second<<'\n';
    if (cur_word->first=="variable"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::variable(cur_word->second));
        focus->add_child(p);
        *cur_word=next_word();
        if (cur_word->first=="assign"){
            std::shared_ptr<parse_node>pp(new parse_tree_nodes::keyword("assign"));
            focus->add_child(pp);
            *cur_word=next_word();
            std::shared_ptr<parse_node>ppp(new parse_tree_nodes::expression);
            focus->add_child(ppp);
            if (expression(ppp)){
                //std::cout<<cur_word->first<<' '<<cur_word->second<<'\n';
                if (cur_word->first=="end_line"){
                    std::shared_ptr<parse_node>p4(new parse_tree_nodes::keyword("end_line"));
                    focus->add_child(p4);
                    *cur_word=next_word();
                    return true;}
            }
        }
    }
    return FAIL(focus);
    //return 1;
}
short rd_parser::_if(std::shared_ptr<parse_node> focus){
    if (cur_word->first=="keyword" && cur_word->second=="if"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("if"));
        focus->add_child(p);
        *cur_word=next_word();
        std::shared_ptr<parse_node>pp(new parse_tree_nodes::bol_eq);
        focus->add_child(pp);
        if (bool_eq(pp)){
            if (cur_word->first=="scope_begin"){
                std::shared_ptr<parse_node>ppp(new parse_tree_nodes::keyword("scope_begin"));
                focus->add_child(ppp);
                *cur_word=next_word();
                std::shared_ptr<parse_node>p4(new parse_tree_nodes::start);
                focus->add_child(p4);
                if (start(p4)){
                    if (cur_word->first=="scope_end"){
                        std::shared_ptr<parse_node>p5(new parse_tree_nodes::keyword("scope_end"));
                        focus->add_child(p5);
                        *cur_word=next_word();
                        return true;
                    }
                }
            }
        }
    }
    return FAIL(focus);
    return 1;
}
short rd_parser::loop(std::shared_ptr<parse_node> focus){
    if (cur_word->first=="keyword" && cur_word->second=="while"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("while"));
        focus->add_child(p);
        *cur_word=next_word();
        std::shared_ptr<parse_node>pp(new parse_tree_nodes::bol_eq);
        focus->add_child(pp);
        if (bool_eq(pp)){
            if (cur_word->first=="scope_begin"){
                std::shared_ptr<parse_node>ppp(new parse_tree_nodes::keyword("scope_begin"));
                focus->add_child(ppp);
                *cur_word=next_word();
                std::shared_ptr<parse_node>p4(new parse_tree_nodes::start);
                focus->add_child(p4);
                if (start(p4)){
                    if (cur_word->first=="scope_end"){
                        std::shared_ptr<parse_node>p5(new parse_tree_nodes::keyword("scope_end"));
                        focus->add_child(p5);
                        *cur_word=next_word();
                        return true;
                    }
                }
            }
        }
    }
    return FAIL(focus);
    //return 1;
}
short rd_parser::expression(std::shared_ptr<parse_node> focus){
    //std::cout<<cur_word->first<<' '<<cur_word->second<<'\n';
    if (cur_word->first=="integer" || cur_word->first=="variable" || cur_word->first=="begin_par"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::term);
        focus->add_child(p);
        if (term(p)){
            std::shared_ptr<parse_node>pp(new parse_tree_nodes::expression_extend);
            focus->add_child(pp);
            return expression_extend(pp);
        }
    }
    return FAIL(focus);
    return 1;
}
short rd_parser::expression_extend(std::shared_ptr<parse_node> focus){
    //std::cout<<cur_word->first<<' '<<cur_word->second<<'\n';
   if (cur_word->first=="scope_begin" || cur_word->first=="bin_op" || cur_word->first=="end_line"){
        //*cur_word=next_word();
        return true;
    }
    if (cur_word->first=="end_par"){
        return true;
    }
    else if (cur_word->first=="operator" && (cur_word->second=="+" || cur_word->second=="-")){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::operator1(cur_word->second));
        focus->add_child(p);
        *cur_word=next_word();
        std::shared_ptr<parse_node>pp(new parse_tree_nodes::term);
        focus->add_child(pp);
        if (term(pp)){
            std::shared_ptr<parse_node>ppp(new parse_tree_nodes::expression_extend);
            focus->add_child(ppp);
            return expression_extend(ppp);
        }
    }
    return FAIL(focus);
    return 1;
}
short rd_parser::term(std::shared_ptr<parse_node> focus){
    //std::cout<<cur_word->first<<' '<<cur_word->second<<'\n';
    if (cur_word->first=="begin_par" || cur_word->first=="integer"|| cur_word->first=="variable"){
        //*cur_word=next_word();
        std::shared_ptr<parse_node>p(new parse_tree_nodes::operand);
        focus->add_child(p);
    if (operand(p)){
        std::shared_ptr<parse_node>pp(new parse_tree_nodes::term_extend);
        focus->add_child(pp);
        return term_extend(pp);
    }
    }
    return FAIL(focus);
    return 1;
}
short rd_parser::term_extend(std::shared_ptr<parse_node> focus){
    //std::cout<<cur_word->first<<' '<<cur_word->second<<'\n';
    if (cur_word->first=="scope_begin" || cur_word->first=="bin_op" || cur_word->first=="end_par" || cur_word->first=="end_line" || (cur_word->first=="operator" && (cur_word->second=="+" || cur_word->second=="-"))){
        //*cur_word=next_word();
        //std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword(cur_))
        return true;
    }
    if (cur_word->first=="operator" && (cur_word->second=="*" || cur_word->second=="/")){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::operator2(cur_word->second));
        focus->add_child(p);
        *cur_word=next_word();
        std::shared_ptr<parse_node>pp(new parse_tree_nodes::operand);
        focus->add_child(pp);
        if (operand(pp)){
            std::shared_ptr<parse_node>ppp(new parse_tree_nodes::term_extend);
            focus->add_child(ppp);
            return term_extend(ppp);
        }
    }
    return FAIL(focus);
    return 1;
}
short rd_parser::operand(std::shared_ptr<parse_node> focus){
    //std::cout<<cur_word->first<<' '<<cur_word->second<<'\n';
    if (cur_word->first=="variable" || cur_word->first=="integer"){
        if (cur_word->first=="variable"){
            std::shared_ptr<parse_node> p(new parse_tree_nodes::variable(cur_word->second));
            focus->add_child(p);
        }
        else{
            std::shared_ptr<parse_node> p(new parse_tree_nodes::integer(cur_word->second));
            focus->add_child(p);
        }
        *cur_word=next_word();
        return true;
    }
    if (cur_word->first=="begin_par"){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::keyword("begin_par"));
        focus->add_child(p);
        *cur_word=next_word();
        std::shared_ptr<parse_node>pp(new parse_tree_nodes::expression);
        focus->add_child(pp);
        if (expression(pp)){
            if (cur_word->first=="end_par"){
                std::shared_ptr<parse_node>ppp(new parse_tree_nodes::keyword("end_par"));
                focus->add_child(ppp);
                *cur_word=next_word();
                return true;
            }
        }
    }
    return FAIL(focus);
    return 1;
}   
short rd_parser::FAIL(std::shared_ptr<parse_node> focus){
    return 0;
}
short rd_parser::bool_eq(std::shared_ptr<parse_node> focus){
    if (cur_word->first=="begin_par" || cur_word->first=="variable"||(cur_word->first=="keyword" && cur_word->second=="int")){
        std::shared_ptr<parse_node>p(new parse_tree_nodes::expression);
        focus->add_child(p);
        if (expression(p)){ 
            //std::shared_ptr<parse_node>p(new parse_tree_nodes::)
            if (cur_word->first=="bin_op"){
                std::shared_ptr<parse_node>pp(new parse_tree_nodes::bin_op(cur_word->second));
                *cur_word=next_word();
                focus->add_child(pp);
                std::shared_ptr<parse_node>ppp(new parse_tree_nodes::expression);
                focus->add_child(ppp);
                return expression(ppp);
            }
        }
    }
   //return 1;
    /*else if (cur_word->first=="keyword" && cur_word->second=="int"){
        if (expression()){
            *cur_word=next_word();
            return expression();
        }
    }*/
    /*else if (cur_word->first=="begin_par"){
        if (expression()){
            *cur_word=next_word();
            return expression();
        }
    }*/
    return FAIL(focus);
}