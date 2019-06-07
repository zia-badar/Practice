cmake_minimum_required(VERSION 3.13)
project(Practice)

set(CMAKE_CXX_STANDARD 14)

add_executable(dijkstra tests/dijkstra.cpp)
add_executable(sorting tests/sorting.cpp)
add_executable(union_find tests/union_find.cpp)

add_executable(avl tests/avl.cpp)
add_executable(binary_index_tree tests/binary_index_tree.cpp)
add_executable(dynamic_heap tests/dynamic_heap.cpp)
add_executable(hashamp tests/hashmap.cpp)
add_executable(heap tests/heap.cpp)
add_executable(kruskal tests/kruskal.cpp)
add_executable(linklist tests/linklist.cpp)
add_executable(order_statistic tests/order_statistic)
add_executable(queue tests/queue.cpp)
add_executable(segmented_tree tests/segmented_tree.cpp)
add_executable(stack tests/stack.cpp)

add_executable(test test.cpp)

#to do check hashmap
