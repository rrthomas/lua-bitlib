/* Bitwise operations library */
/* (c) Reuben Thomas 2000-2008 */
/* See README for license */

#include "config.h"

#include <lua.h>
#include <lauxlib.h>
#include <limits.h>


#define BIT_BITS                                                        \
  (CHAR_BIT * sizeof(lua_Integer) > BITLIB_FLOAT_BITS ?                 \
   BITLIB_FLOAT_BITS : (CHAR_BIT * sizeof(lua_Integer)))


#ifdef BUILTIN_CAST
/* FIXME: Should really use limits of lua_Integer (currently not given
   by Lua); the code below assumes that lua_Integer is ptrdiff_t, that
   size_t is the same as unsigned ptrdiff_t, that lua_Integer fits in
   a long (constants) and that lua_Number is floating-point and fits
   in a double (use of fmod). */
#define TOINTEGER(L, n, f)                      \
  ((void)(f), luaL_checkinteger((L), (n)))
#else
#include <stdint.h>
#include <math.h>
#include "bit_limits.h"

/* This code may give warnings if BITLIB_FLOAT_* are too big to fit in
   long, but that doesn't matter since in that case they won't be
   used. */
#define BIT_MAX                                                         \
  (CHAR_BIT * sizeof(lua_Integer) > BITLIB_FLOAT_BITS ? BITLIB_FLOAT_MAX : PTRDIFF_MAX)

#define BIT_MIN                                                         \
  (CHAR_BIT * sizeof(lua_Integer) > BITLIB_FLOAT_BITS ? BITLIB_FLOAT_MIN : PTRDIFF_MIN)

#define BIT_UMAX                                                        \
  (CHAR_BIT * sizeof(lua_Integer) > BITLIB_FLOAT_BITS ? BITLIB_FLOAT_UMAX : SIZE_MAX)

#define TOINTEGER(L, n, f)                                              \
  ((ptrdiff_t)(((f) = fmod(luaL_checknumber((L), (n)), (double)BIT_UMAX + 1.0)), \
               (f) > BIT_MAX ? ((f) -= (double)BIT_UMAX + 1) :          \
               ((f) < BIT_MIN ? ((f) += (double)BIT_UMAX + 1) : (f))))
#endif

#define TDYADIC(name, op, ty)                             \
  static int bit_ ## name(lua_State *L) {                 \
    lua_Number f;                                         \
    lua_Integer w = TOINTEGER(L, 1, f);                   \
    lua_pushinteger(L, (ty)w op TOINTEGER(L, 2, f));      \
    return 1;                                             \
  }

#define MONADIC(name, op)                                 \
  static int bit_ ## name(lua_State *L) {                 \
    lua_Number f;                                         \
    lua_pushinteger(L, op TOINTEGER(L, 1, f));            \
    return 1;                                             \
  }

#define VARIADIC(name, op)                      \
  static int bit_ ## name(lua_State *L) {       \
    lua_Number f;                               \
    int n = lua_gettop(L), i;                   \
    lua_Integer w = TOINTEGER(L, 1, f);         \
    for (i = 2; i <= n; i++)                    \
      w op TOINTEGER(L, i, f);                  \
    lua_pushinteger(L, w);                      \
    return 1;                                   \
  }

MONADIC(cast,    +)
MONADIC(bnot,    ~)
VARIADIC(band,   &=)
VARIADIC(bor,    |=)
VARIADIC(bxor,   ^=)
TDYADIC(lshift,  <<, lua_Integer)
TDYADIC(rshift,  >>, size_t)
TDYADIC(arshift, >>, lua_Integer)

static const struct luaL_reg bitlib[] = {
  {"cast",    bit_cast},
  {"bnot",    bit_bnot},
  {"band",    bit_band},
  {"bor",     bit_bor},
  {"bxor",    bit_bxor},
  {"lshift",  bit_lshift},
  {"rshift",  bit_rshift},
  {"arshift", bit_arshift},
  {NULL, NULL}
};

LUALIB_API int luaopen_bit (lua_State *L) {
  luaL_register(L, "bit", bitlib);
  lua_pushnumber(L, BIT_BITS);
  lua_setfield(L, -2, "bits");
  return 1;
}
