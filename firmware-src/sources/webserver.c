/*
 * webserver.c
 *
 * Copyright 2016 DeviceHive
 *
 * Author: Nikolay Khabarov
 *
 */

#include <c_types.h>
#include <osapi.h>
#include "webserver.h"
#include "httpd.h"
#include "rest.h"

static const char api[] = "/api/";

LOCAL HTTP_RESPONSE_STATUS ICACHE_FLASH_ATTR get_cb(const char *path,
		const char *key, HTTP_CONTENT *content_in, HTTP_CONTENT *content_out) {
	if(os_strncmp(path, api, sizeof(api) - 1) == 0) {
		return rest_handle(&path[sizeof(api) - 1], key, content_in, content_out);
	}
	char hw[] = "Hello, world";
	content_out->data = hw;
	content_out->len = sizeof(hw) - 1;
	return HRCS_ANSWERED;
}

LOCAL HTTP_RESPONSE_STATUS ICACHE_FLASH_ATTR post_cb(const char *path,
		const char *key, HTTP_CONTENT *content_in, HTTP_CONTENT *content_out) {
	if(os_strncmp(path, api, sizeof(api) - 1) == 0) {
		return rest_handle(&path[sizeof(api) - 1], key, content_in, content_out);
	}
	return HRCS_NOT_FOUND;
}

void ICACHE_FLASH_ATTR webserver_init() {
	httpd_init(get_cb, post_cb);
}
