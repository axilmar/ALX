#ifndef ALX_CONFIG_HPP
#define ALX_CONFIG_HPP


#include "File.hpp"
#include "ConfigSectionContainer.hpp"
#include "ConfigEntryContainer.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_CONFIG.
 */
class Config : public Shared<ALLEGRO_CONFIG> {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Config(ALLEGRO_CONFIG *object, bool managed = true) : Shared(object, managed, al_destroy_config, [](ALLEGRO_CONFIG *){}) {
    }

    /**
        creates an internal config object.
     */
    Config() : Shared(al_create_config(), al_destroy_config) {
    }

    /**
        Constructor from disk file.
        @param filename filename.
     */
    Config(const char *filename) : Shared(al_load_config_file(filename), al_destroy_config) {
    }

    /**
        Constructor from open file.
        @param file file.
     */
    Config(File &file) : Shared(al_load_config_file_f(file.get()), al_destroy_config) {
    }

    /**
        Saves the configuration to a file.
        @param filename name of file.
        @return true on success.
     */
    bool save(const char *filename) const {
        return al_save_config_file(filename, get());
    }

    /**
        Saves the configuration to an opened file.
        @param file file.
        @return true on success.
     */
    bool save(File &file) const {
        return al_save_config_file_f(file.get(), get());
    }

    /**
        Adds a section.
        @param name section name.
     */
    void addSection(const char *name) {
        al_add_config_section(get(), name);
    }

    /**
        Adds a comment.
        @param section name of section.
        @param comment comment.
     */
    void addComment(const char *section, const char *comment) {
        al_add_config_comment(get(), section, comment);
    }

    /**
        Returns a value.
        @param section name of section.
        @param key name of key.
        @return the key's value or null.
     */
    const char *getValue(const char *section, const char *key) const {
        return al_get_config_value(get(), section, key);
    }

    /**
        Sets a value.
        @param section name of section.
        @param key name of key.
        @param value value.
     */
    void setValue(const char *section, const char *key, const char *value) {
        al_set_config_value(get(), section, key, value);
    }

    /**
        Returns a container for sections.
        @return a container for sections.
     */
    ConfigSectionContainer getSections() const {
        return *this;
    }

    /**
        Returns a container for entries of a section.
        @param section section name.
        @return a container for entries of a section.
     */
    ConfigEntryContainer getEntries(const char *section) const {
        return ConfigEntryContainer(section, *this);
    }

    /**
        Merges two configurations.
        @param a first config.
        @param b second config.
        @return result config.
     */
    friend Config operator + (const Config &a, const Config &b) {
        return Config(al_merge_config(a.get(), b.get()));
    }

    /**
        Merges the given configuration to this.
        @param conf config.
        @return reference to this.
     */
    Config &operator << (const Config &config) {
        al_merge_config_into(get(), config.get());
        return *this;
    }
};


} //namespace alx


#endif //ALX_CONFIG_HPP
