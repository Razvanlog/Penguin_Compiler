#include <iostream>
#include "front_end.h"
#include "code_execution.h"
using namespace std;
int main(int argc, char**argv){
    string file;
    if (argc<2){
        cout<<"enter program path: ";
        //string a;
        cin>>file;
    }
    else file=argv[1];
    ifstream a(file.c_str());
    if (file.size()>=3){
        string a;
        a=file[file.size()-4];
        a=a+file[file.size()-3];
        a=a+file[file.size()-2];
        a=a+file[file.size()-1];
        if (a==".pin"){

        }
        else {
        cout<<"file is invalid: does not have .pin file extension";
            return 0;
        }
    }
    else {
        cout<<"file is invalid: does not have .pin file extension";
        return 0;
    }
    if (a.fail()){
        cout<<"cannot find "<<file<<'\n';
        return 0;
    }
    a.close();
    cout<<"scanning symbols in "<<file<<"..."<<'\n';
    scanner p(file.c_str());
    cout<<"succesfully scanned!"<<'\n';
    /*vector<pair<string,string>>  vs=p.execute();
    for (int i=0; i<vs.size(); i++){
        cout<<vs[i].first<<' '<<vs[i].second<<'\n';
    }*/
    cout<<"parsing in progess..."<<'\n';
    rd_parser parser(p.execute());
    int ok=parser.execute();
    if (ok){
    cout<<"succesfully parsed "<<file<<"!"<<'\n';
    //parser.print();
    if (ok){
        cout<<"executing code..."<<'\n'<<'\n'<<'\n';
    execute back_end(parser.parse_tree);
    //cout<<'\n'<<back_end.execute_value;
    if (back_end.execute_value)
        cout<<"\n\nruntime error: "<<back_end.error_message;
    else cout<<"\n\nprogram executed succesfully!\n";
    }
    }
    else cout<<"parser failed!\n check program";
    //parser.print();
    return 0;
}