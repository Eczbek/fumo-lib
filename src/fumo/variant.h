#pragma once
#include "../structs.h"

// random structs to test
#define ALL_VARIANT_TYPES(F) \
    F(Position) \
    F(Shape) \
    F(Body) \
    F(Rectangle)

#define ALL_VARIANT_TYPES_V(F, Variant) \
    F(Position, Variant) \
    F(Shape, Variant) \
    F(Body, Variant) \
    F(Rectangle, Variant)

// clang-format off
//---------------------------------------------------------
//---------------------------------------------------------
#define T_UNREGISTERED -420
#define auto __auto_type
#define let auto

typedef struct _variant { 

#define XMACRO(Type) Type _##Type;
    union value_t { ALL_VARIANT_TYPES(XMACRO) } value;
#undef XMACRO

#define XMACRO(Type) T_id_##Type,
      enum T_id { ALL_VARIANT_TYPES(XMACRO) } type_id;
#undef XMACRO

} _variant;

#define XMACRO1(Type) Type : T_id_##Type,
#define fumo$get_type_id(var) (enum T_id)\
    _Generic(var, \
             ALL_VARIANT_TYPES(XMACRO1)\
            default: T_UNREGISTERED) 

#define _variant(var) (_variant) {\
    .type_id = fumo$get_type_id(var),\
    .value = (union value_t) var\
} 
//---------------------------------------------------------
//---------------------------------------------------------
#define TypeName(Type) #Type,
static const char* all_type_names[] = {ALL_VARIANT_TYPES(TypeName)};
#undef TypeName

static inline const char* variant_type_name(_variant any) {
    return all_type_names[any.type_id];
}

#define _UNDERLYING_VALUE(T, Variant) case T_id_##T: result = &Variant.value._##T; break;

#define _GET_UNDERLYING(T, Variant) \
    switch (Variant.type_id) {ALL_VARIANT_TYPES_V(_UNDERLYING_VALUE, Variant)}

#define get_if(T, Variant) (T*) ({ \
    void* result = NULL; \
    _GET_UNDERLYING(T, Variant); \
    result; \
}); if ((fumo$get_type_id(*(T*)0) == Variant.type_id))


#define _CASE_VAL_(T, Variant) case T_id_##T: result = &Variant.value._##T; break;

#define case(T) break;}); case T_id_##T: ({ T* _##T = &____value____->_##T; 

#define match(Variant) auto ____value____ = (union value_t *)({ \
    auto result = NULL; \
    switch (Variant.type_id) {ALL_VARIANT_TYPES_V(_CASE_VAL_, Variant)}\
    result; \
}); switch(Variant.type_id) {(

#define _default break;}); default:

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------

#define _IS_SAME_TYPE(T, U) _Generic(typeof(T), typeof(U): 1, default: 0)

#define is_same_t(X, Y) \
    (({ \
         let is_x_v = _Generic(typeof(X), _variant: 1, default: 0); \
         let is_y_v = _Generic(typeof(Y), _variant: 1, default: 0); \
         let is_same_t =  \
            (is_x_v && is_y_v) \
            ? ( (*(_variant*)&X).type_id == (*(_variant*)&Y).type_id ) \
            : (is_x_v && !is_y_v) \
            ? ( (*(_variant*)&X).type_id == fumo$get_type_id(typeof(Y)) ) \
            : (!is_x_v && is_y_v) \
            ? ( fumo$get_type_id(typeof(X)) == (*(_variant*)&Y).type_id ) \
            : (!is_x_v && !is_y_v) \
            ? ( _IS_SAME_TYPE(X, Y) ) \
            : 0; \
        is_same_t; \
    }))



// #define autofree __attribute__((__cleanup__(autofree_impl)))
// static inline void autofree_impl(void* p) {
//     free(*((void**)p));
// }


/*
NOTE: code below isnt very useful
---------------------------------------------------------
#define GET_TYPE_INSTANCE(T) \
    static inline T instance_of_##T(T type) { \
        return (T) {}; \
    }
ALL_VARIANT_TYPES(GET_TYPE_INSTANCE)
#define INSTANCE_OF(T) , T: instance_of_##T
#define fumo$make_instance_of(var) \
    (typeof(var))((_Generic(typeof(var) ALL_VARIANT_TYPES(INSTANCE_OF))(var)))
---------------------------------------------------------

#define STATIC_IF(EXPR,THEN,ELSE)     \
  _Generic( &(char[1 + !!(EXPR)]){0}, \
    char (*)[2]: (THEN),              \
    char (*)[1]: (ELSE)               \
  )

#define _CHECK_TYPE_SAFETY(T) , T : 1
#define _TYPE_SAFE(T) \
    _Generic( *(T*)0\
             ALL_VARIANT_TYPES(_CHECK_TYPE_SAFETY),\
             default: 0)

#define fumo🔨get fumo$get


#define _X_isnt_variant(X, Y)\
    _Generic(typeof(Y),\
            variant: (fumo$get_type_id(typeof(X)) == Y.type_id)),\
            default: (typeof(X) == typeof(Y))

#define _X_is_variant(X, Y) \
    _Generic(typeof(Y),\
            variant: (X.type_id == ((variant)Y).type_id), \
            default: (X.type_id == fumo$get_type_id(typeof(Y))))
*/
