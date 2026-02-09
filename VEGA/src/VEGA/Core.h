#pragma once

#include <memory>

#ifdef VG_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
      #ifdef VG_BUILD_DLL
             #define  VEGA_API __declspec(dllexport)
      #else
             #define VEGA_API __declspec(dllimport)
      #endif // HZ_BUILD_DLL
#else
#define VEGA_API
#endif // HZ_DYNAMIC_LINK
#else
       #error Vega only support Window!
#endif


#ifdef HZ_DEBUG
   #define HZ_ENABLE_ASSERTS
#endif


#ifdef VG_ENABLE_ASSERTS
   #define VG_ASSERT(x,...) {if(!x) {HZ_ERROR("assertion Failed :{0} ",__VA_ARGS__);__debugbreak();}}
   #define VG_CORE_ASSERT(x,...) {if(!x) {HZ_CORE_ERROR("assertion Failed :{0} ",__VA_ARGS__);__debugbreak();}}
#else 
   #define VG_ASSERT(x,...)
   #define VG_CORE_ASSERT(x,...)
#endif

#define BIT(x)(1<<x)

#define VG_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)


namespace VEGA {
    template<typename T>
    using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
    }
    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T,typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}