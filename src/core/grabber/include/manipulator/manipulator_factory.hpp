#pragma once

#include "core_configuration.hpp"
#include "manipulator/details/base.hpp"
#include "manipulator/details/basic.hpp"
#include "manipulator/details/conditions/frontmost_application.hpp"
#include "manipulator/details/conditions/nop.hpp"
#include "manipulator/details/nop.hpp"
#include "manipulator/details/types.hpp"
#include <memory>

namespace krbn {
namespace manipulator {
class manipulator_factory final {
public:
  static std::shared_ptr<details::base> make_manipulator(const nlohmann::json& json,
                                                         const core_configuration::profile::complex_modifications::parameters& parameters) {
    {
      const std::string key = "type";
      if (json.find(key) != std::end(json) && json[key].is_string()) {
        if (json[key] == "basic") {
          return std::make_shared<details::basic>(json, parameters);
        }
      }
    }
    return std::make_shared<details::nop>();
  }

  static std::shared_ptr<details::conditions::base> make_condition(const nlohmann::json& json) {
    {
      const std::string key = "type";
      if (json.find(key) != std::end(json) && json[key].is_string()) {
        if (json[key] == "frontmost_application_if" ||
            json[key] == "frontmost_application_unless") {
          return std::make_shared<details::conditions::frontmost_application>(json);
        }
      }
    }
    return std::make_shared<details::conditions::nop>();
  }
};
} // namespace manipulator
} // namespace krbn
