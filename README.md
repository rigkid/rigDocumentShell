# rigDocumentShell

Desktop **UI chrome** for hosts that open Rig documents (`.rig`) - today [RigViewer](https://github.com/rigkid/RigViewer) and [RigPlayer](https://github.com/rigkid/RigPlayer).

**Viewer presents; Player plays.** This pack does neither. It wires File > Open, skipped-key honesty UI, optional Edit Mode / dock passthrough, and a play-loop heuristic so Viewer can point at Player.

## Scope

| This pack | Not this pack |
|-----------|----------------|
| File > Open (default filters: `.rig`, `.json`; `.pg` legacy) | Load / serialize / Contract import to **rigProject** |
| Skipped-keys window + document title | Present geometry / GLSL to **RigViewer** |
| Edit Mode UI + central-dock passthrough via `attachChrome` | Run Lua SUDE to **RigPlayer** |
| `needsPlayer` / `notifyNeedsPlayer` | Generic chrome for plotter / OSC / other hosts |

Not every RigKit host should register this - only document hosts that care about Contract honesty UI.

**Edit Mode:** registering the pack does **not** enable the engine feature. Viewer should call `engine->enableEditMode(true)` then `attachChrome(ui, true, ...)`. Player uses `attachChrome(ui, false, ...)`.

## Use

```cpp
packs->registerPack<rigkit::rigDocumentShell>();
packs->initAll();
packs->setupAll();

if (auto shellPack = packs->getPack<rigkit::rigDocumentShell>()) {
	auto& shell = shellPack->shell();
	shell.setOpenFilters({".rig", ".json"}); // optional; defaults include legacy .pg
	shell.setOnOpenPath([&](const std::string& path) { /* app loads via rigProject / PlayRuntime */ });
	shell.setOnNeedsPlayer([&]() { /* optional UI */ });
	if (auto* ui = engine->getUiManager()) {
		engine->enableEditMode(true); // Viewer only
		shell.attachChrome(*ui, true, true);
	}
	shell.setSkippedKeys(doc.skipped);
	shell.setDocumentTitle(doc.title);
	if (rigkit::DocumentShell::needsPlayer(doc.skipped, hasLuaCode)) {
		shell.notifyNeedsPlayer();
	}
}
```

Web share (`?doc=` / `?src=`) stays in RigViewer JS - not this pack.

## Depends

**rigImGui** only (`IMui` / IWindow). Does **not** depend on **rigProject**; the app owns load.
