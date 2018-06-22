#include "libtcapi.h"

int  cpe_refresh_igd_wlanconfiguration(cwmp_t * cwmp, parameter_node_t * param_node, callback_register_func_t callback_reg)
{
    FUNCTION_TRACE();

    if(!param_node)
    {
        return FAULT_CODE_9002;
    }
    parameter_node_t * tmp_param, *tmp_node, *child_param;
    child_param = param_node->child;
    if(child_param)
    {
        for(tmp_param=child_param->next_sibling; tmp_param; )
        {
            cwmp_log_info("refresh WANDevice node, delete param %s\n", tmp_param->name);
            tmp_node = tmp_param->next_sibling;
            cwmp_model_delete_parameter(tmp_param);
            tmp_param = tmp_node;
        }
        child_param->next_sibling = NULL;
                
        parameter_node_t * wlan1_param;
        cwmp_model_copy_parameter(param_node, &wlan1_param, 1);
        parameter_node_t * wlan2_param;
        cwmp_model_copy_parameter(param_node, &wlan2_param, 2);
       
        cwmp_model_refresh_object(cwmp, param_node, 0, callback_reg); 
    }
    
    return FAULT_CODE_OK;
}

//InternetGatewayDevice.LANDevice.WLANConfiguration.Enable
int cpe_get_igd_WLANConfiguration_Enable(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{   
    //always enable
    *value = PSTRDUP("1");
    return FAULT_CODE_OK;
}
int cpe_set_igd_WLANConfiguration_Enable(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
    //always enable
	return FAULT_CODE_OK;
}

//InternetGatewayDevice.LANDevice.WLANConfiguration.BeaconType
int cpe_get_igd_WLANConfiguration_BeaconType(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{    
    return FAULT_CODE_OK;
}
int cpe_set_igd_WLANConfiguration_BeaconType(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
	return FAULT_CODE_OK;
}

//InternetGatewayDevice.LANDevice.WLANConfiguration.WPAEncryptionModes
int cpe_get_igd_WLANConfiguration_WPAEncryptionModes(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{    
    return FAULT_CODE_OK;
}
int cpe_set_igd_WLANConfiguration_WPAEncryptionModes(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
	return FAULT_CODE_OK;
}

//InternetGatewayDevice.LANDevice.WLANConfiguration.WPAAuthenticationMode
int cpe_get_igd_WLANConfiguration_WPAAuthenticationMode(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{    
    return FAULT_CODE_OK;
}
int cpe_set_igd_WLANConfiguration_WPAAuthenticationMode(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
	return FAULT_CODE_OK;
}

//InternetGatewayDevice.LANDevice.WLANConfiguration.SSID
int cpe_get_igd_WLANConfiguration_SSID(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{   
    char buf[128] = {0};
    if (get_config_value("uci get wireless.@wifi-iface[0].ssid", buf, sizeof(buf))) {
        return FAULT_CODE_9007;
    }
    *value = PSTRDUP(buf);
    return FAULT_CODE_OK;
}
int cpe_set_igd_WLANConfiguration_SSID(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
    int i = 0;
    char cmdline[64] = {0};
    const char *cmd= "uci set wireless.@wifi-iface[0].ssid=";
    
    for (; i < strlen(value); i++) {
        if (isascii(value[i]))
            continue;
        else
            return FAULT_CODE_9007;
    }
    snprintf(cmdline, sizeof(cmdline) - 1, "%s%s",cmd,value);
    cmdline[strlen(cmdline)] = '\0';
    system(cmdline);
    system("uci commit wireless");
	return FAULT_CODE_OK;
}