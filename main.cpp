#include <cstdint> // uintptr_t

int main() {
    volatile auto i{0};
    while (1) {
        i++;
    }
}

struct startup {
    uintptr_t stack_pointer;
    uintptr_t entry_point;
};
__attribute__((section(".startup"))) startup _ {
    .stack_pointer = 0x20050000,
    .entry_point = reinterpret_cast<uintptr_t>(main)
};