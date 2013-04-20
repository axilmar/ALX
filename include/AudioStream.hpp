#ifndef ALX_AUDIOSTREAM_HPP
#define ALX_AUDIOSTREAM_HPP


#include <allegro5/allegro_audio.h>
#include "EventSource.hpp"
#include "File.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_AUDIO_STREAM.
 */
class AudioStream : public Shared<ALLEGRO_AUDIO_STREAM> {
public:
    /**
        Null constructor.
     */
    AudioStream() {
    }

    /**
        constructor.
        @param fragmentCount How many fragments to use for the audio stream.
        @param samples The size of a fragment in samples.
        @param freq The frequency, in Hertz.
        @param depth Must be one of the values listed for ALLEGRO_AUDIO_DEPTH.
        @param conf Must be one of the values listed for ALLEGRO_CHANNEL_CONF.
     */
    AudioStream(size_t fragmentCount, unsigned int samples, unsigned int freq, ALLEGRO_AUDIO_DEPTH depth, ALLEGRO_CHANNEL_CONF conf) :
        Shared(al_create_audio_stream(fragmentCount, samples, freq, depth, conf), al_destroy_audio_stream)
    {
    }

    /**
        Loads an audio stream from a disk file.
        @param filename file name.
        @param bufferCount number of buffers.
        @param sampleCount number of samples.
     */
    AudioStream(const char *filename, size_t bufferCount, size_t sampleCount) :
        Shared(al_load_audio_stream(filename, bufferCount, sampleCount), al_destroy_audio_stream)
    {
    }

    /**
        Loads an audio stream from an open file.
        @param file file.
        @param ext extension.
        @param bufferCount number of buffers.
        @param sampleCount number of samples.
     */
    AudioStream(const File &file, const char *ext, size_t bufferCount, size_t sampleCount) :
        Shared(al_load_audio_stream_f(file.get(), ext, bufferCount, sampleCount), al_destroy_audio_stream)
    {
    }

    /**
        Returns the event source for this stream.
        @return the event source for this stream.
     */
    EventSource getEventSource() const {
        return EventSource(al_get_audio_stream_event_source(get()), false);
    }

    /**
        Returns the stream's frequency.
        @return the stream's frequency.
     */
    unsigned int getFrequency() const {
        return al_get_audio_stream_frequency(get());
    }

    /**
        Returns the stream's channel configuration.
        @return the stream's channel configuration.
     */
    ALLEGRO_CHANNEL_CONF getChannelConfiguration() const {
        return al_get_audio_stream_channels(get());
    }

    /**
        Returns the stream's depth.
        @return the stream's depth.
     */
    ALLEGRO_AUDIO_DEPTH getDepth() const {
        return al_get_audio_stream_depth(get());
    }

    /**
        Returns the stream's samples count.
        @return the stream's samples count.
     */
    unsigned int getLength() const {
        return al_get_audio_stream_length(get());
    }

    /**
        Returns the relative speed playback.
        @return the relative speed playback.
     */
    float getSpeed() const {
        return al_get_audio_stream_speed(get());
    }

    /**
        Returns the playback gain.
        @return the playback gain.
     */
    float getGain() const {
        return al_get_audio_stream_gain(get());
    }

    /**
        Returns the pan.
        @return the pan.
     */
    float getPan() const {
        return al_get_audio_stream_pan(get());
    }

    /**
        Checks if the stream is playing.
        @return true if the stream is playing.
     */
    bool isPlaying() const {
        return al_get_audio_stream_playing(get());
    }

    /**
        Checks if the stream is attached.
        @return true if the stream is attached.
     */
    bool isAttached() const {
        return al_get_audio_stream_attached(get());
    }

    /**
        Returns the play mode.
        @return the play mode.
     */
    ALLEGRO_PLAYMODE getPlayMode() const {
        return al_get_audio_stream_playmode(get());
    }

    /**
        Returns a buffer to provide new sample data to the stream.
        @return a buffer to provide new sample data to the stream.
     */
    void *getFragment() const {
        return al_get_audio_stream_fragment(get());
    }

