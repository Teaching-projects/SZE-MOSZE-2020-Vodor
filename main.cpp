#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>
 
#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
 
const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." }
};
 
void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}
 
int main(int argc, char** argv){
    if(argc==1){
    Game thegame{};
    std::string order, filename;
    int x,y;
    do{
        std::cout<<"Pls tell order (setmap, puthero, putmonster, run, exit)!\n";
        std::cin >> order;
        if(order == "setmap")
        {
            std::cout<<"Pls add map filename!\n";
            std::cin >> filename;
            try
            {
                thegame.setMap(Map{filename});
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        if(order == "puthero")
        {
            std::cout<<"Pls add Hero filename and coordinate (filename x y)!\n";
            std::cin >> filename >> x >> y;
            try
            {
                thegame.putHero(Hero{Hero::parse(filename)},x,y);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        if(order == "putmonster")
        {
            std::cout<<"Pls add Monster filename and coordinate (filename x y)!\n";
            std::cin >> filename >> x >> y;
            try
            {
                thegame.putMonster(Monster{Monster::parse(filename)},x,y);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        if("run" == order){
            thegame.run();
        }
    }while(order != "exit");
    }
    else if (argc == 2){
    if (!std::filesystem::exists(argv[1])) bad_exit(2);
    std::string hero_file;
    std::list<std::string> monster_files;
    try {
        JSON scenario = JSON::parseFromFile(argv[1]); 
        if (!(scenario.count("hero")&&scenario.count("monsters"))) bad_exit(3);
        else {
            hero_file=scenario.get<std::string>("hero");
            JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
            for(auto monster_file : monster_file_list)
                monster_files.push_back(std::get<std::string>(monster_file));
        }
    } catch (const JSON::ParseException& e) {bad_exit(4);}
 
    try { 
        int x,y;
        std::string str;
        std::cin >> str;
        Game thegame{str};
        for (const auto& monster_file : monster_files){
            std::cin >> x >> y;
            thegame.putMonster(Monster::parse(monster_file),x,y);
        }
        std::cin >> x >> y;
        thegame.putHero(Hero::parse(hero_file),x,y);
        thegame.run();
    } catch (const JSON::ParseException& e) {bad_exit(4);}
    }
    else  bad_exit(1);
    
    return 0;
}
