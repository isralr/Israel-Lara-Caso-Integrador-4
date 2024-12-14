#ifndef VARIANT_H
#define VARIANT_H

#include <vector>
#include <string>
#include <json11.hpp>

// Clase Variant
class Variant {
public:
    // Enumeración para los tipos de datos que puede manejar Variant
    enum class Type { Symbol, Number, List, Proc, Lambda, Cadena };

    // Atributos
    Type type;                  // Tipo de la variante
    std::string value;          // Valor como cadena
    std::vector<Variant> list;  // Lista de variantes (para el tipo List)
    typedef Variant(*proc_type)(const std::vector<Variant>&);  // Tipo para procedimientos
    proc_type proc;             // Procedimiento (para el tipo Proc)

    // Constructores
    Variant(Type type = Type::Symbol);
    Variant(Type type, const std::string& val);
    Variant(proc_type proc);

    // Métodos
    std::string to_string() const;
    std::string to_json_string() const;
    static Variant from_json_string(const std::string& json);
};

#endif // VARIANT_H

