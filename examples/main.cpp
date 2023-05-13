#include <autograd/autograd.hpp>

using namespace autograd;

int main(int argc, char const *argv[])
{
  auto v = Variable(1.5);
  std::cout << v;

  return 0;
}