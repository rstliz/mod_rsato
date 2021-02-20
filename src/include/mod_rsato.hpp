#ifndef __MOD_RSATO_H_
#define __MOD_RSATO_H_

namespace rsato {

typedef struct {
    const char *config_on_dir;
} api_dir_conf_t;

typedef struct {
    const char *config_on_server;
} api_svr_conf_t;

}  // namespace rsato

#endif
