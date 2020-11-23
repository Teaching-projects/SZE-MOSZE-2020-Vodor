#include "Game.h"

void Game::printMonsters(int x, int y){
    int count = 0;
    for (auto &&i : monsters)
        if (x == i.x && y == i.y)
            count++;
    
    if (count == 1) std::cout<<"M░";
    else if(count == 2) std::cout<<"MM";
}

void Game::setMap(Map map){  
    if(!gamestarted)     
        if(this->hero == nullptr && monsters.empty() && !gamestarted){
            gameMap = map;
            mapsetready = true;
        }
        else 
            throw AlreadyHasUnitsException("Game already has Units.");
    else throw GameAlreadyStartedException("Game already started!");
}

void Game::putHero(Hero hero, int x, int y){
    if(!gamestarted)
        if(this->hero != nullptr && !gamestarted) throw AlreadyHasHeroException("Game already has Hero.");
        else
        {
            if(mapsetready){
                if(gameMap.get(x,y) == Map::type::Free){
                    this->hero = new Hero(hero);
                    heroX = x;
                    heroY = y;
                }
                else throw OccupiedException("Coordinate occupied");
            }
            else throw Map::WrongIndexException("Map not set");
        }
    else throw GameAlreadyStartedException("Game already started!");
}

void Game::putMonster(Monster monster, int x, int y){
    if(mapsetready){ 
        if(gameMap.get(x,y) == Map::type::Free){
            MonsterCoords onemonster = {monster,x,y};
            monsters.push_back(onemonster);
        }
        else
            throw OccupiedException("Coordinate occupied");
    }
    else 
        throw Map::WrongIndexException("Map not set");
}

bool Game::checkIfMoveIsValid(const std::string& direction){
    if (direction == "north") return (gameMap.get(heroX, heroY-1) == Map::type::Free ? true : false); 
    else if (direction == "east") return (gameMap.get(heroX-1, heroY) == Map::type::Free ? true : false);
    else if (direction == "west") return (gameMap.get(heroX+1, heroY) == Map::type::Free ? true : false);
    else if (direction == "south") return (gameMap.get(heroX, heroY+1) == Map::type::Free ? true : false);
    else return false;
}

void Game::moveHero(const std::string& direction){
    if (direction == "north") heroY--;
    if (direction == "east") heroX--;
    if (direction == "west") heroX++;
    if (direction == "south") heroY++;
}

void Game::run(){
    if (hero == nullptr && !monsters.empty() && mapsetready)
    {
        std::string moveTo ="";
        gamestarted = true;
        std::list<std::string> expectedInputs = {"north", "east", "west", "south"};
        while (!monsters.empty() || hero->isAlive())
        {
            printMap();
            do
            {
                std::cout<<"Enter the direction you would like to move (north, east, west, south): ";
                getline(std::cin, moveTo);
            } while (std::find(expectedInputs.begin(), expectedInputs.end(), moveTo) == expectedInputs.end() || !checkIfMoveIsValid(moveTo));

            moveHero(moveTo);
            if (heroX == monsters.front().x && heroY == monsters.front().y){
                std::cout 
                    << hero->getName() << "(" << hero->getLevel()<<")"
                    << " vs "
                    << monsters.front().monster.getName()
                    <<std::endl;
                hero->fightTilDeath(monsters.back().monster);
                if (!monsters.front().monster.isAlive())
                    monsters.pop_front();                
            }
            
        }
        if (hero->isAlive())
            std::cout<<std::endl<<hero->getName()<<" cleared the map."<<std::endl;
        else std::cout<<"The hero died";
        std::cout << hero->getName() << ": LVL" << hero->getLevel() << std::endl
                  << "   HP: "<<hero->getHealthPoints()<<"/"<<hero->getMaxHealthPoints()<<std::endl
                  << "  DMG: "<<hero->getDamage()<<std::endl
                  << "  ACD: "<<hero->getAttackCoolDown()<<std::endl
                  ;
    }
    else throw NotInitializedException("Game was not initialized properly.");
    
}

void Game::printMap(){
    int maxWidth = gameMap.getMaxLength();
    std::cout<<"╔";

    for (int i = 0; i < maxWidth; i++)
        std::cout<<"═";

    std::cout<<"╗"<<std::endl;

    for (int y = 0; y < gameMap.getMapSize(); y++){
        std::cout<<"║";
        for (int x = 0; x < gameMap.getRowWidth(y); x++){
            if (gameMap.get(x, y) == Map::type::Free) std::cout<<"░░";
            else if (gameMap.get(x,y) == Map::type::Wall) std::cout<<"██";
            else if (heroX == x && heroY == y) std::cout<<"┣┫";
            else printMonsters(x,y);
        }
        if(gameMap.getRowWidth(y)<maxWidth)
            for (int i = 0; i < (maxWidth-gameMap.getRowWidth(y)); i++)
                std::cout<<"██";
        std::cout<<"║"<<std::endl;
    }
    std::cout<<"╚";

    for (int i = 0; i < maxWidth; i++)
        std::cout<<"══";

    std::cout<<"╝"<<std::endl;
}