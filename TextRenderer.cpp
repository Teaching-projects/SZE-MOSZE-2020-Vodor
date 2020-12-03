#include "TextRenderer.h"

void HeroTextRenderer::render(const Game& game) const{
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

    b_Hero hero = game.getHero();
    std::list<MonsterCoords> monsters = game.getMonsters();
    Map gameMap = game.getMap();

    int west = (hero.x < hero.hero->getLightRadius()) ? 0 : hero.x-hero.hero->getLightRadius();
    int east = (gameMap.getMaxLength() > hero.x+hero.hero->getLightRadius()) ? hero.x+hero.hero->getLightRadius()+1 : gameMap.getMaxLength();
    int north = (hero.y < hero.hero->getLightRadius()) ? 0 : hero.y-hero.hero->getLightRadius();
    int south = (gameMap.getMapSize() > (hero.y+hero.hero->getLightRadius())) ? (hero.y+hero.hero->getLightRadius()+1) : gameMap.getMapSize();

    b_stream<<TOP_LEFT;
    for (int i = west; i < east; i++)
        b_stream<<HORIZONTAL;
    b_stream<<TOP_RIGHT<<std::endl;

    for (int y = north; y < south; y++){
        b_stream<<VERTICAL;
        for (int x = west; x < ((gameMap.getRowWidth(y) < east) ? gameMap.getRowWidth(y) : east) ; x++){
                int countmonster = 0;
                for (auto &&monster : monsters)
                if (x == monster.x && y == monster.y)
                    countmonster++;
            if (gameMap.get(x,y) == Map::type::Wall) b_stream<<WALL;
            else if (hero.x == x && hero.y == y) b_stream<<HERO;
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

    b_Hero hero = game.getHero();
    std::list<MonsterCoords> monsters = game.getMonsters();
    Map gameMap = game.getMap();

    b_stream<<TOP_LEFT;
    for (int i = 0; i < gameMap.getMaxLength(); i++)
        b_stream<<HORIZONTAL;
    b_stream<<TOP_RIGHT<<std::endl;

    for (int y = 0; y < gameMap.getMapSize(); y++){
        b_stream<<VERTICAL;
        for (int x = 0; x < gameMap.getRowWidth(y); x++){
                int countmonster = 0;
                for (auto &&monster : monsters)
                if (x == monster.x && y == monster.y)
                    countmonster++;
            if (gameMap.get(x,y) == Map::type::Wall) b_stream<<WALL;
            else if (hero.x == x && hero.y == y) b_stream<<HERO;
            else if (countmonster == 1) b_stream<<SINGLEMONSTER;
            else if (countmonster >= 2) b_stream<<MULTIPLEMONSTERS;
            else b_stream<<FREE;
        }
        if(gameMap.getRowWidth(y)<gameMap.getMaxLength())
            for (int i = 0; i < (gameMap.getMaxLength()-gameMap.getRowWidth(y)); i++)
                b_stream<<FREE;
        b_stream<<VERTICAL<<std::endl;
    }

    b_stream<<BOTTOM_LEFT;
    for (int i = 0; i < gameMap.getMaxLength(); i++)
        b_stream<<HORIZONTAL;
    b_stream<<BOTTOM_RIGHT<<std::endl;
}

