#include "../Hero.h"
#include "../JSON.h"
#include "../Monster.h"
#include "../Unit.h"
#include "../Map.h"
#include "../Damage.h"
#include "../Game.h"
#include <gtest/gtest.h>
#include <string>
#include <list>
#include <fstream>


TEST(parserTest, test_iostream){                       
    std::ifstream jsonFile;
    jsonFile.open("units/unit1.json");
    JSON testJSON = JSON::parseJson(jsonFile);
    jsonFile.close();
    ASSERT_EQ(testJSON.get<std::string>("name"),"Hunkrow");
    ASSERT_EQ(testJSON.get<int>("base_health_points"),200);
    ASSERT_EQ(testJSON.get<int>("damage"),11);
}

TEST(parserTest, test_filename){
    std::string fname = "units/unit5.json";
    JSON testJSON = JSON::parseFromFile(fname);
    ASSERT_EQ(testJSON.get<std::string>("name"),"Agent 5.");
    ASSERT_EQ(testJSON.get<int>("base_health_points"),55);
    ASSERT_EQ(testJSON.get<int>("damage"),5);
}

TEST(parserTest, test_string){     
    std::string fname = "units/unit3.json";
    std::ifstream jsonFile;
    jsonFile.open(fname);
    std::string line;
    std::string jsonToString = "";

    while(getline(jsonFile,line))
        jsonToString += line;

    jsonFile.close();
    JSON testJSON = JSON::parseFromString(jsonToString);
    ASSERT_EQ(testJSON.get<std::string>("name"),"Maytcreme");
    ASSERT_EQ(testJSON.get<int>("base_health_points"),300);
    ASSERT_EQ(testJSON.get<int>("damage"),5);
}

TEST(unittests, good_battle_end){
    Hero hero = Hero::parse("units/unit1.json");
    Monster monster = Monster::parse("units/Fallen.json");
    hero.fightTilDeath(monster);
    ASSERT_EQ(hero.isAlive(),1);
}

TEST(unittests,good_levelup){
    Hero hero = Hero::parse("units/unit1.json");
    Monster monster = Monster::parse("units/Zombie.json");
    hero.fightTilDeath(monster);
    ASSERT_EQ(hero.getLevel(),3);   
}

TEST(unittests, name_check){
    Hero hero = Hero::parse("units/unit1.json");
    ASSERT_EQ(hero.getName(),"Hunkrow");
}

TEST(unittests, hp_check){
    Hero hero = Hero::parse("units/unit1.json");
    ASSERT_EQ(hero.getHealthPoints(),200);
}

TEST(unittests, parsunit_test){
    ASSERT_NO_THROW(JSON::parseFromFile("units/unit1.json"));
}

TEST(unittests, whitespaceTest){
    JSON testJSON = JSON::parseFromFile("test/muchWhitespace.json");
    ASSERT_EQ(testJSON.get<std::string>("name"),"Teszt");
    ASSERT_EQ(testJSON.get<int>("health_points"),12);
    ASSERT_EQ(testJSON.get<int>("damage"),20);
    ASSERT_EQ(testJSON.get<double>("attack_cooldown"),2.2);
}

TEST(unittests, missingKeys){
    ASSERT_THROW(Monster::parse("test/missingKeys.json"), JSON::ParseException);
}

TEST(unittests, mixedupAttributes){
    ASSERT_NO_THROW(Monster::parse("test/mixedupKeys.json"));    
}

TEST(unittests, brokenFile){
    ASSERT_THROW(Hero::parse("test/brokenFile.json"), JSON::ParseException);
}

TEST(unittests, parseTest){
    ASSERT_NO_THROW(Hero::parse("units/unit1.json"));
    ASSERT_NO_THROW(Monster::parse("units/Zombie.json"));
}

TEST(unittests, wrongPathTaken){
    ASSERT_THROW(JSON::parseFromFile("test/thisfiledoesnotexist.json"), JSON::ParseException);
}

