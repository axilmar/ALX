#ifndef ALX_SAMPLEID_HPP
#define ALX_SAMPLEID_HPP


#include <allegro5/allegro_audio.h>
#include "alx_Value.hpp"


namespace alx {


/**
    Value-based wrapper around ALLEGRO_SAMPLE_ID.
 */
class SampleId : public Value<ALLEGRO_SAMPLE_ID> {
public:
    /**
        Stops playing this sample.
     */
    void stop() {
        al_stop_sample(&get());
    }
};


} //namespace alx


#endif //ALX_SAMPLEID_HPP
