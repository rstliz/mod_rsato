#ifndef __RENDERER_H_
#define __RENDERER_H_

#include <unistd.h>

#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>

#include "request.hpp"

namespace rsato {
class Renderer {
   private:
    const std::int8_t debug_flg_;

   public:
    Renderer(std::int8_t debug_flg) : debug_flg_(debug_flg){};
    std::string RenderJson(RequestParameter params);

   private:
    nlohmann::json CreateDebugJson();
};

}  // namespace rsato

#endif
