# rigDocumentShell

Shared **desktop** chrome for document hosts ([RigViewer](https://github.com/rigkid/RigViewer), [RigPlayer](https://github.com/rigkid/RigPlayer)).

**Viewer presents; Player plays.** This pack does not present scenes or run cart Lua — it wires File → Open, skipped-key honesty UI, and optional Edit Mode / dock passthrough defaults.

## Use

```cpp
packs->registerPack<rigkit::rigDocumentShell>();
// after initAll/setupAll:
auto* shellPack = dynamic_cast<rigkit::rigDocumentShell*>(packs->getPack("rigDocumentShell"));
auto& shell = shellPack->shell();
shell.setOnOpenPath([&](const std::string& path) { /* load */ });
shell.attachChrome(*mui); // File→Open, Edit Mode ON, dock passthrough
shell.setSkippedKeys(doc.skipped);
shell.setDocumentTitle(doc.title);
if (rigkit::DocumentShell::looksLikeCart(doc.skipped, hasLuaCode)) {
	shell.notifyNeedsPlayer(); // logs + optional callback
}
```

Web share (`?doc=` / `?src=`) stays in RigViewer JS — not this pack.

## Depends

**rigImGui** (IMui / IWindow).
