
#include "mod_rsato.hpp"

#include <ap_config.h>
#include <apr_strings.h>
#include <apr_tables.h>
#include <apreq_module_apache2.h>
#include <http_config.h>
#include <http_protocol.h>
#include <httpd.h>

#include <stdexcept>

#include "ap_logger.hpp"
#include "controller.hpp"

namespace rsato {
#define UNUSED(x) ((void)(x))
#define CXX_AP_INIT_TAKE1(directive, func, mconfig, where, help) \
    AP_INIT_TAKE1(directive, (const char *(*)())func, mconfig, where, help)

static void *create_per_svr_config(apr_pool_t *p, server_rec *s) {
    api_svr_conf_t *svr_conf;
    UNUSED(s);
    svr_conf                   = (api_svr_conf_t *)apr_pcalloc(p, sizeof(*svr_conf));
    svr_conf->config_on_server = (const char *)apr_pstrdup(p, "your_setting_on_server");
    return ((void *)svr_conf);
}

static void *create_per_dir_config(apr_pool_t *p, char *arg) {
    UNUSED(arg);
    api_dir_conf_t *dir_conf = NULL;

    dir_conf                = (api_dir_conf_t *)apr_pcalloc(p, sizeof(*dir_conf));
    dir_conf->config_on_dir = apr_pstrdup(p, "your_setting_on_dir");

    return ((void *)dir_conf);
}

static const char *cmd_set_config_on_server(cmd_parms *cmd, void *dest, const char *arg) {
    UNUSED(dest);
    api_svr_conf_t *svr_conf   = (api_svr_conf_t *)ap_get_module_config(cmd->server->module_config, &rsato_module);
    svr_conf->config_on_server = (const char *)apr_pstrdup(cmd->pool, arg);
    return (NULL);
}

static const char *cmd_set_config_on_dir(cmd_parms *cmd, void *dest, const char *arg) {
    api_dir_conf_t *dir_conf = (api_dir_conf_t *)dest;
    dir_conf->config_on_dir  = (const char *)apr_pstrdup(cmd->pool, arg);
    return (NULL);
}

static const command_rec read_conf_cmds[] = {
    CXX_AP_INIT_TAKE1("SERVER_CONF", cmd_set_config_on_server, NULL, OR_FILEINFO, "set server conf"),
    CXX_AP_INIT_TAKE1("DIR_CONF", cmd_set_config_on_dir, NULL, OR_FILEINFO, "set directory conf"),
    {NULL}};

static void rsato_init_child(apr_pool_t *p, server_rec *s) {
    UNUSED(p);
    api_svr_conf_t *svr_conf = (api_svr_conf_t *)ap_get_module_config(s->module_config, &rsato_module);
    try {
        Controller::Init(svr_conf);
    } catch (std::runtime_error e) {
        ApLogger::SCritical("%s", e.what());
    }
    return;
}

static int apr_table_to_map(void *dest, const char *key, const char *value) {
    auto *params = (std::map<std::string, std::string> *)dest;
    params->emplace(std::string(key), std::string(value));
    return 1;
}

static int rsato_handler(request_rec *r) {
    if (strcmp(r->handler, "rsato") != 0) {
        return (DECLINED);
    }

    apr_table_set(r->err_headers_out, "Connection", "close");
    apr_table_set(r->err_headers_out, "Cache-Control", "private, max-age=0, no-cache");

    if (r->header_only) {
        return (OK);
    }

    r->content_type = "application/json; charset=utf-8";

    api_dir_conf_t *dir_conf = (api_dir_conf_t *)ap_get_module_config(r->per_dir_config, &rsato_module);

    std::map<std::string, std::string> param_map;
    apr_table_do(apr_table_to_map, &param_map, apreq_params(apreq_handle_apache2(r), r->pool), nullptr);
    RequestParameter params(param_map);
    Request request(params, apr_time_sec(r->request_time));

    ApLogger ap_logger(r);
    Controller rsato(dir_conf, ap_logger);

    int http_status = rsato.HandleRequest(request);
    ap_rputs(rsato.Output().c_str(), r);
    return (http_status);
}

static void rsato_register_hooks(apr_pool_t *p) {
    UNUSED(p);
    ap_hook_handler(rsato_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(rsato_init_child, NULL, NULL, APR_HOOK_MIDDLE);
    return;
}
}  // namespace rsato

// Dispatch list for API hooks
module AP_MODULE_DECLARE_DATA rsato_module = {
    STANDARD20_MODULE_STUFF,
    rsato::create_per_dir_config,  // create per-dir    config structures
    NULL,                          // merge  per-dir    config structures
    rsato::create_per_svr_config,  // create per-server config structures
    NULL,                          // merge  per-server config structures
    rsato::read_conf_cmds,         // table of config file commands
    rsato::rsato_register_hooks    // register hooks
};
