/*
 * Copyright 2018-2026 Eduardo Chappa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#ifndef JSON_H_INCLUDED
#define JSON_H_INCLUDED

typedef enum {JObject = 0, JString, JLong, JDecimal, JExponential, JNumberError,
	      JArray, JBoolean, JNull, JEnd} JObjType;

/*
 * states that allow us to identify which part of the
 * json object we are in. DEFAULT means we treat
 * the object by its type and value, other states
 * indicate that we are either at the beginning or end
 * of an object or array. When the state is at
 * JSON_START it means that we just got a "{" character
 * and we are at the first element. In that case
 * jtype is the type of the first element in the
 * json object. If state is JSON_ARRAY_START, then
 * value points to a JSON_S * object which lists
 * all elements in the array.
 */
#define JSON_DEFAULT		0x00
#define JSON_START		0x01
#define JSON_END		0x02
#define JSON_ARRAY_START	0x10
#define JSON_ARRAY_END		0x20

typedef struct json_s {
   JObjType jtype;
   int state;
   unsigned char *name;
   void *value;
   struct json_s *next;
} JSON_S;

#define json_value_type(J, I, T) 					\
	(((jx = json_body_value((J), (I))) != NIL)			\
	  && jx->jtype == (T) && jx->value)				\
	? ((T) == JLong							\
	    ? *(long *) jx->value					\
	    : ((T) == JBoolean						\
	        ? (compare_cstring("false", (char *) jx->value) ? 1 : 0)\
		: NIL							\
	      )								\
          )								\
	: NIL

void json_assign(void **, JSON_S *, char *, JObjType);
JSON_S *json_by_name_and_type(JSON_S *, char *, JObjType);
JSON_S *json_parse(unsigned char *);
JSON_S *json_body_value(JSON_S *, unsigned char *);
JSON_S *json_new();
void json_free(JSON_S **);
unsigned char *json2uchar(JSON_S *, unsigned char **);

#endif /* JSON_H_INCLUDED */
