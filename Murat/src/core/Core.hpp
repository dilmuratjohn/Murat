//
// Created by Murat on 2019/8/25.
//

#ifndef M_CORE_HPP
#define M_CORE_HPP

#include <memory>

#define MURAT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Murat {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

}

#endif //APPLICATION_CORE_HPP
