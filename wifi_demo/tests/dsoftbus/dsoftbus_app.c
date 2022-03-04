/*
 * Copyright (c) 2022 ASR Microelectronics (Shanghai) Co., Ltd. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <string.h>
#include "cmsis_os2.h"
#include "ohos_init.h"

extern void InitSoftBusServer(void);
extern int lega_wlan_get_connected_status();

static void DSoftTask(void *arg)
{
    while(lega_wlan_get_connected_status()==0)
    {
        osDelay(500);
    }
    printf("InitSoftBusServer: %s\r\n", __func__);
    InitSoftBusServer();
}

static void DSoftBus_App(void)
{
    printf("example: %s\r\n", __func__);
    osThreadAttr_t attr;
    attr.name = "dsoftbus task";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 1024*4;
    attr.priority = 24;

    if (osThreadNew((osThreadFunc_t)DSoftTask, NULL, &attr) == NULL) {
        printf("Falied to create dsoftbus task!\n");
    }
}

APP_FEATURE_INIT(DSoftBus_App);
