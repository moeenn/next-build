#include "Template.hpp"
#include <iostream>

// TODO
// - [ ] make template name dynamic.
// - [ ] generate .clang-format file using clang-format -dump-config command.

int main()
{
    Template tmpl{"example"};

    Template::Error err = tmpl.create();
    if (err != Template::Error::NoError)
    {
        return 1;
    }

    std::cout << "Template created successfully.\n";
    return 0;
}
