#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================

class WaveformDisplay    : public Component, 
                           public ChangeListener
{
public:
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
    ~WaveformDisplay();

    // Graphics override: Custom painting code.
    void paint (Graphics&) override;
    // Resize the component.
    void resized() override;

    // ChangeListener callback for handling changes in the audio thumbnail.
    void changeListenerCallback (ChangeBroadcaster *source) override;

    // Load an audio file from a URL.
    void loadURL(URL audioURL);

    // Set the relative position of the playhead.
    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumb;
    bool fileLoaded; 
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
