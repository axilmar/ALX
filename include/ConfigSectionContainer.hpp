#ifndef ALX_CONFIGSECTIONCONTAINER_HPP
#define ALX_CONFIGSECTIONCONTAINER_HPP


#include <memory>
#include <iterator>
#include <allegro5/allegro.h>


namespace alx {


/**
    Value-base wrapper for container of sections.
 */
class ConfigSectionContainer {
public:
    /**
        Iterator for sections.
     */
    class const_iterator : public std::iterator<std::forward_iterator_tag, const char *> {
    public:
        /**
            Returns the section name.
            @return the section name.
         */
        const char *operator *() const {
            return m_name;
        }

        /**
            Checks if two iterators point to the same section.
            @param it the other iterator.
            @return true if this and given iterator point to the same section.
         */
        bool operator == (const const_iterator &it) const {
            return m_section == it.m_section;
        }

        /**
            Checks if two iterators point to a different section.
            @param it the other iterator.
            @return true if this and given iterator point to a different section.
         */
        bool operator != (const const_iterator &it) const {
            return !operator ==(it);
        }

        /**
            Increments the iterator to point to the next section.
            @return reference to this.
         */
        const_iterator &operator ++() {
            m_name = al_get_next_config_section(&m_section);
            return *this;
        }

    private:
        //pointer to section.
        ALLEGRO_CONFIG_SECTION *m_section;

        //section name
        const char *m_name;

        //internal constructor
        const_iterator() : m_section(0), m_name(0) {
        }

        friend class ConfigSectionContainer;
    };

    /**
        Returns an iterator that points to the first section.
        @return an iterator that points to the first section.
     */
    const_iterator begin() const {
        const_iterator it;
        it.m_name = al_get_first_config_section(m_config.get(), &it.m_section);
        return it;
    }

    /**
        Returns an iterator that points to the section end.
     */
    const_iterator end() const {
        return const_iterator();    
    }

private:
    //pointer to config
    std::shared_ptr<ALLEGRO_CONFIG> m_config;

    //internal constructor
    ConfigSectionContainer(const std::shared_ptr<ALLEGRO_CONFIG> &config) : m_config(config) {
    }

    friend class Config;
};


} //namespace alx


#endif //ALX_CONFIGSECTIONCONTAINER_HPP
