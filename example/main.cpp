#include <iostream>
#include <pqrs/osx/application.hpp>
#include <thread>

int main() {
  std::cout << "The application will exit in 3 seconds." << std::endl;

  pqrs::osx::application::set_activation_policy(pqrs::osx::application::activation_policy::regular);
  pqrs::osx::application::finish_launching();
  pqrs::osx::application::set_should_terminate_callback([] {
    pqrs::osx::application::stop();
    return pqrs::osx::application::terminate_reply::cancel;
  });

  std::thread t([] {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    pqrs::osx::application::stop();
  });

  pqrs::osx::application::run();

  t.join();

  return 0;
}
