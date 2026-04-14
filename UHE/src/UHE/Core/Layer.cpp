#include "uhepch.h"
#include "UHE/Core/Layer.h"
namespace UHE {

    Layer::Layer(const std::string& debugName)
        : m_DebugName(debugName)
    {
    }

    Layer::~Layer() {}

}
