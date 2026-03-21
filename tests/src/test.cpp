#include <boost/ut.hpp>
#include <pqrs/osx/application.hpp>
#include <thread>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "run and stop"_test = [] {
    pqrs::osx::application::set_activation_policy(pqrs::osx::application::activation_policy::regular);
    pqrs::osx::application::finish_launching();

    std::thread t([] {
      std::this_thread::sleep_for(std::chrono::seconds(3));
      pqrs::osx::application::stop();
    });

    pqrs::osx::application::run();

    t.join();
  };

  return 0;
}
