## Version 3.0

* Moved to c++17 as minimum supported standard c++ version.
* Renamed luabridge::Nil to luabridge::LuaNil to allow including LuaBridge in Obj-C sources.
* Removed the limitation to 8 parameters in functions.
* Removed the limitation to 8 parameters in constructors.
* Allow specifying a non virtual base class method when declaring a class function not exposed in the inherited class
* Fixed unaligned access in user allocated member pointers in 64bit machines reported by ASAN.
* Added single header amalgamated distribution file, to simplify including in projects.
* Removed juce traces from unit tests, simplified unit tests run.
* Bumped unit tests from lua 5.2.0 to 5.2.4.
* Added unit tests against lua 5.3.6 and 5.4.1.
* Added more asserts for functions and property names
* Small improvements to code and doxygen comments readability.

## Version 2.6

* Added namespace `addFunction()` accepting `std::function` (C++11 only).
* Added class `addStaticFunction()` accepting `std::function` (C++11 only).
* Update the Doxygen documentation.
* Add brief API reference into the manual.
* Hide non-public `luabridge` members into the `detail` namespace.
* Fix stack cleanup by `LuaRef::isInstance()` method.

## Version 2.5

* Introduce stack `isInstance()` method.
* Introduce LuaRef `isInstance()` method.
* Added a convenience `isInstance()` function template.

## Version 2.4.1

* Do not call the object destructor then its constructor throws.

## Version 2.4

* String stack get specialization doesn't change the stack value anymore.
* Added namespace `addProperty()` accepting C-functions.
* Introduce enableExceptions function.

## Version 2.3.2

* Fixed registration continuation for an already registered class.

## Version 2.3.1

* Fixed registration continuation issues.

## Version 2.3

* Added class `addFunction()` accepting proxy functions (C++11 only).
* Added class `addFunction()` accepting `std::function` (C++11 only).
* Added class `addProperty()` accepting functions with lua_State* parameter.
* Added class `addProperty()` accepting `std::function` (C++11 only).
* Added stack traits for `std::unordered_map` (`UnorderedMap.h`).
* Now using lightuserdata for function pointers.

## Version 2.2.2

* Performance optimization.

## Version 2.2.1

* Refactored namespace and class handling.

## Version 2.2

* Refactored stack operations.
* Handle exceptions in stack operations.

## Version 2.1.2

* Added `operator==` and `operator!=` for `RefCountedPtr` template.

## Version 2.1.1

* Support for `__stdcall` function pointers.

## Version 2.1

* Added stack traits for `std::vector` (`Vector.h`).
* Added stack traits for `std::list` (`List.h`).
* Added stack traits for `std::map` (`Map.h`).
* Added ability to use `LuaRef` objects as an `std::map` keys.
* Fixed some manual errata.

## Version 2.0

* Numerous bug fixes.
* Feature Requests from Github issues.
* Added `LuaRef` object.
* Rewritten documentation.

## Version 1.1.0

* Split code up into several files.
* Add Lua table and type representations (based on Nigel's code).
* Reformat documentation as external HTML file.

## Version 1.0.3

* Pass `nil` to Lua when a null pointer is passed for objects with shared lifetime.

## Version 1.0.2

* Option to hide metatables selectable at runtime, default to true.
* `addStaticMethod()` renamed to `addStaticFunction()` for consistency.
* `addMethod()` renamed to `addFunction()` for consistency.
* `addCFunction()` registrations.
* Convert null pointers to and from `nil`.
* Small performance increase in class pointer extraction.

## Version 1.0.1

* Backward compatibility with Lua 5.1.x.

## Version 1.0

* Explicit lifetime management models.
* Generalized containers.
* Single header distribution.
