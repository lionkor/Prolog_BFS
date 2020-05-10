//
// Created by leonhard on 08.05.20.
//

#ifndef PROLOG_BFS_EXPR_EVALUATOR_H
#define PROLOG_BFS_EXPR_EVALUATOR_H

#include <wam/executor/executor.h>

namespace wam::arithmetic{
    int eval_int_expr(executor& exec, const heap_reg& expr);

    int eval_int_sum(executor& exec, const node& sum);
    int eval_int_product(executor& exec, const node& prod);
    int eval_int_power(executor& exec, const node& power);
    int eval_int_value(executor& exec, const node& value);
}

#endif //PROLOG_BFS_EXPR_EVALUATOR_H
