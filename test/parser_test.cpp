#include "../Parser.h"
#include <gtest/gtest.h>


TEST(parserTest, test_iostream){
    Parser p;
    std::map<std::string, std::string> outputMap; 
    std::map<std::string, std::string> expectedMap{
        {"name", "Hunkrow"},
        {"hp", "28000"},
        {"dmg", "2800"}};                       
    std::ifstream jsonFile;
    jsonFile.open("units/unit1.json");
    outputMap = p.parseJson(jsonFile);
    jsonFile.close();
    for (auto e : expectedMap){
        ASSERT_TRUE(outputMap[e.first]==expectedMap[e.first]);
    }
}

TEST(parserTest, test_filename){
    Parser p;
    std::map<std::string, std::string> outputMap; 
    std::map<std::string, std::string> expectedMap{
        {"name", "Kakazhom"},
        {"hp", "33000"},
        {"dmg", "2500"}};                       
    std::string fname = "units/unit2.json";
    outputMap = p.parseJson(fname);
    for (auto e : expectedMap){
        ASSERT_TRUE(outputMap[e.first]==expectedMap[e.first]);
    }
}

TEST(parserTest, test_string){
    Parser p;
    std::map<std::string, std::string> outputMap; 
    std::map<std::string, std::string> expectedMap{
        {"name", "Maytcreme"},
        {"hp", "30000"},
        {"dmg", "3100"}};                       
    std::string fname = "units/unit3.json";
    std::ifstream jsonFile;
    jsonFile.open(fname);
    std::string line;
    std::string jsonToString="";
    while(getline(jsonFile,line))
        jsonToString+=line;
    jsonFile.close();
    outputMap = p.parseJson(jsonToString);
    for (auto e : expectedMap){
        ASSERT_TRUE(outputMap[e.first]==expectedMap[e.first]);
    }
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}