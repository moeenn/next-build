#include <iostream>
#include "CppProjectTemplate.hpp"

int main()
{
    const CppProjectTemplate tmpl{"sandbox"};
    CppProjectTemplate::Error err = tmpl.create();
    if (err != CppProjectTemplate::Error::NoError)
    {
        return 1;
    }

    std::cout << "Project created successfully!\n";
    return 0;
}
