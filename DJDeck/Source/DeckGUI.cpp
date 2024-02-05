#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================

DeckGUI::DeckGUI(DJAudioPlayer* _player,
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{

    // Add and make visible various UI components.
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);

    // Add listeners to the buttons and sliders.
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    // Set the range for sliders.
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);

    // Start a timer with a callback interval of 500 milliseconds.
    startTimer(500);


}

DeckGUI::~DeckGUI()
{
    // Stop the timer in the destructor.
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    // Custom painting code.
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (Colours::green);
    g.setFont (10.0f);
    g.drawText ("Simon's DJ Deck", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    const double rowH = getHeight() / 8;
    const int componentWidth = getWidth();
    
    loadButton.setBounds(0, 0, componentWidth, rowH);
    volSlider.setBounds(componentWidth/8, rowH * 4, componentWidth/4*3, rowH);
    speedSlider.setBounds(componentWidth/8, rowH * 5, componentWidth/4*3, rowH);
    posSlider.setBounds(componentWidth/8, rowH * 6, componentWidth/4*3, rowH);
    waveformDisplay.setBounds(0, rowH, componentWidth, rowH * 2.5);
    playButton.setBounds(0, rowH * 7, componentWidth/2, rowH);
    stopButton.setBounds(componentWidth/2, rowH * 7, componentWidth/2, rowH);
}


void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
       if (button == &loadButton)
    {
        auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            player->loadURL(URL{chooser.getResult()});
            // and now the waveformDisplay as well
            waveformDisplay.loadURL(URL{chooser.getResult()}); 
        });
    }
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}


    

