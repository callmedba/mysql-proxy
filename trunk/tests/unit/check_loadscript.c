/* Copyright (C) 2007, 2008 MySQL AB */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LUA_H
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

#include "lua-scope.h"

#if GLIB_CHECK_VERSION(2, 16, 0)
#define C(x) x, sizeof(x) - 1

#define START_TEST(x) void (x)(void)
#define END_TEST
/**
 * Tests for the Lua script loading facility
 * @ingroup Core
 */

/*@{*/

/**
 * @test luaL_loadfile_factory()
 *
 */
START_TEST(test_luaL_loadfile_factory) {
#ifdef HAVE_LUA_H
	lua_scope *sc = lua_scope_init();
	g_assert(sc->L != NULL);
	
	/* lua_scope_load_script used to give a bus error, when supplying a non-existant script */
	lua_scope_load_script(sc, "/this/is/not/there.lua");
	g_assert(lua_isstring(sc->L, -1));		/* if it's a string, loading failed. exactly what we expect */
	lua_pop(sc->L, 1);
	lua_scope_free(sc);
#else
	g_assert(1 != 0);	/* always succeeds */
#endif
} END_TEST


/*@}*/

int main(int argc, char **argv) {
#ifdef HAVE_GTHREAD	
	g_thread_init(NULL);
#endif

	g_test_init(&argc, &argv, NULL);
	g_test_bug_base("http://bugs.mysql.com/");

	g_test_add_func("/core/lua-load-factory", test_luaL_loadfile_factory);

	return g_test_run();
}
#else
int main() {
	return 77;
}
#endif
