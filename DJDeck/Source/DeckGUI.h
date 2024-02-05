#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================

class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    // Constructor for DeckGUI.
    DeckGUI(DJAudioPlayer* player,
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    // Destructor for DeckGUI.
    ~DeckGUI();

    // Graphics override: Custom painting code.
    void paint (Graphics&) override;
    
    // Resize the component.
    void resized() override;

    // Button::Listener implementation.
    void buttonClicked (Button *) override;

    // Slider::Listener implementation.
    void sliderValueChanged (Slider *slider) override;

    // Determine if the component is interested in file drag-and-drop.
    bool isInterestedInFileDrag (const StringArray &files) override;
    
    // Handle files dropped onto the component.
    void filesDropped (const StringArray &files, int x, int y) override;

    // Timer callback.
    void timerCallback() override;

private:

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"UPLOAD"};
  
    Slider volSlider; 
    Slider speedSlider;
    Slider posSlider;

    FileChooser fChooser{"Select a file..."};


    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
