/* --------------------------------------------------
 * @brief: 
 *
 * @version: 1.0
 *
 * @date: 08/01/2018
 *
 * @author: 
 * --------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hsf.h>

#include "cJSON.h"

#include "joylink_log.h"
#include "joylink_extern.h"
#include "joylink_memory.h"
#include "joylink_socket.h"
#include "joylink_string.h"
#include "joylink_stdio.h"
#include "joylink_stdint.h"
#include "joylink_time.h"

/**
 * brief: 
 *
 * @Param: pMsg
 * @Param: user_dev
 *
 * @Returns: 
 */
int 
joylink_dev_parse_ctrl(const char *pMsg, user_dev_status_t *userDev)
{
//	int a = 0;
//	a =strlen(pMsg);
	u_printf("service contrl:%02x,%02x  strlen: %d\n",pMsg[0],pMsg[1],strlen(pMsg));

	userDev->OnOff_state = pMsg[1];

	if(user_dev.OnOff_state)
		hfgpio_fset_out_low(USER_LINK);
	else
		hfgpio_fset_out_high(USER_LINK);
	
	return 0;
}

/**
 * brief: 
 * NOTE: If return is not NULL, 
 * must free it, after use.
 *
 * @Param: retMsg
 * @Param: retCode
 * @Param: wci
 * @Param: devlist
 *
 * @Returns: char * 
 */
char * 
joylink_dev_package_info(const int retCode, user_dev_status_t *userDev)
{
	if(NULL == userDev){
		return NULL;
	}
	cJSON *root, *arrary;
	char *out  = NULL; 

	root = cJSON_CreateObject();
	if(NULL == root){
		goto RET;
	}
	arrary = cJSON_CreateArray();
	if(NULL == arrary){
		cJSON_Delete(root);
		goto RET;
	}
	cJSON_AddNumberToObject(root, "code", retCode);
	cJSON_AddItemToObject(root, "streams", arrary);

//	char i2str[64];
	cJSON *data_Power = cJSON_CreateObject();
	cJSON_AddItemToArray(arrary, data_Power);
	cJSON_AddStringToObject(data_Power, "stream_id", "Power");
	cJSON_AddNumberToObject(data_Power, "current_value", userDev->OnOff_state);

	out=cJSON_PrintUnformatted(root);
	cJSON_Delete(root);
RET:
	return out;
}

#ifdef _JOYLINK_UART_PROCOTOL_SUPPORTED_
/**
 * brief: 
 *
 * @Param: msg
 *
 * @Returns: 
 */
char *
joylink_json_delete_snapshot(const char *msg)
{
	char *out = NULL;

	if(NULL == msg){
		goto RET;
	}
	log_debug("json_org:%s", msg);

	cJSON *pJson = cJSON_Parse(msg);
	if(NULL == pJson){
		log_error("--->:ERROR: pMsg is NULL\n");
		goto RET;
	}

	cJSON_DeleteItemFromObject(pJson, "snapshot");

	out = cJSON_PrintUnformatted(pJson);
	cJSON_Delete(pJson);
	
	log_debug("json_org:%s", out);
RET:
	return out;
}
#endif