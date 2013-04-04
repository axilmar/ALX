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

    String() {
    }

    bool isNull() const {
        return m_object;
    }

    operator const char *() const {
        return al_cstr(m_object.get());
    }

private:
    std::shared_ptr<ALLEGRO_USTR> m_object;
};


} //namespace alx


#endif //ALX_STRING_HPP
