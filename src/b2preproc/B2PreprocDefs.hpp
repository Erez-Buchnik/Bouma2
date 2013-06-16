
#ifndef B2PreprocDefs___HPP
#define B2PreprocDefs___HPP

#include <string>
#include <vector>

#ifdef __GNUC__

#include <backward/hash_map>
#define B2HashMap /**/ __gnu_cxx::hash_map /**/
#define B2_HASH_MAP_ERASE(hash_map_inst, iter) { (hash_map_inst).erase(iter++); };

namespace __gnu_cxx
{
	template<> struct hash<std::string>
	{
		unsigned int fnv_hash(const char *bytes, unsigned int len) const
		{
			unsigned int hashval = 2166136261U;
			for(unsigned int i = 0; i < len; ++i)
			{
				hashval = (16777619U * hashval) ^ (unsigned char)(bytes[i]);
			};
			return hashval;
		};

		size_t operator () (const std::string &str) const
		{
			return fnv_hash(str.c_str(), str.size());
		};
	};
};

#else

#include <hash_map>
#define B2HashMap /**/ std::hash_map /**/
#define B2_HASH_MAP_ERASE(hash_map_inst, iter) { (iter) = (hash_map_inst).erase(iter); };

#endif


#endif // B2PreprocDefs___HPP
