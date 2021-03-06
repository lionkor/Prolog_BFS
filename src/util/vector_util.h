//
// Created by leonhard on 03.08.19.
//

#ifndef PROLOG_BFS_VECTOR_UTIL_H
#define PROLOG_BFS_VECTOR_UTIL_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

namespace std{
    template<typename Out, typename T>
    Out& operator<< (Out& out, const std::vector<T>& v) {
        using std::vector;
        using std::ostream;
        out << "[";
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>{out, " "});
        out << "]";
        return out;
    }
}
#endif //PROLOG_BFS_VECTOR_UTIL_H
