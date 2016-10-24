#include <cstdint>
#include <System.hpp>

#if INTPTR_MAX == INT32_MAX
	#define X86_ENVIRONMENT
#elif INTPTR_MAX == INT64_MAX
	#define X64_ENVIRONMENT
#else
    #error "Environment not 32 or 64-bit."
#endif

template <typename DestT>
static DestT interface_query_cast (TObject* obj)
{
	if (obj)
	{
		TInterfaceEntry* entry = obj->GetInterfaceEntry (__uuidof(DestT));

		if (entry == nullptr)
			return nullptr;

#ifdef X86_ENVIRONMENT
		if (entry) return (DestT) ((int) obj + entry->IOffset);
#else
		if (entry) return (DestT) ((__int64) obj + entry->IOffset);
#endif
	}
	return nullptr;
}
