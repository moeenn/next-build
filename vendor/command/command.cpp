#include "Command.hpp"

bool command::exec(const char* cmd)
{
    int status = std::system(cmd);
    return status == 0;
}
