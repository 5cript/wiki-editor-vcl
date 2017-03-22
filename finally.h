//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include <functional>
//---------------------------------------------------------------------------
class Finally
{
public:
	Finally(std::function <void()> onEnd)
		: onEnd_{onEnd}
	{
	}
	~Finally()
	{
        onEnd_();
	}

private:
    std::function <void()> onEnd_;
};
//---------------------------------------------------------------------------

#define ON_SCOPE_EXIT(F) \
	auto __scope_exit_guard = Finally{ \
		F \
	};
