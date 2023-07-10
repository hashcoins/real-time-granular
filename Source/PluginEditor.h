#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/EditorLnf.h"
#include "EditorContent.h
#include "Dial.h"



//==============================================================================
/**
*/
class JRGranularAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    JRGranularAudioProcessorEditor(JRGranularAudioProcessor& p,
        juce::AudioProcessorValueTreeState& apvts,
        juce::UndoManager& um);
    ~JRGranularAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    bool keyPressed(const juce::KeyPress& key) override;

private:
    JRGranularAudioProcessor& audioProcessor;

    juce::UndoManager& undoManager;

    EditorContent editorContent;

    static constexpr int defaultWidth{ 440 };
    static constexpr int defaultHeight{ 280 };

    struct SharedLnf
    {
        SharedLnf() { juce::LookAndFeel::setDefaultLookAndFeel(&editorLnf); }
        ~SharedLnf() { juce::LookAndFeel::setDefaultLookAndFeel(nullptr); }

        EditorLnf editorLnf;
    };

    SharedResourcePointer<SharedLnf> lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JRGranularAudioProcessorEditor)
};