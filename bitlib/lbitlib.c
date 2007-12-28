/* Bitwise operations library */
/* (c) Reuben Thomas 2000-2007 */
/* See README for license */

#include <lauxlib.h>
#include <lua.h>

#define TDYADIC(name, op)                                               \
  static int bit_ ## name(lua_State *L) {                               \
    lua_pushinteger(L, luaL_checkinteger(L, 1) op luaL_checkinteger(L, 2)); \
    return 1;                                                           \
  }

#define MONADIC(name, op)                               \
  static int bit_ ## name(lua_State *L) {               \
    lua_pushinteger(L, op luaL_checkinteger(L, 1));     \
    return 1;                                           \
  }

#define VARIADIC(name, op)                      \
  static int bit_ ## name(lua_State *L) {       \
    int n = lua_gettop(L), i;                   \
    lua_Integer w = luaL_checkinteger(L, 1);    \
    for (i = 2; i <= n; i++)                    \
      w op luaL_checkinteger(L, i);             \
    lua_pushinteger(L, w);                      \
    return 1;                                   \
  }

MONADIC(cast,    +)
MONADIC(bnot,    ~)
VARIADIC(band,   &=)
VARIADIC(bor,    |=)
VARIADIC(bxor,   ^=)
TDYADIC(lshift,  <<)
TDYADIC(rshift,  >>)
TDYADIC(arshift, >>)

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
  luaL_openlib(L, "bit", bitlib, 0);
  return 1;
}
