//---------------------------------------------------------------------------
#pragma once

#include <memory>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
namespace WikiElements
{
	class BasicElement
	{
	public:
    	virtual ~BasicElement() = default;
    };

	template <typename Derivative, typename UnderlyingUiElement, typename DataElement>
	class Element : public BasicElement
	{
	public:
		Element(TPanel* parent)
			: control_{new UnderlyingUiElement(parent)}
		{
			control_->Parent = parent;
		}

		void setStyle(std::string const& style)
		{
            // ...
        }

	protected:
		DataElement* getDataHandle()
		{
			return &data_;
		}

    protected:
		std::unique_ptr <UnderlyingUiElement> control_;
		DataElement data_;
    };
};
//---------------------------------------------------------------------------
