#ifndef FLECS_COMPONENTS_HTTP_H
#define FLECS_COMPONENTS_HTTP_H

#include "bake_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum EcsHttpMethod {
    EcsHttpGet,
    EcsHttpPost,
    EcsHttpPut,
    EcsHttpDelete,
    EcsHttpMethodUnknown
} EcsHttpMethod;

typedef struct EcsHttpEndpoint EcsHttpEndpoint;

typedef struct EcsHttpRequest {
    const char *url;
    const char *relative_url;
    const char *params;
    void *ctx;
    EcsHttpMethod method;
    ecs_entity_t server;
} EcsHttpRequest;

typedef struct EcsHttpReply {
    char *header;
    char *body;
    int status;
    bool is_file;
} EcsHttpReply;

typedef bool (*EcsHttpServiceAction)(
    ecs_world_t *world,
    ecs_entity_t entity,
    EcsHttpEndpoint *endpoint,
    EcsHttpRequest *request,
    EcsHttpReply *reply);

typedef struct EcsHttpServer {
    uint16_t port;
} EcsHttpServer;

struct EcsHttpEndpoint {
    char *url;
    void *ctx;
    bool synchronous;
    EcsHttpServiceAction action;
};

typedef struct EcsComponentsHttpHandles {
    ECS_DECLARE_COMPONENT(EcsHttpServer);
    ECS_DECLARE_COMPONENT(EcsHttpEndpoint);
} EcsComponentsHttpHandles;

void EcsComponentsHttp(
    ecs_world_t *world,
    int flags,
    void *handles_out);

#define EcsComponentsHttp_ImportHandles(handles)\
    ECS_IMPORT_COMPONENT(handles, EcsHttpServer);\
    ECS_IMPORT_COMPONENT(handles, EcsHttpEndpoint);

#ifdef __cplusplus
}
#endif

#endif
