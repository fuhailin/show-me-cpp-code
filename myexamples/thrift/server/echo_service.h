#pragma once

#include <memory>

#include "EchoService.h"
#include "demo.h"

namespace echo {
class EchoService : virtual public EchoServiceSvIf {
 public:
  EchoService();
  ~EchoService() = default;
  void echo(EchoResponse& response,
            std::unique_ptr<EchoRequest> request) override;

 private:
  std::shared_ptr<Demo> demo_;
};
}  // namespace echo
