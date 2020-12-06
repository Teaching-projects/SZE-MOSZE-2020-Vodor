#include "SVGRenderer.h"
#include <filesystem>
#include <fstream>
#include <list>
#include <map>

bool printMonsters(int x, int y, std::list<MonsterCoords> monsters, std::ostream& stream, int xSvg, int ySvg){
    std::string monsterTexture;
    for (auto &&monster : monsters)
        if (x == monster.x && y == monster.y){
            monsterTexture = monster.monster.getTexture();
            stream<< "\t<image href=\""<<monsterTexture<<"\" width=\"10\" height=\"10\" x=\""<<xSvg<<"\" y=\""<<ySvg<<"\"/>\n";
            return true;
        }
    return false;
}

void ObserverSVGRenderer::render(const Game& g) const{
    int xSvg=0;
    int ySvg=0;
    Map map = g.getMap();
    b_Hero hero = g.getHero();
    std::list<MonsterCoords> monsters = g.getMonsters();
    int maxWidth = map.getMaxLength();
    std::ofstream svg(this->b_out);
    std::map<std::string, std::string> textures = g.getTextures();
    std::string WALL = textures["wall_texture"];
    std::string FREE = textures["free_texture"];
    std::string HERO = hero.hero->getTexture();

    if (!std::filesystem::exists(WALL)) WALL = "textures/placeholder.svg";
    if (!std::filesystem::exists(FREE)) FREE = "textures/placeholder.svg";

    int svgWidth = map.getMaxLength()*10;
    int svgHeight = map.getMapSize()*10;

    svg<<"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\""<<svgWidth<<"\" height=\""<<svgHeight<<"\">\n";
    for (int y = 0; y < map.getMapSize(); y++)
    {
        xSvg=0;
        for (int x = 0; x < map.getRowWidth(y); x++)
        {
            if(map.get(x,y) == Map::type::Wall) svg<<"\t<image href=\""<<WALL<<"\" width=\"10\" height=\"10\" x=\""<<xSvg<<"\" y=\""<<ySvg<<"\"/>\n";
            else if (hero.x == x && hero.y == y) svg<<"\t<image href=\""<<HERO<<"\" width=\"10\" height=\"10\" x=\""<<xSvg<<"\" y=\""<<ySvg<<"\"/>\n";
            else if (printMonsters(x,y, monsters, svg, xSvg, ySvg));
            else svg<<"\t<image href=\""<<FREE<<"\" width=\"10\" height=\"10\" x=\""<<xSvg<<"\" y=\""<<ySvg<<"\"/>\n";
            xSvg+=10;
        }
        if (map.getRowWidth(y)<maxWidth)
            for (int i = 0; i < (maxWidth-map.getRowWidth(y)); i++){
                svg<<"\t<image href=\""<<WALL<<"\" width=\"10\" height=\"10\" x=\""<<xSvg<<"\" y=\""<<ySvg<<"\"/>\n";
                xSvg+=10; 
            }
        ySvg+=10;
    }
    svg<<"</svg>";
    svg.close();
}

void CharacterSVGRenderer::render(const Game& g) const{
    int xSvg=0;
    int ySvg=0;
    Map map = g.getMap();
    b_Hero hero = g.getHero();
    std::list<MonsterCoords> monsters = g.getMonsters();
    std::ofstream svg(this->b_out);
    std::map<std::string, std::string> textures = g.getTextures();
    std::string WALL = textures["wall_texture"];
    std::string FREE = textures["free_texture"];
    std::string HERO = hero.hero->getTexture();

    if (!std::filesystem::exists(WALL)) WALL = "textures/placeholder.svg";
    if (!std::filesystem::exists(FREE)) FREE = "textures/placeholder.svg";

    int west = (hero.x < hero.hero->getLightRadius()) ? 0 : hero.x-hero.hero->getLightRadius();
    int east = (map.getMaxLength() > hero.x+hero.hero->getLightRadius()) ? hero.x+hero.hero->getLightRadius()+1 : map.getMaxLength();
    int north = (hero.y < hero.hero->getLightRadius()) ? 0 : hero.y-hero.hero->getLightRadius();
    int south = (map.getMapSize() > (hero.y+hero.hero->getLightRadius())) ? (hero.y+hero.hero->getLightRadius()+1) : map.getMapSize();
    int svgWidth = map.getMaxLength()*10;
    int svgHeight = map.getMapSize()*10;
    svg<<"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\""<<svgWidth<<"\" height=\""<<svgHeight<<"\">\n";
    for (int y = north; y < south; y++)
    {
        xSvg=0;
        for (int x = west; x < ((map.getRowWidth(y) < east) ? map.getRowWidth(y) : east) ; x++){
            if(map.get(x,y) == Map::type::Wall) svg<<"\t<image href=\""<<WALL<<"\" width=\"10\" height=\"10\" x=\""<<xSvg<<"\" y=\""<<ySvg<<"\"/>\n";
            else if (hero.x == x && hero.y == y) svg<<"\t<image href=\""<<HERO<<"\" width=\"10\" height=\"10\" x=\""<<xSvg<<"\" y=\""<<ySvg<<"\"/>\n";
            else if (printMonsters(x,y, monsters, svg, xSvg, ySvg));
            else svg<<"\t<image href=\""<<FREE<<"\" width=\"10\" height=\"10\" x=\""<<xSvg<<"\" y=\""<<ySvg<<"\"/>\n";
            xSvg+=10;
        }
        ySvg+=10;
    }
    svg<<"</svg>";
    svg.close();
}