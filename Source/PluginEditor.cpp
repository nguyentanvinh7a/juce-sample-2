/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestjuceAudioProcessorEditor::TestjuceAudioProcessorEditor (TestjuceAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    mLoadButton.onClick = [&]() {audioProcessor.loadFile(); };
    addAndMakeVisible(mLoadButton);
    setSize (200, 200);
}

TestjuceAudioProcessorEditor::~TestjuceAudioProcessorEditor()
{
}

//==============================================================================
void TestjuceAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.setFont(15.f);
    if (audioProcessor.getNumSamplerSounds() > 0) {
        g.fillAll(Colours::red);
        g.setColour(Colours::white);
        g.setFont(15.f);
        g.drawText("Sound loaded", getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 20, Justification::centred);
    }
    else
        g.drawText("Loading a sound", getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 20, Justification::centred);
    //if we have a sound
        //"sound loaded"
    //else 
        //"loaded a sound"
}

void TestjuceAudioProcessorEditor::resized()
{
    //mLoadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
}

bool TestjuceAudioProcessorEditor::isInterestedInFileDrag(const StringArray& files) {
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
            return true;
    }
    return false;
}
void TestjuceAudioProcessorEditor::filesDropped(const StringArray& files, int x, int y) {
    for (auto file : files) {
        if (isInterestedInFileDrag(file)) {
            audioProcessor.loadFile(file);
        }
    }
    repaint();
}
