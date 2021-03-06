//
// Created by leonhard on 27.07.19.
//

#ifndef PROLOG_BFS_INSTRUCTIONS_H
#define PROLOG_BFS_INSTRUCTIONS_H

#include "../executor/executor.h"

namespace wam {
    void put_structure(executor& executor, heap_reg structure, size_t regist_index);
    void get_structure(executor& executor, heap_reg structure, size_t x_reg);

    void set_variable(executor& executor , size_t x_reg, short var_index);
    void set_permanent_variable(executor& executor , size_t y_reg, short var_index);

    void set_value(executor& executor,size_t x_reg);
    void set_permanent_value(executor& executor, size_t y_reg);

    void get_eval_fun_structure(executor &executor, int eval_fun_i, size_t x_reg);
    void get_functor(executor& executor, int functor, size_t x_reg);
    void get_int(wam::executor &executor, int value, size_t x_reg);
    void get_constant(executor& executor, int constant_i, size_t x_reg);

    void unify_variable(executor& executor,  size_t x_reg, short var_index);
    void unify_permanent_variable(executor& executor, size_t y_reg, short var_index);

    void unify_value(executor& executor, size_t x_reg);
    void unify_permanent_value(executor& executor, size_t y_reg);

    void unify_structure(wam::executor &executor, heap_reg structure, size_t x_reg);
    void unify(executor& executor, size_t addr_a, size_t addr_b);

    void put_variable(executor& executor, size_t x_reg, size_t a_reg, short var_index);
    void put_permanent_variable(executor& executor, size_t y_reg, size_t a_reg, short var_index);

    void put_value(executor& executor, size_t x_reg, size_t a_reg);
    void put_permanent_value(executor& executor, size_t y_reg, size_t a_reg);

    void get_variable(executor& executor, size_t x_reg, size_t a_reg);
    void get_permanent_variable(executor& executor, size_t y_reg, size_t a_reg);

    void get_value(executor& executor, size_t x_reg, size_t a_reg);
    void get_permanent_value(executor& executor, size_t y_reg, size_t a_reg);

    void call(wam::executor &old_executor, const functor_view &functor);
    void proceed(executor& old_exec);

    void allocate(executor& executor, size_t permanent_var_count);
    void deallocate(executor& executor);
}

#endif //PROLOG_BFS_INSTRUCTIONS_H
