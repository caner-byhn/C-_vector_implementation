#include <iostream>
#include "mytl_vector.h"


int main(int argc, char *argv[]) {
    mytl::vector<int> v1;

    v1.push_back(10);
    std::cout << v1[0] << "\n";
    v1.erase(v1.begin());
    std::cout << v1[0];

    return 0;
}
