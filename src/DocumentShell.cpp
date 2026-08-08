#include "DocumentShell.h"

#include "core/IMui.h"

#include <spdlog/spdlog.h>

namespace rigkit {

void DocumentShell::attachChrome(IMui& ui, bool editModeOn, bool dockPassthroughCentral) {
	m_ui = &ui;
	ui.setDockPassthroughCentral(dockPassthroughCentral);
	if (editModeOn) {
		ui.setEditMode(true);
	}
	ui.registerFileAction(
		"Open...", [this]() { promptOpen(); }, "Ctrl+O");
}

void DocumentShell::promptOpen() {
	if (!m_ui) {
		spdlog::warn("[rigDocumentShell] promptOpen: attachChrome first");
		return;
	}
	m_ui->openFileDialog("Open Rig document", m_filters, [this](const std::string& path) {
		if (path.empty() || !m_onOpen) {
			return;
		}
		m_ui->noteRecentFile(path);
		m_onOpen(path);
	});
}

void DocumentShell::notifyNeedsPlayer() {
	spdlog::info("[rigDocumentShell] Document looks like a cart — Viewer presents; Player plays. "
				 "Open the .rig in RigPlayer.");
	if (m_onNeedsPlayer) {
		m_onNeedsPlayer();
	}
}

bool DocumentShell::looksLikeCart(const std::vector<std::string>& skippedKeys, bool hasLuaCode) {
	if (hasLuaCode) {
		return true;
	}
	for (const auto& key : skippedKeys) {
		if (key.rfind("rig.pixel.", 0) == 0 || key.rfind("rig.music.", 0) == 0 ||
			key.rfind("rig.input.", 0) == 0 || key.rfind("rig.media.code", 0) == 0) {
			return true;
		}
	}
	return false;
}

} // namespace rigkit
