#ifndef ALX_TIMEOUT_HPP
#define ALX_TIMEOUT_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


//TODO


class Timeout {
public:

private:
    std::shared_ptr<ALLEGRO_TIMEOUT> m_object;

    friend class Condition;
};


} //namespace alx


#endif //ALX_TIMEOUT_HPP
