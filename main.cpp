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
    if(argc==1){
        Game thegame{};
        std::string input, filename;
        int x,y;
        do{
            std::cout<<"What would you like to do? Possible commands: setmap, puthero, putmonster, run, exit\n";
            std::cin >> input;
            if(input == "setmap")
            {
                std::cout<<"Add the file path for the map!\n";
                std::cin >> filename;
                try
                {
                    if (!std::filesystem::exists(filename)) bad_exit(2);
                    thegame.setMap(Map{filename});
                    std::cout<<"The selected map: "<<std::endl;
                    thegame.printMap();
                }
                catch(const Game::AlreadyHasUnitsException& e) { bad_exit(6);}
                catch(const Game::GameAlreadyStartedException& e) {bad_exit(7);}
            }
            if(input == "puthero")
            {
                std::cout<<"Add the hero file path and coordinates with a whitespace character separated (eg: filename x y)!\n";
                std::cin >> filename >> x >> y;
                try
                {
                    if (!std::filesystem::exists(filename)) bad_exit(2);
                    if(std::cin.good()) bad_exit(-1);
                    thegame.putHero(Hero{Hero::parse(filename)},x,y);
                }
                catch(const Game::GameAlreadyStartedException& e){bad_exit(7);}
                catch(const Game::OccupiedException& e){bad_exit(8);}
                catch(const Map::WrongIndexException& e){bad_exit(9);}
            }
            if(input == "putmonster")
            {
                std::cout<<"Add the monster file path and coordinates with a whitespace character separated (eg: filename x y)!\n";
                std::cin >> filename >> x >> y;
                try
                {
                    if (!std::filesystem::exists(filename)) bad_exit(2);
                    if(!std::cin.good()) bad_exit(-1);
                    thegame.putMonster(Monster{Monster::parse(filename)},x,y);
                }
                catch(const Game::OccupiedException& e){bad_exit(8);}
                catch(const Map::WrongIndexException& e){bad_exit(9);}
            }
            if("run" == input){
                try
                {
                    thegame.run();
                }
                catch(const Game::NotInitializedException& e) {bad_exit(5);}
                std::cout<<"Would you like to play another round? Note: you have to set a new Hero for a new game. (Y/N)";
                std::cin >> input;
                if(input == "N")
                    input = "exit";
            }
        }while(input != "exit");
    }

    else if (argc == 2){
        if (!std::filesystem::exists(argv[1])) bad_exit(2);
        std::string hero_file;
        std::list<std::string> monster_files;
        int x,y;
        std::string mapFile;
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

            
        if (!std::filesystem::exists(mapFile)) bad_exit(2);
        std::cout<<"Add the file path for the map!\n";
        std::cin >> mapFile;
        Game thegame{mapFile};
        std::cout<<"The selected map: "<<std::endl;
        thegame.printMap();
        std::cout <<"Add the coordinates for the Hero("<<hero_file<<") (x,y): ";
        std::cin >> x >> y;
        try
        {
            if(!std::cin.good()) bad_exit(-1);
            thegame.putHero(Hero::parse(hero_file),x,y);
        }
        catch(const Game::GameAlreadyStartedException& e){bad_exit(7);}
        catch(const Game::OccupiedException& e){bad_exit(8);}
        catch(const Map::WrongIndexException& e){bad_exit(9);}

        for (const auto& monster_file : monster_files){
            std::cout<<"Add the coordinates for Monster("<<monster_file<<") (x, y): ";
            std::cin >> x >> y;
            try{
                if(!std::cin.good()) bad_exit(-1);
                    thegame.putMonster(Monster::parse(monster_file),x,y);
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
    else bad_exit(1);
    
    return 0;
}
