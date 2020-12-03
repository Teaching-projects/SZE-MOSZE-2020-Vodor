#include "SVGRenderer.h"

void ObserverSVGRenderer::render(const Game& g) const{
    Map map = g.getMap();
    std::pair<int, int> heroPosition = g.getHeroCoords();
    std::list<std::pair<int,int>> monsterPositions = g.getMonsterCoords();
    int maxWidth = map.getMaxLength();
    

}