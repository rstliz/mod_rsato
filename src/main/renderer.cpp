#include "renderer.hpp"

#include <limits.h>
#include <unistd.h>

#include <nlohmann/json.hpp>

#include "request.hpp"

namespace rsato {
using json = nlohmann::json;

std::string Renderer::RenderJson(RequestParameter params) {
    json jarray_products = json::array();

    json jobj_person    = json::object();
    jobj_person["Name"] = params.name_;
    jobj_person["Age"]  = params.age_;

    json jobj_root      = json::object();
    jobj_root["Person"] = jobj_person;

    if (this->debug_flg_) {
        jobj_root["Debug"] = this->CreateDebugJson();
    }

    return jobj_root.dump();
}

nlohmann::json Renderer::CreateDebugJson() {
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, sizeof(hostname));

    json debug_jobj        = json::object();
    debug_jobj["Hostname"] = hostname;
    return debug_jobj;
}

}  // namespace rsato