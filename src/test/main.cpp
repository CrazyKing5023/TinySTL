#include <iostream>


#include "vector_test.h"
int main() {
    using namespace tinystl::test;

    std::cout.sync_with_stdio(false);


    RUN_ALL_TESTS();
    //vector_test::vector_test();
    return 0;
}