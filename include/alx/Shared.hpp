#ifndef ALX_SHARED_HPP
#define ALX_SHARED_HPP


#include <memory>


namespace alx {


/**
    Base class for shared-based wrapper classes.
    @param T type of resource to manage via shared pointer.
 */
template <class T> class Shared : public std::shared_ptr<T> {
    static void nullDeleter(T*) {}
protected:
    /**
        null object constructor.
     */
    Shared() {
    }

    /**
        Constructor from external object.
        @param object pointer to object.
        @param managed the managed flag; if true, the deleter instance will be used to delete the object; if false, the null deleter will be used as a deleter.
        @param deleter the functor that will delete the object.
        @param nullDeleter an empty deleter.
     */
    template <class DELETER> Shared(T *object, bool managed, DELETER deleter) :
        std::shared_ptr<T>(object, managed ? deleter : nullDeleter)
    {
    }

    /**
        Managed object constructor.
        @param object pointer to object.
        @param deleter functor to use for deleting the object.
     */
    template <class DELETER> Shared(T *object, DELETER deleter) :
        std::shared_ptr<T>(object, deleter)
    {
    }

    /**
        Managed object constructor with the default deleter.
        @param object pointer to object.
     */
    Shared(T *object) :
        std::shared_ptr<T>(object)
    {
    }

    /**
        constructor from shared pointer.
        @param ptr ptr.
     */
    Shared(const std::shared_ptr<T> &ptr) : std::shared_ptr<T>(ptr) {
    }
};


} //namespace alx


#endif //ALX_SHARED_HPP
