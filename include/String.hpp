#ifndef ALX_STRING_HPP
#define ALX_STRING_HPP


#include <allegro5/allegro.h>
#include "Shared.hpp"


namespace alx {


//TODO


class String : public Shared<ALLEGRO_USTR> {
public:
    String(ALLEGRO_USTR *object, bool managed = true) : Shared(object, managed, al_ustr_free, [](ALLEGRO_USTR *){}) {
    }

    String() {
    }

    String(const char *str) : Shared(al_ustr_new(str), al_ustr_free) {
    }

    operator const char *() const {
        return al_cstr(get());
    }
};


} //namespace alx


#endif //ALX_STRING_HPP
