#include "vgpch.h"
#include "MemoryProfile.h"

#if VG_PROFILE
#include <Glad/glad.h>
#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>
#include <array>
#include <cstdlib>
#include <new>
#include <vector>

namespace VEGA::Debug
{
    void RunMemoryProfilingSmokeTest()
    {
        VG_PROFILE_SCOPE("Debug::RunMemoryProfilingSmokeTest");

        std::vector<std::vector<int>> blocks;
        blocks.reserve(64);
        for (int i = 0; i < 64; ++i)
        {
            blocks.emplace_back(2048 + i * 64, i);
        }
    }

    void RunGpuProfilingSmokeTest()
    {
        VG_PROFILE_SCOPE("Debug::RunGpuProfilingSmokeTest");
        VG_GPU_ZONE("Debug::GPU Smoke");

        std::array<float, 4> clearColor = { 0.08f, 0.08f, 0.1f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, clearColor.data());
        glFinish();
        VG_GPU_COLLECT;
    }
}

#if VG_TRACY_MEMORY_TRACKING
void* operator new(std::size_t count)
{
    auto ptr = malloc(count);
    if (!ptr)
        throw std::bad_alloc{};
    TracyAlloc(ptr, count);
    return ptr;
}

void operator delete(void* ptr) noexcept
{
    TracyFree(ptr);
    free(ptr);
}

void* operator new[](std::size_t count)
{
    auto ptr = malloc(count);
    if (!ptr)
        throw std::bad_alloc{};
    TracyAlloc(ptr, count);
    return ptr;
}

void operator delete[](void* ptr) noexcept
{
    TracyFree(ptr);
    free(ptr);
}

void operator delete(void* ptr, std::size_t) noexcept
{
    TracyFree(ptr);
    free(ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept
{
    TracyFree(ptr);
    free(ptr);
}

void* operator new(std::size_t count, const std::nothrow_t&) noexcept
{
    auto ptr = malloc(count);
    if (ptr)
        TracyAlloc(ptr, count);
    return ptr;
}

void* operator new[](std::size_t count, const std::nothrow_t&) noexcept
{
    auto ptr = malloc(count);
    if (ptr)
        TracyAlloc(ptr, count);
    return ptr;
}
#endif
#else
namespace VEGA::Debug
{
    void RunMemoryProfilingSmokeTest() {}
    void RunGpuProfilingSmokeTest() {}
}
#endif
