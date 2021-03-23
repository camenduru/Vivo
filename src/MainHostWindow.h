#pragma once

#include "PluginGraph.h"
#include "GraphEditorPanel.h"

//==============================================================================
namespace CommandIDs
{
#if ! (JUCE_IOS || JUCE_ANDROID)
	static const int open = 0x30000;
	static const int save = 0x30001;
	static const int saveAs = 0x30002;
	static const int newFile = 0x30003;
#endif
	static const int showPluginListEditor = 0x30100;
	static const int showAudioSettings = 0x30200;
	static const int aboutBox = 0x30300;
	static const int allWindowsForward = 0x30400;
	static const int toggleDoublePrecision = 0x30500;
	static const int autoScalePluginWindows = 0x30600;
}

//==============================================================================
ApplicationCommandManager& getCommandManager();
ApplicationProperties& getAppProperties();
bool isOnTouchDevice();

//==============================================================================
enum class AutoScale
{
	scaled,
	unscaled,
	useDefault
};

constexpr bool autoScaleOptionAvailable =
#if JUCE_WINDOWS && JUCE_WIN_PER_MONITOR_DPI_AWARE
true;
#else
false;
#endif

AutoScale getAutoScaleValueForPlugin(const String&);
void setAutoScaleValueForPlugin(const String&, AutoScale);
bool shouldAutoScalePlugin(const PluginDescription&);
void addPluginAutoScaleOptionsSubMenu(AudioPluginInstance*, PopupMenu&);

//==============================================================================
class MainHostWindow : public DocumentWindow,
	public MenuBarModel,
	public ApplicationCommandTarget,
	public ChangeListener,
	public FileDragAndDropTarget
{
public:
	//==============================================================================
	MainHostWindow();
	~MainHostWindow() override;

	//==============================================================================
	void closeButtonPressed() override;
	void changeListenerCallback(ChangeBroadcaster*) override;

	bool isInterestedInFileDrag(const StringArray& files) override;
	void fileDragEnter(const StringArray& files, int, int) override;
	void fileDragMove(const StringArray& files, int, int) override;
	void fileDragExit(const StringArray& files) override;
	void filesDropped(const StringArray& files, int, int) override;

	void menuBarActivated(bool isActive) override;

	StringArray getMenuBarNames() override;
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& menuName) override;
	void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
	ApplicationCommandTarget* getNextCommandTarget() override;
	void getAllCommands(Array<CommandID>&) override;
	void getCommandInfo(CommandID, ApplicationCommandInfo&) override;
	bool perform(const InvocationInfo&) override;

	void tryToQuitApplication();

	void createPlugin(const PluginDescription&, Point<int> pos);

	void addPluginsToMenu(PopupMenu&);
	PluginDescription getChosenType(int menuID) const;

	std::unique_ptr<GraphDocumentComponent> graphHolder;

private:
	//==============================================================================
	static bool isDoublePrecisionProcessingEnabled();
	static bool isAutoScalePluginWindowsEnabled();

	static void updatePrecisionMenuItem(ApplicationCommandInfo& info);
	static void updateAutoScaleMenuItem(ApplicationCommandInfo& info);

	void showAudioSettings();

	//==============================================================================
	AudioDeviceManager deviceManager;
	AudioPluginFormatManager formatManager;

	std::vector<PluginDescription> internalTypes;
	KnownPluginList knownPluginList;
	KnownPluginList::SortMethod pluginSortMethod;
	Array<PluginDescription> pluginDescriptions;

	class PluginListWindow;
	std::unique_ptr<PluginListWindow> pluginListWindow;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainHostWindow)
};
