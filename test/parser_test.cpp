#include "../JSON.h"
#include <gtest/gtest.h>


TEST(parserTest, test_iostream){
    std::map<std::string, std::string> outputMap; 
    std::map<std::string, std::string> expectedMap{
        {"name", "Hunkrow"},
        {"hp", "200"},
        {"dmg", "11"}};                       
    std::ifstream jsonFile;
    jsonFile.open("test/units/unit1.json");
    JSON testJSON = JSON::parseJson(jsonFile);
    jsonFile.close();
    outputMap["name"]=testJSON.get<std::string>("name");
    outputMap["hp"]=testJSON.get<std::string>("hp");
    outputMap["dmg"]=testJSON.get<std::string>("dmg");
    for (auto e : expectedMap){
        ASSERT_EQ(outputMap[e.first],e.second);
    }
}

TEST(parserTest, test_filename){
    std::map<std::string, std::string> outputMap; 
    std::map<std::string, std::string> expectedMap{
        {"name", "Kakazhom"},
        {"hp", "150"},
        {"dmg", "15"}};                       
    std::string fname = "test/units/unit2.json";
    JSON testJSON = JSON::parseFromFile(fname);
    outputMap["name"]=testJSON.get<std::string>("name");
    outputMap["hp"]=testJSON.get<std::string>("hp");
    outputMap["dmg"]=testJSON.get<std::string>("dmg");
    for (auto e : expectedMap){
        ASSERT_EQ(outputMap[e.first],e.second);
    }
}

TEST(parserTest, test_string){
    std::map<std::string, std::string> outputMap; 
    std::map<std::string, std::string> expectedMap{
        {"name", "Maytcreme"},
        {"hp", "300"},
        {"dmg", "5"}};             
              
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
    outputMap["hp"]=testJSON.get<std::string>("hp");
    outputMap["dmg"]=testJSON.get<std::string>("dmg");
    for (auto e : expectedMap){
        ASSERT_EQ(outputMap[e.first],e.second);
    }
}

TEST(parserTest, wrongJsonFile){
    const std::string expectedError = "Error in file: incorrect value.";
    const std::string fname = "test/wrongUnit.json";
    std::ifstream jsonFile;
    jsonFile.open(fname);
    try{
        JSON testJSON = JSON::parseJson(jsonFile);
    }
    catch(std::string e){
        ASSERT_EQ(e, expectedError);
    }
    
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}