#ifndef TEMPLATE_TOOLS_HPP_
#define TEMPLATE_TOOLS_HPP_

#include <type_traits>

namespace bst {
namespace template_tools {

/**
 * @brief Converts an enum class to its underlying type.
 *
 * @tparam E - The enum class type.
 * @param e - The enum class to convert.
 * @return constexpr auto - The underlying type of the enum class.
 *
 * @cite https://stackoverflow.com/questions/8357240/
 */
template <typename E>
constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

} // namespace template_tools
} // namespace bst

#endif /* TEMPLATE_TOOLS_HPP_ */