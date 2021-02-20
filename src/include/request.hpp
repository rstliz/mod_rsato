#ifndef __REQUEST_PARAMETER_H_
#define __REQUEST_PARAMETER_H_

#include <cstdint>
#include <ctime>
#include <map>
#include <string>

namespace rsato {

class RequestParameter;
class Request {
   public:
    RequestParameter *params_ = nullptr;
    const std::time_t request_time_;

    Request(RequestParameter &params, std::time_t request_time) : params_(&params), request_time_(request_time){};
};

class RequestParameter {
   public:
    const std::map<std::string, std::string> param_map_;
    const std::int8_t debug_;
    const std::string name_;
    const std::int8_t age_;

   public:
    RequestParameter(std::map<std::string, std::string> &param_map)
        : param_map_(param_map),
          debug_(ToInt(GetByName("debug"), 0)),
          name_(GetByName("name")),
          age_(ToInt(GetByName("age"), 0)){};

    std::string GetByName(std::string name);

   private:
    std::int32_t ToInt(std::string str_value, std::int32_t default_value);
};

inline std::string RequestParameter::GetByName(std::string name) {
    try {
        return this->param_map_.at(name);
    } catch (std::out_of_range &e) {
        return std::string("");
    }
}

inline std::int32_t RequestParameter::ToInt(std::string str_value, std::int32_t default_value) {
    try {
        return std::stol(str_value);
    } catch (std::invalid_argument &e) {
        return default_value;
    }
}
}  // namespace rsato

#endif
