#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "libtcapi.h"

/* FIXME: get instance num for node name by parent No.*/
/*
 * \param instance_no, the num for parent
 */
int tcapi_get_special_instance (const char* node_name, int instance_no,
                                int *instance_num)
{
    char *p = NULL;
    char tmp_str[1024] = { 0 };
    int len = 0;
    int i = 0;

    if ((NULL == node_name) || (NULL == instance_num))
    {
         return -1;
    }

    strcpy (tmp_str, node_name);
    for (i = 0; i < instance_no; i++)
    {
          p = strrchr (tmp_str, '.');
         if (NULL != p)
         {
            len = strlen (tmp_str) - strlen (p);

            tmp_str[len] = '\0';
         }
    }

    if ((NULL != p) || (0 == instance_no))
    {
        p = strrchr (tmp_str, '.');

        if (NULL != p)
        {
            *instance_num = atoi (p + 1);
        }
        else
        {
            cwmp_log_error ("NULL for get . from str\n");
            return -1;
        }
    }
    else
    {
        cwmp_log_error ("NULL for get . from str\n");
        return -1;
    }

    return 0;
}

//get values from file int /etc/config
int get_config_value(char *cmd, char *value, unsigned size)
{
    FILE *fp = NULL;

    if (NULL == (fp = popen(cmd, "r"))) {
        cwmp_log_error("%s failed (%s)\n", __FUNCTION__, strerror(errno));
        return -1;
    }
    if (NULL == fgets(value, size, fp)) {
        cwmp_log_error("%s failed (%s)\n", __FUNCTION__, strerror(errno));
        pclose(fp);
        return -1;
    }
    return 0;
}