#include <tuple>
#include <utility>
template <typename Tuple, typename Func, std::size_t... I>
Func forEachOnTuple_impl(Tuple&& tuple, Func&& func,
                         std::index_sequence<I...>) {
	std::initializer_list<int>{(func(std::get<I>(tuple)), 0)...};
	return func;
}

template <typename Tuple, typename Func>
Func forEachOnTuple(Tuple&& tuple, Func&& func) {
	return forEachOnTuple_impl(
	    std::forward<Tuple>(tuple), std::forward<Func>(func),
	    std::make_index_sequence<
	        std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
}