#include "DocumentShell.h"

#include "Mui.h"
#include "core/IMui.h"

#include <spdlog/spdlog.h>

namespace rigkit {

void DocumentShell::attachChrome(Mui& mui, bool editModeOn, bool dockPassthroughCentral) {
	m_ui = &mui;
	mui.setDockPassthroughCentral(dockPassthroughCentral);
	if (editModeOn) {
		mui.setEditMode(true);
	}
	mui.registerFileAction(
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
		m_onOpen(path);
	});
}

void DocumentShell::notifyNeedsPlayer() {
	spdlog::info("[rigDocumentShell] Document looks like a cart — Viewer presents; Player plays. "
				 "Open in RigPlayer (or export .p8 via PicoForge).");
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
			key.rfind("rig.input.", 0) == 0 || key == "rig.led.uv_map") {
			return true;
		}
	}
	return false;
}

} // namespace rigkit
