#include "../Source/PluginProcessor.h"
#include "PluginEditor.h"
#include "GUI/MyColours.h"
#include "ParamIDs.h"

//==============================================================================
JRGranularAudioProcessorEditor::JRGranularAudioProcessorEditor(JRGranularAudioProcessor& p,
    juce::AudioProcessorValueTreeState& apvts,
    juce::UndoManager& um)
    : AudioProcessorEditor(&p), audioProcessor(p), undoManager(um), editorContent(apvts, um)
{
    juce::ignoreUnused(audioProcessor);

    const auto ratio = static_cast<double> (defaultWidth) / defaultHeight;
    setResizable(false, true);
    getConstrainer()->setFixedAspectRatio(ratio);
    getConstrainer()->setSizeLimits(defaultWidth / 2, defaultHeight / 2,
        defaultWidth * 2, defaultHeight * 2);
    setSize(defaultWidth, defaultHeight);
    editorContent.setSize(defaultWidth, defaultHeight);

    addAndMakeVisible(editorContent);
}


JRGranularAudioProcessorEditor::JRGranularAudioProcessorEditor(JRGranularAudioProcessor& p,
    juce::AudioProcessorValueTreeState& state,
    juce::UndoManager& um)
    : AudioProcessorEditor(&p), audioProcessor(p), undoManager(um),
    intvDial(*state.getParameter(ParamIDs::interval), um),
    pitchDial(*state.getParameter(ParamIDs::pitch), um),
    sizeDial(*state.getParameter(ParamIDs::grainSize), um),
    posDial(*state.getParameter(ParamIDs::grainPos), um),
    widthDial(*state.getParameter(ParamIDs::width), um),
    mixDial(*state.getParameter(ParamIDs::mix), um),
    gainDial(*state.getParameter(ParamIDs::gain), um)

{
    setWantsKeyboardFocus(true);
    setSize(440, 280);

    intvDial.setLabelText("intv");
    mixDial.setLabelText("mix");
    posDial.setLabelText("pos");
    sizeDial.setLabelText("size");
    gainDial.setLabelText("vol");

    // Set interval of values changed by arrow keys or shift + arrow keys.
    intvDial.setInterval(5.0f);
    intvDial.setFineInterval(1.0f);
    sizeDial.setInterval(5.0f);
    sizeDial.setFineInterval(1.0f);
    posDial.setInterval(5.0f);
    posDial.setFineInterval(1.0f);
    pitchDial.setInterval(1.0f);
    pitchDial.setFineInterval(0.1f);
    gainDial.setInterval(1.0f);
    gainDial.setFineInterval(0.1f);

    addAndMakeVisible(sizeDial);
    addAndMakeVisible(posDial);
    addAndMakeVisible(intvDial);
    addAndMakeVisible(widthDial);
    addAndMakeVisible(pitchDial);
    addAndMakeVisible(mixDial);
    addAndMakeVisible(gainDial);
}

JRGranularAudioProcessorEditor::~JRGranularAudioProcessorEditor()
{
}

//==============================================================================
JRGranularAudioProcessorEditor::JRGranularAudioProcessorEditor(JRGranularAudioProcessor& p,
    juce::AudioProcessorValueTreeState& state,
    juce::UndoManager& um)

{
    auto futuraMedium = juce::Typeface::createSystemTypefaceFor(BinaryData::FuturaMedium_ttf,
        BinaryData::FuturaMedium_ttfSize);
    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(futuraMedium);
}

void JRGranularAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(MyColours::black);
}

void JRGranularAudioProcessorEditor::resized()
{
    const auto factor = static_cast<float> (getWidth()) / defaultWidth;
    editorContent.setTransform(juce::AffineTransform::scale(factor));
}

void JRGranularAudioProcessorEditor::resized()
{
    intvDial.setBounds(30, 30, 80, 95);
    pitchDial.setBounds(130, 30, 80, 95);
    sizeDial.setBounds(230, 30, 80, 95);
    posDial.setBounds(330, 30, 80, 95);
    widthDial.setBounds(80, 155, 80, 95);
    mixDial.setBounds(180, 155, 80, 95);
    gainDial.setBounds(280, 155, 80, 95);
}

bool JRGranularAudioProcessorEditor::keyPressed(const juce::KeyPress& key)
{
    const auto cmdZ = juce::KeyPress{ 'z', juce::ModifierKeys::commandModifier, 0 };

    if (key == cmdZ && undoManager.canUndo())
    {
        undoManager.undo();
        return true;
    }

    const auto cmdShiftZ = juce::KeyPress{ 'z', juce::ModifierKeys::commandModifier
                                                 | juce::ModifierKeys::shiftModifier, 0 };

    if (key == cmdShiftZ && undoManager.canRedo())
    {
        undoManager.redo();
        return true;
    }

    return false;
}