#ifndef ALX_VOICE_HPP
#define ALX_VOICE_HPP


#include "AudioStream.hpp"
#include "Mixer.hpp"
#include "SampleInstance.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_VOICE.
 */
class Voice : public Shared<ALLEGRO_VOICE> {
public:
    /**
        Null constructor.
     */
    Voice() {
    }

    /**
        Constructs a new voice.
        @param freq frequency.
        @param depth depth.
        @param conf channel configuration.
     */
    Voice(unsigned int freq, ALLEGRO_AUDIO_DEPTH depth, ALLEGRO_CHANNEL_CONF conf) :
        Shared(al_create_voice(freq, depth, conf), al_destroy_voice)
    {
    }

    /**
        Returns the frequency of the voice.
        @return the frequency of the voice.
     */
    unsigned int getFrequency() const {
        return al_get_voice_frequency(get());
    }

    /**
        Returns the channel configuration of the voice.
        @return the channel configuration of the voice.
     */
    ALLEGRO_CHANNEL_CONF getChannelConfiguration() const {
        return al_get_voice_channels(get());
    }

    /**
        Returns the depth of the voice.
        @return the depth of the voice.
     */
    ALLEGRO_AUDIO_DEPTH getDepth() const {
        return al_get_voice_depth(get());
    }

    /**
        Checks if the voice is playing.
        @return true if playing.
     */
    bool isPlaying() const {
        return al_get_voice_playing(get());
    }

    /**
        It returns the curent sample's position, if there is one.
        @return the current position.
     */
    unsigned int getPosition() const {
        return al_get_voice_position(get());
    }

    /**
        Detaches the voice from the mixer.
     */
    void detach() {
        al_detach_voice(get());
    }

    /**
        Attaches an audio stream to this voice.
        @param stream audio stream to attach.
        @return true on success.
     */
    bool attach(AudioStream &stream) {
        return al_attach_audio_stream_to_voice(stream.get(), get());
    }

    /**
        Attaches a mixer to this voice.
        @param mixer mixer to attach.
        @return true on success.
     */
    bool attach(Mixer &mixer) {
        return al_attach_mixer_to_voice(mixer.get(), get());
    }

    /**
        Attaches a sample instance to this voice.
        @param sample sample instance.
        @return true on success.
     */
    bool attach(SampleInstance &sample) {
        return al_attach_sample_instance_to_voice(sample.get(), get());
    }

    /**
        Set the voice playing or not.
        @param playing playing flag.
        @return true on success.
     */
    bool setPlaying(bool playing) {
        return al_set_voice_playing(get(), playing);
    }

    /**
        Sets the voice position, if it as a non-streaming object.
        @param val new value.
        @return true on success.
     */
    bool setVoicePosition(unsigned int val) {
        return al_set_voice_position(get(), val);
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Voice(ALLEGRO_VOICE *object, bool managed = true) : 
        Shared(object, managed, al_destroy_voice)
    {
    }
};


} //namespace alx


#endif //ALX_VOICE_HPP
