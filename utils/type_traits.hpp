#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <uchar.h>

namespace ft
{

	/* enable_if */
	template<bool B, class T = void>
		struct enable_if {};

	template<class T>
		struct enable_if<true, T> { typedef T type; };

	/* is_integral */
	template< class T > struct is_integral { static const bool value = false; };
	template<> struct is_integral<bool> { static const bool value = true; };
	template<> struct is_integral<char> { static const bool value = true; };
	template<> struct is_integral<char16_t> { static const bool value = true; };
	template<> struct is_integral<char32_t> { static const bool value = true; };
	template<> struct is_integral<wchar_t> { static const bool value = true; };
	template<> struct is_integral<signed char> { static const bool value = true; };
	template<> struct is_integral<short int> { static const bool value = true; };
	template<> struct is_integral<int> { static const bool value = true; };
	template<> struct is_integral<long int> { static const bool value = true; };
	template<> struct is_integral<long long int> { static const bool value = true; };
	template<> struct is_integral<unsigned char> { static const bool value = true; };
	template<> struct is_integral<unsigned long int> { static const bool value = true; };
	template<> struct is_integral<unsigned long long int> { static const bool value = true; };

	template<> struct is_integral<const bool> { static const bool value = true; };
	template<> struct is_integral<const char> { static const bool value = true; };
	template<> struct is_integral<const char16_t> { static const bool value = true; };
	template<> struct is_integral<const char32_t> { static const bool value = true; };
	template<> struct is_integral<const wchar_t> { static const bool value = true; };
	template<> struct is_integral<const signed char> { static const bool value = true; };
	template<> struct is_integral<const short int> { static const bool value = true; };
	template<> struct is_integral<const int> { static const bool value = true; };
	template<> struct is_integral<const long int> { static const bool value = true; };
	template<> struct is_integral<const long long int> { static const bool value = true; };
	template<> struct is_integral<const unsigned char> { static const bool value = true; };
	template<> struct is_integral<const unsigned long int> { static const bool value = true; };
	template<> struct is_integral<const unsigned long long int> { static const bool value = true; };

} // namespace ft

#endif