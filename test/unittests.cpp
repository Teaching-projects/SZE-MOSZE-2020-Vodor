#include "../Hero.h"
#include "../JSON.h"
#include "../Monster.h"
#include "../Unit.h"
#include "../Map.h"
#include <gtest/gtest.h>

TEST(parserTest, test_iostream){                       
    std::ifstream jsonFile;
    jsonFile.open("test/units/unit1.json");
    JSON testJSON = JSON::parseJson(jsonFile);
    jsonFile.close();
    ASSERT_EQ(testJSON.get<std::string>("name"),"Hunkrow");
    ASSERT_EQ(testJSON.get<int>("base_health_points"),200);
    ASSERT_EQ(testJSON.get<int>("base_damage"),11);
}

TEST(parserTest, test_filename){
    std::string fname = "test/units/unit2.json";
    JSON testJSON = JSON::parseFromFile(fname);
    ASSERT_EQ(testJSON.get<std::string>("name"),"Kakazhom");
    ASSERT_EQ(testJSON.get<int>("base_health_points"),150);
    ASSERT_EQ(testJSON.get<int>("base_damage"),15);
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
    ASSERT_EQ(testJSON.get<int>("base_damage"),5);
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
    ASSERT_EQ(hero.getDamage(), 11);
    ASSERT_DOUBLE_EQ(hero.getAttackCoolDown(), 12.123);
}

TEST(unittests, scenarioParseTest){
    ASSERT_NO_THROW(JSON::parseFromFile("test/testScenario.json"));
}

TEST(unittests, mapClassTest){
    ASSERT_NO_THROW(Map("exampleMap.txt"));
    ASSERT_THROW(Map("nincsilyen.txt"),std::runtime_error);
    Map test("exampleMap.txt");
    ASSERT_THROW(test.get(2689,3543),Map::WrongIndexException);       
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
