#include "front_end.h"
//last used state 35
short word_trans_func(short state,char c){
    //start position
    /*if (c==' ' || c=='\0' || c=='\n' || c=='\t'){
        return 32767;
    }*/
    if (state==0){
        if (c>='1' && c<='9'){
            return 1;
        }
        else if (c=='0'){
            return 2;
        }
        else if (c=='+' || c=='-' ||c=='/' || c=='*')
            return 7;
        else if (c=='=')
            return 32;
        else if (c=='!')
            return 34;
        else if (c=='>')
            return 36;
        else if (c=='<')
            return 38;
        else if (c=='l'){
            return 3;
        }
        else if (((c>='a' && c<='z')||(c=='_' || c=='@' || c=='#' || c=='$')) && c!='r' && c!='p' && c!='i' && c!='f' && c!='e' && c!='w'){
            return 6;
        }
        else if (c=='e')
            return 21;
        else if (c=='w')
            return 25;
        else if (c=='r')
            return 11;
        else if (c=='i')
            return 3;
        else if (c=='f')
            return 8;
        else if (c=='p')
            return 15;
        else return -1;
    }
    //bin ops
    else if (state==36){
        if (c=='=')
            return 37;
    }
    else if (state==37)
        return -1;
    else if (state==38){
        if (c=='=')
            return 39;
    }
    else if (state==39){
        return -1;
    }
    else if (state==32){
        if (c=='='){
            return 33;
        }
    }
    else if (state==33){
        return -1;
    }
    else if (state==34){
        if (c=='=')
            return 35;
    }
    else if (state==35)
        return -1;
    //integers
    else if (state==1){
        if (c>='0' && c<='9'){
            return 1;
        }
        else return -1;
    }
    else if (state==2){
        return -1;
    }
    //operators
    else if (state==7){
        return -1;
    }
    //variable
    else if (state==6){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    //while
    else if (state==25){
        if (c=='h')
            return 26;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==26){
        if (c=='i')
            return 27;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==27){
        if (c=='l')
            return 28;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==28){
        if (c=='e')
            return 29;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==29){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    //else and end
    else if (state==21){
        if (c=='l')
            return 22;
        if (c=='n')
            return 30;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==22){
        if (c=='s')
            return 23;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==23){
        if (c=='e')
            return 24;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==24){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==30){
        if (c=='d')
            return 31;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==31){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    //print
    else if (state==15){
        if (c=='r')
            return 16;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==16){
        if (c=='i')
            return 17;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==17){
        if (c=='n')
            return 18;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==18){
        if (c=='t')
            return 19;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==19){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    //if and int
    else if (state==3){
        //go if
        if (c=='f')
            return 20;
        //go int
        else if (c=='n')
            return 4;
        //go var
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    //if 
    else if (state==20){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    //int
    else if (state==4){
        if (c=='t')
        return 5;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==5){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    //for
    else if(state==8){
        if (c=='o')
            return 9;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==9){
        if (c=='r')
            return 10;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==10){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    //read
    else if (state==11){
        if (c=='e')
            return 12;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==12){
        if (c=='a')
            return 13;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==13){
        if (c=='d')
            return 14;
        else if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    else if (state==14){
        if ((c>='a' && c<='z')||(c>='0' && c<='9')||(c=='_' || c=='@' || c=='#' || c=='$'))
            return 6;
        else return -1;
    }
    return -1;
}
/*short integer_trans_func(short state,char c){
    if (state==0){
        if (c=='0')
            return 2;
        else if (c>='1' && c<='9')
            return 1;
    }
    else if (state==1){
        if (c>='0' && c<='9')
            return 1;
    }
    else if (state==2){

    }
    return -1;
}
short operators_trans_func(short state,char c){
    if (state==0){
        if (c=='=')
            return 3;
        if (c=='!')
            return 4;
        if (c=='+' || c=='-' || c=='/' || c=='*')
            return 5;
    }
    if (state==3){
        if (c=='=')
            return 6;
    }
    if (state==4){
        if (c=='=')
            return 6;
    }
    return -1;
}
short operand_trans_func(short state,char c){
    if (state==0){
        if ((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='@' || c=='#' || c=='$'){
            return 7;
        }
    }
    if (state==7){
        if ((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z') || c=='@' || c=='#' || c=='$'){
            return 7;
        }
    }
    return -1;
}*/
short scanner::rollback(){
    if (input==fence)
        return -1;
    input=(input-1)%(2*MAX_N);
    return 0;
}
char scanner::next_char(){
    char c;
    if (input<buffer.size()){
        c=buffer[input];
    }
    else c='\0';
    //memset(buffer,0,sizeof(buffer));
    input=(input+1)%(2*MAX_N);
    if (input%MAX_N==0){
        /*for (int i=0; i<MAX_N; i++){
            program>>buffer[input+i];
            fence=(input+MAX_N)%(2*MAX_N);
        }*/
        char c=1;
        for (int i=0; i<MAX_N && !program.eof(); i++){
            program>>std::noskipws>>c;
            buffer=buffer+c;
            if (c=='\0')
                break;
        }
        fence=(input+MAX_N)%(2*MAX_N);
    }
    return c;
}
std::pair<std::string,std::string> scanner::next_word(){
    int state=0;
    std::string s="",type="bad";
    char c;
    c=next_char();
    while (c==' '){
        c=next_char();
    }
    //rollback();
    //c=next_char();
    //std::cout<<(int)c<<' '<<c<<'\n';
    if (c=='\n'){

        return std::make_pair("end_line","end_line");
    }
    if (c=='\0'){
        return std::make_pair("end_program","end_program");
    }
    if (c=='{'){
        return std::make_pair("scope_begin","scope_begin");
    }
    if (c=='}')
        return std::make_pair("scope_end","scope_end");
    if (c=='(')
        return std::make_pair("begin_par","begin_par");
    if (c==')')
        return std::make_pair("end_par","end_par");
    if (c==',')
        return std::make_pair("comma","comma");
    while (state>=0){
        //c=next_char();
        state=word_trans_func(state,c);
        if (state>=0){
            if (state<=32767){
            s=s+c;
            if (state==1 || state==2)
                type="integer";
            else if (state==7 || state==32 || state==33 || state==35 || state==37 || state==39){
                if (s=="+" || s=="-" || s=="/" || s=="*")
                    type="operator";
                else if (s=="=")
                    type="assign";
                else if (s=="==" || s=="!=" || s==">" || s=="<" || s=="<=" || s==">=")
                    type="bin_op";
            }
            else if (state==14 || state==19 || state==20 || state==5 || state==10 || state==29 || state==24 || state==31)
                type="keyword";
            else type="variable";
            if (s=="end"){
                type="end_program";
                s="end_program";
            }
            }
        }
        else{
            rollback();
        }
        c=next_char();
    }
    rollback();
    return std::make_pair(type,s);
 //   }
}
std::vector<std::pair<std::string,std::string>> scanner::execute(){
    if (first_take.empty()){
    std::pair<std::string,std::string> p;
    //std::vector<std::pair<std::string,std::string>> v;
    int ok=1;
    do{
        p=next_word();
        //p=next_word();
        if (p.first=="bad")
            ok=0;
        else{
            if (p.first=="end_program"){
                std::pair<std::string,std::string> pp=std::make_pair("end_line","end_line");
                first_take.push_back(pp);
            }
            if ((first_take.size() && first_take.back().first=="end_line" && p.first=="end_line")){
            }
            else{
            first_take.push_back(p);
            }
        }
    }while (p.second!="end_program" && ok);
    if (ok==0){
        first_take.push_back(std::make_pair<std::string,std::string>("bad","bad"));
    }
    }
    return first_take;
    //while (strcmp(p.first))
}
/*
std::pair<std::string,std::string> parser::next_word(std::vector<std::pair<std::string,std::string>> scan){
    std::pair<std::string,std::string> word=scan.front();
    scan.erase(scan.begin());
    return word;
}
bool parser::check_terminal(std::pair<std::string,std::string> root){
    if (root.first=="integer" || 
    root.first=="variable" || 
    //root->get_type().first=="operand" || 
    root.first=="keyword"||
    root.first=="comma"||
    root.first=="operator"||
    root.first=="assign"||
    root.first=="begin_par"||
    root.first=="second_par"||
    root.first=="end_line"//||
    //root->get_type().first=="end"
    )
        return 1;
    return 0;
}*/