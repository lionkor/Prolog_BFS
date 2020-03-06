//
// Created by leonhard on 05.07.19.
//

#ifndef PROLOG_BFS_COMPILER_H
#define PROLOG_BFS_COMPILER_H


#include <string>
#include <functional>
#include "util/node.h"
#include "../executor/executor.h"
#include "../data/term_code.h"
#include "../data/functor_view.h"
#include "util/seen_register.h"

namespace wam {

    std::pair<functor_view, std::vector<term_code>> compile_program_term(node& program_node);

    int assign_registers(node &functor, node* first_body_atom = nullptr);
    int assign_permanent_registers(std::vector<node> &nodes, bool program_term);

    std::vector<wam::var_reg_substitution>
    find_var_reg_substitutions(const node &atom);

    std::vector<const node *> flatten_program(const node &outer_functor);
    std::vector<const node *> flatten_query(const node &node);

    template<typename OutputIter>
    void
    to_query_instructions(const std::vector<const node *> &flattened_term, const node &outer_functor, OutputIter out,
                          std::unordered_map<wam::helper::seen_register, bool> &seen_registers);

    template<typename OutputIter>
    void to_program_instructions(const std::vector<const node *> &flattened_term, OutputIter out,
                                 std::unordered_map<wam::helper::seen_register,bool> &seen_regs);



    std::unordered_multimap<wam::functor_view, std::vector<wam::term_code>>
    compile_program(std::string_view program_code);
    /*
     * Parses a query term e.G. p(Z,h(Z,W),f(W))
     */
    std::vector<term_code> compile_query(std::string_view query_code);

    void compile_query_atom(node &atom,
                                 std::unordered_map<wam::helper::seen_register, bool> &seen_registers,
                                 std::vector<std::function<void(wam::executor &)>> &instructions,
                                 std::vector<term_code> &term_codes,
                                 bool from_original_query);
}


#endif //PROLOG_BFS_COMPILER_H
