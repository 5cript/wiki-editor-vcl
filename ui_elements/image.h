//---------------------------------------------------------------------------
#pragma once

#include "../element.h"
#include "../section.h"
#include "image/image_attributes.h"

// Model / Data
#include "wiki-markup/components/exportable_components/exportable_text.hpp"
#include "wiki-markup/components/exportable_components/exportable_link.hpp"

// View
#include <Vcl.ComCtrls.hpp> // TRichEdit
#include <Vcl.ExtCtrls.hpp> // TImage
#include "JvRichEdit.hpp"

// STL
#include <memory>
//---------------------------------------------------------------------------
namespace WikiElements
{

	class Image : public Element <Image, TPanel, WikiMarkup::Components::ExportableLink>
	{
	private:
        std::unique_ptr <TImage> image_;
		ImageAttributes attributes_;
	};
}
//---------------------------------------------------------------------------
