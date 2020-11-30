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
    { 2 , "The provided file is not accessible." },
    { 3 , "The provided file is invalid." },
    { 4 , "JSON parsing error." },
    { 5 , "Game was not initialized properly."},
    { 6 , "Game already has units."},
    { 7 , "Game already started."},
    { 8 , "Coordinate occupied."},
    { 9 , "Wrong index."}
};
 
void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error.")
        << std::endl;
    exit(exitcode);
}
 
int main(int argc, char** argv){
    if (argc!=2) bad_exit(1);
    else{
        if (!std::filesystem::exists(argv[1])) bad_exit(2);
        int herox, heroy, monsterx, monstery, spacePos;
        std::string hero_file;
        std::string mapFile;
        std::list<std::string> monster_files;
        std::list<std::string> monster_positions;
        try {
            JSON scenario = JSON::parseFromFile(argv[1]); 
            if (!(scenario.count("hero")&&scenario.count("monsters"))&&scenario.count("hero_position")&&scenario.count("positions")&&scenario.count("map")) bad_exit(3);
            else {
                hero_file=scenario.get<std::string>("hero");
                mapFile = scenario.get<std::string>("map");
                std::string hero_position = scenario.get<std::string>("hero_position");
                spacePos = hero_position.find(" ");
                herox = std::stoi(hero_position.substr(0,spacePos));
                heroy = std::stoi(hero_position.substr(spacePos));
                JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
                JSON::list monster_positions_list = scenario.get<JSON::list>("positions");
                for(auto monster_file : monster_file_list)
                    monster_files.push_back(std::get<std::string>(monster_file));
                for (auto monster_position : monster_positions_list)
                    monster_positions.push_back(std::get<std::string>(monster_position));
            }
        } catch (const JSON::ParseException& e) {bad_exit(4);}

        if (!std::filesystem::exists(mapFile)) bad_exit(2);
        Game thegame{mapFile};
        try
        {
            thegame.putHero(Hero::parse(hero_file),herox,heroy);
        }
        catch(const Game::GameAlreadyStartedException& e){bad_exit(7);}
        catch(const Game::OccupiedException& e){bad_exit(8);}
        catch(const Map::WrongIndexException& e){bad_exit(9);}
        
        while (!monster_files.empty())
        {
            try{
                monsterx = std::stoi(monster_positions.front());
                monster_positions.pop_front();
                monstery = std::stoi(monster_positions.front());
                thegame.putMonster(Monster::parse(monster_files.front()),monsterx,monstery);
                monster_files.pop_front();
                monster_positions.pop_front();
            }
            catch(const Game::OccupiedException& e){bad_exit(8);}
            catch(const Map::WrongIndexException& e){bad_exit(9);}
        }
        try
        {
            thegame.run();
        }
        catch(const Game::NotInitializedException& e) {bad_exit(5);}
    }    
    return 0;
}
