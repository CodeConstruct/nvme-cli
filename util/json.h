/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef __JSON__H
#define __JSON__H

#include <json.h>

/* Wrappers around json-c's API */

#define json_create_object(o) json_object_new_object(o)
#define json_create_array(a) json_object_new_array(a)
#define json_free_object(o) json_object_put(o)
#define json_free_array(a) json_object_put(a)
#define json_object_add_value_uint(o, k, v) \
	json_object_object_add(o, k, json_object_new_int(v))
#define json_object_add_value_int(o, k, v) \
	json_object_object_add(o, k, json_object_new_int(v))
#ifdef CONFIG_JSONC_14
#define json_object_add_value_uint64(o, k, v) \
	json_object_object_add(o, k, json_object_new_uint64(v))
#else
#define json_object_add_value_uint64(o, k, v) \
	if ((v) > UINT_MAX) {						\
		fprintf(stderr, "Value overflow in %s", k);		\
		json_object_object_add(o, k, json_object_new_int(-1));	\
	} else								\
		json_object_object_add(o, k, json_object_new_int(v))
#endif
#define json_object_add_value_double(o, k, v) \
	json_object_object_add(o, k, util_json_object_new_double(v))
#define json_object_add_value_float(o, k, v) \
	json_object_object_add(o, k, json_object_new_double(v))
#define json_object_add_value_string(o, k, v) \
	json_object_object_add(o, k, json_object_new_string(v))
#define json_object_add_value_array(o, k, v) \
	json_object_object_add(o, k, v)
#define json_object_add_value_object(o, k, v) \
	json_object_object_add(o, k, v)
#define json_array_add_value_object(o, k) \
	json_object_array_add(o, k)
#define json_array_add_value_string(o, v) \
	json_object_array_add(o, json_object_new_string(v))
#define json_print_object(o, u)						\
	printf("%s", json_object_to_json_string_ext(o,			\
		JSON_C_TO_STRING_PRETTY |				\
		JSON_C_TO_STRING_NOSLASHESCAPE))

struct json_object *util_json_object_new_double(long double d);

#endif
