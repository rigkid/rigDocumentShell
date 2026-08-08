#include "rigDocumentShell.h"

#include "SkippedKeysWindow.h"
#include "core/IMui.h"
#include "core/RigKitEngine.h"
#include "core/pack/PackRegistry.h"
#include "MWindow.h"

#include <memory>
#include <spdlog/spdlog.h>

namespace rigkit {

rigDocumentShell::rigDocumentShell() : IPack("rigDocumentShell") {
	setDescription("Document host chrome — File Open, skipped keys, Edit Mode defaults");
	addDependency("rigImGui");
}

bool rigDocumentShell::init() {
	spdlog::info("[rigDocumentShell] init");
	return true;
}

void rigDocumentShell::setup() {
	auto* engine = getEngine();
	if (!engine) {
		return;
	}
	engine->enableEditMode(true);
	auto* ui = engine->getUiManager();
	if (!ui) {
		spdlog::warn("[rigDocumentShell] no IMui — chrome skipped (need rigImGui)");
		return;
	}
	auto* wm = ui->getWindowManager();
	if (!wm) {
		return;
	}
	wm->createWindow<SkippedKeysWindow>(&m_shell);
	wm->hideWindow("Skipped keys");
	spdlog::info("[rigDocumentShell] Skipped keys window registered");
}

} // namespace rigkit

namespace {
struct rigDocumentShellRegistrar {
	rigDocumentShellRegistrar() {
		rigkit::PackRegistry::instance().addFactory("rigDocumentShell", []() {
			return std::shared_ptr<rigkit::IPack>(std::make_shared<rigkit::rigDocumentShell>());
		});
	}
};
static rigDocumentShellRegistrar rigDocumentShell_auto_reg;
} // namespace
