#pragma once

#include <iostream>
#include <type_traits>

/** Library version: 0xMmP (M=Major,m=minor,P=patch) */
#define AUTOGRAD_VERSION 0x100

#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), bool>::type = true

namespace autograd
{

/** A compile-time constant that indicates whether a type is arithmetic */
template <typename T>
constexpr bool is_arithmetic = std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>>;

/**
 * @brief      This class describes a variable.
 *
 * @tparam     T         { description }
 * @tparam     REQUIRES  { description }
 */
template <typename T, REQUIRES(is_arithmetic<T>)>
class Variable
{
public:
  /**
   * Disable default constructor
   */
  Variable() = delete;

  /**
   * @brief TODO
   */
  explicit Variable(T&& other) { m_data = other; }

  /**
   * @brief      Bitwise left shift operator.
   *
   * @param      os    The operating system
   * @param[in]  v     { parameter_description }
   *
   * @return     The result of the bitwise left shift
   */
  friend std::ostream& operator<<(std::ostream& os, const Variable& v)
  {
    // TODO(Phone): replace this with either fmt or std::format
    return os << "Variable(data = " << v.m_data << ")\n";
  }

private:
  T m_data{};
};

}  // namespace autograd
