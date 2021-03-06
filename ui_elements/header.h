//---------------------------------------------------------------------------
#pragma once

#include "../element.h"

// Model / Data
// #include "stub/exportable_header_stub.hpp"
#include "wiki-markup/components/exportable_components/exportable_header.hpp"

// View
#include <Vcl.ComCtrls.hpp>

// STL
#include <memory>
//---------------------------------------------------------------------------
namespace WikiElements
{
	class Header : public Element <Header, TPanel, WikiMarkup::Components::ExportableHeader>
	{
	public:
		Header(Section* parentSection);

		void setLevel(int level);
		int getLevel() const;

		void setText(std::string const& text);
		std::string const& getText() const;

		void realignAfter(BasicElement* element) const override;
		void realignAfter(int position) const override;

		BoundingBox getBoundingBox() const override;

		BoundingBox getRenderedBox() const;

		void writeModelToUserInterface() override;

	protected:
		void initializeOptionsFrame() override;

	protected: // events
		void styleChanged(WretchedCss::StyleSheet const& style, bool delayRealign) override;

	private: // vcl events
		void __fastcall onTextChange(TObject* Sender);
		void __fastcall onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall onResize(TObject* Sender);

	private:
		std::unique_ptr <TEdit> textbox_;
		std::unique_ptr <TPanel> underline_;
		unsigned int deleteCounter_;
	};
}
//---------------------------------------------------------------------------
