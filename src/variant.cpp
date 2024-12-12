#include "variant.h"
#include <iostream>
#include "json/json11.hpp"
#include <sstream>

Variant::Variant(variant_type type) : type(type), env(nullptr), proc(nullptr) {}

Variant::Variant(variant_type type, const std::string& val)
    : type(type), val(val), env(nullptr), proc(nullptr) {}

Variant::Variant(proc_type proc) : type(Proc), proc(proc), env(nullptr) {}

std::string Variant::to_string() {
    switch (type) {
        case Symbol:
            return "Symbol: " + val;
        case Number:
            return "Number: " + val;
        case List: {
            std::string result = "List: [";
            for (const auto& item : list) {
                result += item.to_string() + ", ";
            }
            if (!list.empty()) result.pop_back(), result.pop_back();  // Eliminar última coma
            result += "]";
            return result;
        }
        case Proc:
            return "Proc: Function Pointer";
        case Lambda:
            return "Lambda: Function Pointer";
        case Cadena:
            return "Cadena: " + val;
        default:
            return "Unknown type";
    }
}

std::string Variant::to_json_string() {
    json11::Json json_obj;
    switch (type) {
        case Symbol:
        case Cadena:
            json_obj = json11::Json(val);
            break;
        case Number:
            json_obj = json11::Json::number(stoi(val));  // Convertir string a número
            break;
        case List: {
            std::vector<json11::Json> json_list;
            for (const auto& item : list) {
                json_list.push_back(json11::Json(item.to_json_string()));  // Recursión para listas
            }
            json_obj = json11::Json(json_list);
            break;
        }
        case Proc:
        case Lambda:
            json_obj = json11::Json::object();  // Reemplazar con la representación adecuada si es necesario
            break;
        default:
            json_obj = json11::Json::object();
            break;
    }
    return json_obj.dump();  // Retorna la cadena JSON
}

Variant Variant::from_json_string(std::string sjson) {
    json11::Json json_obj = json11::Json::parse(sjson, nullptr);
    if (json_obj.is_string()) {
        return Variant(Symbol, json_obj.string_value());
    } else if (json_obj.is_number()) {
        return Variant(Number, std::to_string(json_obj.int_value()));
    } else if (json_obj.is_array()) {
        Variant list_variant(List);
        for (const auto& item : json_obj.array_items()) {
            list_variant.list.push_back(Variant::from_json_string(item.dump()));
        }
        return list_variant;
    }
    return Variant();  // Valor predeterminado en caso de error
}

Variant Variant::parse_json(jsonlib::Json job) {
    if (job.is_string()) {
        return Variant(Symbol, job.string_value());
    } else if (job.is_number()) {
        return Variant(Number, std::to_string(job.int_value()));
    } else if (job.is_array()) {
        Variant list_variant(List);
        for (const auto& item : job.array_items()) {
            list_variant.list.push_back(Variant::parse_json(item));
        }
        return list_variant;
    }
    return Variant();  // Valor predeterminado en caso de error
}
