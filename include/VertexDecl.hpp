#ifndef ALX_VERTEXDECL_HPP
#define ALX_VERTEXDECL_HPP


#include <allegro5/allegro_primitives.h>
#include "Shared.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_VERTEX_DECL.
 */
class VertexDecl : public Shared<ALLEGRO_VERTEX_DECL> {
public:
    /**
        Null constructor.
     */
    VertexDecl() {
    }

    /**
        Constructor.
        @param elements An array of ALLEGRO_VERTEX_ELEMENT structures.
        @param stride Size of the custom vertex structure 
     */
    VertexDecl(const ALLEGRO_VERTEX_ELEMENT *elements, int stride) :
        Shared(al_create_vertex_decl(elements, stride), al_destroy_vertex_decl)
    {
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    VertexDecl(ALLEGRO_VERTEX_DECL *object, bool managed = true) : 
        Shared(object, managed, al_destroy_vertex_decl, [](ALLEGRO_VERTEX_DECL *){})
    {
    }
};


} //namespace alx


#endif //ALX_VERTEXDECL_HPP
