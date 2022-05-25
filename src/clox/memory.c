#include "memory.h"
#include "vm.h"

void* reallocate(void* pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, new_size);
  if (result == NULL) {
    EXIT(ERR_OUT_OF_MEMORY);
  }
  return result;
}

static void free_object(obj_t* object) {
  switch (object->type) {
    case OBJ_FUNCTION: {
      obj_function_t* function = (obj_function_t*)object;
      free_chunk(&function->chunk);
      FREE(obj_function_t, object);
      break;
    }
    case OBJ_STRING: {
      obj_string_t* string = (obj_string_t*)(object);
      FREE_ARRAY(char, string->chars, string->length + 1);
      FREE(obj_string_t, object);
      break;
    }
    case OBJ_NATIVE: {
      FREE(obj_native_t, object);
      break;
    }
    case OBJ_CLOSURE: {
      obj_closure_t* closure = (obj_closure_t*)object;
      FREE_ARRAY(obj_upvalue_t*, closure->upvalues, closure->upvalue_count);
      FREE(obj_closure_t, object);
      break;
    }
    case OBJ_UPVALUE: {
      FREE(obj_upvalue_t, object);
      break;
    }
  }
}

void free_objects() {
  obj_t* object = vm.objects;
  while (object != NULL) {
    obj_t* next = object->next;
    free_object(object);
    object = next;
  }
}
