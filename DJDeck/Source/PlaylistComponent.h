#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

//==============================================================================

class PlaylistComponent  :  public juce::Component,
                            public juce::TableListBoxModel,
                            public Button::Listener

{
public:
    // Constructor for PlaylistComponent.
    PlaylistComponent();
    
    // Destructor for PlaylistComponent.
    ~PlaylistComponent() override;

    // Graphics override: Custom painting code.
    void paint (juce::Graphics&) override;
    
    // Resize the component and set bounds for child components.
    void resized() override;
    
    // Get the number of rows in the table.
    int getNumRows () override;
    
    // Custom painting of row backgrounds.
    void paintRowBackground (Graphics &,
                             int rowNumber,
                             int width,
                             int height,
                             bool rowIsSelected) override;
    
    // Custom painting of cells.
    void paintCell (Graphics &,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    
    // Refresh the component for a cell.
    Component* refreshComponentForCell (int rowNumber,
                                        int columnId,
                                        bool isRowSelected,
                                        Component *existingComponentToUpdate) override;
    
    // Handle button clicks.
    void buttonClicked(Button* button) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
    TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    TextButton addFilesButton;
};
