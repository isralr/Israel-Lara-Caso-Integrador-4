#ifndef JSON11_HPP
#define JSON11_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <initializer_list>

namespace json11 {

    class Json {
    public:
        enum Type { NUL, NUMBER, BOOL, STRING, ARRAY, OBJECT };

        // Constructor por defecto
        Json() noexcept;  // null
        Json(std::nullptr_t) noexcept;  // null
        Json(double value);  // número
        Json(bool value);  // booleano
        Json(const std::string& value);  // cadena
        Json(std::string&& value);  // cadena (movimiento)
        Json(const char* value);  // cadena
        Json(const std::vector<Json>& value);  // array
        Json(std::vector<Json>&& value);  // array (movimiento)
        Json(const std::map<std::string, Json>& value);  // objeto
        Json(std::map<std::string, Json>&& value);  // objeto (movimiento)

        // Tipo
        Type type() const;

        // Métodos de acceso
        double number_value() const;
        bool bool_value() const;
        const std::string& string_value() const;
        const std::vector<Json>& array_items() const;
        const std::map<std::string, Json>& object_items() const;

        // Métodos de utilidad
        bool is_null() const { return type() == NUL; }
        bool is_number() const { return type() == NUMBER; }
        bool is_bool() const { return type() == BOOL; }
        bool is_string() const { return type() == STRING; }
        bool is_array() const { return type() == ARRAY; }
        bool is_object() const { return type() == OBJECT; }

        // Métodos de serialización
        std::string dump() const;

        // Métodos de parsing
        static Json parse(const std::string& in, std::string& err);
        static Json parse(const char* in, std::string& err) { return parse(std::string(in), err); }

    private:
        struct Impl;
        std::shared_ptr<Impl> m_impl;
    };

}  // namespace json11

#endif // JSON11_HPP
