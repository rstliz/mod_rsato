#include "renderer.hpp"

#include <gtest/gtest.h>

#include "request.hpp"

#define REQUEST_TIME 1590973200  // 2020-06-01 10:00:00

class RendererTest : public ::testing::Test {
   protected:
    virtual void SetUp(){};
    virtual void TearDown(){};
};

TEST_F(RendererTest, RenderJson_Valid) {
    std::map<std::string, std::string> param_map;
    param_map["name"] = "Ryo Sato";
    param_map["age"]  = "36";

    rsato::RequestParameter params(param_map);
    rsato::Request request(params, REQUEST_TIME);

    rsato::Renderer renderer(0);
    std::string output = renderer.RenderJson(params);
    auto output_json   = nlohmann::json::parse(output);

    EXPECT_STREQ("Ryo Sato", output_json["Person"]["Name"].get<std::string>().c_str());
    EXPECT_EQ(36, output_json["Person"]["Age"].get<std::int32_t>());
}