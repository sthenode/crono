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
///   File: function.hpp
///
/// Author: $author$
///   Date: 4/9/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LOGGER_FUNCTION_HPP
#define _XOS_LOGGER_FUNCTION_HPP

#include "xos/logger/level.hpp"
#include "xos/base/string.hpp"

namespace xos {
namespace logger {

typedef char_string::implements functiont_implements;
typedef char_string functiont_extends;
///////////////////////////////////////////////////////////////////////
///  Class: functiont
///////////////////////////////////////////////////////////////////////
template <class TImplements = functiont_implements, class TExtends = functiont_extends>
class _EXPORT_CLASS functiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    functiont(const char* chars): extends(chars) {
    }
    functiont(const wchar_t* chars): extends(chars) {
    }
    functiont(const functiont &copy): extends(copy) {
    }
    functiont() {
    }
    virtual ~functiont() {
    }
};
typedef functiont<> function;

} /// namespace logger
} /// namespace xos

///
///
/// 
#if !defined(__XOS_LOGGER_FUNC__)
#define __XOS_LOGGER_FUNC__ __FUNCTION__
#endif // !defined(__XOS_LOGGER_FUNCTION__)

#if !defined(XOS_LOGGER_FUNCTION)
#define XOS_LOGGER_FUNCTION \
    ::xos::logger::function(__XOS_LOGGER_FUNC__)
#endif // !defined(XOS_LOGGER_LOCATION)

#endif /// _XOS_LOGGER_FUNCTION_HPP 
