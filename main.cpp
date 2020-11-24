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
        if("run" == order)
            thegame.run();

    }while(order != "exit");
    return 0;
    



    /*
    if (argc != 2) bad_exit(1);
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
        Hero hero{Hero::parse(hero_file)};
        std::list<Monster> monsters;
        for (const auto& monster_file : monster_files)
            monsters.push_back(Monster::parse(monster_file));        
 
        while (hero.isAlive() && !monsters.empty()) {
            std::cout 
                << hero.getName() << "(" << hero.getLevel()<<")"
                << " vs "
                << monsters.front().getName()
                <<std::endl;
            hero.fightTilDeath(monsters.front());
            if (!monsters.front().isAlive()) monsters.pop_front();
        }
        std::cout << (hero.isAlive() ? "The hero won." : "The hero died.") << std::endl;
        std::cout << hero.getName() << ": LVL" << hero.getLevel() << std::endl
                  << "   HP: "<<hero.getHealthPoints()<<"/"<<hero.getMaxHealthPoints()<<std::endl
                  << "  DMG: "<<hero.getDamage()<<std::endl
                  << "  ACD: "<<hero.getAttackCoolDown()<<std::endl
                  ;
    } catch (const JSON::ParseException& e) {bad_exit(4);}
    return 0;*/
}
