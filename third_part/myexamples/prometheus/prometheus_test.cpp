#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>

#include <prometheus/counter.h>
#include <prometheus/gateway.h>
#include <prometheus/registry.h>

#ifdef _WIN32
#include <Winsock2.h>
#else
#include <sys/param.h>
#include <unistd.h>
#endif

static std::string GetHostName() {
  char hostname[1024];

  if (::gethostname(hostname, sizeof(hostname))) {
    return {};
  }
  return hostname;
}

int main() {
  using namespace prometheus;

  // create a push gateway
  const auto labels = Gateway::GetInstanceLabel(GetHostName());

  Gateway gateway{"172.16.17.121", "9091", "cpp_test", labels};
    // Gateway gateway{"127.0.0.1:9092"};

  // create a metrics registry with component=main labels applied to all its
  // metrics
  auto registry = std::make_shared<Registry>();

  // add a new counter family to the registry (families combine values with the
  // same name, but distinct label dimensions)
  auto& counter_family = BuildGauge()
                             .Name("Segmentation")
                             .Help("How many seconds is this server running?")
                             .Labels({{"label", "value"}})
                             .Register(*registry);

                             

  // add a counter to the metric family
  auto& second_counter = counter_family.Add(
      {
        {"test_label", "value"}, 
        // {"yet_another_label", "value"}
        });

  auto& one_counter = counter_family.Add(
      {
        // {"another_label", "value"}, 
        {"fuhailin_label", "value"}
        });
  
  prometheus::Gauge* p = &one_counter;

  // ask the pusher to push the metrics to the pushgateway
  gateway.RegisterCollectable(registry);

  for (;;) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // increment the counter by one (second)
    second_counter.Set(5);
    p->Set(15);

    // push metrics
    auto returnCode = gateway.Push();
    std::cout << "returnCode is " << returnCode << std::endl;
  }
  return 0;
}