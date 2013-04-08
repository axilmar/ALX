#ifndef ALX_STRINGINFO_HPP
#define ALX_STRINGINFO_HPP


#include <allegro5/allegro.h>
#include "Value.hpp"


namespace alx {


/**
    Value-based wrapper around ALLEGRO_USTR_INFO.
 */
class StringInfo : public Value<ALLEGRO_USTR_INFO> {
public:
};


} //namespace alx


#endif //ALX_STRINGINFO_HPP
