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

    b_stream<<TOP_LEFT;
    for (int i = west; i < east; i++)
        b_stream<<HORIZONTAL;
    b_stream<<TOP_RIGHT<<std::endl;

    for (int y = north; y < south; y++){
        b_stream<<VERTICAL;
        for (int x = west; x < ((gameMap.getRowWidth(y) < east) ? gameMap.getRowWidth(y) : east) ; x++){
                int countmonster = 0;
                for (auto &&monster : monsters)
                if (x == monster.first && y == monster.second)
                    countmonster++;
            if (gameMap.get(x,y) == Map::type::Wall) b_stream<<WALL;
            else if (hero.first == x && hero.second == y) b_stream<<HERO;
            else if (countmonster == 1) b_stream<<SINGLEMONSTER;
            else if (countmonster >= 2) b_stream<<MULTIPLEMONSTERS;
            else b_stream<<FREE;
        }
        if(gameMap.getRowWidth(y)<east)
            for (int i = 0; i < (east-gameMap.getRowWidth(y)); i++)
                b_stream<<FREE;
        b_stream<<VERTICAL<<std::endl;
    }

    b_stream<<BOTTOM_LEFT;
    for (int i = west; i < east; i++)
        b_stream<<HORIZONTAL;
    b_stream<<BOTTOM_RIGHT<<std::endl;
}

void ObserverTextRenderer::render(const Game& game) const{
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

    b_stream<<TOP_LEFT;
    for (int i = west; i < east; i++)
        b_stream<<HORIZONTAL;
    b_stream<<TOP_RIGHT<<std::endl;

    for (int y = north; y < south; y++){
        b_stream<<VERTICAL;
        for (int x = west; x < ((gameMap.getRowWidth(y) < east) ? gameMap.getRowWidth(y) : east) ; x++){
                int countmonster = 0;
                for (auto &&monster : monsters)
                if (x == monster.first && y == monster.second)
                    countmonster++;
            if (gameMap.get(x,y) == Map::type::Wall) b_stream<<WALL;
            else if (hero.first == x && hero.second == y) b_stream<<HERO;
            else if (countmonster == 1) b_stream<<SINGLEMONSTER;
            else if (countmonster >= 2) b_stream<<MULTIPLEMONSTERS;
            else b_stream<<FREE;
        }
        if(gameMap.getRowWidth(y)<east)
            for (int i = 0; i < (east-gameMap.getRowWidth(y)); i++)
                b_stream<<FREE;
        b_stream<<VERTICAL<<std::endl;
    }

    b_stream<<BOTTOM_LEFT;
    for (int i = west; i < east; i++)
        b_stream<<HORIZONTAL;
    b_stream<<BOTTOM_RIGHT<<std::endl;
}

