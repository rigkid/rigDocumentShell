#pragma once

#include "IWindow.h"
namespace rigkit {

class DocumentShell;

/** @brief Lists Contract keys the host skipped (Viewer / Player). */
class SkippedKeysWindow : public IWindow {
  public:
	explicit SkippedKeysWindow(DocumentShell* shell);

  protected:
	void renderContents() override;

  private:
	DocumentShell* m_shell = nullptr;
};

} // namespace rigkit
