#pragma once
#include <iostream>
#include <cstdint>

class Progress
{
private:
    uint m_total = 0;
    uint m_current = 0;
    uint m_size = 40;

    void char_repeat(char *buf, size_t start, char c, int n) const;
    void to_buffer(char *buf) const;

public:
    Progress(int total, uint size = 50) : m_total(total), m_current(0), m_size(size)
    {
    }

    float perc() const;
    bool is_done() const;
    void increment(int by);
    void render(char *buf) const;
};
