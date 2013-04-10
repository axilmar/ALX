#ifndef ALX_SAMPLEINSTANCE_HPP
#define ALX_SAMPLEINSTANCE_HPP


#include "Sample.hpp"


namespace alx {


/**
    Wrapper class around ALLEGRO_SAMPLE_INSTANCE
 */
class SampleInstance : public Shared<ALLEGRO_SAMPLE_INSTANCE> {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    SampleInstance(ALLEGRO_SAMPLE_INSTANCE *object, bool managed = true) : 
        Shared(object, managed, al_destroy_sample_instance, [](ALLEGRO_SAMPLE_INSTANCE *){})
    {
    }

    /**
        Null constructor.
     */
    SampleInstance() {
    }

    /**
        Constructor from sample.
        @param sample sample.
     */
     SampleInstance(Sample &sample) :
        Shared(al_create_sample_instance(sample.get()), al_destroy_sample_instance)
    {
    }

    /**
        Returns the sample instance's channel configuration.
        @return the sample instance's channel configuration.
     */
    ALLEGRO_CHANNEL_CONF getChannelConfiguration() const {
        return al_get_sample_instance_channels(get());
    }

    /**
        Returns the sample instance's depth.
        @return the sample instance's depth.
     */
    ALLEGRO_AUDIO_DEPTH getDepth() const {
        return al_get_sample_instance_depth(get());
    }

    /**
        Returns the sample instance's frequency.
        @return the sample instance's frequency.
     */
    unsigned int getFrequency() const {
        return al_get_sample_instance_frequency(get());
    }

    /**
        Returns the sample instance's length.
        @return the sample instance's length.
     */
    unsigned int getLength() const {
        return al_get_sample_instance_length(get());
    }

    /**
        Returns the sample instance's position.
        @return the sample instance's position.
     */
    unsigned int getPosition() const {
        return al_get_sample_instance_position(get());
    }

    /**
        Returns the sample instance's speed.
        @return the sample instance's speed.
     */
    float getSpeed() const {
        return al_get_sample_instance_speed(get());
    }

    /**
        Returns the sample instance's gain.
        @return the sample instance's gain.
     */
    float getGain() const {
        return al_get_sample_instance_gain(get());
    }

    /**
        Returns the sample instance's pan.
        @return the sample instance's pan.
     */
    float getPan() const {
        return al_get_sample_instance_pan(get());
    }

    /**
        Returns the sample instance's duration, in seconds.
        @return the sample instance's duration, in seconds.
     */
    float getDuration() const {
        return al_get_sample_instance_time(get());
    }

    /**
        Returns the sample instance's play mode.
        @return the sample instance's play mode.
     */
    ALLEGRO_PLAYMODE getPlayMode() const {
        return al_get_sample_instance_playmode(get());
    }

    /**
        Returns the sample instance's playing state.
        @return the sample instance's playing state.
     */
    bool isPlaying() const {
        return al_get_sample_instance_playing(get());
    }

    /**
        Returns the sample instance's attached state.
        @return the sample instance's attached state.
     */
    bool isAttached() const {
        return al_get_sample_instance_attached(get());
    }

    /**
        Returns the sample instance's sample.
        @return the sample instance's sample.
     */
    Sample getSample() const {
        return Sample(al_get_sample(get()), false);
    }

    /**
        Sets the sample instance's length.
        @param val the new value.
        @return true on success.
     */
    bool setLength(unsigned int val) {
        return al_set_sample_instance_length(get(), val);
    }

    /**
        Sets the sample instance's position.
        @param val the new value.
        @return true on success.
     */
    bool setPosition(unsigned int val) {
        return al_set_sample_instance_position(get(), val);
    }

    /**
        Sets the sample instance's speed.
        @param val the new value.
        @return true on success.
     */
    bool setSpeed(float val) {
        return al_set_sample_instance_speed(get(), val);
    }

    /**
        Sets the sample instance's gain.
        @param val the new value.
        @return true on success.
     */
    bool setGain(float val) {
        return al_set_sample_instance_gain(get(), val);
    }

    /**
        Sets the sample instance's pan.
        @param val the new value.
        @return true on success.
     */
    bool setPan(float val) {
        return al_set_sample_instance_pan(get(), val);
    }

    /**
        Sets the sample instance's play mode.
        @param val the new value.
        @return true on success.
     */
    bool setPlayMode(ALLEGRO_PLAYMODE val) {
        return al_set_sample_instance_playmode(get(), val);
    }

    /**
        Sets the sample instance's playing state.
        @param val the new value.
        @return true on success.
     */
    bool setPlaying(bool val) {
        return al_set_sample_instance_playing(get(), val);
    }

    /**
        Plays this sample instance.
        @return true on success.
     */
    bool play() {
        return al_play_sample_instance(get());
    }

    /**
        Stops this sample instance.
        @return true on success.
     */
    bool stop() {
        return al_stop_sample_instance(get());
    }

    /**
        Detaches the instance.
        @return true on success.
     */
    bool detach() {
        return al_detach_sample_instance(get());
    }

    /**
        Change the sample.
        @param sample new sample.
        @return true on success.
     */
    bool setSample(Sample &sample) {
        return al_set_sample(get(), sample.get());
    }
};


} //namespace alx


#endif //ALX_SAMPLEINSTANCE_HPP