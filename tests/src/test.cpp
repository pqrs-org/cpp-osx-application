#include <boost/ut.hpp>
#include <objc/message.h>
#include <objc/runtime.h>
#include <pqrs/osx/application.hpp>
#include <atomic>
#include <thread>

namespace {

void terminate_ns_application_on_main_thread() {
  auto cls = objc_getClass("NSApplication");
  auto app = reinterpret_cast<id (*)(id, SEL)>(objc_msgSend)(
      reinterpret_cast<id>(cls),
      sel_registerName("sharedApplication"));

  reinterpret_cast<void (*)(id, SEL, SEL, id, BOOL)>(objc_msgSend)(
      app,
      sel_registerName("performSelectorOnMainThread:withObject:waitUntilDone:"),
      sel_registerName("terminate:"),
      nil,
      false);
}

} // namespace

int main() {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "terminate callback exceptions are treated as now"_test = [] {
    pqrs::osx::application::set_should_terminate_callback([]() -> pqrs::osx::application::terminate_reply {
      throw 1;
    });

    expect(pqrs_osx_application_terminate_reply_now ==
           pqrs::osx::application::impl::should_terminate_callback_trampoline());

    pqrs::osx::application::set_should_terminate_callback(nullptr);
  };

  "terminate callback can cancel and stop"_test = [] {
    pqrs::osx::application::set_activation_policy(pqrs::osx::application::activation_policy::regular);
    pqrs::osx::application::finish_launching();

    std::atomic<bool> callback_called = false;

    pqrs::osx::application::set_should_terminate_callback([&callback_called] {
      callback_called = true;
      pqrs::osx::application::stop();
      return pqrs::osx::application::terminate_reply::cancel;
    });

    std::thread t([] {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      terminate_ns_application_on_main_thread();
    });

    pqrs::osx::application::run();

    t.join();

    expect(callback_called.load());

    pqrs::osx::application::set_should_terminate_callback(nullptr);
  };

  return 0;
}
