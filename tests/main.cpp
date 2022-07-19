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
    tester.addTest("vector", "vect_relation_op.cpp", true);

    tester.addTest("stack", "stack_constructor.cpp", true);
    tester.addTest("stack", "stack_empty.cpp", true);
    tester.addTest("stack", "stack_size.cpp", true);
    tester.addTest("stack", "stack_top.cpp", true);
    tester.addTest("stack", "stack_push_pop.cpp", true);
    tester.addTest("stack", "stack_relation_op.cpp", true);

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
    tester.addTest("map", "map_relation_op.cpp", true);

    tester.addTest("set", "set_constructor.cpp", true);
    tester.addTest("set", "set_operator=.cpp", true);
    tester.addTest("set", "set_begin_end.cpp", true);
    tester.addTest("set", "set_rbegin_rend.cpp", true);
    tester.addTest("set", "set_empty.cpp", true);
    tester.addTest("set", "set_size.cpp", true);
    tester.addTest("set", "set_max_size.cpp", true);
    tester.addTest("set", "set_insert.cpp", true);
    tester.addTest("set", "set_erase.cpp", true);
    tester.addTest("set", "set_swap.cpp", true);
    tester.addTest("set", "set_clear.cpp", true);
    tester.addTest("set", "set_key_comp.cpp", true);
    tester.addTest("set", "set_value_comp.cpp", true);
    tester.addTest("set", "set_find.cpp", true);
    tester.addTest("set", "set_count.cpp", true);
    tester.addTest("set", "set_lower_upper_bound.cpp", true);
    tester.addTest("set", "set_equal_range.cpp", true);
    tester.addTest("set", "set_relation_op.cpp", true);

    try
    {
        if (argc == 2)
#ifndef CMP
            tester.runCategory(argv[1]);
#else
            tester.compareCategoryTo(argv[1], "std");
#endif
        else if (argc == 3)
#ifndef CMP
            tester.runTest(argv[1], argv[2]);
#else
            tester.compareTo(argv[1], argv[2], "std");
#endif
        else if (argc == 1)
#ifndef CMP
            tester.runAll();
#else
            tester.compareAllTo("std");
#endif
        else
            std::cerr << "Bad args" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}