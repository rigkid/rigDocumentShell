#include "SkippedKeysWindow.h"

#include <imgui.h>
#include "DocumentShell.h"

namespace rigkit {

SkippedKeysWindow::SkippedKeysWindow(DocumentShell* shell)
	: ImGuiPanel("Skipped keys", 0), m_shell(shell) {
	setCategory("Document");
}

void SkippedKeysWindow::renderContents() {
	if (!m_shell) {
		ImGui::TextUnformatted("No document shell.");
		return;
	}
	const auto& title = m_shell->documentTitle();
	if (!title.empty()) {
		ImGui::Text("Document: %s", title.c_str());
		ImGui::Separator();
	}
	const auto& keys = m_shell->skippedKeys();
	if (keys.empty()) {
		ImGui::TextDisabled("No skipped rig.* keys.");
		ImGui::TextWrapped("Unknown Contract keys from the last open would list here.");
		return;
	}
	ImGui::TextWrapped(
		"%zu skipped key(s). Play-loop schemas (pixel / music / Lua) need RigPlayer - "
		"Viewer presents; Player plays.",
		keys.size());
	ImGui::Separator();
	for (const auto& k : keys) {
		ImGui::BulletText("%s", k.c_str());
	}
}

} // namespace rigkit
