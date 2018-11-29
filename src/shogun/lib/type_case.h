/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Gil Hoben
 */

#ifndef SHOGUN_TYPE_CASE_H
#define SHOGUN_TYPE_CASE_H

#include <typeindex>
#include <unordered_map>

#include <shogun/lib/any.h>
#include <shogun/lib/type_list.h>

using namespace shogun;

// here we define a list of all types that are implemented in shogun
// the head of the list returns the type
typedef Types<
    bool, char, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t,
    uint64_t, float32_t, float64_t, floatmax_t>::type AllTypes;

namespace shogun
{
	// here we make types switchable
	enum class TYPE
	{
		PT_BOOL = 1,
		PT_CHAR = 2,
		PT_INT8 = 3,
		PT_UINT8 = 4,
		PT_INT16 = 5,
		PT_UINT16 = 6,
		PT_INT32 = 7,
		PT_UINT32 = 8,
		PT_INT64 = 9,
		PT_UINT64 = 10,
		PT_FLOAT32 = 11,
		PT_FLOAT64 = 12,
		PT_FLOATMAX = 13,
		PT_SGOBJECT = 14,
		PT_COMPLEX128 = 15,
		PT_UNDEFINED = 16
	};
} // namespace shogun

template <typename T>
struct sg_primitive_type
{
};

#define SG_PRIMITIVE_TYPE(T, ptype)                                            \
	template <>                                                                \
	struct sg_primitive_type<T>                                                \
	{                                                                          \
		static constexpr TYPE value = ptype;                                   \
	};

typedef std::unordered_map<std::type_index, TYPE> typemap;

SG_PRIMITIVE_TYPE(bool, TYPE::PT_BOOL)
SG_PRIMITIVE_TYPE(char, TYPE::PT_CHAR)
SG_PRIMITIVE_TYPE(int8_t, TYPE::PT_INT8)
SG_PRIMITIVE_TYPE(uint8_t, TYPE::PT_UINT8)
SG_PRIMITIVE_TYPE(int16_t, TYPE::PT_INT16)
SG_PRIMITIVE_TYPE(uint16_t, TYPE::PT_UINT16)
SG_PRIMITIVE_TYPE(int32_t, TYPE::PT_INT32)
SG_PRIMITIVE_TYPE(uint32_t, TYPE::PT_UINT32)
SG_PRIMITIVE_TYPE(int64_t, TYPE::PT_INT64)
SG_PRIMITIVE_TYPE(uint64_t, TYPE::PT_UINT64)
SG_PRIMITIVE_TYPE(float32_t, TYPE::PT_FLOAT32)
SG_PRIMITIVE_TYPE(float64_t, TYPE::PT_FLOAT64)
SG_PRIMITIVE_TYPE(floatmax_t, TYPE::PT_FLOATMAX)
SG_PRIMITIVE_TYPE(complex128_t, TYPE::PT_COMPLEX128)

namespace shogun
{
	extern typemap all_types;

	template <typename T>
	void map_type(TYPE type, typemap& map);

	template <typename T>
	TYPE get_type(typemap map);

	TYPE get_type(std::type_index type, typemap map);

	TYPE get_type(Any any, typemap map);

	template <typename T1, typename T2>
	typename std::enable_if<(not std::is_same<T1, Types0>::value), int>::type
	recursive_type_finder(const Any& any, TYPE type, T2 func)
	{
		if (type == sg_primitive_type<typename T1::Head>::value)
		{
			typename T1::Head i;
			func(i);
			return 1;
		}
		else
		{
			return recursive_type_finder<typename T1::Tail>(any, type, func);
		}
	}

	template <typename T1, typename T2>
	typename std::enable_if<std::is_same<T1, Types0>::value, int>::type
	recursive_type_finder(const Any& any, TYPE type, T2 func)
	{
		return 0;
	}

	template <typename T>
	int type_finder(const Any& any, typemap& typesmap, T func)
	{
		TYPE type = get_type(any, typesmap);
		return recursive_type_finder<AllTypes>(any, type, func);
	}

	void init_types();
} // namespace shogun

#endif // SHOGUN_TYPE_CASE_H
