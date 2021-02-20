#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "logger.hpp"
#include "mod_rsato.hpp"
#include "renderer.hpp"
#include "request.hpp"

namespace rsato {

class Controller {
   private:
    static api_svr_conf_t *svr_conf_;
    api_dir_conf_t *dir_conf_ = nullptr;
    Logger *logger_           = nullptr;
    Request *request_         = nullptr;
    std::string output_       = "";

   public:
    static void Init(api_svr_conf_t *svr_conf);
    Controller(api_dir_conf_t *dir_conf, Logger &logger) : dir_conf_(dir_conf), logger_(&logger){};
    ~Controller();
    int HandleRequest(Request &request);
    std::string Output() { return this->output_; };
};
}  // namespace rsato

#endif
