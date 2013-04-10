#ifndef ALX_OBJECT_HPP
#define ALX_OBJECT_HPP


namespace alx {


/**
    Base class for objects.
 */
class Object {
public:
    /**
        The default constructor.
     */
    Object() {
    }

    /**
        Destructor.
     */
    virtual ~Object() {
    }

private:
    //non-copyable, non-moveable
    Object(const Object &);
    Object(Object &&);
    Object &operator = (const Object &);
    Object &operator = (Object &&);
};


} //namespace alx


#endif //ALX_OBJECT_HPP
