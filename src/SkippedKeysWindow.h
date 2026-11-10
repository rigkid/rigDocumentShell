#pragma once

#include "ImGuiPanel.h"
namespace rigkit {

class DocumentShell;

/** @brief Lists Contract keys the host skipped (Viewer / Player). */
class SkippedKeysWindow : public ImGuiPanel {
  public:
	explicit SkippedKeysWindow(DocumentShell* shell);

  protected:
	void renderContents() override;

  private:
	DocumentShell* m_shell = nullptr;
};

} // namespace rigkit
