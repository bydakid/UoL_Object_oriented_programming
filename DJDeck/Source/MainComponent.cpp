#include "MainComponent.h"

//==============================================================================

MainComponent::MainComponent()
{
    setSize (800, 600);
    
    // Check if recording audio permissions are required and if not already granted, request them.
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // If audio recording permissions are not required or have already been granted, set audio channels to 0.
        setAudioChannels (0, 2);
    }  

    // Add and make the GUI components visible.
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlistComponent);

    // Register basic audio formats with the format manager.
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    // Shut down the audio.
    shutdownAudio();
}

//==============================================================================

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // Prepare the audio player for play.
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    // Prepare the mixer source for play.
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // Add input sources (players) to the mixer.
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

 }
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Get the next audio block from the mixer source.
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This function will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // Release audio resources for player1, player2, and the mixer source.
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================

void MainComponent::paint (Graphics& g)
{
    // Fill the background with a solid color.
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // Set the bounds for the GUI components.
    deckGUI1.setBounds(0, 0, getWidth()/2, getHeight()/2);
    deckGUI2.setBounds(getWidth()/2, 0, getWidth()/2, getHeight()/2);
    
    playlistComponent.setBounds(0, getHeight()/2, getWidth(), getHeight()/2);

}

