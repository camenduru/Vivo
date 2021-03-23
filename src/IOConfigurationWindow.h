#pragma once

class MainHostWindow;
class GraphDocumentComponent;

//==============================================================================
class IOConfigurationWindow : public  AudioProcessorEditor
{
public:
	IOConfigurationWindow(AudioProcessor&);
	~IOConfigurationWindow() override;

	//==============================================================================
	void paint(Graphics& g) override;
	void resized() override;

private:
	class InputOutputConfig;

	AudioProcessor::BusesLayout currentLayout;
	Label title;
	std::unique_ptr<InputOutputConfig> inConfig, outConfig;

	InputOutputConfig* getConfig(bool isInput) noexcept { return isInput ? inConfig.get() : outConfig.get(); }
	void update();

	MainHostWindow* getMainWindow() const;
	GraphDocumentComponent* getGraphEditor() const;
	AudioProcessorGraph* getGraph() const;
	AudioProcessorGraph::NodeID getNodeID() const;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IOConfigurationWindow)
};
