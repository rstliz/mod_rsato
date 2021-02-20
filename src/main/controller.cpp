#include "controller.hpp"

#include <errno.h>
#include <httpd.h>

#include "logger.hpp"
#include "mod_rsato.hpp"
#include "renderer.hpp"
#include "request.hpp"

namespace rsato {

api_svr_conf_t *Controller::svr_conf_ = nullptr;

void Controller::Init(api_svr_conf_t *svr_conf) {
    Controller::svr_conf_ = svr_conf;

    return;
}

Controller::~Controller() {
    if (nullptr == this->request_) {
        return;
    }
    RequestParameter *params = this->request_->params_;

    this->logger_->Note("NAME", params->name_.c_str());
    this->logger_->Note("AGE", params->age_);
    this->logger_->Note("DEBUG", params->debug_);
}

int Controller::HandleRequest(Request &request) {
    this->request_          = &request;
    RequestParameter params = *(request.params_);

    if (params.name_.empty() || params.age_ < 0) {
        return HTTP_BAD_REQUEST;
    }
    Renderer renderer(params.debug_);
    this->output_ = renderer.RenderJson(params);
    return (OK);
}

}  // namespace rsato
