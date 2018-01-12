#include "legato.h"
#include "interfaces.h"

COMPONENT_INIT
{
    LE_INFO("Hello world.");
    
    char imei[LE_INFO_IMEI_MAX_BYTES] = {0};
    le_info_GetImei(imei, sizeof(imei));

    LE_INFO("My IMEI is...: %s", imei);
}
