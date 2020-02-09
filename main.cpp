#include "gpio.hpp"

using namespace stm32f7;

int main() {
    auto gpioi = GPIOI{};
    constexpr auto n = 1;

    gpioi.write<gpio::pin<n>::mode::output>();
    gpioi.write<gpio::pin<n>::set>();

    while(1){}
}

struct startup {
    uint32_t stack_pointer;
    uint32_t entry_point;
};
__attribute__((section(".startup"))) startup _ {
    .stack_pointer = 0x20050000,
    .entry_point = reinterpret_cast<uint32_t>(main)
};
