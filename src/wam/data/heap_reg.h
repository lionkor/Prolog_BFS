//
// Created by leonhard on 27.07.19.
//

#ifndef PROLOG_BFS_HEAP_REG_H
#define PROLOG_BFS_HEAP_REG_H


#include "heap_tag.h"
#include <cstddef>

namespace wam {
    struct heap_reg {
        int index;
        short var_index;
        heap_tag type;

        heap_reg()= default;
        heap_reg(heap_tag type, int index): type{type}, index{index}{}
        heap_reg(int index, short var_index): type{heap_tag::REF}, index{index}, var_index{var_index}{}

        inline bool is_REF()const {
            return type == heap_tag::REF;
        }
        inline bool is_STR()const{
            return type == heap_tag ::STR;
        }
        inline bool is_FUN()const{
            return type == heap_tag ::FUN;
        }
        inline bool is_INT()const{
            return type == heap_tag ::INT;
        }
        inline bool is_EXPR()const{
            return type == heap_tag ::EXPR;
        }

        inline int get_int_val()const{
            assert(is_INT());
            return index;
        }

        inline int get_expr_i()const{
            assert(is_EXPR());
            return index;
        }

        inline void bind_to(int index){
            assert(is_REF());
            this->index = index;
        }

        std::string type_as_str();
    };
}



#endif //PROLOG_BFS_HEAP_REG_H