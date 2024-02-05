#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================

PlaylistComponent::PlaylistComponent()
{
    // Add and make the table component visible.
    addAndMakeVisible(tableComponent);
    
    // Initialize track titles.
    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    
    // Define table columns.
    tableComponent.getHeader().addColumn("Track Title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 400);
    
    // Set the model for the table component to this PlaylistComponent instance.
    tableComponent.setModel(this);
    
}

// Destructor for PlaylistComponent.
PlaylistComponent::~PlaylistComponent()
{
}


// Graphics override: Custom painting code.
void PlaylistComponent::paint (juce::Graphics& g)
{
    // Fill the background with a color.
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    // Draw an outline around the component.
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    // Set color, font, and draw placeholder text.
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

// Resize the component and set bounds for child components.
void PlaylistComponent::resized()
{
    // Set the bounds of the table component to fill the entire area of this component.
    tableComponent.setBounds(0, 0, getWidth(), getHeight());

}

// Get the number of rows in the table.
int PlaylistComponent::getNumRows(){
    return trackTitles.size();
}

// Custom painting of row backgrounds.
void PlaylistComponent::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(Colours::darkgrey);
    }
}

// Custom painting of cells.
void PlaylistComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.drawText(trackTitles[rowNumber], 2, 0, width - 4, Justification::centredLeft, true);
}

// Refresh the component for a cell.
Component* PlaylistComponent::refreshComponentForCell ( int rowNumber, int columnId, bool isRowSelected, Component*existingComponentToUpdate)
{
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            // Create an "Upload" button for the cell.
            TextButton* btn = new TextButton("Upload");
            String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            
            // Add a listener to the button.
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

// Handle button clicks.
void PlaylistComponent::buttonClicked(Button* button)
{
    // Extract the ID from the button's component ID and log the clicked track title.
    int id = std::stoi(button->getComponentID().toStdString());
    DBG("PlaylistComponent::buttonClicked " << trackTitles[id]);
}




