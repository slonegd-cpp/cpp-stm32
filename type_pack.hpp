#include <cstdint> // std::size_t
#include <type_traits> // std::is_same
#include <array>

template <class T>
struct type_identity { 
    using type = T;

    template <class U>
    constexpr auto operator== (type_identity<U>) const { return std::is_same_v<T,U>; }
};

template <class...Ts>
struct type_pack {
    template <class...Us>
    constexpr auto operator+ (type_pack<Us...>) const { 
        return type_pack<Ts..., Us...>{}; 
    }

    template <class F>
    constexpr auto all_of(F f) const {
        return (f(type_identity<Ts>{}) and ...);
    }

    template <class F>
    constexpr auto any_of(F f) const {
        return (f(type_identity<Ts>{}) or ...);
    }

    template <class F>
    constexpr auto filter(F f) const {
        auto filter_one = [](auto v, auto f) {
            using T = typename decltype(v)::type;
            if constexpr (f(v))
                return type_pack<T>{};
            else
                return type_pack<>{};
        };
        return (type_pack<>{} + ... + filter_one(type_identity<Ts>{}, f));
    }

    template <class T>
    constexpr auto contains(type_identity<T> v) const { 
        return ((type_identity<Ts>{} == v) or ...); 
    }

    template <class F>
    constexpr auto to_array(F f) const {
        return std::array{f(type_identity<Ts>{})...};
    }

};

template<template<int> class F, std::size_t...i>
constexpr auto generate_type_pack_impl(std::index_sequence<i...>) {
    return (type_pack<>{} + ... + F<i>::value);
}

template<template<int> class F, int n>
constexpr auto generate_type_pack() {
    return generate_type_pack_impl<F>(std::make_index_sequence<n>{});
}
