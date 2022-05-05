/* Copyright (c) 2017 pcbreflux. All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>. *
 */
#ifndef __BLUFI_GATTS_PROFILE_H__
#define __BLUFI_GATTS_PROFILE_H__

#include "esp_bt.h"
//#include "bta_api.h"
#include "esp_gatt_common_api.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"




void ble_app_start(void);

extern uint8_t raw_scan_rsp_data[100];

#endif /* __BLUFI_GATTS_PROFILE_H__ */