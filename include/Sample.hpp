#ifndef ALX_SAMPLE_HPP
#define ALX_SAMPLE_HPP


#include <vector>
#include <tuple>
#include "File.hpp"
#include "SampleId.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_SAMPLE.
 */
class Sample : public Shared<ALLEGRO_SAMPLE> {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Sample(ALLEGRO_SAMPLE *object, bool managed = true) : 
        Shared(object, managed, al_destroy_sample, [](ALLEGRO_SAMPLE *){})
    {
    }

    /**
        constructor.
        @param buffer buffer with sample data.
        @param samples number of samples.
        @param freq frequency.
        @param conf channel configuration.
     */
    Sample(std::vector<char> &buffer, unsigned int samples, unsigned int freq, ALLEGRO_AUDIO_DEPTH depth, ALLEGRO_CHANNEL_CONF conf) :
        Shared(al_create_sample(buffer.data(), samples, freq, depth, conf, false), al_destroy_sample)
    {
    }

    /**
        Constructor from file.
        @param filename filename.
     */
    Sample(const char *filename) :
        Shared(al_load_sample(filename), al_destroy_sample)
    {
    }

    /**
        Returns the channel configuration of the sample.
        @return the channel configuration of the sample.
     */
    ALLEGRO_CHANNEL_CONF getChannelConfiguration() const {
        return al_get_sample_channels(get());
    }

    /**
        Returns the depth of the sample.
        @return the depth of the sample.
     */
    ALLEGRO_AUDIO_DEPTH getDepth() const {
        return al_get_sample_depth(get());
    }

    /**
        Returns the frequency of the sample.
        @return the frequency of the sample.
     */
    unsigned int getFrequency() const {
        return al_get_sample_frequency(get());
    }

    /**
        Returns the length of the sample.
        @return the length of the sample.
     */
    unsigned int getLength() const {
        return al_get_sample_length(get());
    }

    /**
        Returns a pointer to the sample data.
        @return a pointer to the sample data.
     */
    void *getData() const {
        return al_get_sample_data(get());
    }

    /**
        Plays this sample.
        @param gain gain.
        @param pan pan.
        @param loop loop flag.
        @param speed speed.
        @return success flag and sample id.
     */
    std::tuple<bool, SampleId> play(float gain, float pan, float speed, ALLEGRO_PLAYMODE loop) {
        SampleId id;
        return std::make_tuple(al_play_sample(get(), gain, pan, speed, loop, &id.get()), id);
    }

    /**
        Loads the sample from a disk file.
        @param filename filename.
        @return true on success.
     */
    bool load(const char *filename) {
        reset(al_load_sample(filename), al_destroy_sample);
        return *this;
    }

    /**
        loads a sample from a file.
        @param file file.
        @param ext filename extension.
     */
    bool load(const File &file, const char *ext) {
        reset(al_load_sample_f(file.get(), ext), al_destroy_sample);
        return *this;
    }

    /**
        Saves a sample.
        @param filename filename.
        @return true on success.
     */
    bool save(const char *filename) const {
        return al_save_sample(filename, get());
    }

    /**
        Saves a sample.
        @param file file.
        @param ext filename extension.
        @return true on success.
     */
    bool save(const File &file, const char *ext) const {
        return al_save_sample_f(file.get(), ext, get());
    }
};


} //namespace alx


#endif //ALX_SAMPLEINSTANCE_HPP