#pragma once
#include "../structs.h"
#include <wchar.h>

// clang-format off
#define __split(e) e
#define ALL_DATA_TYPES_VARIABLE(E, F, ...)                            \
    _Bool              __split(E)F##_Bool               __VA_ARGS__   \
    char               __split(E)F##char                __VA_ARGS__   \
    signed char        __split(E)F##signed_char         __VA_ARGS__   \
    unsigned char      __split(E)F##unsigned_char       __VA_ARGS__   \
    short              __split(E)F##short               __VA_ARGS__   \
    int                __split(E)F##int                 __VA_ARGS__   \
    long               __split(E)F##long                __VA_ARGS__   \
    long long          __split(E)F##long_long           __VA_ARGS__   \
    unsigned short     __split(E)F##unsigned_short      __VA_ARGS__   \
    unsigned int       __split(E)F##unsigned_int        __VA_ARGS__   \
    unsigned long      __split(E)F##unsigned_long       __VA_ARGS__   \
    unsigned long long __split(E)F##unsigned_long_long  __VA_ARGS__   \
    float              __split(E)F##float               __VA_ARGS__   \
    double             __split(E)F##double              __VA_ARGS__   \
    long double        __split(E)F##long_double         __VA_ARGS__   \
    char*              __split(E)F##char_ptr            __VA_ARGS__   \
    char const*        __split(E)F##char_const_ptr      __VA_ARGS__   \
    wchar_t*           __split(E)F##wchar_t_ptr         __VA_ARGS__   \
    wchar_t const*     __split(E)F##wchar_t_const_ptr   __VA_ARGS__   \
    void*              __split(E)F##void_ptr            __VA_ARGS__   \
    void const*        __split(E)F##void_const_ptr      __VA_ARGS__ 

#define ALL_DATA_TYPES(F)    \
    F(_Bool              )   \
    F(char               )   \
    F(signed char        )   \
    F(unsigned char      )   \
    F(short              )   \
    F(int                )   \
    F(long               )   \
    F(long long          )   \
    F(unsigned short     )   \
    F(unsigned int       )   \
    F(unsigned long      )   \
    F(unsigned long long )   \
    F(float              )   \
    F(double             )   \
    F(long double        )   \
    F(char*              )   \
    F(char const*        )   \
    F(wchar_t*           )   \
    F(wchar_t const*     )   \
    F(void*              )   \
    F(void const*        )   

#define ALL_DATA_TYPE_NAMES(F)   \
    F(_Bool             )       \
    F(char              )       \
    F(signed_char       )       \
    F(unsigned_char     )       \
    F(short             )       \
    F(int               )       \
    F(long              )       \
    F(long_long         )       \
    F(unsigned_short    )       \
    F(unsigned_int      )       \
    F(unsigned_long     )       \
    F(unsigned_long_long)       \
    F(float             )       \
    F(double            )       \
    F(long_double       )       \
    F(char_ptr          )       \
    F(char_const_ptr    )       \
    F(wchar_t_ptr       )       \
    F(wchar_t_const_ptr )       \
    F(void_ptr          )       \
    F(void_const_ptr    )       

#define ALL_DATA_TYPES_V(F, Variant)  \
    F(_Bool             , Variant)   \
    F(char              , Variant)   \
    F(signed_char       , Variant)   \
    F(unsigned_char     , Variant)   \
    F(short             , Variant)   \
    F(int               , Variant)   \
    F(long              , Variant)   \
    F(long_long         , Variant)   \
    F(unsigned_short    , Variant)   \
    F(unsigned_int      , Variant)   \
    F(unsigned_long     , Variant)   \
    F(unsigned_long_long, Variant)   \
    F(float             , Variant)   \
    F(double            , Variant)   \
    F(long_double       , Variant)   \
    F(char_ptr          , Variant)   \
    F(char_const_ptr    , Variant)   \
    F(wchar_t_ptr       , Variant)   \
    F(wchar_t_const_ptr , Variant)   \
    F(void_ptr          , Variant)   \
    F(void_const_ptr    , Variant)   
// ----------------------------------------------------------------

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

#define T_UNREGISTERED -420
#define auto __auto_type
#define let auto
//---------------------------------------------------------
//---------------------------------------------------------
// NOTE: fumo_c syntax and useful operator definitions

#define XMACRO1(Type) Type : T_id_##Type,
#define XMACRO1(Type) Type : T_id_##Type,
#define fumo$get_type_id(var) (enum T_id)   \
    _Generic(var,                           \
             ALL_VARIANT_TYPES(XMACRO1)     \
             ALL_DATA_TYPES_VARIABLE(:, T_id_, ,)     \
            default: T_UNREGISTERED) 

//---------------------------------------------------------

#define _UNDERLYING_VALUE(T, Variant) case T_id_##T: result = &Variant.value._##T; break;

#define _GET_UNDERLYING(T, Variant)                 \
    switch (Variant.type_id) {                      \
    ALL_VARIANT_TYPES_V(_UNDERLYING_VALUE, Variant) \
    ALL_DATA_TYPES_V(_UNDERLYING_VALUE, Variant)    \
}

#define get_if(T, Variant) (T*) ({ \
    void* result = NULL; \
    _GET_UNDERLYING(T, Variant); \
    result; \
}); if ((fumo$get_type_id(*(T*)0) == Variant.type_id))

//---------------------------------------------------------

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
// type comparison macro

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