TEST(unittests, parseTest2){
    Hero hero = Hero::parse("units/unit1.json");
    ASSERT_EQ(hero.getName(), "Hunkrow");
    ASSERT_EQ(hero.getHealthPoints(), 200);
    ASSERT_EQ(hero.getDamage().physical, 11);
    ASSERT_DOUBLE_EQ(hero.getAttackCoolDown(), 12.123);
}

TEST(unittests, scenarioParseTest){
    ASSERT_NO_THROW(JSON::parseFromFile("test/testScenario.json"));
    JSON test = JSON::parseFromFile("test/testScenario.json");
    JSON::list testList = { "Fallen.json", "Fallen.json", "Zombie.json", "Fallen.json",
        "Zombie.json", "Fallen.json", "Blood_Raven.json" };
    ASSERT_EQ(test.get<std::string>("hero"), "Dark_Wanderer.json");
    ASSERT_EQ(test.get<JSON::list>("monsters"), testList);
    ASSERT_EQ(test.get<std::string>("teszt"), "Elek.json");
}

TEST(unittests, checkMagicalDMG){
    Hero hero = Hero::parse("units/unit1.json");
    Monster monster = Monster::parse("units/Zombie.json");
    ASSERT_EQ(hero.getDamage().magical, 20);
    ASSERT_EQ(monster.getDamage().magical,0);
}

TEST(unittests, checkMagicalDMG2){
    JSON test = JSON::parseFromFile("units/unit5.json");
    ASSERT_EQ(test.get<int>("magical-damage"), 0);

}
TEST(unittests, mapClassTest){
    ASSERT_NO_THROW(Map("maps/exampleMap.txt"));
    ASSERT_THROW(Map("nincsilyen.txt"),std::runtime_error);
    Map test("maps/exampleMap.txt");
    ASSERT_THROW(test.get(2689,3543),Map::WrongIndexException);       
}

TEST(unittests, checkDefense){
    Hero hero = Hero::parse("units/unit1.json");
    Monster monster = Monster::parse("units/Zombie.json");
    ASSERT_EQ(hero.getDefense(), 1);
    ASSERT_EQ(monster.getDefense(), 1);
}

TEST(unittests, gameTestNoThrow){
    Game game;
    ASSERT_NO_THROW(game.setMap(Map("maps/exampleMap.txt")));
    ASSERT_NO_THROW(game.putHero(Hero::parse("units/Dark_Wanderer.json"),1,2));
    ASSERT_NO_THROW(game.putMonster(Monster::parse("units/Zombie.json"),1,2));
    ASSERT_NO_THROW(game.run());
}

TEST(unittests, gameTestThrow){
    Game game;
    ASSERT_THROW(game.run(), Game::NotInitializedException);
    ASSERT_THROW(game.putHero(Hero::parse("units/unit1.json"),1,2), Map::WrongIndexException);
}

TEST(unittests, checkHeroPosition){
    MarkedMap map("maps/markedmap.txt");
    std::pair<int, int> testPair(2,1);
    ASSERT_EQ(map.getHeroPosition(),testPair);
}

TEST(unittests, checkMonsterPosition){
    MarkedMap map("maps/markedmap.txt");
    std::list<std::pair<int,int>> testV1 = {
        std::make_pair(2, 3),
        std::make_pair(3, 4),
        std::make_pair(6, 5)
        };
     std::list<std::pair<int,int>> testV2 = {
        std::make_pair(6, 2),
        std::make_pair(7, 2),
        std::make_pair(3, 3)
        };
    std::list<std::pair<int,int>> testV3 = {
        std::make_pair(6, 3)
        };
    ASSERT_EQ(map.getMonsterPositions('1'),testV1);
    ASSERT_EQ(map.getMonsterPositions('2'),testV2);
    ASSERT_EQ(map.getMonsterPositions('3'),testV3);    
}

TEST(unittests, preparedGameTests){
    ASSERT_NO_THROW(PreparedGame game("scenarios/preparedGameScenario.json"));
}

TEST(unittests, checkLightRadius){
    Hero hero = Hero::parse("units/unit1.json");
    ASSERT_EQ(hero.getLightRadius(), 2);
    hero.addXp(15);
    hero.levelup();
    ASSERT_EQ(hero.getLightRadius(), 3);
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

