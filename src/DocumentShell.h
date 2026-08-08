#pragma once

#include <functional>
#include <string>
#include <vector>

namespace rigkit {

class Mui;
class IMui;

/**
 * @brief Shared document-host chrome (Viewer / Player).
 * @details File → Open, skipped-key list, Edit Mode / dock defaults.
 * Does not load documents or run code — apps supply @ref setOnOpenPath.
 */
class DocumentShell {
  public:
	using OpenPathFn = std::function<void(const std::string& path)>;
	using NeedsPlayerFn = std::function<void()>;

	void setOnOpenPath(OpenPathFn fn) { m_onOpen = std::move(fn); }
	void setOnNeedsPlayer(NeedsPlayerFn fn) { m_onNeedsPlayer = std::move(fn); }

	/** @brief Extensions for the open dialog (default `.json` `.rig` `.pg`). */
	void setOpenFilters(std::vector<std::string> filters) { m_filters = std::move(filters); }

	void setDocumentTitle(std::string title) { m_title = std::move(title); }
	const std::string& documentTitle() const { return m_title; }

	void setSkippedKeys(std::vector<std::string> keys) { m_skipped = std::move(keys); }
	const std::vector<std::string>& skippedKeys() const { return m_skipped; }

	/**
	 * @brief Wire File→Open, Edit Mode, dock passthrough onto @p mui.
	 * @param editModeOn Start in Edit Mode (Ctrl+E still toggles when enabled on engine).
	 * @param dockPassthroughCentral GL bed shows through central dock node.
	 */
	void attachChrome(Mui& mui, bool editModeOn = true, bool dockPassthroughCentral = true);

	/** @brief Open the file dialog (also bound to File → Open… by @ref attachChrome). */
	void promptOpen();

	/** @brief Cart-like document — call after load so hosts can deep-link to Player. */
	void notifyNeedsPlayer();

	/**
	 * @brief Heuristic: skipped pixel/music/input keys and/or Lua code buffer.
	 * Viewer cannot play these; Player / PICO-8 can.
	 */
	static bool looksLikeCart(const std::vector<std::string>& skippedKeys, bool hasLuaCode);

  private:
	OpenPathFn m_onOpen;
	NeedsPlayerFn m_onNeedsPlayer;
	IMui* m_ui = nullptr;
	std::vector<std::string> m_filters{".json", ".rig", ".pg"};
	std::string m_title;
	std::vector<std::string> m_skipped;
};

} // namespace rigkit
