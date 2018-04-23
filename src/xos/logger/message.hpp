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
///   File: message.hpp
///
/// Author: $author$
///   Date: 4/9/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LOGGER_MESSAGE_HPP
#define _XOS_LOGGER_MESSAGE_HPP

#include "xos/logger/location.hpp"

namespace xos {
namespace logger {

typedef char_string::implements messaget_implements;
typedef char_string messaget_extends;
///////////////////////////////////////////////////////////////////////
///  Class: messaget
///////////////////////////////////////////////////////////////////////
template <class TImplements = messaget_implements, class TExtends = messaget_extends>
class _EXPORT_CLASS messaget: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    messaget(const char* chars): extends(chars) {
    }
    messaget(const wchar_t* chars): extends(chars) {
    }
    messaget(const messaget &copy): extends(copy) {
    }
    messaget() {
    }
    virtual ~messaget() {
    }

    virtual messaget& operator << (const extends& str) { 
        this->append(str); 
        return *this; 
    }
    virtual messaget& operator << (const char* chars) { 
        this->append(chars); 
        return *this; 
    }
    virtual messaget& operator << (const wchar_t* chars) { 
        this->append(chars); 
        return *this; 
    }
    virtual messaget& operator << (int i) {
        this->append_int(i);
        return *this; 
    }
};
typedef messaget<> message;

} /// namespace logger
} /// namespace xos

#endif /// _XOS_LOGGER_MESSAGE_HPP 
        

