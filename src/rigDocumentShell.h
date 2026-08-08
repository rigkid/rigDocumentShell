#pragma once

#include "DocumentShell.h"
#include "core/pack/IPack.h"

namespace rigkit {

/**
 * @brief Code pack — shared document-host chrome for Viewer / Player apps.
 * @details Registers Skipped keys window. Configure via @ref shell().
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
