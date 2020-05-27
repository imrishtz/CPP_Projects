#ifndef REACTOR_SELECT_HPP_	
#define REACTOR_SELECT_HPP_

#include <algorithm>    // std::make_heap
#include <vector>

#include "reactor.hpp"

namespace ilrd{

class ReactorSelect
{
public:
    inline explicit ReactorSelect();

    inline void add(int fd);
    inline void detach(int fd);
    inline int wait();
    inline int get_next(int curr) const;

private:
    fd_set m_masterfds;
    fd_set m_is_on_fds;
    std::vector<int> m_max;
};

ReactorSelect::ReactorSelect()
{
    FD_ZERO(&m_masterfds);
    FD_ZERO(&m_is_on_fds);
}
void ReactorSelect::add(int fd)
{
    FD_SET(fd, &m_masterfds);
    m_max.push_back(fd);
    std::push_heap(m_max.begin(),m_max.end());
}
void ReactorSelect::detach(int fd)
{
    FD_CLR(fd, &m_masterfds);
    std::vector<int>::iterator it = std::find(m_max.begin(), m_max.end(), fd);
    m_max.erase(it);
    std::sort_heap (m_max.begin(),m_max.end());
}
int ReactorSelect::wait()
{
    m_is_on_fds = m_masterfds;

    return (select(m_max.front() + 1, &m_is_on_fds, nullptr, nullptr, nullptr));
}
int ReactorSelect::get_next(int curr) const
{
    int max = m_max.front();

    int i = curr + 1;
    for ( ; (i <= max) && (!FD_ISSET(i, &m_is_on_fds)); ++i)
    {}
    return (i);
}

} // end ilrd

#endif //REACTOR_SELECT