#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public AudioSource {
  public:

    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    // AudioSource override: Prepare to play audio.
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    // AudioSource override: Get the next audio block.
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    // AudioSource override: Release audio resources.
    void releaseResources() override;

    // Load an audio file from a URL.
    void loadURL(URL audioURL);
    
    // Set the gain (volume) for the audio.
    void setGain(double gain);
    
    // Set the speed (playback rate) for the audio.
    void setSpeed(double ratio);
    
    // Set the playback position in seconds.
    void setPosition(double posInSecs);
    
    // Set the playback position relative to the current position.
    void setPositionRelative(double pos);
    
    // Start audio playback.
    void start();
    // Stop audio playback.
    void stop();

    // Get the relative position of the playhead.
    double getPositionRelative();

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource; 
    ResamplingAudioSource resampleSource{&transportSource, false, 2};

};




