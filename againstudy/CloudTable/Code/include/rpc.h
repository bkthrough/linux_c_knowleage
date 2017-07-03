#ifndef CONN_H_
#define CONN_H_

#include "global.h"
#include "item.h"

/** Status Code Part, which show the status of RPC Call **/
#define SUCCESS 0 //The cmd has been processed successfully
#define CONN_FAIL 1 //Has failed to connect to remote target node
#define REMOTE_FAIL 2 //The remote target node has encounter some execution failure situation
#define ERROR_NO_CMD 3 //The RPC Request has not included any cmd
#define ERROR_WRONG_CMD 4 //The RPC Request can not handle this kind of cmd
#define ERROR_NO_PARAM 5 //The RPC Request has not included needed parameter
#define ERROR_TABLET_NOT_EXIST 6 //The Region Node don't have the target tablet
#define ERROR_ONLY_ALLOWS_ONE_REGION 7 //In the version 0.9, only allows has one region node

/*#define IN_PROGRESS*/ //Which means the cmd is still processing, may has use in the future
#define CONN_FAIL_MSG "connection Failed"
#define REMOTE_FAIL_MSG "the remote node have some troubles"
#define ERROR_NO_CMD_MSG "no command included in the request"
#define ERROR_WRONG_CMD_MSG "this request can not be handled by the remote node"
#define ERROR_NO_PARAM_MSG "not enough parameters included in the request"
#define ERROR_TABLET_NOT_EXIST_MSG "the Region Node don't have the the tablet belong to this table"
#define ERROR_ONLY_ALLOWS_ONE_REGION_MSG "In the version 0.9, the master only allows has one region node"
#define UNDEFINED_STATUS_CODE_MSG "the Status Code has not been defined"

typedef struct _RPCRequest RPCRequest;
typedef struct _RPCResponse RPCResponse;
typedef struct _ConnParam ConnParam;

char* get_error_message(int status_code);
int get_status_code(RPCResponse* rpcResponse);
int get_result_length(RPCResponse* rpcResponse);
byte* get_result(RPCResponse* rpcResponse);
RPCRequest* create_rpc_request(char* cmd, List *params);
RPCResponse* create_rpc_response(int status, int result_length, byte* result);
void destory_rpc_request(RPCRequest* rpcRequest);
void destory_rpc_response(RPCResponse* rpcResponse);
byte* get_param(List* params, int index);
List* add_int_param(List* params, int param_value);
List* add_param(List* params, int param_size, byte* param_value);
RPCResponse* connect_conn(char* conn, RPCRequest* rpcRequest);
List* generate_charactor_params(int size, ...);
void startup(int servPort, RPCResponse* (*handler_request)(char *cmd, List* params));
boolean check_node_validity(char* conn, char* type);

#endif /* CONN_H_ */
