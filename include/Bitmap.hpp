#ifndef ALX_BITMAP_HPP
#define ALX_BITMAP_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


//TODO


class Bitmap {
public:
    Bitmap(ALLEGRO_BITMAP *object, bool managed = true) : m_object(object, managed ? al_destroy_bitmap : [](ALLEGRO_BITMAP *){}) {
    }

private:
    std::shared_ptr<ALLEGRO_BITMAP> m_object;

    friend class Display;
};


} //namespace alx


#endif //ALX_BITMAP_HPP