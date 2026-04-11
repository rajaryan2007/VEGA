#pragma once

namespace VEGA::Debug
{
    // Small allocation churn to verify Tracy allocation events.
    void RunMemoryProfilingSmokeTest();

    // Tiny GL workload wrapped in Tracy GPU zone.
    void RunGpuProfilingSmokeTest();
}
