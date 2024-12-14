#include <iostream>
#include "variant.h"
#include "funciones.h"

// Función para mostrar un símbolo
void show_symbol() {
    Variant symbol(Variant::Type::Symbol, "test_symbol");
    std::cout << "Symbol: " << symbol.to_string() << std::endl;
}

// Función para mostrar un número
void show_number() {
    Variant number(Variant::Type::Number, "42");
    std::cout << "Number: " << number.to_string() << std::endl;
}

// Función para mostrar una lista
void show_list() {
    Variant list(Variant::Type::List);
    list.list.push_back(Variant(Variant::Type::Number, "1"));
    list.list.push_back(Variant(Variant::Type::Number, "2"));
    std::cout << "List: " << list.to_string() << std::endl;
}
