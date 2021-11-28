#include <iostream>
#include <vector>
#ifdef USE_CLANG_EXP
#include <experimental/coroutine> // clang for c++20
namespace stdcoro = std::experimental;
#else
#include <coroutine>
namespace stdcoro = std;
#endif
#include <cassert>

// template <typename T> using stdcoro::coroutine_handle<T>;
struct Debug {
  ~Debug() { std::cout << "Debug destroy" << std::endl; }
};

class resumable {
public:
  struct promise_type;
  using coro_handle = stdcoro::coroutine_handle<
      promise_type>; // 模板使用时只检察实参个数，真正声明对象、调用方法时才会实例化代码
  resumable(coro_handle handle) : handle_(handle) {
    assert(handle);
  } // 实例化，但coroutin_handle中只使用promise_type的引用，也不定义其成员
  resumable(resumable &) = delete;
  resumable(resumable &&) = delete;
  bool resume() {
    if (not handle_.done())
      handle_.resume();
    return not handle_.done(); // 不可被resumable
  }
  // bool resume1(){ return handle_.resume(); }
  ~resumable() {
    std::cout << "resumable" << std::endl;
    // handle_.destroy();
  }
  // private:
  coro_handle handle_;
};
struct resumable::promise_type {
  using coro_handle = stdcoro::coroutine_handle<promise_type>;
  ~promise_type() { std::cout << "Promise" << std::endl; }
  auto get_return_object() { return coro_handle::from_promise(*this); }
  auto initial_suspend() { return stdcoro::suspend_always(); }
  void return_void() { std::cout << "return void" << std::endl; }
  auto final_suspend() noexcept {
    std::cout << "final_suspend" << std::endl;
    return stdcoro::suspend_never();
  }
  auto
  yield_value(const char *string) { // can return something by promise member
    std::cout << string << std::endl;
    return stdcoro::suspend_always();
  }
  void unhandled_exception() { std::terminate(); }
};
resumable foo() {
  Debug debug;
  std::cout << "Hello" << std::endl;
  co_yield "yield value";
  // co_return 1;
  co_await stdcoro::suspend_always();
  std::cout << "Coroutine" << std::endl;
}
int main() {
  // vector<int> a{10, 5};
  // for(auto &&i:a){
  // cout << i << endl;
  // }
  resumable res = foo();

  std::vector<int> test{10, 1};
  std::cout << test[0] << std::endl;
  auto *promise = &res.handle_.promise();
  while (res.resume())
    ;
  // std::cout << "res.resume1()" << std::endl;
  // res.resume1();
  return 0;
}
