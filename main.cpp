#include <map>
#include <string>
#include <filesystem>
#include <fstream>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
#include "TextRenderer.h"
#include "SVGRenderer.h"
 
const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided file is not accessible." },
    { 3 , "Game was not initialized properly."},
    { 4 , "JSON parsing error." },
    { 5 , "Game already has units."},
    { 6 , "Game already has a hero."},
    { 7 , "Game already started."},
    { 8 , "Coordinate occupied."},
    { 9 , "Wrong index."}
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
        
        try
        {
            PreparedGame game(argv[1]);
            std::ofstream stream = std::ofstream("log.txt");
            game.registerRenderer(new ObserverTextRenderer(stream));
            game.registerRenderer(new HeroTextRenderer()); 
            game.registerRenderer(new ObserverTextRenderer());
            game.registerRenderer(new ObserverSVGRenderer("observerOutput.svg"));
            game.registerRenderer(new CharacterSVGRenderer("characterOutput.svg"));
            game.run();
        }
        catch(const Game::NotInitializedException& e) {bad_exit(3);}
        catch(const JSON::ParseException& e) {bad_exit(4);}
        catch(const Game::AlreadyHasUnitsException& e) {bad_exit(5);}
        catch(const Game::AlreadyHasHeroException& e) {bad_exit(6);}
        catch(const Game::GameAlreadyStartedException& e) {bad_exit(7);}
        catch(const Game::OccupiedException& e) {bad_exit(8);}
        catch(const Map::WrongIndexException& e) {bad_exit(9);}
    }
    return 0;
}
