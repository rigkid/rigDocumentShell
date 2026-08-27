#pragma once

#include "core/pack/IPack.h"
#include "DocumentShell.h"

namespace rigkit {

/**
 * @brief Code pack - shared document-host chrome for Viewer / Player apps.
 * @details Registers Skipped keys window. Configure via `shell()`.
 */
class rigDocumentShell : public IPack {
  public:
	rigDocumentShell();
	bool init() override;
	void setup() override;

	DocumentShell& shell() { return m_shell; }
	const DocumentShell& shell() const { return m_shell; }

  private:
	DocumentShell m_shell;
};

} // namespace rigkit
