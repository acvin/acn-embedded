/* Copyright (c) 2017 Arrow Electronics, Inc.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Apache License 2.0
 * which accompanies this distribution, and is available at
 * http://apache.org/licenses/LICENSE-2.0
 * Contributors: Arrow Electronics, Inc.
 */

#include "json/telemetry.h"
#include <config.h>
#include <json/json.h>
#include <json/data.h>


char *telemetry_serialize(arrow_device_t *device, void *data) {
    JsonNode *_node = json_mkobject();
    gevk_data_t *sens_data = (gevk_data_t *)data;
    json_append_member(_node, TELEMETRY_DEVICE_HID, json_mkstring(P_VALUE(device->hid)));
//    json_append_member(_node, TELEMETRY_TEMPERATURE, json_mknumber(sens_data->Temperature));
//    json_append_member(_node, TELEMETRY_HUMIDITY, json_mknumber(sens_data->Humidity));
    json_append_member(_node, "i|als", json_mknumber(sens_data->als));
    json_append_member(_node, "f|lux", json_mknumber(sens_data->abmienceInLux));
    json_append_member(_node, "i|pir", json_mknumber(sens_data->pir));
    char *tmp = json_encode(_node);
    json_delete(_node);
    return tmp;
}
