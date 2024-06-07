#include "global.hpp"

auto ptr = UniquePtr<int>(5);

void UniquePointerTest() {
    cout << *ptr << endl;

    auto ptr2 = std::move(ptr);
    cout << *ptr2 << endl;
}