#pragma once

#include "Alisa/Core/Base.h"
#include "Alisa/Core/TimeStep.h"
#include "Alisa/Events/Event.h"

namespace Alisa
{
    class Layer
    {
    public:
        explicit Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(TimeStep ts) {}
        virtual void OnEvent(Event& e) {}

        const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
}