    /**
        Returns the number of fragments the stream uses.
        @return the number of fragments the stream uses.
     */
    unsigned int getFragmentCount() const {
        return al_get_audio_stream_fragments(get());
    }

    /**
        Returns the number of available fragments.
        @return the number of available fragments.
     */
    unsigned int getAvailableFragmentCount() const {
        return al_get_available_audio_stream_fragments(get());
    }

    /**
        Returns the time position of the stream, in seconds.
        @return the time position of the stream, in seconds.
     */
    double getTimePosition() const {
        return al_get_audio_stream_position_secs(get());
    }

    /**
        Returns the length of the stream, in seconds.
        @return the length of the stream, in seconds.
     */
    double getTimeLength() const {
        return al_get_audio_stream_length_secs(get());
    }

    /**
        finalises an audio stream that will no longer be fed.
     */
    void drain() {
        al_drain_audio_stream(get());
    }

    /**
        Sets the playing position to the beginning.
        @return true on success.
     */
    bool rewind() {
        return al_rewind_audio_stream(get());
    }

    /**
        Sets the playback speed.
        @param val speed value.
        @return true on success.
     */
    bool setSpeed(float val) {
        return al_set_audio_stream_speed(get(), val);
    }

    /**
        Sets the playback gain.
        @param val gain value.
        @return true on success.
     */
    bool setGain(float val) {
        return al_set_audio_stream_gain(get(), val);
    }

    /**
        Sets the pan.
        @param val pan value.
        @return true on success.
     */
    bool setPan(float val) {
        return al_set_audio_stream_pan(get(), val);
    }

    /**
        Sets the playing state of the stream.
        @param val the new playing state.
        @return true on success.
     */
    bool setPlaying(bool val) {
        return al_set_audio_stream_playing(get(), val);
    }

    /**
        Sets the play mode.
        @param val the new play mode.
        @return true on success.
     */
    bool setPlayMode(ALLEGRO_PLAYMODE val) {
        return al_set_audio_stream_playmode(get(), val);
    }

    /**
        Detaches the audio stream for whatever it is attached to.
        @return true on success.
     */
    bool detach() {
        return al_detach_audio_stream(get());
    }

    /**
        This function needs to be called for every successful call of getFragment to indicate that the buffer is filled with new data.
        @param val the fragmnet pointer returned by getFragment.
        @return true on success.
     */
    bool setFragment(void *val) {
        return al_set_audio_stream_fragment(get(), val);
    }

    /**
        Seeks a file playing position.
        @param secs time in seconds to seek.
        @return true on success.
     */
    bool setTimePosition(double secs) {
        return al_seek_audio_stream_secs(get(), secs);
    }

    /**
        Sets the loop points.
        @param startSecs start time point, in seconds.
        @param endSecs end time point, in seconds.
     */
    bool setTimeLoop(double startSecs, double endSecs) {
        return al_set_audio_stream_loop_secs(get(), startSecs, endSecs);
    }

    /**
        Loads an audio stream from a disk file.
        @param filename filename.
        @param bufferCount number of buffers.
        @param sampleCount number of samples.
        @return true on success.
     */
    bool load(const char *filename, size_t bufferCount, size_t sampleCount) {
        reset(al_load_audio_stream(filename, bufferCount, sampleCount), al_destroy_audio_stream);
        return (bool)(*this);
    }

    /**
        loads an audio stream from a file.
        @param file file.
        @param ext filename extension.
        @param bufferCount number of buffers.
        @param sampleCount number of samples.
     */
    bool load(const File &file, const char *ext, size_t bufferCount, size_t sampleCount) {
        reset(al_load_audio_stream_f(file.get(), ext, bufferCount, sampleCount), al_destroy_audio_stream);
        return (bool)(*this);
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    AudioStream(ALLEGRO_AUDIO_STREAM *object, bool managed = true) :
        Shared(object, managed, al_destroy_audio_stream, [](ALLEGRO_AUDIO_STREAM *){})
    {
    }
};


} //namespace alx


#endif //ALX_AUDIOSTREAM_HPP
