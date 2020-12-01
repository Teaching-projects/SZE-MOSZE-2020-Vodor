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
    if(map[y][x] == ' ') return Map::type::Free;
    else return Map::type::Wall;
    
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

std::pair<int,int> MarkedMap::getHeroPosition() const{
    for(int i=1; i < (int)map.size();i++){
        for (int j = 0; j < (int) map[i].length(); j++)
        {
            if(map[i][j] == 'H'){
                std::pair<int, int> heroposition(i,j);
                return heroposition;
            }  
        }
    }
};

std::vector<std::pair<int,int>> MarkedMap::getMonsterPositions(char c) const{
    std::vector<std::pair<int,int>> MonsterPosition;
    for(int i=1; i < (int)map.size();i++){
        for (int j = 0; j < (int) map[i].length(); j++)
        {
            if(map[i][j] == c){
                std::pair<int, int> monster(i,j);
                MonsterPosition.push_back(monster);
            }  
        }
    }
    return MonsterPosition;
};