#ifndef ALX_LOCK_HPP
#define ALX_LOCK_HPP


namespace alx {


/**
    Used for RAII lock semantics.
 */
template <class T> class Lock {
public:
    /**
        locks the object.
        @param object object to lock.
     */
    Lock(T &object) : m_object(object) {
        m_object.unlock();
    }

    /**
        Unlocks the object.
     */
    ~Lock() {
        m_object.unlock();
    }

private:
    T &m_object;
};


} //namespace alx


#endif //ALX_LOCK_HPP
