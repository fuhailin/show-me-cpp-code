#ifndef PROMETHUS_UTIL_H
#define PROMETHUS_UTIL_H
#include <prometheus/counter.h>
#include <prometheus/gateway.h>
#include <prometheus/registry.h>
#include <prometheus/gauge.h>

using namespace prometheus;
struct prometheus_util {

	prometheus_util(std::string gw_ip, std::string gw_port, std::string name) {
		gateway = std::make_shared<prometheus::Gateway>(gw_ip, gw_port, name);
		registry = std::make_shared<Registry>();
		model_name = name;
	}

	int push() {
		int ret_code = gateway->Push();
		return ret_code;
	}

	void Register() {
        gateway->RegisterCollectable(registry);
    }

	Gauge* NewGauge(std::string name) {
		auto& family = prometheus::BuildGauge()
			.Name(model_name + "_" + name)
			.Register(*registry);
		Gauge& gauge = family.Add({});
                gauges[name] = &gauge;
		return &gauge;
	}

	void Set(std::string name, long value) {
		gauges[name]->Set(value);
	}

	std::shared_ptr<Gateway> gateway;
	std::shared_ptr<Registry> registry;
	std::map<std::string, Gauge*> gauges;
	std::string model_name;

	static std::shared_ptr<prometheus_util> inst_;
	static std::shared_ptr<prometheus_util> Instance() { return inst_; }
	static void new_instance(std::string gw_ip, std::string gw_port, std::string name) {
	    inst_.reset(new prometheus_util(gw_ip, gw_port, name));
	}
};

#endif
