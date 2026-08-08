#pragma once

#include <functional>
#include <string>
#include <vector>

namespace rigkit {

class IMui;

/**
 * @brief Shared document-host chrome (Viewer / Player).
 * @details File → Open, skipped-key list, Edit Mode / dock defaults.
 * Does not load documents or run code — apps supply @ref setOnOpenPath.
 * Not generic host chrome (plotter / OSC / …); not rigProject serialize.
 */
class DocumentShell {
  public:
	using OpenPathFn = std::function<void(const std::string& path)>;
	using NeedsPlayerFn = std::function<void()>;

	void setOnOpenPath(OpenPathFn fn) { m_onOpen = std::move(fn); }
	/** @brief Optional; called from @ref notifyNeedsPlayer after the log line. */
	void setOnNeedsPlayer(NeedsPlayerFn fn) { m_onNeedsPlayer = std::move(fn); }

	/** @brief Extensions for the open dialog (default `.rig` `.json`; `.pg` legacy alias). */
	void setOpenFilters(std::vector<std::string> filters) { m_filters = std::move(filters); }

	void setDocumentTitle(std::string title) { m_title = std::move(title); }
	const std::string& documentTitle() const { return m_title; }

	void setSkippedKeys(std::vector<std::string> keys) { m_skipped = std::move(keys); }
	const std::vector<std::string>& skippedKeys() const { return m_skipped; }

	/**
	 * @brief Wire File→Open, Edit Mode, dock passthrough onto @p ui.
	 * @param editModeOn Start Edit Mode UI ON (host must also call
	 *        RigKitEngine::enableEditMode(true) when it wants the feature).
	 * @param dockPassthroughCentral GL bed shows through central dock node.
	 */
	void attachChrome(IMui& ui, bool editModeOn = true, bool dockPassthroughCentral = true);

	/** @brief Open the file dialog (also bound to File → Open… by @ref attachChrome). */
	void promptOpen();

	/** @brief Cart-like document — call after load so Viewer can point at RigPlayer. */
	void notifyNeedsPlayer();

	/**
	 * @brief Heuristic: skipped cart schemas and/or Lua / pico8 code buffer.
	 * Viewer cannot play these; RigPlayer can.
	 */
	static bool looksLikeCart(const std::vector<std::string>& skippedKeys, bool hasLuaCode);

  private:
	OpenPathFn m_onOpen;
	NeedsPlayerFn m_onNeedsPlayer;
	IMui* m_ui = nullptr;
	std::vector<std::string> m_filters{".rig", ".json", ".pg"};
	std::string m_title;
	std::vector<std::string> m_skipped;
};

} // namespace rigkit
