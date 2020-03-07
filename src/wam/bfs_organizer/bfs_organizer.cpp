//
// Created by leonhard on 29.07.19.
//

#include "bfs_organizer.h"
#include "../visual/substitution_util.h"
#include "../compiler/compiler.h"
#include "util/read_program_code.h"
#include "../compiler/parser/parser.h"

void wam::bfs_organizer::load_program_from_file(const std::string_view file_path) {
    auto code = read_file(file_path);
    load_term_lines(code);
}

void wam::bfs_organizer::load_program(const std::string_view code) {
    return load_term_lines(code);
}

void wam::bfs_organizer::load_term_lines(const std::string_view code) {
    program_code = wam::compile_program(code);

    functor_index_map.reserve(program_code.size());
    functors.reserve(program_code.size());

    std::for_each(program_code.cbegin(), program_code.cend(),[&](const auto& it){
        //it->first is the head_functor

        //if the head_functor is already added simply return
        if(functor_index_map.find(it.first) != functor_index_map.cend()){
           return;
        }
        functor_index_map[it.first] = functors.size();
        functors.push_back(it.first);
    });
}


std::optional<std::vector<wam::var_substitution>> wam::bfs_organizer::get_answer() {
    while (!executors.empty()) {
        executor* next_exec = executors.front();
        executors.pop_front();

        if (next_exec->term_codes.empty()) {
            auto substitutes = find_substitutions(*next_exec);
            return substitutes;
        }

        term_code *next_term_code = next_exec->term_codes.top();
        //Let the exec save, what he has done :)
        next_exec->solves_term_code = next_term_code;
        next_exec->term_codes.pop();

        next_exec->registers.resize(next_term_code->expected_register_count);
        //*2 is a heuristic
        next_exec->heap.reserve(next_term_code->expected_register_count * 2);

        for (const auto &instruction : next_term_code->instructions) {
            instruction(*next_exec);
            //if the executor fails we stop executing
            if (next_exec->fail) {
                break;
            }
        }
    }

    //no more executor
    return std::nullopt;
}


void wam::bfs_organizer::load_query(const std::string &query_line) {
    //Clear the old executors
    executors.clear();
    //parse the query and save the results
    current_query_code = compile_query(query_line);

    init_executor = executor{};
    //Copy references to query instructions into the executor instructions
    std::for_each(current_query_code.rbegin(), current_query_code.rend(),
                  [&](term_code &term_code) {
                      init_executor.term_codes.push(&term_code);
                  });
    init_executor.organizer = this;
    executors.push_back(&init_executor);
}

void wam::bfs_organizer::clear(){
    executors.clear();
    functor_index_map.clear();
    functors.clear();
    program_code.clear();
    current_query_code.clear();
}

wam::parser_error wam::bfs_organizer::validate_program(const std::string_view code) {
//TODO the code uses the parser code, a simple syntax checker would be good enough here
    try{
        std::vector<boost::optional<node>> parser_result;
        parse_program(code, parser_result);
        return parser_error{};
    }catch(const parser_error& e){
        return e;
    }
}

wam::parser_error wam::bfs_organizer::validate_query(const std::string_view code) {
//TODO the code uses the parser code, a simple syntax checker would be good enough here
    try{
        std::vector<node> query_nodes; //= compiler result
        parse_query(code, query_nodes);
        return parser_error{};
    }catch(const parser_error& e){
        return e;
    }
}

std::vector<wam::var_substitution> wam::bfs_organizer::find_substitutions(const wam::executor& executor) {
    std::vector<wam::var_substitution> result;
    //normally user have 1 to 5 vars in their queries. so using vector should be more efficient than set

    //This exec is an empty executor. According to impl of proceed instruction, the father will have
    //unified a term. So we can skip this exec and his father

    const wam::executor* parent = &executor.get_parent();
    parent = &parent->get_parent();
    while(true){
        if(parent->is_from_user_entered_query()){
            auto var_heap_subs = wam::point_var_reg_substs_to_heap(parent);
            for(const auto& var_heap_sub : var_heap_subs){
                if(std::find_if(result.begin(), result.end(),
                        [&](const var_substitution& var_subst){
                    return var_subst.var_name == var_heap_sub.var_name;
                }) != result.end()){
                    continue;
                }

                result.emplace_back(
                                var_heap_sub.var_name,
                                wam::string_representation_of(executor, var_heap_sub.heap_index, functors)
                );
            }
        }
        if(!parent->has_parent()){
            break;
        }

        //Its always: query_exec --> fact_exec --> query_exec -->fact_exec ...
        //So we can skip the fact execs
        parent = &parent->get_parent();
        parent = &parent->get_parent();
    }
    return result;
}
