#ifndef ALX_FILEPATH_HPP
#define ALX_FILEPATH_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


//TODO


class FilePath {
public:
    FilePath(ALLEGRO_PATH *path, bool managed = true) : m_object(path, managed ? al_destroy_path : [](ALLEGRO_PATH *){}) {
    }

private:
    std::shared_ptr<ALLEGRO_PATH> m_object;
};


} //namespace alx


#endif //ALX_FILEPATH_HPP
