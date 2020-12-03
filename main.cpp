#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
#include "TextRenderer.h"
#include "SVGRenderer.h"
#include "Renderer.h"
 
const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided file is not accessible." },
    { 3 , "Game was not initialized properly."},
};
 
void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error.")
        << std::endl;
    exit(exitcode);
}
 
int main(int argc, char** argv){
    if (argc!=2) bad_exit(1);
    else{
        if (!std::filesystem::exists(argv[1])) bad_exit(2);
        PreparedGame game(argv[1]);
        std::ofstream stream = std::ofstream("log.txt");
        game.registerRenderer(new ObserverTextRenderer(stream));
        game.registerRenderer(new HeroTextRenderer()); 
        game.registerRenderer(new ObserverTextRenderer());
        game.registerRenderer(new ObserverSVGRenderer("observerOutput.svg"));
        game.registerRenderer(new CharacterSVGRenderer("characterOutput.svg"));
        try
        {
            game.run();
        }
        catch(const Game::NotInitializedException& e) {bad_exit(3);}
    }
    return 0;
}
