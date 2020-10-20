/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
        getLookAndFeel().setColour (juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB (242, 202, 16));
        getLookAndFeel().setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB (115, 155, 184));
        getLookAndFeel().setColour (juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB (44, 53, 57));
        
        using SliderStyle    = juce::Slider::SliderStyle;
        using Attachment     = juce::SliderParameterAttachment;
        const auto boxWidth  = 35;
        const auto boxHeight = 15;
        
        rateSlider.setSliderStyle (SliderStyle::RotaryVerticalDrag);
        rateSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, boxWidth, boxHeight);
        addAndMakeVisible (rateSlider);
        
        depthSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
        depthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, boxWidth, boxHeight);
        addAndMakeVisible (depthSlider);
        
        centreDelaySlider.setSliderStyle (SliderStyle::RotaryVerticalDrag);
        centreDelaySlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, boxWidth, boxHeight);
        addAndMakeVisible (centreDelaySlider);
        
        feedbackSlider.setSliderStyle (SliderStyle::RotaryVerticalDrag);
        feedbackSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, boxWidth, boxHeight);
        addAndMakeVisible (feedbackSlider);
        
        mixSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
        mixSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, boxWidth, boxHeight);
        addAndMakeVisible (mixSlider);
        
        rateLabel.setJustificationType (juce::Justification::centred);
        addAndMakeVisible (rateLabel);
        depthLabel.setJustificationType (juce::Justification::centred);
        addAndMakeVisible (depthLabel);
        delayLabel.setJustificationType (juce::Justification::centred);
        addAndMakeVisible (delayLabel);
        feedbackLabel.setJustificationType (juce::Justification::centred);
        addAndMakeVisible (feedbackLabel);
        mixLabel.setJustificationType (juce::Justification::centred);
        addAndMakeVisible (mixLabel);
        
        pluginTitle.setFont (currentFont.boldened().withHeight (60.0f));
        pluginTitle.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
        addAndMakeVisible (pluginTitle);
        
        auto& apvts = audioProcessor.apvts;
        
        rateSliderAttachment        = std::make_unique<Attachment>(*apvts.getParameter ("RATE"), rateSlider);
        depthSliderAttachment       = std::make_unique<Attachment>(*apvts.getParameter ("DEPTH"), depthSlider);
        centreDelaySliderAttachment = std::make_unique<Attachment>(*apvts.getParameter ("CENTREDELAY"), centreDelaySlider);
        feedbackSliderAttachment    = std::make_unique<Attachment>(*apvts.getParameter ("FEEDBACK"), feedbackSlider);
        mixSliderAttachment         = std::make_unique<Attachment>(*apvts.getParameter ("MIX"), mixSlider);
        
    
        setSize (400, 350);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    
    currentFont = g.getCurrentFont();

    g.setColour (juce::Colours::white);
    
}

void NewProjectAudioProcessorEditor::resized()
{
    const auto column0      = 0.05f;
    const auto column1      = 0.28f;
    const auto column2      = 0.52f;
    const auto row0         = 0.27f;
    const auto row1         = 0.67f;
    const auto row2         = 0.40;
    const auto dialSize     = 0.30;
    const auto labelSpace   = 0.03;
    const auto labelHeight  = 0.05f;
    
    pluginTitle.setBoundsRelative (0.45f, 0.04f, 0.5f, 0.15f);
    
    rateLabel.setBoundsRelative (column0, row0 - labelSpace, dialSize, labelHeight);
    rateSlider.setBoundsRelative (column0, row0, dialSize, dialSize);
    
    depthLabel.setBoundsRelative (column1, row0 - labelSpace, dialSize, labelHeight);
    depthSlider.setBoundsRelative (column1, row0, dialSize, dialSize);
    
    delayLabel.setBoundsRelative (column0, row1 - labelSpace, dialSize, labelHeight);
    centreDelaySlider.setBoundsRelative (column0, row1, dialSize, dialSize);
    
    feedbackLabel.setBoundsRelative (column1, row1 - labelSpace, dialSize, labelHeight);
    feedbackSlider.setBoundsRelative (column1, row1, dialSize, dialSize);
    
    mixLabel.setBoundsRelative (column2, row2 - labelSpace, dialSize, labelHeight);
    mixSlider.setBoundsRelative (column2, row2, (dialSize * 0.33f), dialSize + (dialSize * 0.33f));
}
