#ifndef CPPROUTER_LITEERLAS_HPP
#define CPPROUTER_LITEERLAS_HPP

//namespace CppRouter {

template<char...>
struct _string {};

template<typename T, T... Ts>
constexpr auto operator""_s()
{
    return _string<Ts...>{};
}

//}

#endif // CPPROUTER_LITEERLAS_HPP
