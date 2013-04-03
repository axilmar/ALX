#ifndef ALX_CONFIG_HPP
#define ALX_CONFIG_HPP


#include "File.hpp"
#include "ConfigSectionContainer.hpp"
#include "ConfigEntryContainer.hpp"


namespace alx {


/**
    Value-based wrapper around ALLEGRO_CONFIG.
 */
class Config {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Config(ALLEGRO_CONFIG *object, bool managed = true) : m_object(object, managed ? al_destroy_config : [](ALLEGRO_CONFIG *){}) {
    }

    /**
        creates an internal config object.
     */
    Config() : m_object(al_create_config(), al_destroy_config) {
    }

    /**
        Constructor from disk file.
        @param filename filename.
     */
    Config(const char *filename) : m_object(al_load_config_file(filename), al_destroy_config) {
    }

    /**
        Constructor from open file.
        @param file file.
     */
    Config(File &file) : m_object(al_load_config_file_f(file.m_object.get()), al_destroy_config) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Saves the configuration to a file.
        @param filename name of file.
        @return true on success.
     */
    bool save(const char *filename) const {
        return al_save_config_file(filename, m_object.get());
    }

    /**
        Saves the configuration to an opened file.
        @param file file.
        @return true on success.
     */
    bool save(File &file) const {
        return al_save_config_file_f(file.m_object.get(), m_object.get());
    }

    /**
        Adds a section.
        @param name section name.
     */
    void addSection(const char *name) {
        al_add_config_section(m_object.get(), name);
    }

    /**
        Adds a comment.
        @param section name of section.
        @param comment comment.
     */
    void addComment(const char *section, const char *comment) {
        al_add_config_comment(m_object.get(), section, comment);
    }

    /**
        Returns a value.
        @param section name of section.
        @param key name of key.
        @return the key's value or null.
     */
    const char *getValue(const char *section, const char *key) const {
        return al_get_config_value(m_object.get(), section, key);
    }

    /**
        Sets a value.
        @param section name of section.
        @param key name of key.
        @param value value.
     */
    void setValue(const char *section, const char *key, const char *value) {
        al_set_config_value(m_object.get(), section, key, value);
    }

    /**
        Returns a container for sections.
        @return a container for sections.
     */
    ConfigSectionContainer getSections() const {
        return m_object;
    }

    /**
        Returns a container for entries of a section.
        @param section section name.
        @return a container for entries of a section.
     */
    ConfigEntryContainer getEntries(const char *section) const {
        return ConfigEntryContainer(section, m_object);
    }

    /**
        Merges two configurations.
        @param a first config.
        @param b second config.
        @return result config.
     */
    friend Config operator + (const Config &a, const Config &b) {
        return Config(al_merge_config(a.m_object.get(), b.m_object.get()));
    }

    /**
        Merges the given configuration to this.
        @param conf config.
        @return reference to this.
     */
    Config &operator += (const Config &config) {
        al_merge_config_into(m_object.get(), config.m_object.get());
        return *this;
    }

private:
    //internal pointer to the allegro object
    std::shared_ptr<ALLEGRO_CONFIG> m_object;
};


} //namespace alx


#endif //ALX_CONFIG_HPP
