#include "../Hero.h"
#include "../JSON.h"
#include "../Monster.h"
#include "../Unit.h"
#include "../Map.h"
#include "../Damage.h"
#include "../Game.h"
#include <gtest/gtest.h>

TEST(parserTest, test_iostream){                       
    std::ifstream jsonFile;
    jsonFile.open("test/units/unit1.json");
    JSON testJSON = JSON::parseJson(jsonFile);
    jsonFile.close();
    ASSERT_EQ(testJSON.get<std::string>("name"),"Hunkrow");
    ASSERT_EQ(testJSON.get<int>("base_health_points"),200);
    ASSERT_EQ(testJSON.get<int>("damage"),11);
}

TEST(parserTest, test_filename){
    std::string fname = "test/units/unit2.json";
    JSON testJSON = JSON::parseFromFile(fname);
    ASSERT_EQ(testJSON.get<std::string>("name"),"Kakazhom");
    ASSERT_EQ(testJSON.get<int>("base_health_points"),150);
    ASSERT_EQ(testJSON.get<int>("damage"),15);
}

TEST(parserTest, test_string){     
    std::string fname = "test/units/unit3.json";
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
    Hero hero = Hero::parse("test/units/unit1.json");
    Monster monster = Monster::parse("Fallen.json");
    hero.fightTilDeath(monster);
    ASSERT_EQ(hero.isAlive(),1);
}

TEST(unittests,good_levelup){
    Hero hero = Hero::parse("test/units/unit1.json");
    Monster monster = Monster::parse("Zombie.json");
    hero.fightTilDeath(monster);

    ASSERT_EQ(hero.getLevel(),1);
   
}

TEST(unittests, name_check){
    Hero hero = Hero::parse("test/units/unit1.json");

    ASSERT_EQ(hero.getName(),"Hunkrow");

}

TEST(unittests, hp_check){
    Hero hero = Hero::parse("test/units/unit1.json");

    ASSERT_EQ(hero.getHealthPoints(),200);

}

TEST(unittests, parsunit_test){
    ASSERT_NO_THROW(JSON::parseFromFile("test/units/unit1.json"));
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
    ASSERT_NO_THROW(Hero::parse("test/units/unit1.json"));
    ASSERT_NO_THROW(Monster::parse("Zombie.json"));
}

TEST(unittests, wrongPathTaken){
    ASSERT_THROW(JSON::parseFromFile("test/thisfiledoesnotexist.json"), JSON::ParseException);
}

TEST(unittests, parseTest2){
    Hero hero = Hero::parse("test/units/unit1.json");
    ASSERT_EQ(hero.getName(), "Hunkrow");
    ASSERT_EQ(hero.getHealthPoints(), 200);
    ASSERT_EQ(hero.getDamage().physical, 11);
    ASSERT_DOUBLE_EQ(hero.getAttackCoolDown(), 12.123);
}

TEST(unittests, scenarioParseTest){
    ASSERT_NO_THROW(JSON::parseFromFile("test/testScenario.json"));
}

TEST(unittests, checkMagicalDMG){
    Hero hero = Hero::parse("test/units/unit1.json");
    Monster monster = Monster::parse("Zombie.json");
    ASSERT_EQ(hero.getDamage().magical, 20);
    ASSERT_EQ(monster.getDamage().magical,0);
    }

TEST(unittests, checkMagicalDMG2){
    JSON test = JSON::parseFromFile("test/units/unit2.json");
    ASSERT_EQ(test.get<int>("magical-damage"), 2);

    }
TEST(unittests, mapClassTest){
    ASSERT_NO_THROW(Map("exampleMap.txt"));
    ASSERT_THROW(Map("nincsilyen.txt"),std::runtime_error);
    Map test("exampleMap.txt");
    ASSERT_THROW(test.get(2689,3543),Map::WrongIndexException);       
}

TEST(unittests, checkDefense){
    Hero hero = Hero::parse("test/units/unit1.json");
    Monster monster = Monster::parse("Zombie.json");
    ASSERT_EQ(hero.getDefense(), 1);
    ASSERT_EQ(monster.getDefense(), 1);
}

TEST(unittests, gameTestNoThrow){
    Game game;
    ASSERT_NO_THROW(game.setMap(Map("exampleMap.txt")));
    ASSERT_NO_THROW(game.putHero(Hero::parse("Dark_Wanderer.json"),1,2));
    ASSERT_NO_THROW(game.putMonster(Monster::parse("Zombie.json"),1,2));
    ASSERT_NO_THROW(game.run());
}

TEST(unittests, gameTestThrow){
    Game game;
    ASSERT_THROW(game.run(), Game::NotInitializedException);
    ASSERT_THROW(game.putHero(Hero::parse("test/units/unit1.json"),1,2), Map::WrongIndexException);
}

TEST(unittests, checkHeroPosition){
   MarkedMap map("exampleMarkedMap.txt");
    std::pair<int, int> testPair(2,1);
    ASSERT_EQ(map.getHeroPosition(),testPair);
}

TEST(unittests, checkMonsterPosition){
    MarkedMap map("exampleMarkedMap.txt");
    std::vector<std::pair<int,int>> testV1 = {
        std::make_pair(2, 3),
        std::make_pair(3, 4),
        std::make_pair(6, 5)
        };
     std::vector<std::pair<int,int>> testV2 = {
        std::make_pair(3, 3),
        std::make_pair(6, 2),
        std::make_pair(7, 2)
        };
    std::vector<std::pair<int,int>> testV3 = {
        std::make_pair(6, 3)
        };
    ASSERT_EQ(map.getMonsterPosition('1'),testV1);
    ASSERT_EQ(map.getMonsterPosition('2'),testV2);
    ASSERT_EQ(map.getMonsterPosition('3'),testV3);    
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

