
#pragma once

namespace Jadeite::Utilities
{
std::string ConvertWideToANSI( const std::wstring& wstr );
std::wstring ConvertAnsiToWide( const std::string& str );
std::string ConvertWideToUtf8( const std::wstring& wstr );
std::wstring ConvertUtf8ToWide( const std::string& str );

template <typename CharT, typename Traits, typename Alloc>
inline void RemoveSuffixIfPresent( std::basic_string<CharT, Traits, Alloc>& str,
                                   std::basic_string_view<CharT, Traits> suffix )
{
    if ( str.ends_with( suffix ) )
    {
        str.erase( str.size() - suffix.size() );
    }
}

template <typename CharT, typename Traits, typename Alloc>
inline void RemovePrefixIfPresent( std::basic_string<CharT, Traits, Alloc>& str,
                                   std::basic_string_view<CharT, Traits> prefix )
{
    if ( str.starts_with( prefix ) )
    {
        str.erase( 0, prefix.size() );
    }
}

// Return a copy with suffix removed (if present)
template <typename CharT, typename Traits, typename Alloc>
[[nodiscard]] inline std::basic_string<CharT, Traits, Alloc>
RemoveSuffixCopy( std::basic_string<CharT, Traits, Alloc> str,
                  std::basic_string_view<CharT, Traits> suffix )
{
    RemoveSuffixIfPresent( str, suffix );
    return str;
}

// Overload for suffix (string literal)
template <typename CharT, typename Traits, typename Alloc, size_t N>
[[nodiscard]] inline std::basic_string<CharT, Traits, Alloc>
RemoveSuffixCopy( std::basic_string<CharT, Traits, Alloc> str, const CharT ( &suffix )[ N ] )
{
    RemoveSuffixIfPresent( str, std::basic_string_view<CharT>( suffix, N - 1 ) );
    return str;
}

// Return a copy with prefix removed (if present)
template <typename CharT, typename Traits, typename Alloc>
[[nodiscard]] inline std::basic_string<CharT, Traits, Alloc>
RemovePrefixCopy( std::basic_string<CharT, Traits, Alloc> str,
                  std::basic_string_view<CharT, Traits> prefix )
{
    RemovePrefixIfPresent( str, prefix );
    return str;
}

// Overload for prefix (string literal)
template <typename CharT, typename Traits, typename Alloc, size_t N>
[[nodiscard]] inline std::basic_string<CharT, Traits, Alloc>
RemovePrefixCopy( std::basic_string<CharT, Traits, Alloc> str, const CharT ( &prefix )[ N ] )
{
    RemovePrefixIfPresent( str, std::basic_string_view<CharT>( prefix, N - 1 ) );
    return str;
}

} // namespace Jadeite::Utilities