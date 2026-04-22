#include <iostream>
#include "mytl_vector.h"


int main(int argc, char *argv[]) {
    mytl::vector<int> v1;

    v1.resize(10);

    for (int i = 0; i < 10; i++) {
        std::cout << v1[i] << " ";
    }

    return 0;
}
