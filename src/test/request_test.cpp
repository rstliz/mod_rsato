#include "request.hpp"

#include <gtest/gtest.h>

#define REQUEST_TIME 1590973200  // 2020-06-01 10:00:00

TEST(RequestParameterTest_Constructor, debug_empty) {
    std::map<std::string, std::string> param_map;
    rsato::RequestParameter params(param_map);
    EXPECT_EQ(0, params.debug_);
}

TEST(RequestParameterTest_Constructor, debug_0) {
    std::map<std::string, std::string> param_map;
    param_map["debug"] = "0";
    rsato::RequestParameter params(param_map);
    EXPECT_EQ(0, params.debug_);
}

TEST(RequestParameterTest_Constructor, debug_1) {
    std::map<std::string, std::string> param_map;
    param_map["debug"] = "1";
    rsato::RequestParameter params(param_map);
    EXPECT_EQ(1, params.debug_);
}

TEST(RequestParameterTest_Constructor, name) {
    std::map<std::string, std::string> param_map;
    param_map["name"] = "Ryo Sato";
    rsato::RequestParameter params(param_map);
    EXPECT_STREQ("Ryo Sato", params.name_.c_str());
}
