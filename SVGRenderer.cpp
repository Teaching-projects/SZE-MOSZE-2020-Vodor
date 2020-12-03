#include "SVGRenderer.h"

void ObserverSVGRenderer::render(const Game& g) const{
    Map map = g.getMap();
    b_Hero hero = g.getHero();
    MonsterCoords monster = g.getMonsterCoords();
    int maxWidth = map.getMaxLength();


}