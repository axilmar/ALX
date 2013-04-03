#ifndef ALX_STRING_HPP
#define ALX_STRING_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


//TODO


class String {
public:
    String(ALLEGRO_USTR *object, bool managed = true) : m_object(object, managed ? al_ustr_free : [](ALLEGRO_USTR *){}) {
    }

    String() : m_object(al_ustr_dup(al_ustr_empty_string()), al_ustr_free) {
    }

private:
    std::shared_ptr<ALLEGRO_USTR> m_object;
};


} //namespace alx


#endif //ALX_STRING_HPP
