#include "Angle.h"

using json = nlohmann::json;

void to_json(nlohmann::json &j, const Angle &v) {
  j = json{{"value", v}};
}

void from_json(const nlohmann::json &j, Angle &v) {
  j.at("value").get_to(v);
}