#include "variant.h"
#include <stdexcept>

// Constructor por defecto
Variant::Variant(Type type) : type(type), value(""), proc(nullptr) {}

// Constructor para un valor específico
Variant::Variant(Type type, const std::string& val) : type(type), value(val), proc(nullptr) {}

// Constructor para procedimientos
Variant::Variant(proc_type proc) : type(Type::Proc), value(""), proc(proc) {}

// Método to_string para representar la variante como cadena
std::string Variant::to_string() const {
    switch (type) {
        case Type::Symbol:
        case Type::Cadena:
            return value;
        case Type::Number:
            return value;
        case Type::List: {
            std::string result = "[";
            for (const auto& item : list) {
                result += item.to_string() + ", ";
            }
            if (!list.empty()) {
                result.pop_back();  // Quitar la coma final
                result.pop_back();  // Quitar el espacio
            }
            result += "]";
            return result;
        }
        default:
            return "Unknown Type";
    }
}

// Método para convertir la variante a una cadena JSON
std::string Variant::to_json_string() const {
    json11::Json json_obj;
    switch (type) {
        case Type::Symbol:
        case Type::Cadena:
            json_obj = json11::Json(value);
            break;
        case Type::Number:
            json_obj = json11::Json(std::stoi(value));  // Convertir string a número
            break;
        case Type::List: {
            std::vector<json11::Json> json_list;
            for (const auto& item : list) {
                json_list.push_back(item.to_json_string());
            }
            json_obj = json11::Json(json_list);
            break;
        }
        default:
            json_obj = json11::Json::object();
            break;
    }
    return json_obj.dump();  // Retorna la cadena JSON
}

// Método estático para convertir una cadena JSON a un objeto Variant
Variant Variant::from_json_string(const std::string& json) {
    std::string err;
    json11::Json json_obj = json11::Json::parse(json, err);  // Parsear el JSON
    if (!err.empty()) {
        throw std::runtime_error("Error al parsear JSON: " + err);
    }

    if (json_obj.is_string()) {
        return Variant(Type::Symbol, json_obj.string_value());
    } else if (json_obj.is_number()) {
        return Variant(Type::Number, std::to_string(json_obj.number_value()));
    } else if (json_obj.is_array()) {
        Variant list_variant(Type::List);
        for (const auto& item : json_obj.array_items()) {
            list_variant.list.push_back(Variant::from_json_string(item.dump()));
        }
        return list_variant;
    }

    return Variant();  // Valor predeterminado en caso de error
}
