#ifndef BASE_CORE_TRAIT_H
#define BASE_CORE_TRAIT_H


#include "Header.h"


namespace ty {
/// <summary>
/// 引数を分ける
/// </summary>
/// <typeparam name="Head"></typeparam>
/// <typeparam name="...Tail"></typeparam>
template<class Head, class...Tail>
struct ArgSeparator {
    typedef Head head;
    typedef std::tuple<Tail...> tail;
};
template<class...Args>
struct ArgList {
    typedef typename ArgSeparator<Args...>::head head;
    typedef typename ArgSeparator<Args...>::tail tail;
};


template<class T>
struct is_shared : std::false_type {
};
template<class T>
struct is_shared<std::shared_ptr<T>> : std::true_type {
};
template<class T>
struct remove_shared {
    typedef T type;
};
template<class T>
struct remove_shared<std::shared_ptr<T>> {
    typedef T type;
};

/// <summary>
/// タプルのインデックス
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="Tuple"></typeparam>
template <typename Tuple, typename T, int i = std::tuple_size<Tuple>::value - 1>
struct tuple_index {
    static const int value = std::is_same<typename std::tuple_element<i, Tuple>::type, T>::value ?
        i :
        tuple_index<Tuple, T, i - 1>::value;
};
/// <summary>
/// タプルのインデックス
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="Tuple"></typeparam>
template <typename Tuple, typename T>
struct tuple_index<Tuple, T, -1> {
    static const int value = -1;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_input_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Input(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_input : public decltype(has_func_input_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_initialize_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Initialize(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_initialize : public decltype(has_func_initialize_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_update_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Update(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_update : public decltype(has_func_update_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_render_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Render(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_render : public decltype(has_func_render_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_release_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Release(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_release : public decltype(has_func_release_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};
} // namespace
#endif // !BASE_CORE_TRAIT_H