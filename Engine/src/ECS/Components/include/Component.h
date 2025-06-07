#pragma once

namespace Planets {

    class Component
    {
    public:
        virtual ~Component() = default;
        virtual void update() = 0;
    };

}
