#include "TextRenderer.h"

void HeroTextRender::render(const Game& game) const{
    const std::string TOP_LEFT = "\u2554";
    const std::string TOP_RIGHT = "\u2557";
    const std::string BOTTOM_LEFT = "\u255A";
    const std::string BOTTOM_RIGHT = "\u255D";
    const std::string HORIZONTAL = "\u2550\u2550";
    const std::string VERTICAL =  "\u2551";
    const std::string FREE = "\u2591\u2591";
    const std::string WALL = "\u2588\u2588"; 
    const std::string SINGLEMONSTER = "M\u2591";
    const std::string MULTIPLEMONSTERS = "MM";
    const std::string HERO = "\u2523\u252B";

    std::pair<int,int> hero = game.getHeroCoords();
    int lightRadius = game.getHeroLightRadius();
    std::list<std::pair<int,int>> monsters = game.getMonsterCoords();
    Map gameMap = game.getMap();

    int west = (hero.first < lightRadius) ? 0 : hero.first-lightRadius;
    int east = (gameMap.getMaxLength() > hero.first+lightRadius) ? hero.first+lightRadius+1 : gameMap.getMaxLength();
    int north = (hero.second < lightRadius) ? 0 : hero.second-lightRadius;
    int south = (gameMap.getMapSize() > (hero.second+lightRadius)) ? (hero.second+lightRadius+1) : gameMap.getMapSize();

    std::cout<<TOP_LEFT;
    for (int i = west; i < east; i++)
        std::cout<<HORIZONTAL;
    std::cout<<TOP_RIGHT<<std::endl;

    for (int y = north; y < south; y++){
        std::cout<<VERTICAL;
        for (int x = west; x < ((gameMap.getRowWidth(y) < east) ? gameMap.getRowWidth(y) : east) ; x++){
                int countmonster = 0;
                for (auto &&monster : monsters)
                if (x == monster.first && y == monster.second)
                    countmonster++;
            if (gameMap.get(x,y) == Map::type::Wall) std::cout<<WALL;
            else if (hero.first == x && hero.second == y) std::cout<<HERO;
            else if (countmonster == 1) std::cout<<SINGLEMONSTER;
            else if (countmonster >= 2) std::cout<<MULTIPLEMONSTERS;
            else std::cout<<FREE;
        }
        if(gameMap.getRowWidth(y)<east)
            for (int i = 0; i < (east-gameMap.getRowWidth(y)); i++)
                std::cout<<FREE;
        std::cout<<VERTICAL<<std::endl;
    }

    std::cout<<BOTTOM_LEFT;
    for (int i = west; i < east; i++)
        std::cout<<HORIZONTAL;
    std::cout<<BOTTOM_RIGHT<<std::endl;
}