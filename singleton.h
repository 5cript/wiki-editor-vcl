//---------------------------------------------------------------------------
#pragma once

#include <mutex>
//---------------------------------------------------------------------------
/**
 **/
template <typename T>
class Singleton
{
	friend T;

	Singleton(Singleton const&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton const&) = delete;
	Singleton& operator=(Singleton&&) = delete;

private:
    Singleton() {}
};
//---------------------------------------------------------------------------
#define SINGLETON_GLOBALS(NAME) \
class NAME; \
namespace SingletonGlobals ## NAME \
{ \
	extern NAME* inst; \
	extern std::once_flag onceFlag; \
}

#define SINGLETON_GLOBALS_DECLARATION(NAME) \
namespace SingletonGlobals ## NAME \
{ \
	NAME* inst; \
	std::once_flag onceFlag; \
}

#define SINGLETON_GLOBAL(NAME) SingletonGlobals ## NAME

#define SINGLETON_GET_INSTANCE(NAME) \
static NAME& getInstance() { \
	std::call_once(SINGLETON_GLOBAL(NAME)::onceFlag, [](){ \
		SINGLETON_GLOBAL(NAME)::inst = new NAME(); \
	}); \
	return *SINGLETON_GLOBAL(NAME)::inst; \
}

#define SINGLETON_CTOR(NAME) private: NAME()
//---------------------------------------------------------------------------
