#ifndef ALX_MIXER_HPP
#define ALX_MIXER_HPP


#include <functional>
#include <list>
#include "SampleInstance.hpp"
#include "AudioStream.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_MIXER.
 */
class Mixer : public Shared<ALLEGRO_MIXER> {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Mixer(ALLEGRO_MIXER *object, bool managed = true) : 
        Shared(object, managed, al_destroy_mixer, [](ALLEGRO_MIXER *){})
    {
    }

    /**
        constructor.
        @param freq frequency.
        @param depth depth.
        @param conf configuration.
     */
    Mixer(unsigned int freq, ALLEGRO_AUDIO_DEPTH depth, ALLEGRO_CHANNEL_CONF conf) :
        Shared(al_create_mixer(freq, depth, conf), al_destroy_mixer)
    {
    }

    /**
        Returns the default mixer.
        @return the default mixer.
     */
    static Mixer getDefault() {
        return Mixer(al_get_default_mixer(), false);
    }

    /**
        Returns the mixer's .
        @return the mixer's .
     */
    unsigned int getFrequency() const {
        return al_get_mixer_frequency(get());
    }

    /**
        Returns the mixer's channel configuration.
        @return the mixer's channel configuration.
     */
    ALLEGRO_CHANNEL_CONF getChannelConfiguration() const {
        return al_get_mixer_channels(get());
    }

    /**
        Returns the mixer's depth.
        @return the mixer's depth.
     */
    ALLEGRO_AUDIO_DEPTH getDepth() const {
        return al_get_mixer_depth(get());
    }

    /**
        Returns the mixer's .
        @return the mixer's .
     */
    ALLEGRO_MIXER_QUALITY getQuality() const {
        return al_get_mixer_quality(get());
    }

    /**
        Returns the mixer's playing state.
        @return the mixer's playing state.
     */
    bool isPlaying() const {
        return al_get_mixer_playing(get());
    }

    bool isAttached() const {
    /**
        Returns the mixer's .
        @return the mixer's .
     */
        return al_get_mixer_attached(get());
    }

    /**
        Sets the mixer's .
        @param val the new value.
        @return true on success.
     */
    bool setFrequency(unsigned int val) {
        return al_set_mixer_frequency(get(), val);
    }

    /**
        Sets the mixer's .
        @param val the new value.
        @return true on success.
     */
    bool setQuality(ALLEGRO_MIXER_QUALITY val) {
        return al_set_mixer_quality(get(), val);
    }

    /**
        Sets the mixer's .
        @param val the new value.
        @return true on success.
     */
    bool setPlaying(bool val) {
        return al_set_mixer_playing(get(), val);
    }

    /**
        Sets this mixer as the default.
        @return true on success.
     */
    bool setDefault() {
        return al_set_default_mixer(get());
    }

    /**
        Attaches the given mixer to this.
        @param mixer mixer to attach to this.
        @return true on success.
     */
    bool attach(Mixer &mixer) {
        return al_attach_mixer_to_mixer(mixer.get(), get());
    }

    /**
        Attaches the given sample instance to this.
        @param instance sample instance to attach to this.
        @return true on success.
     */
    bool attach(SampleInstance &instance) {
        return al_attach_sample_instance_to_mixer(instance.get(), get());
    }

    /**
        Attaches the given audio stream to this.
        @param stream the audio stream to attach to this.
        @return true on success.
     */
    bool attach(AudioStream &stream) {
        return al_attach_audio_stream_to_mixer(stream.get(), get());
    }

    /**
        Detaches the mixer from whatever it is attached on.
        @return true on success.
     */
    bool detach() {
        return al_detach_mixer(get());
    }

    /**
        Sets the post-process callback.
        @param ppCallback pointer to the callback function.
        @param ppCallbackUserData user data.
        @return true on success.
     */
    bool setPostProcessCallback(void (*ppCallback)(void *buf, unsigned int samples, void *data), void *ppCallbackUserdata) {
        return al_set_mixer_postprocess_callback(get(), ppCallback, ppCallbackUserdata);
    }

    /**
        Type of std::function for the post-process callback.
     */
    typedef std::function<void(void *, unsigned int, void *)> PostProcessCallbackFunctionType;

    /**
        Type of shared pointer to the function.
     */
    typedef std::shared_ptr<PostProcessCallbackFunctionType> PostProcessCallbackFunctionTypePtr;

    /**
        Sets an std::function to be invoked as a post-process callback.
        @param fn function to invoke.
        @return the pointer to the function or null if the function fails.
            The result must be kept around for as long as the post process callback is valid.
     */
    PostProcessCallbackFunctionTypePtr setPostProcessCallback(PostProcessCallbackFunctionType &fn) {
        PostProcessCallbackFunctionTypePtr ptr = PostProcessCallbackFunctionTypePtr(new PostProcessCallbackFunctionType(fn));
        return al_set_mixer_postprocess_callback(get(), _postProcessFunctionCallback, ptr.get()) ? ptr : nullptr;        
    }

private:
    //invokes the user function object.
    static void _postProcessFunctionCallback(void *buf, unsigned int samples, void *data) {
        PostProcessCallbackFunctionType *fn = (PostProcessCallbackFunctionType *)data;
        fn->operator ()(buf, samples, data);
    }
};


} //namespace alx


#endif //ALX_MIXER_HPP