#include <cstdint> // uint32_t

class Register {
    using Pointer = volatile uint32_t*;
    Pointer pointer;

public:
    Register (uint32_t base, int offset) 
        : pointer { reinterpret_cast<Pointer>(base + offset) }
    {}

    void write (uint32_t v) { *pointer = v; }
};

int main() {
    auto constexpr rcc_base   = 0x4002'3800;
    auto constexpr gpioi_base = 0x4002'2000;

    auto ahb1enr =  Register (rcc_base, 0x30);
    ahb1enr.write(1 << 8);

    auto moder = Register (gpioi_base, 0);
    moder.write(1 << (1 * 2));

    auto bssr = Register (gpioi_base, 0x18);
    bssr.write(1 << 1);

    while(1) {}
}

struct startup {
    uint32_t stack_pointer;
    uint32_t entry_point;
};
__attribute__((section(".startup"))) startup _ {
    .stack_pointer = 0x20050000,
    .entry_point = reinterpret_cast<uint32_t>(main)
};