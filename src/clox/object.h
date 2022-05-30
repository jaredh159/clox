#ifndef clox_object_h
#define clox_object_h

#include "chunk.h"
#include "common.h"
#include "table.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_FUNCTION(value) is_obj_type(value, OBJ_FUNCTION)
#define IS_STRING(value) is_obj_type(value, OBJ_STRING)
#define IS_NATIVE(value) is_obj_type(value, OBJ_NATIVE)
#define IS_CLOSURE(value) is_obj_type(value, OBJ_CLOSURE)
#define IS_CLASS(value) is_obj_type(value, OBJ_CLASS)
#define IS_INSTANCE(value) is_obj_type(value, OBJ_INSTANCE)

#define AS_CLASS(value) ((obj_class_t*)AS_OBJ(value))
#define AS_CLOSURE(value) ((obj_closure_t*)AS_OBJ(value))
#define AS_FUNCTION(value) ((obj_function_t*)AS_OBJ(value))
#define AS_STRING(value) ((obj_string_t*)AS_OBJ(value))
#define AS_CSTRING(value) (((obj_string_t*)AS_OBJ(value))->chars)
#define AS_NATIVE(value) (((obj_native_t*)AS_OBJ(value))->function)
#define AS_INSTANCE(value) ((obj_instance_t*)AS_OBJ(value))

typedef enum {
  OBJ_CLASS,
  OBJ_CLOSURE,
  OBJ_FUNCTION,
  OBJ_INSTANCE,
  OBJ_NATIVE,
  OBJ_STRING,
  OBJ_UPVALUE,
} obj_type_t;

struct obj_t {
  obj_type_t type;
  bool is_marked;
  struct obj_t* next;
};

typedef value_t (*native_fn_t)(int arg_count, value_t* args);

typedef struct {
  obj_t obj;
  native_fn_t function;
} obj_native_t;

typedef struct {
  obj_t obj;
  int arity;
  int upvalue_count;
  chunk_t chunk;
  obj_string_t* name;
} obj_function_t;

struct obj_string_t {
  obj_t obj;
  int length;
  char* chars;
  uint32_t hash;
};

typedef struct obj_upvalue_t {
  obj_t obj;
  value_t* location;
  value_t closed;
  struct obj_upvalue_t* next;
} obj_upvalue_t;

typedef struct {
  obj_t obj;
  obj_function_t* function;
  obj_upvalue_t** upvalues;
  int upvalue_count;
} obj_closure_t;

typedef struct {
  obj_t obj;
  obj_string_t* name;
} obj_class_t;

typedef struct {
  obj_t obj;
  obj_class_t* class;
  table_t fields;
} obj_instance_t;

obj_instance_t* new_instance(obj_class_t* class);
obj_closure_t* new_closure(obj_function_t* function);
obj_function_t* new_function();
obj_class_t* new_class(obj_string_t* name);
obj_upvalue_t* new_upvalue(value_t* slot);
obj_native_t* new_native(native_fn_t function);
obj_string_t* take_string(char* chars, int length);
obj_string_t* copy_string(const char* chars, int length);
void print_object(value_t value);

static inline bool is_obj_type(value_t value, obj_type_t type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
