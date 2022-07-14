#include "Tester.hpp"

int main(int argc, char **argv)
{
    Tester tester;

    tester.addTest("vector", "vect_constructor.cpp", true);
    tester.addTest("vector", "vect_operator=.cpp", true);
    tester.addTest("vector", "vect_begin_end.cpp", true);
    tester.addTest("vector", "vect_rbegin_rend.cpp", true);
    tester.addTest("vector", "vect_size.cpp", true);
    tester.addTest("vector", "vect_max_size.cpp", true);
    tester.addTest("vector", "vect_resize.cpp", true);
    tester.addTest("vector", "vect_capacity.cpp", true);
    tester.addTest("vector", "vect_empty.cpp", true);
    tester.addTest("vector", "vect_reserve.cpp", true);
    tester.addTest("vector", "vect_operator[].cpp", true);
    tester.addTest("vector", "vect_at.cpp", true);
    tester.addTest("vector", "vect_front.cpp", true);
    tester.addTest("vector", "vect_back.cpp", true);
    tester.addTest("vector", "vect_assign.cpp", true);
    tester.addTest("vector", "vect_push_back.cpp", true);
    tester.addTest("vector", "vect_pop_back.cpp", true);
    tester.addTest("vector", "vect_insert.cpp", true);
    tester.addTest("vector", "vect_erase.cpp", true);
    tester.addTest("vector", "vect_swap.cpp", true);
    tester.addTest("vector", "vect_clear.cpp", true);
    tester.addTest("vector", "vect_get_allocator.cpp", true);
    tester.addTest("vector", "vect_relation_op.cpp", true);

    tester.addTest("map", "map_constructor.cpp", true);
    tester.addTest("map", "map_operator=.cpp", true);
    tester.addTest("map", "map_begin_end.cpp", true);
    tester.addTest("map", "map_rbegin_rend.cpp", true);
    tester.addTest("map", "map_size.cpp", true);
    tester.addTest("map", "map_max_size.cpp", true);
    tester.addTest("map", "map_empty.cpp", true);
    tester.addTest("map", "map_operator[].cpp", true);
    tester.addTest("map", "map_insert.cpp", true);
    tester.addTest("map", "map_erase.cpp", true);
    tester.addTest("map", "map_swap.cpp", true);
    tester.addTest("map", "map_clear.cpp", true);
    tester.addTest("map", "map_key_comp.cpp", true);
    tester.addTest("map", "map_value_comp.cpp", true);
    tester.addTest("map", "map_find.cpp", true);
    tester.addTest("map", "map_count.cpp", true);
    tester.addTest("map", "map_lower_upper_bound.cpp", true);
    tester.addTest("map", "map_equal_range.cpp", true);
    tester.addTest("map", "map_get_allocator.cpp", true);
    tester.addTest("map", "map_relation_op.cpp", true);
    if (argc == 2)
        tester.runCategory(argv[1]);
    else if (argc == 3)
        tester.runTest(argv[1], argv[2]);
    else
        tester.runAll();
    return (0);
}