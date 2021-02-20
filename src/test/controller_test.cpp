#include "controller.hpp"

#include <gtest/gtest.h>

#define REQUEST_TIME 1590973200  // 2020-06-01 10:00:00

class TestLogger : public rsato::Logger {
   public:
    std::map<std::string, std::string> note_;

   public:
    TestLogger(){};
    void Note(const char *key, const char *value) override { note_[key] = value; };
    void Note(const char *key, const int value) override { note_[key] = std::to_string(value); };
    void Notice(const char *format, ...) override {}
    void Warning(const char *format, ...) override {}
    void Critical(const char *format, ...) override {}
};

class ControllerTest : public ::testing::Test {
   protected:
    rsato::api_dir_conf_t *dir_conf_;
    TestLogger *logger_;

   protected:
    virtual void SetUp() {
        this->logger_ = new TestLogger;
        this->InitDirConf();

        rsato::api_svr_conf_t svr_conf;
        rsato::Controller::Init(&svr_conf);
    };
    virtual void TearDown() {
        delete this->logger_;
        delete this->dir_conf_;
    };
    void InitDirConf() {
        this->dir_conf_          = new rsato::api_dir_conf_t;
        dir_conf_->config_on_dir = "";
    };

    std::map<std::string, std::string> CreateParameter() {
        std::map<std::string, std::string> param_map;
        param_map["debug"] = "1";
        return param_map;
    }
};

TEST_F(ControllerTest, age_under_min) {
    auto param_map   = this->CreateParameter();
    param_map["age"] = "-1";

    rsato::RequestParameter params(param_map);
    rsato::Request request(params, REQUEST_TIME);

    rsato::Controller *rsato = new rsato::Controller(this->dir_conf_, *this->logger_);
    EXPECT_EQ(400, rsato->HandleRequest(request));
    EXPECT_STREQ("", rsato->Output().c_str());
    delete rsato;
}

TEST_F(ControllerTest, LogNote) {
    auto param_map    = this->CreateParameter();
    param_map["name"] = "Ryo Sato";
    param_map["age"]  = "36";

    rsato::Controller *rsato = new rsato::Controller(this->dir_conf_, *this->logger_);
    rsato::RequestParameter params(param_map);
    rsato::Request request(params, REQUEST_TIME);

    EXPECT_EQ(0, rsato->HandleRequest(request));
    std::string output = rsato->Output();
    delete rsato;

    auto output_json = nlohmann::json::parse(output);
    EXPECT_STREQ("Ryo Sato", output_json["Person"]["Name"].get<std::string>().c_str());
    EXPECT_EQ(36, output_json["Person"]["Age"].get<std::int32_t>());

    EXPECT_STREQ("Ryo Sato", this->logger_->note_["NAME"].c_str());
    EXPECT_STREQ("1", this->logger_->note_["DEBUG"].c_str());
}