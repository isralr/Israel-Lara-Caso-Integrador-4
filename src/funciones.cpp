#include <iostream>
#include "variant.h"
#include "funciones.h"

void show_symbol() {
    Variant symbol(Variant::Symbol, "test_symbol");
    std::cout << "Symbol: " << symbol.to_string() << std::endl;
}

void show_number() {
    Variant number(Variant::Number, "42");
    std::cout << "Number: " << number.to_string() << std::endl;
}

void show_list() {
    Variant list(Variant::List);
    list.list.push_back(Variant(Variant::Number, "1"));
    list.list.push_back(Variant(Variant::Number, "2"));
    std::cout << "List: " << list.to_string() << std::endl;
}
