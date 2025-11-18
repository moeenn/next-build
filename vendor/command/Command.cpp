#include "Command.hpp"

bool Command::exec(const char* cmd)
{
    int status = std::system(cmd);
    return status == 0;
}
