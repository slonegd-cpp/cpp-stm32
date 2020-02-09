#pragma once

#include "periph.hpp"
#include "rcc.hpp"

namespace stm32f7::gpio {

template<int n>
struct pin {

    enum class mode { input, output, alternate, analog, mask = 0b11 << (n * 2) };

    enum class set_t { mask = 0b1 << n };
    static constexpr auto set = set_t::mask;

    enum class reset_t { mask = 0b1 << (n + 16) };
    static constexpr auto reset = reset_t::mask;
};

} // namespace stm32f7::gpio {

namespace stm32f7::gpio::registers {

template<auto i> struct mode  { static constexpr auto value = type_pack<typename pin<i>::mode>{}; };
template<auto i> struct set   { static constexpr auto value = type_pack<typename pin<i>::set_t>{}; };
template<auto i> struct reset { static constexpr auto value = type_pack<typename pin<i>::reset_t>{}; };

struct moder {
    static constexpr std::size_t offset = 0x0;
    static constexpr auto params = generate_type_pack<mode, 16>();
};

struct bsrr {
    static constexpr std::size_t offset = 0x18;
    static constexpr auto params = 
          generate_type_pack<set, 16>()
        + generate_type_pack<reset, 16>();
};

} // namespace stm32f7::gpio::registers


namespace stm32f7 {

template<class meta>
struct GPIO final : periph<
      meta
    , gpio::registers::moder
    , gpio::registers::bsrr
>{
    GPIO() { RCC{}.write<meta::clock::enable>(); };
};

struct GPIOI_meta {
    static constexpr std::size_t address = 0x4002'2000;
    using clock = rcc::gpioi;
};

using GPIOI = GPIO<GPIOI_meta>;

} // namespace stm32f7 {


