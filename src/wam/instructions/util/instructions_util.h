//
// Created by leonhard on 29.07.19.
//

#ifndef PROLOG_BFS_INSTRUCTIONS_UTIL_H
#define PROLOG_BFS_INSTRUCTIONS_UTIL_H

#include "../../data/regist.h"
#include "../../executor/executor.h"

namespace wam{
    size_t deref(const executor& exec,const regist& init_regist);
    size_t deref(const executor& exec, size_t heap_i);
}
#endif //PROLOG_BFS_INSTRUCTIONS_UTIL_H
