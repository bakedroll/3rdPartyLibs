// https://github.com/kunitoki/LuaBridge
// Copyright 2020, Lucio Asnaghi
// Copyright 2012, Vinnie Falco <vinnie.falco@gmail.com>
// Copyright 2007, Nathan Reed
// SPDX-License-Identifier: MIT

#pragma once

#include "Config.h"

#include <cassert>
#include <utility>

namespace luabridge {

// These are for Lua versions prior to 5.2.0.

#if LUA_VERSION_NUM < 502
inline int lua_absindex(lua_State* L, int idx)
{
    if (idx > LUA_REGISTRYINDEX && idx < 0)
        return lua_gettop(L) + idx + 1;
    else
        return idx;
}

inline void lua_rawgetp(lua_State* L, int idx, void const* p)
{
    idx = lua_absindex(L, idx);
    lua_pushlightuserdata(L, const_cast<void*>(p));
    lua_rawget(L, idx);
}

inline void lua_rawsetp(lua_State* L, int idx, void const* p)
{
    idx = lua_absindex(L, idx);
    lua_pushlightuserdata(L, const_cast<void*>(p));
    // put key behind value
    lua_insert(L, -2);
    lua_rawset(L, idx);
}

#define LUA_OPEQ 1
#define LUA_OPLT 2
#define LUA_OPLE 3

inline int lua_compare(lua_State* L, int idx1, int idx2, int op)
{
    switch (op)
    {
    case LUA_OPEQ:
        return lua_equal(L, idx1, idx2);
        break;

    case LUA_OPLT:
        return lua_lessthan(L, idx1, idx2);
        break;

    case LUA_OPLE:
        return lua_equal(L, idx1, idx2) || lua_lessthan(L, idx1, idx2);
        break;

    default:
        return 0;
    };
}

inline int get_length(lua_State* L, int idx)
{
    return int(lua_objlen(L, idx));
}

#else
inline int get_length(lua_State* L, int idx)
{
    lua_len(L, idx);
    int len = int(luaL_checknumber(L, -1));
    lua_pop(L, 1);
    return len;
}

#endif

#ifndef LUA_OK
#define LUABRIDGE_LUA_OK 0
#else
#define LUABRIDGE_LUA_OK LUA_OK
#endif

/**
 * @brief Get a table value, bypassing metamethods.
 */
inline void rawgetfield(lua_State* L, int index, char const* key)
{
    assert(lua_istable(L, index));
    index = lua_absindex(L, index);
    lua_pushstring(L, key);
    lua_rawget(L, index);
}

/**
 * @brief Set a table value, bypassing metamethods.
 */
inline void rawsetfield(lua_State* L, int index, char const* key)
{
    assert(lua_istable(L, index));
    index = lua_absindex(L, index);
    lua_pushstring(L, key);
    lua_insert(L, -2);
    lua_rawset(L, index);
}

/**
 * @brief Returns true if the value is a full userdata (not light).
 */
inline bool isfulluserdata(lua_State* L, int index)
{
    return lua_isuserdata(L, index) && !lua_islightuserdata(L, index);
}

/**
 * @brief Test lua_State objects for global equality.
 *
 * This can determine if two different lua_State objects really point
 * to the same global state, such as when using coroutines.
 * 
 * @note This is used for assertions.
 */
inline bool equalstates(lua_State* L1, lua_State* L2)
{
    return lua_topointer(L1, LUA_REGISTRYINDEX) == lua_topointer(L2, LUA_REGISTRYINDEX);
}

/**
 * @brief Return an aligned pointer of type T.
 */
template <class T>
T* align(void* ptr) noexcept
{
    auto address = reinterpret_cast<size_t>(ptr);

    auto offset = address % alignof(T);
    auto aligned_address = (offset == 0) ? address : (address + alignof(T) - offset);

    return reinterpret_cast<T*>(aligned_address);
}

/**
 * @brief Return the space needed to align the type T on an unaligned address.
 */
template <class T>
size_t maximum_space_needed_to_align() noexcept
{
    return sizeof(T) + alignof(T) - 1;
}

/**
 * @brief Allocate lua userdata taking into account alignment.
 *
 * Using this instead of lua_newuserdata directly prevents alignment warnings on 64bits platforms.
 */
template <class T, class... Args>
void* lua_newuserdata_aligned(lua_State* L, Args&&... args)
{
    void* pointer = lua_newuserdata(L, maximum_space_needed_to_align<T>());
    T* aligned = align<T>(pointer);
    new (aligned) T(std::forward<Args>(args)...);
    return pointer;
}

} // namespace luabridge
