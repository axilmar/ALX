#ifndef ALX_ALLEGROFILE_HPP
#define ALX_ALLEGROFILE_HPP


namespace alx {


/**
    Wrapper class that deals with the problem of possibly calling fclose() twice on the same FILE handle.

    The function al_fclose() uses fclose() internally.

    The problem is that fclose() doesn't check its arguments for validity,
    and so if its called manually first (via File.close()) and then automatically
    (from ~File()), the app will die horribly.
 */
class AllegroFile {
public:
    /**
        The constructor.
     */
    AllegroFile(ALLEGRO_FILE *file, bool managed = true) :
        m_file(file), m_managed(managed)
    {
    }

    /**
        The destructor.
        It invokes the function close(), if managed.
     */
    ~AllegroFile() {
        if (m_managed) {
            close();
        }
    }

    /**
        Returns the pointer to the Allegro file.
     */
    ALLEGRO_FILE *get() const {
        return m_file;
    }

    /**
        Closes the file, if the pointer is not null.
        The internal pointer is set to null if the file is closed.
     */
    void close() {
        if (m_file) {
            al_fclose(m_file);
            m_file = nullptr;
        }
    }

private:
    //pointer to the allegro file.
    ALLEGRO_FILE *m_file;

    //if the file is managed
    bool m_managed;
};


} //namespace alx


#endif //ALX_ALLEGROFILE_HPP

