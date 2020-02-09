#pragma once

#include "type_pack.hpp"

constexpr auto shift(std::size_t mask) {
   return __builtin_ffs(mask) - 1;
}

template<class Register, class Arg>
constexpr std::size_t arg_value(type_identity<Register>, Arg arg) {
    // значение вычисляется только, если аргумент соотвествует регистру
    if constexpr (not Register::params.contains(type_identity<Arg>{}))
        return 0;

    constexpr auto mask = static_cast<std::size_t>(Arg::mask);
    constexpr auto arg_shift = shift(mask);
    return static_cast<std::size_t>(arg) << arg_shift;
}

template<class Register, class Arg>
constexpr std::size_t arg_mask(type_identity<Register>, Arg arg) {
    // значение вычисляется только, если аргумент соотвествует регистру
    if constexpr (not Register::params.contains(type_identity<Arg>{}))
        return 0;

    return static_cast<std::size_t>(Arg::mask);
}

template<class Register, class...Args>
constexpr std::size_t register_value(type_identity<Register> reg, Args...args) {
   return (arg_value(reg, args) | ...);
}

template<class Register, class...Args>
constexpr std::size_t register_mask(type_identity<Register> reg, Args...args) {
   return (arg_mask(reg, args) | ...);
}

struct value {
    size_t mask;
    size_t data;
    size_t offset;
};

template<class...Registers, class...Args>
constexpr auto extract(type_pack<Registers...> registers, Args...args) {

    constexpr auto args_types = type_pack<Args...>{};
    
    static_assert(args_types.all_of([=](auto arg){
        return registers.any_of([=](auto reg){
            return decltype(reg)::type::params.contains(arg);
        });
    }), "one of arguments in set method don`t belong to periph type");
    
    constexpr auto registers_for_write = registers.filter([=](auto reg){
        return args_types.any_of([](auto arg){
            return decltype(reg)::type::params.contains(arg);
        });
    });

    return registers_for_write.to_array([=](auto reg){
        return value {
              register_mask(reg, args...)
            , register_value(reg, args...)
            , decltype(reg)::type::offset
        };
    });
};

inline void write(std::size_t address, std::size_t v) {
   *reinterpret_cast<std::size_t*>(address) = v;
}

inline void update(std::size_t address, std::size_t v, std::size_t mask) {
    auto tmp = *reinterpret_cast<std::size_t*>(address);
    tmp &= ~mask;
    tmp |= v;
   *reinterpret_cast<std::size_t*>(address) = tmp;
}

inline void set(std::size_t address, std::size_t v, std::size_t mask) {
   *reinterpret_cast<std::size_t*>(address) |= v;
}

template<class meta, class...Registers>
struct periph {
    static constexpr auto registers = type_pack<Registers...>{};
    
    // просто в запись в регистр значений, игнорирует то, что там было
    template<auto...args>
    static void write() {
        constexpr auto values_for_write = extract(registers, args...);
        for (auto [_, value, offset] : values_for_write) {
            ::write(meta::address + offset, value);
        }
    }

    // обновляет значения в регистрах, не трогая остальные (для обновления предыдущих ненулевых значений)
    template<auto...args>
    static void update() {
        constexpr auto values_for_write = extract(registers, args...);
        for (auto [mask, value, offset] : values_for_write) {
            ::update(meta::address + offset, value, mask);
        }
    }

    // устанавливает значения в регистры, не трогая остальные (для инициализации)
    template<auto...args>
    static void set() {
        constexpr auto values_for_write = extract(registers, args...);
        for (auto [_, value, offset] : values_for_write) {
            ::set(meta::address + offset, value);
        }
    }
};

