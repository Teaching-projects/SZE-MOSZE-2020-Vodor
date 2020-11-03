#include "../Hero.h"
#include "../JSON.h"
#include "../Monster.h"
#include "../Unit.h"
#include <gtest/gtest.h>

TEST(parserTest, test_iostream){
    std::map<std::string, std::variant<std::string, int, double>> outputMap; 
    std::map<std::string, std::variant<std::string, int, double>> expectedMap{
        {"name", "Hunkrow"},
        {"base_health_points", 200},
        {"base_damage", 11}};                       
    std::ifstream jsonFile;
    jsonFile.open("test/units/unit1.json");
    JSON testJSON = JSON::parseJson(jsonFile);
    jsonFile.close();
    outputMap["name"]=testJSON.get<std::string>("name");
    outputMap["base_health_points"]=testJSON.get<int>("base_health_points");
    outputMap["base_damage"]=testJSON.get<int>("base_damage");
    for (auto e : expectedMap){
        ASSERT_EQ(outputMap[e.first],e.second);
    }
}

TEST(parserTest, test_filename){
    std::map<std::string, std::variant<std::string, int, double>> outputMap; 
    std::map<std::string, std::variant<std::string, int, double>> expectedMap{
        {"name", "Kakazhom"},
        {"base_health_points", 150},
        {"base_damage", 15}};                       
    std::string fname = "test/units/unit2.json";
    JSON testJSON = JSON::parseFromFile(fname);
    outputMap["name"]=testJSON.get<std::string>("name");
    outputMap["base_health_points"]=testJSON.get<int>("base_health_points");
    outputMap["base_damage"]=testJSON.get<int>("base_damage");
    for (auto e : expectedMap){
        ASSERT_EQ(outputMap[e.first],e.second);
    }
}

TEST(parserTest, test_string){
    std::map<std::string, std::variant<std::string, int, double>> outputMap; 
    std::map<std::string, std::variant<std::string, int, double>> expectedMap{
        {"name", "Maytcreme"},
        {"base_health_points", 300},
        {"base_damage", 5}};             
              
    std::string fname = "test/units/unit3.json";
    std::ifstream jsonFile;
    jsonFile.open(fname);
    std::string line;
    std::string jsonToString = "";

    while(getline(jsonFile,line))
        jsonToString += line;

    jsonFile.close();
    JSON testJSON = JSON::parseFromString(jsonToString);
    outputMap["name"]=testJSON.get<std::string>("name");
    outputMap["base_health_points"]=testJSON.get<int>("base_health_points");
    outputMap["base_damage"]=testJSON.get<int>("base_damage");
    for (auto e : expectedMap){
        ASSERT_EQ(outputMap[e.first],e.second);
    }
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
    std::map<std::string, std::variant<std::string, int, double>> outputMap; 
    std::map<std::string, std::variant<std::string, int, double>> expectedMap{
        {"name", "Teszt"},
        {"health_points", 12},
        {"damage", 20},
        {"attack_cooldown", 2.2}};
    
    JSON testJSON = JSON::parseFromFile("test/muchWhitespace.json");

    outputMap["name"]=testJSON.get<std::string>("name");
    outputMap["base_health_points"]=testJSON.get<int>("base_health_points");
    outputMap["base_damage"]=testJSON.get<int>("base_damage");
    outputMap["attack_cooldown"] = testJSON.get<double>("attack_cooldown");

    for (auto e : expectedMap)
        ASSERT_EQ(outputMap[e.first], e.second);
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

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
