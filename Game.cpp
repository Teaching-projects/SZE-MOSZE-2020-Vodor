#include "Game.h"

bool Game::printMonsters(int x, int y){
    int count = 0;
    for (auto &&i : monsters)
        if (x == i.x && y == i.y)
            count++;
    
    if (count == 1)
    {
        std::cout<<SINGLEMONSTER;
        return true;
    } 
    else if(count >= 2){
        std::cout<<MULTIPLEMONSTERS;
        return true;
    }
    return false;
}

void Game::setMap(Map map){  
    if(!gamestarted)     
        if(!heroready && monsters.empty()){
            gameMap = map;
            mapsetready = true;
        }
        else 
            throw AlreadyHasUnitsException("Game already has Units.");
    else throw GameAlreadyStartedException("Game already started!");
}

void Game::putHero(Hero hero, int x, int y){
    if(!gamestarted)
        if(heroready) throw AlreadyHasHeroException("Game already has Hero.");
        else
        {
            if(mapsetready){
                if(gameMap.get(x,y) == Map::type::Free){
                    this->hero.hero = new Hero(hero);
                    this->hero.x = x;
                    this->hero.y = y;
                    heroready = true;
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
    if (direction == "north") return (gameMap.get(hero.x, hero.y-1) == Map::type::Free ? true : false); 
    else if (direction == "east") return (gameMap.get(hero.x+1, hero.y) == Map::type::Free ? true : false);
    else if (direction == "west") return (gameMap.get(hero.x-1, hero.y) == Map::type::Free ? true : false);
    else if (direction == "south") return (gameMap.get(hero.x, hero.y+1) == Map::type::Free ? true : false);
    else return false;
}

void Game::moveHero(const std::string& direction){
    if (direction == "north") hero.y--;
    if (direction == "east") hero.x++;
    if (direction == "west") hero.x--;
    if (direction == "south") hero.y++;
}

void Game::run(){
    if (heroready && !monsters.empty() && mapsetready && !gamestarted)
    {
        std::string moveTo ="";
        gamestarted = true;
        std::list<std::string> expectedInputs = {"north", "east", "west", "south"};
        while ((hero.hero->isAlive() && !monsters.empty()))
        {
            std::list<MonsterCoords>::iterator monster = monsters.begin();
            while (monster != monsters.end())
            {
                if(hero.hero->isAlive())
                    if (hero.x == monster->x && hero.y == monster->y){
                        std::cout 
                            << hero.hero->getName() << "(" << hero.hero->getLevel()<<")"
                            << " vs "
                            << monster->monster.getName()
                            <<std::endl;
                        hero.hero->fightTilDeath(monster->monster);        
                    }
                if (!monster->monster.isAlive()) monster = monsters.erase(monster); 
                else monster++;
            }
            if(hero.hero->isAlive() && !monsters.empty()){
            printMap();
            do
            {
                std::cout<<"Enter the direction you would like to move (north, east, west, south): ";
                std::cin >> moveTo;
            } while (std::find(expectedInputs.begin(), expectedInputs.end(), moveTo) == expectedInputs.end() || !checkIfMoveIsValid(moveTo));
            moveHero(moveTo);
            }
        }
        if (hero.hero->isAlive()){
            std::cout<<std::endl<<hero.hero->getName()<<" cleared the map."<<std::endl;
            std::cout << hero.hero->getName() << ": LVL" << hero.hero->getLevel() << std::endl
                << "   HP: "<<hero.hero->getHealthPoints()<<"/"<<hero.hero->getMaxHealthPoints()<<std::endl
                << "  DMG: "<<hero.hero->getDamage()<<std::endl
                << "  ACD: "<<hero.hero->getAttackCoolDown()<<std::endl
                ;

        }
        else{
            std::cout<<"The hero died"<<std::endl;
            std::cout << hero.hero->getName() << ": LVL" << hero.hero->getLevel() << std::endl
                << "   HP: "<<hero.hero->getHealthPoints()<<"/"<<hero.hero->getMaxHealthPoints()<<std::endl
                << "  DMG: "<<hero.hero->getDamage()<<std::endl
                << "  ACD: "<<hero.hero->getAttackCoolDown()<<std::endl
                ;
            heroready = false;
        }
        gamestarted = false;
    }
    else throw NotInitializedException("Game was not initialized properly.");
    
}

void Game::printMap(){
    int maxWidth = gameMap.getMaxLength();
    std::cout<<TOP_LEFT;

    for (int i = 0; i < maxWidth; i++)
        std::cout<<HORIZONTAL;

    std::cout<<TOP_RIGHT<<std::endl;

    for (int y = 0; y < gameMap.getMapSize(); y++){
        std::cout<<VERTICAL;
        for (int x = 0; x < gameMap.getRowWidth(y); x++){
            if (gameMap.get(x,y) == Map::type::Wall) std::cout<<WALL;
            else if (hero.x == x && hero.y == y) std::cout<<HERO;
            else if (printMonsters(x,y));
            else std::cout<<FREE;
        }
        if(gameMap.getRowWidth(y)<maxWidth)
            for (int i = 0; i < (maxWidth-gameMap.getRowWidth(y)); i++)
                std::cout<<WALL;
        std::cout<<VERTICAL<<std::endl;
    }
    std::cout<<BOTTOM_LEFT;

    for (int i = 0; i < maxWidth; i++)
        std::cout<<HORIZONTAL;

    std::cout<<BOTTOM_RIGHT<<std::endl;
}

PreparedGame::PreparedGame(const std::string& filename){
    bool okay = true;
    std::vector<std::string> expectedKeys= {"map", "hero", "monster-1", "monster-2", "monster-3"};
    JSON map = JSON::parseFromFile(filename);
    for (auto &&key : expectedKeys)
        if (!map.count(key))
            okay = false;
   
    if (okay){
        //setMap(MarkedMap(map.get<std::string>("map")));
        //TODO: ??? heroPosition = MarkedMap::getHeroPosition();
        //TODO: ??? monster1Positions = MarkedMap::getMonsterPositions('1');
        //TODO: ??? monster2Positions = MarkedMap::getMonsterPositions('2');
        //TODO: ??? monster3Positions = MarkedMap::getMonsterPositions('3');
        //putHero(map.get<std::string>("hero"),heroPosition[???], heroPosition[??]);
        //amig van monster1 position
        //putMonster(map.get<std::string>("monster-1"), monster1Positions[???], monster1Positions[???]);
        //amig 2..3.. van 
        mapsetready = true;
        heroready = true;
        gamestarted = false;
    }
    else throw JSON::ParseException("Missing keys.");
}