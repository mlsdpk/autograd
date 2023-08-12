#pragma once

#include <iostream>
#include <type_traits>

/** Library version: 0xMmP (M=Major,m=minor,P=patch) */
#define AUTOGRAD_VERSION 0x100

#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), bool>::type = true

namespace autograd
{

/**
 * Forward declarations
 */
template <typename T>
class Variable;

/**
 * some useful type traits to make our lives easier
 */
namespace traits
{

template <typename T>
struct isVariableType
{
  constexpr static bool value = false;
};

template <typename T>
struct isVariableType<Variable<T>>
{
  constexpr static bool value = true;
};

}  // namespace traits

/** A compile-time constant that indicates whether a type is arithmetic */
template <typename T>
constexpr bool is_arithmetic = std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>>;

/** A compile-time constant that indicates whether a type is Variable */
template <typename T>
constexpr bool is_variable =
    traits::isVariableType<std::remove_cv_t<std::remove_reference_t<T>>>::value;

/**
 * @brief      This class describes a variable.
 *
 * @tparam     T         { description }
 * @tparam     REQUIRES  { description }
 */
template <typename T>
class Variable
{
public:
  /**
   * Delete all default constructors
   */
  Variable() = delete;
  Variable(const Variable& other) = delete;
  Variable& operator=(const Variable& other) = delete;

  template <typename U, REQUIRES(is_arithmetic<U> || is_variable<U>)>
  Variable(U&& other)
  {
    assign(std::forward<U>(other));
  }

  template <typename U, REQUIRES(is_arithmetic<U> || is_variable<U>)>
  Variable& operator=(U&& other)
  {
    assign(std::forward<U>(other));
    return *this;
  }

  //=====================================================================================================================
  // Addition assignment
  //=====================================================================================================================
  template <typename U, REQUIRES(is_arithmetic<U> || is_variable<U>)>
  Variable& operator+=(U&& other)
  {
    addition(std::forward<U>(other));
    return *this;
  }

  //=====================================================================================================================
  // Addition
  //=====================================================================================================================
  template <typename U, REQUIRES(is_arithmetic<U> || is_variable<U>)>
  constexpr auto operator+(U&& other)
  {
    Variable tmp(*this);
    addition(tmp, std::forward<U>(other));
    return tmp;
  }

  auto data() const { return m_data; }

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
  template <typename U, typename V>
  constexpr void assign(Variable<U>& self, V&& other)
  {
    static_assert(is_arithmetic<V> || is_variable<V>);

    if constexpr (is_arithmetic<V>)
    {
      self.m_data = other;
    }
    else if constexpr (is_variable<V>)
    {
      self.m_data = other.m_data;
    }
  }

  template <typename U, typename V>
  constexpr void addition(Variable<U>& self, V&& other)
  {
    static_assert(is_arithmetic<V> || is_variable<V>);

    if constexpr (is_arithmetic<V>)
    {
      self.m_data += other;
    }
    else if constexpr (is_variable<V>)
    {
      self.m_data += other.m_data;
    }
  }

  template <typename U>
  constexpr void assign(U&& other)
  {
    assign(*this, other);
  }

  template <typename U>
  constexpr void addition(U&& other)
  {
    addition(*this, other);
  }

private:
  T m_data{};
};

template <typename T>
auto data(T&& expr)
{
  static_assert(is_arithmetic<T> || is_variable<T>);

  if constexpr (is_variable<T>)
    return data(expr.data());
  else
    return std::forward<T>(expr);
}

template <typename L, typename R>
bool operator==(L&& l, R&& r)
{
  return data(l) == data(r);
}

template <typename R, REQUIRES(is_variable<R>)>
constexpr auto operator+(R&& r)
{
  return std::forward<R>(r);  // expression optimization: +(expr) => expr
}

template <typename L, typename R, REQUIRES(is_arithmetic<L>&& is_variable<R>)>
constexpr auto operator+(L&& l, R&& r)
{
  // CASE: number + variable => variable + number
  return std::forward<R>(r) + std::forward<L>(l);
}

}  // namespace autograd
