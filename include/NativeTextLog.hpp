#ifndef ALX_NATIVETEXTLOG_HPP
#define ALX_NATIVETEXTLOG_HPP


#include <allegro5/allegro_native_dialog.h>
#include "String.hpp"
#include "EventSource.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_TEXTLOG.
 */
class NativeTextLog : public Shared<ALLEGRO_TEXTLOG> {
public:
    /**
        Null constructor.
     */
    NativeTextLog() {
    }

    /**
        Constructor.
        @param title the window title.
        @param flags flags.
     */
    NativeTextLog(const char *title, int flags = 0) :
        Shared(al_open_native_text_log(title, flags), al_close_native_text_log)
    {
    }

    /**
        Returns the event source for this object.
        @return the event source for this object.
     */
    EventSource getEventSource() const {
        return EventSource(al_get_native_text_log_event_source(get()), false);
    }

    /**
        Appends a printf-style text.
        @param format format.
        @param ... printf-style arguments.
     */
    void append(const char *format, ...) {
        va_list args;
        va_start(args, format);
        append(format, args);
        va_end(args);
    }

    /**
        Appends a printf-style text.
        @param format format.
        @param args printf-style arguments.
     */
    void append(const char *format, va_list args) {
        String str;
        str.printf(format, args);
        al_append_native_text_log(get(), "%s", str.cstr());
    }

    /**
        Append text.
        @param str string.
     */
    void append(const String &str) {
        al_append_native_text_log(get(), "%s", str.cstr());        
    }

    /**
        Append text using the operator <<.
        @param str string.
        @return reference to this.
     */
    NativeTextLog &operator << (const char *str) {
        al_append_native_text_log(get(), "%s", str);        
        return *this;
    }

    /**
        Append text using the operator <<.
        @param str string.
        @return reference to this.
     */
    NativeTextLog &operator << (const String &str) {
        al_append_native_text_log(get(), "%s", str.cstr());        
        return *this;
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    NativeTextLog(ALLEGRO_TEXTLOG *object, bool managed = true) : 
        Shared(object, managed, al_close_native_text_log)
    {
    }
};


} //namespace alx


#endif //ALX_NATIVETEXTLOG_HPP
