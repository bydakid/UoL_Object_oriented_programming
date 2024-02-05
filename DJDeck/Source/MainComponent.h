#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================

class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    // Constructor for MainComponent.
    MainComponent();
    
    // Destructor for MainComponent.
    ~MainComponent();

    //==============================================================================
    // AudioAppComponent override: Prepare to play audio.
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    // AudioAppComponent override: Get the next audio block.
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    // AudioAppComponent override: Release audio resources.
    void releaseResources() override;

    //==============================================================================
    // Graphics override: Custom drawing code.
    void paint (Graphics& g) override;
    
    // Resize the component and set bounds for GUI components.
    void resized() override;

private:
     
    // Audio format manager for handling audio formats.
    AudioFormatManager formatManager;
    
    // Audio thumbnail cache for storing audio thumbnails.
    AudioThumbnailCache thumbCache{100};
    
    // DJAudioPlayer instances for audio playback.
    DJAudioPlayer player1{formatManager};
    DJAudioPlayer player2{formatManager};
    
    // DeckGUI instances for displaying audio decks.
    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};

    
    // MixerAudioSource for mixing audio from player1 and player2.
    MixerAudioSource mixerSource;
    
    // PlaylistComponent for managing playlists.
    PlaylistComponent playlistComponent;
    
    // Non-copyable class with leak detection support.
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
