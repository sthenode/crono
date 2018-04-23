///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: location.hpp
///
/// Author: $author$
///   Date: 4/9/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LOGGER_LOCATION_HPP
#define _XOS_LOGGER_LOCATION_HPP

#include "xos/logger/function.hpp"

namespace xos {
namespace logger {

typedef char_string::implements locationt_implements;
typedef char_string locationt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: locationt
///////////////////////////////////////////////////////////////////////
template <class TImplements = locationt_implements, class TExtends = locationt_extends>
class _EXPORT_CLASS locationt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    locationt
    (const char* function_name, const char* file_name, size_t line_number)
    : extends(function_name), file_name_(file_name), line_number_(line_number) {
    }
    locationt
    (const wchar_t* function_name, const wchar_t* file_name, size_t line_number)
    : extends(function_name), file_name_(file_name), line_number_(line_number) {
    }
    locationt(const locationt &copy)
    : extends(copy), file_name_(copy.file_name_), line_number_(copy.line_number_) {
    }
    locationt() {
    }
    virtual ~locationt() {
    }

    virtual char_string function_name() const { 
        return *this; 
    }
    virtual char_string file_name() const { 
        return file_name_; 
    }
    virtual char_string line_number() const {
        char_string cs;
        cs.append_unsigned(line_number_);
        return cs;
    }

protected:
    char_string file_name_;
    size_t line_number_;
};
typedef locationt<> location;

///
///
///
#if !defined(XOS_LOGGER_LOCATION)
#define XOS_LOGGER_LOCATION \
    ::xos::logger::location(__XOS_LOGGER_FUNC__, __FILE__, __LINE__)
#endif // !defined(XOS_LOGGER_LOCATION)

} /// namespace logger
} /// namespace xos

#endif /// _XOS_LOGGER_LOCATION_HPP 
