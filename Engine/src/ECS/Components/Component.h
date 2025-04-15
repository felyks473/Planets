#pragma once

namespace Planets {

    class Component
    {
    public:
        virtual ~Component() {}
        virtual void update() = 0;
    };

}
