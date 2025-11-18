#include "Progress.hpp"
#include <cstdio>

void Progress::char_repeat(char *buf, size_t start, char c, int n) const
{
    size_t i;
    for (i = start; i < start + n; i++)
    {
        buf[i] = c;
    }
}

void Progress::to_buffer(char *buf) const
{
    size_t i = 0;
    int fill_size = m_size - (3 + 2 + 1);
    buf[i++] = '[';

    const float p = perc();
    const int filled = p * fill_size;
    const int empty = fill_size - filled;

    char_repeat(buf, i, '#', filled);
    i += filled;

    char_repeat(buf, i, '.', empty);
    i += empty;
    buf[i++] = ']';
    buf[i++] = '\0';
}

float Progress::perc() const
{
    return (m_current * 1.0f) / (m_total * 1.0f);
}

bool Progress::is_done() const
{
    return m_current > m_total;
}

void Progress::increment(int by)
{
    m_current += by;
}

void Progress::render(char *buf) const
{
    to_buffer(buf);
    std::printf("%s %3.0f%%\r", buf, perc() * 100);
    std::fflush(stdout);
}
