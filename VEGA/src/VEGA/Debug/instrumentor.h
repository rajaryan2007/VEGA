#pragma once


#ifndef VG_PROFILE
#define VG_PROFILE 1
#endif

#ifndef VG_TRACY_MEMORY_TRACKING
#define VG_TRACY_MEMORY_TRACKING 0
#endif
#if VG_PROFILE


#include <glad/glad.h>
#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>


#define VG_PROFILE_BEGIN_SESSION(name, filepath) // no-op
#define VG_PROFILE_END_SESSION()                 // no-op

#define VG_PROFILE_SCOPE(name) ZoneScopedN(name)
#define VG_PROFILE_FUNCTION() ZoneScoped


#define VG_PROFILE_FRAMEMARK FrameMark


#define VG_GPU_CONTEXT TracyGpuContext
#define VG_GPU_CONTEXT_NAME(n, s) TracyGpuContextName(n, s)
#define VG_GPU_ZONE(name) TracyGpuZone(name)
#define VG_GPU_COLLECT TracyGpuCollect

#else

#define VG_PROFILE_BEGIN_SESSION(name, filepath)
#define VG_PROFILE_END_SESSION()
#define VG_PROFILE_FUNCTION()
#define VG_PROFILE_SCOPE(name)

#define VG_PROFILE_FRAMEMARK

#define VG_GPU_CONTEXT
#define VG_GPU_CONTEXT_NAME(n, s)
#define VG_GPU_ZONE(name)
#define VG_GPU_COLLECT

#endif