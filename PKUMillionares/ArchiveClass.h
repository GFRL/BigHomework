#ifndef ARCHIVECLASS_H
#define ARCHIVECLASS_H

#include <filesystem>
#include<queue>
#include<QListWidget>
#include<fstream>

using namespace std;
class Student{
public:
    int money=0,health=0;
    void Read(ifstream& o){
        o>>money>>health;
        return;
    }
    void Write(ofstream& o){
        o<<money<<' '<<health<<endl;
        return;
    }
    void init(){
        int money=0,health=0;
    }
};
class Cooker{
public:
    int money=0,health=0;
    void Read(ifstream& o){
        o>>money>>health;
        return;
    }
    void Write(ofstream& o){
        o<<money<<' '<<health<<endl;
        return;
    }
    void init(){
        int money=0,health=0;
    }
};
class Icecreamgirl{
public:
    int money=0,health=0;
    void Read(ifstream& o){
        o>>money>>health;
        return;
    }
    void Write(ofstream& o){
        o<<money<<' '<<health<<endl;
        return;
    }
    void init(){
        int money=0,health=0;
    }
};
class Cleaner{
public:
    int money=0,health=0;
    void Read(ifstream& o){
        o>>money>>health;
        return;
    }
    void Write(ofstream& o){
        o<<money<<' '<<health<<endl;
        return;
    }
    void init(){
        int money=0,health=0;
    }
};

class archive{
public:
    string Name;
    string Root_place;
    int History_score=0;
    int now_score=0;
    int career[4]={1,1,1,1};
    Student student;Cooker cooker;Icecreamgirl icecreamgirl;Cleaner cleaner;

    int score_calculate(){
        return rand();
    }
    void Read(ifstream& o){
        o>>Name;
        o>>History_score;
        o>>career[0];if(career[0])student.Read(o);
        o>>career[1];if(career[1])cooker.Read(o);
        o>>career[2];if(career[2])icecreamgirl.Read(o);
        o>>career[3];if(career[3])cleaner.Read(o);
        now_score=score_calculate();
        if(History_score<now_score)History_score=now_score;
        return;
    }
    void self_Read(){
        ifstream ifs;
        ifs.open(Root_place+"/"+Name+"total.txt");
        Read(ifs);
    }
    void Write(ofstream& o,int mode=0){
        o<<Name<<endl;
        o<<History_score<<endl;
        o<<career[0]<<endl;if(career[0])student.Write(o);
        o<<career[1]<<endl;if(career[1])cooker.Write(o);
        o<<career[2]<<endl;if(career[2])icecreamgirl.Write(o);
        o<<career[3]<<endl;if(career[3])cleaner.Write(o);
        return;
    }
    void self_Write(){
        ofstream ofs;
        ofs.open(Root_place+"/"+Name+"total.txt");
        Write(ofs);
    }
    void init(){
        student.init();
        cooker.init();
        icecreamgirl.init();
        cleaner.init();
        now_score=0;
        self_Write();
        self_Read();
    }
};

class archive_system{
public:
    vector<string>Q;
    int now_page=1;
    string Root_place="1";
    void Read_all_archive(string place){
        Root_place=place;
        Q.clear();
        now_page=1;
        ifstream ifs;
        ifs.open(place+"/total.txt");
        if(ifs.is_open()){
            string tmp;
            while(ifs>>tmp){
                Q.push_back(tmp);
            }
        }
        ifs.close();
    }
    vector<string> Getpage(int& page_num,int num_per_page){
        if(page_num<=0)page_num=1;
        if(Q.size()==0)return vector<string>();
        int m=Q.size()/num_per_page;
        if(Q.size()%num_per_page!=0)m++;
        if(page_num>m)page_num=m;
        int s=page_num*num_per_page;
        if(s>Q.size())s=Q.size();
        return vector<string>(Q.begin()+(page_num-1)*num_per_page,Q.begin()+s);
    }
    bool find_name(string A){
        for(int i=Q.size()-1;i>=0;i--){
            if(Q[i]==A)return true;
        }
        return false;
    }
    archive Get_name(string A){//please be sure that the name exsits
        archive S;
        ifstream ifs;
        ifs.open(Root_place+"/"+A+"total.txt");
        S.Read(ifs);S.Root_place=Root_place;
        ifs.close();
        return S;
    }
    void Save_name(archive& S,string A){
        ofstream ofs;
        ofs.open(Root_place+"/"+A+"total.txt");
        S.Write(ofs);
        ofs.close();
        return;
    }
    void Build_new(string A){
        ofstream ofs;
        ofs.open(Root_place+"/total.txt",ios::app);
        ofs<<A<<endl;
        Q.push_back(A);
        filesystem::create_directories(Root_place+"/"+A);
        ofs.close();
        ofs.open(Root_place+"/"+A+"/total.txt");
        archive S;S.Name=A;S.Root_place=Root_place;
        S.init();
        ofs.close();
    }
};

extern archive Now_player;

#endif // ARCHIVECLASS_H
