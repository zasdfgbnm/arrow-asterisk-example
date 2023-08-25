#include <cstdint>
#include <stdexcept>
#include <string>
#include <variant>
#include <iostream>

struct A {
  int64_t x;
  int64_t y;

  const int64_t& operator->*(const std::string& name) const {
    if (name == "x") {
      return x;
    } else if (name == "y") {
      return y;
    } else {
      throw std::runtime_error("No such field");
    }
  }
};

struct B {
  int64_t y;
  int64_t z;
  const int64_t& operator->*(const std::string& name) const {
    if (name == "y") {
      return y;
    } else if (name == "z") {
      return z;
    } else {
      throw std::runtime_error("No such field");
    }
  }
};

struct C {
  int64_t z;
  int64_t x;
  const int64_t& operator->*(const std::string& name) const {
    if (name == "z") {
      return z;
    } else if (name == "x") {
      return x;
    } else {
      throw std::runtime_error("No such field");
    }
  }
};

struct ABC {
  std::variant<A, B, C> data;

  template <typename T>
  ABC(T&& data) : data(std::forward<T>(data)) {}
  
  template <typename T>
  ABC& operator=(T&& data) {
    this->data = std::forward<T>(data);
    return *this;
  }

  const int64_t& operator->*(const std::string& name) const {
    if (auto* a = std::get_if<A>(&data)) {
      return a->operator->*(name);
    } else if (auto* b = std::get_if<B>(&data)) {
      return b->operator->*(name);
    } else if (auto* c = std::get_if<C>(&data)) {
      return c->operator->*(name);
    } else {
      throw std::runtime_error("No such field");
    }
  }
};

int main() {
  ABC a = A{1, 2};
  ABC b = B{3, 4};
  ABC c = C{5, 6};
  std::cout << "a.x = " << a->*"x" << std::endl;
  std::cout << "a.y = " << a->*"y" << std::endl;
  std::cout << "b.y = " << b->*"y" << std::endl;
  std::cout << "b.z = " << b->*"z" << std::endl;
  std::cout << "c.z = " << c->*"z" << std::endl;
  std::cout << "c.x = " << c->*"x" << std::endl;
}