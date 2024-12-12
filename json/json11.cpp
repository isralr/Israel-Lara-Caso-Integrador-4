#include "json11.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <sstream>
#include <iomanip>

namespace json11 {

// Implementación del struct Impl
struct Json::Impl {
    Impl() : type(NUL) {}
    Impl(double value) : type(NUMBER), number_value(value) {}
    Impl(bool value) : type(BOOL), bool_value(value) {}
    Impl(const std::string& value) : type(STRING), string_value(value) {}
    Impl(std::string&& value) : type(STRING), string_value(std::move(value)) {}
    Impl(const std::vector<Json>& value) : type(ARRAY), array_items(value) {}
    Impl(std::vector<Json>&& value) : type(ARRAY), array_items(std::move(value)) {}
    Impl(const std::map<std::string, Json>& value) : type(OBJECT), object_items(value) {}
    Impl(std::map<std::string, Json>&& value) : type(OBJECT), object_items(std::move(value)) {}

    Type type;
    double number_value{};
    bool bool_value{};
    std::string string_value;
    std::vector<Json> array_items;
    std::map<std::string, Json> object_items;
};

// Métodos del Json

Json::Json() noexcept : m_impl(std::make_shared<Impl>()) {}

Json::Json(std::nullptr_t) noexcept : Json() {}

Json::Json(double value) : m_impl(std::make_shared<Impl>(value)) {}

Json::Json(bool value) : m_impl(std::make_shared<Impl>(value)) {}

Json::Json(const std::string& value) : m_impl(std::make_shared<Impl>(value)) {}

Json::Json(std::string&& value) : m_impl(std::make_shared<Impl>(std::move(value))) {}

Json::Json(const char* value) : Json(std::string(value)) {}

Json::Json(const std::vector<Json>& value) : m_impl(std::make_shared<Impl>(value)) {}

Json::Json(std::vector<Json>&& value) : m_impl(std::make_shared<Impl>(std::move(value))) {}

Json::Json(const std::map<std::string, Json>& value) : m_impl(std::make_shared<Impl>(value)) {}

Json::Json(std::map<std::string, Json>&& value) : m_impl(std::make_shared<Impl>(std::move(value))) {}

Json::Type Json::type() const {
    return m_impl->type;
}

double Json::number_value() const {
    return m_impl->type == NUMBER ? m_impl->number_value : 0.0;
}

bool Json::bool_value() const {
    return m_impl->type == BOOL ? m_impl->bool_value : false;
}

const std::string& Json::string_value() const {
    static const std::string empty_string;
    return m_impl->type == STRING ? m_impl->string_value : empty_string;
}

const std::vector<Json>& Json::array_items() const {
    static const std::vector<Json> empty_vector;
    return m_impl->type == ARRAY ? m_impl->array_items : empty_vector;
}

const std::map<std::string, Json>& Json::object_items() const {
    static const std::map<std::string, Json> empty_map;
    return m_impl->type == OBJECT ? m_impl->object_items : empty_map;
}

std::string Json::dump() const {
    std::ostringstream os;
    if (is_null()) {
        os << "null";
    } else if (is_number()) {
        os << number_value();
    } else if (is_bool()) {
        os << (bool_value() ? "true" : "false");
    } else if (is_string()) {
        os << "\"" << string_value() << "\"";
    } else if (is_array()) {
        os << "[";
        bool first = true;
        for (const auto& item : array_items()) {
            if (!first) os << ",";
            first = false;
            os << item.dump();
        }
        os << "]";
    } else if (is_object()) {
        os << "{";
        bool first = true;
        for (const auto& kv : object_items()) {
            if (!first) os << ",";
            first = false;
            os << "\"" << kv.first << "\":" << kv.second.dump();
        }
        os << "}";
    }
    return os.str();
}

Json Json::parse(const std::string& in, std::string& err) {
    // Un parser completo sería largo. Aquí usarás un parser externo si deseas extender.
    return Json();  // Solo como base
}

}  // namespace json11
