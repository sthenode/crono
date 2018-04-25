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
///   File: timezone.hpp
///
/// Author: $author$
///   Date: 4/24/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_TIMEZONE_HPP
#define _XOS_BASE_TIMEZONE_HPP

#include "xos/base/base.hpp"

namespace xos {

typedef implement_base timezone_implementt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: timezone_implementt
///////////////////////////////////////////////////////////////////////
template <class TImplements = timezone_implementt_implements>
class _EXPORT_CLASS timezone_implementt: virtual public TImplements {
public:
    typedef TImplements implements;
};
typedef timezone_implementt<> timezone_implement;

typedef timezone_implement timezonet_implements;
typedef base timezonet_extends;
///////////////////////////////////////////////////////////////////////
///  Class: timezonet
///////////////////////////////////////////////////////////////////////
template <class TImplements = timezonet_implements, class TExtends = timezonet_extends>
class _EXPORT_CLASS timezonet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    timezonet(const timezonet &copy) {
    }
    timezonet() {
    }
    virtual ~timezonet() {
    }
};
typedef timezonet<> timezone;
typedef timezone* timezone_t;

} /// namespace xos

#endif /// _XOS_BASE_TIMEZONE_HPP 
