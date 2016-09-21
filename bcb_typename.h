#include <boost/type_index.hpp>
#define JSON_TYPENAME_PATCH

#include <boost/algorithm/string/replace.hpp>

namespace JSONPatch
{
	template <typename T>
	std::string type_name_factory()
	{
		auto name = boost::typeindex::type_id_with_cvr <T>().pretty_name();
		boost::replace_all(name, "@", "::");
        return name.substr(1, name.length() - 1);
    }
}
