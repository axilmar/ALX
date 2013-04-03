#ifndef ALX_FILE_HPP
#define ALX_FILE_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


//TODO


class File {
public:

private:
    std::shared_ptr<ALLEGRO_FILE> m_object;

    friend class Config;
};


} //namespace alx


#endif //ALX_FILE_HPP
