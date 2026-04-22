#pragma once

#include <xhash>

namespace UHE {
	class UUID
	{
    public:
        UUID();
        UUID(u64 uuid);
        UUID(const UUID &other) = default;
    
        operator u64() const { return m_UUID; }
    private:
        u64 m_UUID;
	};
}

namespace std 
{
    template<>
    struct hash<UHE::UUID>
        {
        size_t operator()(const UHE::UUID& uuid) const
        {
            return hash<u64>()((u64)uuid);
        }
    };
}
