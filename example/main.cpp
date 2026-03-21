#include <iostream>
#include <pqrs/osx/application.hpp>

int main(void) {
  std::cout << "Type control+c to quit." << std::endl;

  pqrs::osx::application::set_activation_policy(pqrs::osx::application::activation_policy::regular);
  pqrs::osx::application::finish_launching();
  pqrs::osx::application::run();

  return 0;
}
