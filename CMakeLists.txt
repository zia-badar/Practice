cmake_minimum_required(VERSION 3.13)
project(Practice)

set(CMAKE_CXX_STANDARD 14)

# algorithms
add_executable(dijkstra tests/algorithms/dijkstra.cpp)
add_executable(kruskal tests/algorithms/kruskal.cpp)
add_executable(order_statistic tests/algorithms/order_statistic)
add_executable(sorting tests/algorithms/sorting.cpp)
add_executable(union_find tests/algorithms/union_find.cpp)

# datastructures
add_executable(avl tests/datastructures/avl.cpp)
add_executable(binary_index_tree tests/datastructures/binary_index_tree.cpp)
add_executable(binomial_heap tests/datastructures/binomial_heap.cpp)
add_executable(dynamic_heap tests/datastructures/dynamic_heap.cpp)
add_executable(hashamp tests/datastructures/hashmap.cpp)
add_executable(heap tests/datastructures/heap.cpp)
add_executable(linklist tests/datastructures/linklist.cpp)
add_executable(queue tests/datastructures/queue.cpp)
add_executable(segmented_tree tests/datastructures/segmented_tree.cpp)
add_executable(stack tests/datastructures/stack.cpp)

# problems
add_executable(problem1 tests/problems/problem1.cpp)
add_executable(problem2 tests/problems/problem2.cpp)
add_executable(problem3 tests/problems/problem3.cpp)
add_executable(problem4 tests/problems/problem4.cpp)

add_executable(test test.cpp)

#to do check hashmap
