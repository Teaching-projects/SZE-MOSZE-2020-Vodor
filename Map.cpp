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
    if (y >= map.size() || y < 0 || x >= map[y].length() || x < 0) throw WrongIndexException("Given coordinate is out of range!");
    if(map[y][x] == ' ') return Map::type::Free;
    else return Map::type::Wall;
    
}