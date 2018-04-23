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
///   File: logger.hpp
///
/// Author: $author$
///   Date: 4/10/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CONSOLE_LOGGER_HPP
#define _XOS_CONSOLE_LOGGER_HPP

#include "xos/logger/interface.hpp"
#include "xos/console/io.hpp"

namespace xos {
namespace console {

typedef xos::logger::instance::implements loggert_implements;
typedef xos::logger::instance loggert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: loggert
///////////////////////////////////////////////////////////////////////
template <class TImplements = loggert_implements, class TExtends = loggert_extends>
class _EXPORT_CLASS loggert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    loggert(console::io& io): io_(io) {
    }
    loggert(): io_(this_io_) {
    }
    virtual ~loggert() {
    }
private:
    loggert(const loggert &copy): io_(this_io_) {
    }

protected:
    virtual ssize_t logfv(const char_t* format, va_list va) {
        ssize_t count = 0;
        count = io_.errfv(format, va);
        return count;
    }
    virtual ssize_t log(const char_t* chars) {
        ssize_t count = 0;
        count = io_.err(chars);
        return count;
    }
    virtual ssize_t logflush() {
        ssize_t count = 0;
        count = io_.err_flush();
        return count;
    }

    virtual bool lock() { 
        return io_.lock(); 
    }
    virtual lock_status try_lock() { 
        return io_.try_lock(); 
    }
    virtual lock_status untimed_lock() { 
        return io_.untimed_lock(); 
    }
    virtual lock_status timed_lock(mseconds_t milliseconds) { 
        return io_.timed_lock(milliseconds); 
    }
    virtual bool unlock() { 
        return io_.unlock(); 
    }

protected:
    console::io this_io_;
    console::io& io_;
};
typedef loggert<> logger;

} /// namespace console
} /// namespace xos

#endif /// _XOS_CONSOLE_LOGGER_HPP 
        

