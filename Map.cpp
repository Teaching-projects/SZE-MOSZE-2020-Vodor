#include "Map.h"
#include <fstream>

Map::Map(const std::string& filename){
    std::ifstream mapFile(filename);
    if(mapFile.good()) 
    {
        std::string line;
        while (getline(mapFile, line))
            map.push_back(line);
    }
    else throw std::runtime_error("File does not exist: " + filename);
    mapFile.close();
}

Map::type Map::get(unsigned int x, unsigned int y) const{
    if (y >= map.size() || x >= map[y].length()) throw WrongIndexException("Given coordinate is out of range!");
    if(map[y][x] == '#') return Map::type::Wall;
    else return Map::type::Free;
    
}

int Map::getMaxLength(){
    int maxLength = 0;
    for (int i = 0; i < (int) map.size(); i++)
        if ((int) map[i].length()>maxLength)
            maxLength = (int) map[i].length();
    return maxLength;
}
MarkedMap::MarkedMap(const std::string& filename){
    std::ifstream mapFile(filename);
    if(mapFile.good()) 
    {
        std::string line;
        while (getline(mapFile, line))
            map.push_back(line);
    }
    else throw std::runtime_error("File does not exist: " + filename);
    mapFile.close();
}

std::pair<int,int> MarkedMap::getHeroPosition() const
{
    std::pair<int, int> heroposition;
    for(int i=0; i < (int)map.size();i++)
        for (int j = 0; j < (int) map[i].length(); j++)
            if(map[i][j] == 'H')
                heroposition = std::make_pair(j,i);

    return heroposition;
}

std::vector<std::pair<int,int>> MarkedMap::getMonsterPositions(char c) const{
    std::vector<std::pair<int,int>> monsterPositions;
    for(int i=0; i < (int)map.size();i++)
        for (int j = 0; j < (int) map[i].length(); j++)
            if(map[i][j] == c)
                monsterPositions.push_back(std::make_pair(j,i));
    
    if(monsterPositions.empty()) throw std::runtime_error(c+ " monster is not on the map.");
    else return monsterPositions;
}