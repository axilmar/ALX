#ifndef ALX_CONFIGENTRYCONTAINER_HPP
#define ALX_CONFIGENTRYCONTAINER_HPP


#include <iterator>
#include "alx/String.hpp"


namespace alx {


/**
    Shared-based wrapper for container of entries.
 */
class ConfigEntryContainer : public Shared<ALLEGRO_CONFIG> {
public:
    /**
        Iterator for entries.
     */
    class const_iterator : public std::iterator<std::forward_iterator_tag, String> {
    public:
        /**
            Returns the entry name.
            @return the entry name.
         */
        String operator *() const {
            return String(m_name, false);
        }

        /**
            Checks if two iterators point to the same entry.
            @param it the other iterator.
            @return true if this and given iterator point to the same entry.
         */
        bool operator == (const const_iterator &it) const {
            return m_entry == it.m_entry;
        }

        /**
            Checks if two iterators point to a different entry.
            @param it the other iterator.
            @return true if this and given iterator point to a different entry.
         */
        bool operator != (const const_iterator &it) const {
            return !operator ==(it);
        }

        /**
            Increments the iterator to point to the next entry.
            @return reference to this.
         */
        const_iterator &operator ++() {
            m_name = al_get_next_config_entry(&m_entry);
            return *this;
        }

    private:
        //pointer to entry.
        ALLEGRO_CONFIG_ENTRY *m_entry;

        //entry name
        const char *m_name;

        //internal constructor
        const_iterator() : m_entry(0), m_name(0) {
        }

        friend class ConfigEntryContainer;
    };

    /**
        Returns an iterator that points to the first entry.
        @return an iterator that points to the first entry.
     */
    const_iterator begin() const {
        const_iterator it;
        it.m_name = al_get_first_config_entry(get(), m_section, &it.m_entry);
        return it;
    }

    /**
        Returns an iterator that points to the entry end.
     */
    const_iterator end() const {
        return const_iterator();
    }

private:
    //section name
    const char *m_section;

    //internal constructor
    ConfigEntryContainer(const char *section, const std::shared_ptr<ALLEGRO_CONFIG> &config) : Shared(config), m_section(section) {
    }

    friend class Config;
};


} //namespace alx


#endif //ALX_CONFIGENTRYCONTAINER_HPP
