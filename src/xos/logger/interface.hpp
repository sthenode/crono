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
///   File: interface.hpp
///
/// Author: $author$
///   Date: 4/9/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LOGGER_INTERFACE_HPP
#define _XOS_LOGGER_INTERFACE_HPP

#include "xos/logger/output.hpp"
#include "xos/base/locked.hpp"

namespace xos {
namespace logger {

typedef unlocked interfacet_implements;
///////////////////////////////////////////////////////////////////////
///  Class: interfacet
///////////////////////////////////////////////////////////////////////
template <class TImplements = interfacet_implements>
class _EXPORT_CLASS interfacet: virtual public TImplements {
public:
    typedef TImplements implements;

    virtual bool init() { 
        return true; 
    }
    virtual bool fini() { 
        return true; 
    }

    virtual void log
    (const level& _level, const location& _location, const message& _message) {
        xos::lock lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->log(_location);
            this->log(_message.c_str());
            this->logln();
        }
    }
    virtual void logf
    (const level& _level, const location& _location, const char* format, ...) {
        xos::lock lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->log(_location);
            if ((format)) {
                va_list va;
                va_start(va, format);
                this->logfv(format, va);
                va_end(va);
            }
            this->logln();
        }
    }
    virtual void logfv
    (const level& _level, const location& _location, const char* format, va_list va) {
        xos::lock lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->log(_location);
            if ((format)) {
                this->logfv(format, va);
            }
            this->logln();
        }
    }
    virtual void logfv
    (const level& _level, const location& _location,
     const message& _message, const char* format, va_list va) {
        xos::lock lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->log(_location);
            this->log(_message.c_str());
            if ((format)) {
                this->logfv(format, va);
            }
            this->logln();
        }
    }

    virtual void log
    (const level& _level, const message& _message) {
        xos::lock lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->log(_message.c_str());
            this->logln();
        }
    }
    virtual void logf
    (const level& _level, const char* format, ...) {
        xos::lock lock(*this);
        if ((this->is_enabled_for(_level))) {
            if ((format)) {
                va_list va;
                va_start(va, format);
                this->logfv(format, va);
                va_end(va);
            }
            this->logln();
        }
    }
    virtual void logfv
    (const level& _level, const char* format, va_list va) {
        xos::lock lock(*this);
        if ((this->is_enabled_for(_level))) {
            if ((format)) {
                this->logfv(format, va);
            }
            this->logln();
        }
    }
    virtual void logfv
    (const level& _level, const message& _message, const char* format, va_list va) {
        xos::lock lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->log(_message.c_str());
            if ((format)) {
                this->logfv(format, va);
            }
            this->logln();
        }
    }

    virtual void enable_for(const level& _level) {
    }
    virtual level enabled_for() const { 
        return enabled_for_default(); 
    }
    virtual bool is_enabled_for(const level& _level) const { 
        level::enable enabled = _level, enabled_for = this->enabled_for();
        bool is_enabled_for = ((enabled_for & enabled) == enabled);
        return is_enabled_for;
    }
    virtual level enabled_for_default() const { 
        return level(XOS_LOGGING_LEVELS_DEFAULT); 
    }

    static interfacet* set_default(interfacet* to) {
        interfacet* old_logger = the_default();
        the_default() = to;
        return old_logger;
    }
    static interfacet* get_default() {
        return the_default();
    }
protected:
    static interfacet*& the_default() {
        static interfacet* the_default = 0;
        return the_default;
    }

protected:
    virtual ssize_t log(const location& _location) {
        ssize_t count = logl
        (_location.file_name().c_str(),
         "[", _location.line_number().c_str(), "]",
         " ", _location.function_name().c_str(), " ", NULL);
        return count;
    }
    virtual ssize_t logl(const char_t* chars, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, chars);
        if ((chars)) {
            count = logv(chars, va);
        }
        va_end(va);
        return count;
    }
    virtual ssize_t logv(const char_t* chars, va_list va) {
        ssize_t count = 0;
        ssize_t amount = 0;
        for (count = 0; chars; count += amount) {
            if (0 > (amount = log(chars)))
                return amount;
            chars = va_arg(va, const char_t*);
        }
        return count;
    }
    virtual ssize_t logfv(const char_t* format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t log(const char_t* chars) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t logflush() {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t logln() {
        ssize_t count = log("\n");
        logflush();
        return count;
    }
};
typedef interfacet<> interface;

typedef interface instancet_implements;
typedef base instancet_extends;
///////////////////////////////////////////////////////////////////////
///  Class: instancet
///////////////////////////////////////////////////////////////////////
template <class TImplements = instancet_implements, class TExtends = instancet_extends>
class _EXPORT_CLASS instancet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    instancet()
    : old_default_(implements::the_default()), 
      enabled_for_(implements::enabled_for_default()) {
        implements::the_default() = this;
    }
    virtual ~instancet() {
        if (implements::the_default() == this) {
            implements::the_default() = old_default_;
        }
    }
private:
    instancet(const instancet &copy) {
    }

    virtual void enable_for(const level& _level) {
        enabled_for_ = _level;
    }
    virtual level enabled_for() const {
        return enabled_for_;
    }

protected:
    implements* old_default_;
    level enabled_for_;
};
typedef instancet<> instance;

} /// namespace logger
} /// namespace xos

///
/// XOS_ INIT / FINI / _LOGGER
/// 
#define XOS_INIT_LOGGER(logger_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) { logger->init(); } }

#define XOS_FINI_LOGGER(logger_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) { logger->fini(); } }

#define XOS_SET_LOGGER_LEVEL(logger_, level_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) { logger->enable_for(level_); } }

#define XOS_GET_LOGGER_LEVEL(logger_) \
((logger_)?(logger_->enabled_for()) \
 :(::xos::logger::level(::xos::logger::level::none)))

///
///  XOS_LOG_PLAIN
/// 
#define XOS_LOG_PLAIN(logger_, level_, message_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   ::xos::logger::message message; \
   logger->log(level_, message << message_); } }

#define XOS_LOG_PLAINF(logger_, level_, format_, ...) { \
::xos::logger::interface* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   logger->logf(level_, format_, ##__VA_ARGS__); } }

#define XOS_LOG_PLAINFV(logger_, level_, format_, va_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   logger->logfv(level_, format_, va_); } }

#define XOS_LOG_PLAINMFV(logger_, level_, message_, format_, va_) { \
::xos::logger::interface* logger = logger_; \
::xos::logger::message message; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   logger->logfv(level_, message << message_, format_, va_); } }

#define XOS_LOG_PLAIN_ANY_LEVEL(logger_, message_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) {\
   ::xos::logger::level level_; \
   ::xos::logger::message message; \
   logger->log(level_, message << message_); } }

#define XOS_LOG_PLAIN_ANY_LEVELF(logger_, format_, ...) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) {\
   ::xos::logger::level level_; \
   logger->logf(level_, format_, ##__VA_ARGS__); } }

#define XOS_LOG_PLAIN_ANY_LEVELFV(logger_, format_, va_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) {\
   ::xos::logger::level level_; \
   logger->logfv(level_, format_, va_); } }

#define XOS_LOG_PLAIN_ANY_LEVELMFV(logger_, message_, format_, va_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) {\
   ::xos::logger::level level_; \
   ::xos::logger::message message; \
   logger->logfv(level_, message << message_, format_, va_); } }

#define XOS_IF_LOGGED_PLAIN(is_logged_, logger_, level_, message_) { \
if ((is_logged_)) { XOS_LOG_PLAIN(logger_, level_, message_); }

#define XOS_IF_LOGGED_PLAINF(is_logged_, logger_, level_, format_, ...) { \
if ((is_logged_)) { XOS_LOG_PLAINF(logger_, level_, format_,  ##__VA_ARGS__); }

#define XOS_IS_LOGGED_PLAIN(logger_, level_, message_) { \
if ((this->is_logged())) { XOS_LOG_PLAIN(logger_, level_, message_); }

#define XOS_IS_LOGGED_PLAINF(logger_, level_, format_, ...) { \
if ((this->is_logged())) { XOS_LOG_PLAINF(logger_, level_, format_,  ##__VA_ARGS__); }

///
/// XOS_LOG_FUNCTION
/// 
#define XOS_LOG_FUNCTION(logger_, level_, message_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   ::xos::logger::message message; \
   logger->log(level_, XOS_LOGGER_FUNCTION, message << message_); } }

#define XOS_LOG_FUNCTIONF(logger_, level_, format_, ...) { \
::xos::logger::interface* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   logger->logf(level_, XOS_LOGGER_FUNCTION, format_, ##__VA_ARGS__); } }

#define XOS_IF_LOGGED_FUNCTION(is_logged_, logger_, level_, message_) { \
if ((is_logged_)) { XOS_LOG_FUNCTION(logger_, level_, message_); }

#define XOS_IF_LOGGED_FUNCTIONF(is_logged_, logger_, level_, format_, ...) { \
if ((is_logged_)) { XOS_LOG_FUNCTIONF(logger_, level_, format_, ##__VA_ARGS__); }

#define XOS_IS_LOGGED_FUNCTION(logger_, level_, message_) { \
if ((this->is_logged())) { XOS_LOG_FUNCTION(logger_, level_, message_); }

#define XOS_IS_LOGGED_FUNCTIONF(logger_, level_, format_, ...) { \
if ((this->is_logged())) { XOS_LOG_FUNCTIONF(logger_, level_, format_,  ##__VA_ARGS__); }

///
/// XOS_LOG_LOCATION
/// 
#define XOS_LOG_LOCATION(logger_, level_, message_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   ::xos::logger::message message; \
   logger->log(level_, XOS_LOGGER_LOCATION, message << message_); } }

#define XOS_LOG_LOCATIONF(logger_, level_, format_, ...) { \
::xos::logger::interface* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   logger->logf(level_, XOS_LOGGER_LOCATION, format_, ##__VA_ARGS__); } }

#define XOS_LOG_LOCATION_ANY_LEVEL(logger_, message_) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) {\
   ::xos::logger::level level_; \
   ::xos::logger::message message; \
   logger->log(level_, XOS_LOGGER_LOCATION, message << message_); } }

#define XOS_LOG_LOCATION_ANY_LEVELF(logger_, format_, ...) { \
::xos::logger::interface* logger = logger_; \
if ((logger)) {\
   ::xos::logger::level level_; \
   logger->logf(level_, XOS_LOGGER_LOCATION, format_, ##__VA_ARGS__); } }

#define XOS_IF_LOGGED_LOCATION(is_logged_, logger_, level_, message_) { \
if ((is_logged_)) { XOS_LOG_LOCATION(logger_, level_, message_); } }

#define XOS_IF_LOGGED_LOCATIONF(is_logged_, logger_, level_, format_, ...) { \
if ((is_logged_)) { XOS_LOG_LOCATIONF(logger_, level_, format_, ##__VA_ARGS__); } }

#define XOS_IS_LOGGED_LOCATION(logger_, level_, message_) { \
if ((this->is_logged())) { XOS_LOG_LOCATION(logger_, level_, message_); } }

#define XOS_IS_LOGGED_LOCATIONF(logger_, level_, format_, ...) { \
if ((this->is_logged())) { XOS_LOG_LOCATIONF(logger_, level_, format_,  ##__VA_ARGS__); } }

///
/// XOS_LOG
/// 
#if defined(XOS_PLAIN_LOGGING)
#define XOS_LOG XOS_LOG_PLAIN
#define XOS_LOGF XOS_LOG_PLAINF
#else // defined(XOS_PLAIN_LOGGING)
#if defined(XOS_FUNCTION_LOGGING)
#define XOS_LOG XOS_LOG_FUNCTION
#define XOS_LOGF XOS_LOG_FUNCTIONF
#else // defined(XOS_FUNCTION_LOGGING)
#define XOS_LOG XOS_LOG_LOCATION
#define XOS_LOGF XOS_LOG_LOCATIONF
#endif // defined(XOS_FUNCTION_LOGGING)
#endif // defined(XOS_PLAIN_LOGGING)

///
/// XOS_IF_LOGGED
/// 
#if defined(XOS_PLAIN_LOGGING)
#define XOS_IF_LOGGED XOS_IF_LOGGED_PLAIN
#define XOS_IF_LOGGEDF XOS_IF_LOGGED_PLAINF
#else // defined(XOS_PLAIN_LOGGING)
#if defined(XOS_FUNCTION_LOGGING)
#define XOS_IF_LOGGED XOS_IF_LOGGED_FUNCTION
#define XOS_IF_LOGGEDF XOS_IF_LOGGED_FUNCTIONF
#else // defined(XOS_FUNCTION_LOGGING)
#define XOS_IF_LOGGED XOS_IF_LOGGED_LOCATION
#define XOS_IF_LOGGEDF XOS_IF_LOGGED_LOCATIONF
#endif // defined(XOS_FUNCTION_LOGGING)
#endif // defined(XOS_PLAIN_LOGGING)

///
/// XOS_LOGGER_  DEFAULT / INIT / FINI / LEVEL
/// 
#define XOS_DEFAULT_LOGGER ::xos::logger::interface::get_default()
#define XOS_LOGGER_INIT() XOS_INIT_LOGGER(XOS_DEFAULT_LOGGER)
#define XOS_LOGGER_FINI() XOS_FINI_LOGGER(XOS_DEFAULT_LOGGER)
#define XOS_SET_LOGGING_LEVEL(level)  XOS_SET_LOGGER_LEVEL(XOS_DEFAULT_LOGGER, level)
#define XOS_GET_LOGGING_LEVEL(level)  (level = XOS_GET_LOGGER_LEVEL(XOS_DEFAULT_LOGGER))

///
/// XOS_LOG_ ANY / FATAL .. TRACE
/// 
#define XOS_LOG_ANY(message) XOS_LOG_ANY_LEVEL(XOS_DEFAULT_LOGGER, message)
#define XOS_LOG_FATAL(message) XOS_LOG(XOS_DEFAULT_LOGGER, ::xos::logger::level::fatal, message)
#define XOS_LOG_ERROR(message) XOS_LOG(XOS_DEFAULT_LOGGER, ::xos::logger::level::error, message)
#define XOS_LOG_WARN(message) XOS_LOG(XOS_DEFAULT_LOGGER, ::xos::logger::level::warn, message)
#define XOS_LOG_INFO(message) XOS_LOG(XOS_DEFAULT_LOGGER, ::xos::logger::level::info, message)
#define XOS_LOG_DEBUG(message) XOS_LOG(XOS_DEFAULT_LOGGER, ::xos::logger::level::debug, message)
#define XOS_LOG_TRACE(message) XOS_LOG(XOS_DEFAULT_LOGGER, ::xos::logger::level::trace, message)

#define XOS_LOG_ANYF(message, ...) XOS_LOG_ANY_LEVELF(XOS_DEFAULT_LOGGER, message, ##__VA_ARGS__)
#define XOS_LOG_FATALF(message, ...) XOS_LOGF(XOS_DEFAULT_LOGGER, ::xos::logger::level::fatal, message, ##__VA_ARGS__)
#define XOS_LOG_ERRORF(message, ...) XOS_LOGF(XOS_DEFAULT_LOGGER, ::xos::logger::level::error, message, ##__VA_ARGS__)
#define XOS_LOG_WARNF(message, ...) XOS_LOGF(XOS_DEFAULT_LOGGER, ::xos::logger::level::warn, message, ##__VA_ARGS__)
#define XOS_LOG_INFOF(message, ...) XOS_LOGF(XOS_DEFAULT_LOGGER, ::xos::logger::level::info, message, ##__VA_ARGS__)
#define XOS_LOG_DEBUGF(message, ...) XOS_LOGF(XOS_DEFAULT_LOGGER, ::xos::logger::level::debug, message, ##__VA_ARGS__)
#define XOS_LOG_TRACEF(message, ...) XOS_LOGF(XOS_DEFAULT_LOGGER, ::xos::logger::level::trace, message, ##__VA_ARGS__)

///
/// XOS_LOG_MESSAGE_ ANY / FATAL .. TRACE
/// 
#define XOS_LOG_MESSAGE_ANY(message) XOS_LOG_PLAIN_ANY_LEVEL(XOS_DEFAULT_LOGGER, message)
#define XOS_LOG_MESSAGE_FATAL(message) XOS_LOG_PLAIN(XOS_DEFAULT_LOGGER, ::xos::logger::level::fatal_message, message)
#define XOS_LOG_MESSAGE_ERROR(message) XOS_LOG_PLAIN(XOS_DEFAULT_LOGGER, ::xos::logger::level::error_message, message)
#define XOS_LOG_MESSAGE_WARN(message) XOS_LOG_PLAIN(XOS_DEFAULT_LOGGER, ::xos::logger::level::warn_message, message)
#define XOS_LOG_MESSAGE_INFO(message) XOS_LOG_PLAIN(XOS_DEFAULT_LOGGER, ::xos::logger::level::info_message, message)
#define XOS_LOG_MESSAGE_DEBUG(message) XOS_LOG_PLAIN(XOS_DEFAULT_LOGGER, ::xos::logger::level::debug_message, message)
#define XOS_LOG_MESSAGE_TRACE(message) XOS_LOG_PLAIN(XOS_DEFAULT_LOGGER, ::xos::logger::level::trace_message, message)

#define XOS_LOG_MESSAGE_ANYF(message, ...) XOS_LOG_PLAIN_ANY_LEVELF(XOS_DEFAULT_LOGGER, message, ##__VA_ARGS__)
#define XOS_LOG_MESSAGE_FATALF(message, ...) XOS_LOG_PLAINF(XOS_DEFAULT_LOGGER, ::xos::logger::level::fatal_message, message, ##__VA_ARGS__)
#define XOS_LOG_MESSAGE_ERRORF(message, ...) XOS_LOG_PLAINF(XOS_DEFAULT_LOGGER, ::xos::logger::level::error_message, message, ##__VA_ARGS__)
#define XOS_LOG_MESSAGE_WARNF(message, ...) XOS_LOG_PLAINF(XOS_DEFAULT_LOGGER, ::xos::logger::level::warn_message, message, ##__VA_ARGS__)
#define XOS_LOG_MESSAGE_INFOF(message, ...) XOS_LOG_PLAINF(XOS_DEFAULT_LOGGER, ::xos::logger::level::info_message, message, ##__VA_ARGS__)
#define XOS_LOG_MESSAGE_DEBUGF(message, ...) XOS_LOG_PLAINF(XOS_DEFAULT_LOGGER, ::xos::logger::level::debug_message, message, ##__VA_ARGS__)
#define XOS_LOG_MESSAGE_TRACEF(message, ...) XOS_LOG_PLAINF(XOS_DEFAULT_LOGGER, ::xos::logger::level::trace_message, message, ##__VA_ARGS__)

///
/// XOS_IF_LOGGED_ FATAL .. TRACE
/// 
#define XOS_IF_LOGGED_FATAL(__is_logged__, message) XOS_IF_LOGGED(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::fatal, message)
#define XOS_IF_LOGGED_ERROR(__is_logged__, message) XOS_IF_LOGGED(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::error, message)
#define XOS_IF_LOGGED_WARN(__is_logged__, message) XOS_IF_LOGGED(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::warn, message)
#define XOS_IF_LOGGED_INFO(__is_logged__, message) XOS_IF_LOGGED(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::info, message)
#define XOS_IF_LOGGED_DEBUG(__is_logged__, message) XOS_IF_LOGGED(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::debug, message)
#define XOS_IF_LOGGED_TRACE(__is_logged__, message) XOS_IF_LOGGED(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::trace, message)

#define XOS_IF_LOGGED_FATALF(__is_logged__, message, ...) XOS_IF_LOGGEDF(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::fatal, message, ##__VA_ARGS__)
#define XOS_IF_LOGGED_ERRORF(__is_logged__, message, ...) XOS_IF_LOGGEDF(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::error, message, ##__VA_ARGS__)
#define XOS_IF_LOGGED_WARNF(__is_logged__, message, ...) XOS_IF_LOGGEDF(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::warn, message, ##__VA_ARGS__)
#define XOS_IF_LOGGED_INFOF(__is_logged__, message, ...) XOS_IF_LOGGEDF(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::info, message, ##__VA_ARGS__)
#define XOS_IF_LOGGED_DEBUGF(__is_logged__, message, ...) XOS_IF_LOGGEDF(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::debug, message, ##__VA_ARGS__)
#define XOS_IF_LOGGED_TRACEF(__is_logged__, message, ...) XOS_IF_LOGGEDF(__is_logged__, XOS_DEFAULT_LOGGER, ::xos::logger::level::trace, message, ##__VA_ARGS__)

///
/// XOS_IS_LOGGED_ ERROR / DEBUG / TRACE
/// 
#define XOS_IS_LOGGED_FATAL(message) XOS_IF_LOGGED_FATAL(this->is_logged(), message)
#define XOS_IS_LOGGED_ERROR(message) XOS_IF_LOGGED_ERROR(this->is_logged(), message)
#define XOS_IS_LOGGED_WARN(message) XOS_IF_LOGGED_WARN(this->is_logged(), message)
#define XOS_IS_LOGGED_INFO(message) XOS_IF_LOGGED_INFO(this->is_logged(), message)
#define XOS_IS_LOGGED_DEBUG(message) XOS_IF_LOGGED_DEBUG(this->is_logged(), message)
#define XOS_IS_LOGGED_TRACE(message) XOS_IF_LOGGED_TRACE(this->is_logged(), message)

///
/// XOS_IF_ERR_LOGGED_ FATAL .. TRACE
/// 
#define XOS_IF_ERR_LOGGED_FATAL(__is_logged__, __is_err_logged__, message) \
if (__is_logged__) { XOS_LOG_FATAL(message); } \
else { if (__is_err_logged__) { XOS_ERR_LOG_FATAL(message); } }

#define XOS_IF_ERR_LOGGED_ERROR(__is_logged__, __is_err_logged__, message) \
if (__is_logged__) { XOS_LOG_ERROR(message); } \
else { if (__is_err_logged__) { XOS_ERR_LOG_ERROR(message); } }

#define XOS_IF_ERR_LOGGED_WARN(__is_logged__, __is_err_logged__, message) \
if (__is_logged__) { XOS_LOG_WARN(message); } \
else { if (__is_err_logged__) { XOS_ERR_LOG_WARN(message); } }

#define XOS_IF_ERR_LOGGED_INFO(__is_logged__, __is_err_logged__, message) \
if (__is_logged__) { XOS_LOG_INFO(message); } \
else { if (__is_err_logged__) { XOS_ERR_LOG_INFO(message); } }

#define XOS_IF_ERR_LOGGED_DEBUG(__is_logged__, __is_err_logged__, message) \
if (__is_logged__) { XOS_LOG_DEBUG(message); } \
else { if (__is_err_logged__) { XOS_ERR_LOG_DEBUG(message); } }

#define XOS_IF_ERR_LOGGED_TRACE(__is_logged__, __is_err_logged__, message) \
if (__is_logged__) { XOS_LOG_TRACE(message); } \
else { if (__is_err_logged__) { XOS_ERR_LOG_TRACE(message); } }

///
/// XOS_IS_ERR_LOGGED_ FATAL .. TRACE
/// 
#define XOS_IS_ERR_LOGGED_FATAL(message) XOS_IF_ERR_LOGGED_FATAL(this->is_logged(), this->is_err_logged(), message)
#define XOS_IS_ERR_LOGGED_ERROR(message) XOS_IF_ERR_LOGGED_ERROR(this->is_logged(), this->is_err_logged(), message)
#define XOS_IS_ERR_LOGGED_WARN(message) XOS_IF_ERR_LOGGED_WARN(this->is_logged(), this->is_err_logged(), message)
#define XOS_IS_ERR_LOGGED_INFO(message) XOS_IF_ERR_LOGGED_INFO(this->is_logged(), this->is_err_logged(), message)
#define XOS_IS_ERR_LOGGED_DEBUG(message) XOS_IF_ERR_LOGGED_DEBUG(this->is_logged(), this->is_err_logged(), message)
#define XOS_IS_ERR_LOGGED_TRACE(message) XOS_IF_ERR_LOGGED_TRACE(this->is_logged(), this->is_err_logged(), message)

///
/// LOG_...
/// 

///
/// LOG_ FATAL .. TRACE
/// 
#if !defined(LOG_FATAL)
#define LOG_FATAL(__message__) XOS_LOG_FATAL(__message__)
#endif /// !defined(LOG_FATAL)

#if !defined(LOG_ERROR)
#define LOG_ERROR(__message__) XOS_LOG_ERROR(__message__)
#endif /// !defined(LOG_ERROR)

#if !defined(LOG_WARN)
#define LOG_WARN(__message__) XOS_LOG_WARN(__message__)
#endif /// !defined(LOG_WARN)

#if !defined(LOG_INFO)
#define LOG_INFO(__message__) XOS_LOG_INFO(__message__)
#endif /// !defined(LOG_INFO)

#if !defined(LOG_DEBUG)
#define LOG_DEBUG(__message__) XOS_LOG_DEBUG(__message__)
#endif /// !defined(LOG_DEBUG)

#if !defined(LOG_TRACE)
#define LOG_TRACE(__message__) XOS_LOG_TRACE(__message__)
#endif /// !defined(LOG_TRACE)

///
/// LOG_ FATALF .. TRACEF
/// 
#if !defined(LOG_FATALF)
#define LOG_FATALF(__message__, ...) XOS_LOG_FATALF(__message__, ##__VA_ARGS__)
#endif /// !defined(LOG_FATALF)

#if !defined(LOG_ERRORF)
#define LOG_ERRORF(__message__, ...) XOS_LOG_ERRORF(__message__, ##__VA_ARGS__)
#endif /// !defined(LOG_ERRORF)

#if !defined(LOG_WARNF)
#define LOG_WARNF(__message__, ...) XOS_LOG_WARNF(__message__, ##__VA_ARGS__)
#endif /// !defined(LOG_WARNF)

#if !defined(LOG_INFOF)
#define LOG_INFOF(__message__, ...) XOS_LOG_INFOF(__message__, ##__VA_ARGS__)
#endif /// !defined(LOG_INFOF)

#if !defined(LOG_DEBUGF)
#define LOG_DEBUGF(__message__, ...) XOS_LOG_DEBUGF(__message__, ##__VA_ARGS__)
#endif /// !defined(LOG_DEBUGF)

#if !defined(LOG_TRACEF)
#define LOG_TRACEF(__message__, ...) XOS_LOG_TRACEF(__message__, ##__VA_ARGS__)
#endif /// !defined(LOG_TRACEF)

///
/// IF_LOGGED_ FATAL .. TRACE
/// 
#if !defined(IF_LOGGED_FATAL)
#define IF_LOGGED_FATAL(__is_logged__, __message__) XOS_IF_LOGGED_FATAL(__is_logged__, __message__)
#endif /// !defined(IF_LOGGED_FATAL)

#if !defined(IF_LOGGED_ERROR)
#define IF_LOGGED_ERROR(__is_logged__, __message__) XOS_IF_LOGGED_ERROR(__is_logged__, __message__)
#endif /// !defined(IF_LOGGED_ERROR)

#if !defined(IF_LOGGED_WARN)
#define IF_LOGGED_WARN(__is_logged__, __message__) XOS_IF_LOGGED_WARN(__is_logged__, __message__)
#endif /// !defined(IF_LOGGED_WARN)

#if !defined(IF_LOGGED_INFO)
#define IF_LOGGED_INFO(__is_logged__, __message__) XOS_IF_LOGGED_INFO(__is_logged__, __message__)
#endif /// !defined(IF_LOGGED_INFO)

#if !defined(IF_LOGGED_DEBUG)
#define IF_LOGGED_DEBUG(__is_logged__, __message__) XOS_IF_LOGGED_DEBUG(__is_logged__, __message__)
#endif /// !defined(IF_LOGGED_DEBUG)

#if !defined(IF_LOGGED_TRACE)
#define IF_LOGGED_TRACE(__is_logged__, __message__) XOS_IF_LOGGED_TRACE(__is_logged__, __message__)
#endif /// !defined(IF_LOGGED_TRACE)

///
/// IF_ERR_LOGGED_ FATAL .. TRACE
/// 
#if !defined(IF_ERR_LOGGED_FATAL)
#define IF_ERR_LOGGED_FATAL(__is_logged__, __is_err_logged__, __message__) XOS_IF_ERR_LOGGED_FATAL(__is_logged__, __is_err_logged__, __message__)
#endif /// !defined(IF_ERR_LOGGED_FATAL)

#if !defined(IF_ERR_LOGGED_ERROR)
#define IF_ERR_LOGGED_ERROR(__is_logged__, __is_err_logged__, __message__) XOS_IF_ERR_LOGGED_ERROR(__is_logged__, __is_err_logged__, __message__)
#endif /// !defined(IF_ERR_LOGGED_ERROR)

#if !defined(IF_ERR_LOGGED_WARN)
#define IF_ERR_LOGGED_WARN(__is_logged__, __is_err_logged__, __message__) XOS_IF_ERR_LOGGED_WARN(__is_logged__, __is_err_logged__, __message__)
#endif /// !defined(IF_ERR_LOGGED_WARN)

#if !defined(IF_ERR_LOGGED_INFO)
#define IF_ERR_LOGGED_INFO(__is_logged__, __is_err_logged__, __message__) XOS_IF_ERR_LOGGED_INFO(__is_logged__, __is_err_logged__, __message__)
#endif /// !defined(IF_ERR_LOGGED_INFO)

#if !defined(IF_ERR_LOGGED_DEBUG)
#define IF_ERR_LOGGED_DEBUG(__is_logged__, __is_err_logged__, __message__) XOS_IF_ERR_LOGGED_DEBUG(__is_logged__, __is_err_logged__, __message__)
#endif /// !defined(IF_ERR_LOGGED_DEBUG)

#if !defined(IF_ERR_LOGGED_TRACE)
#define IF_ERR_LOGGED_TRACE(__is_logged__, __is_err_logged__, __message__) XOS_IF_ERR_LOGGED_TRACE(__is_logged__, __is_err_logged__, __message__)
#endif /// !defined(IF_ERR_LOGGED_TRACE)

///
/// IS_LOGGED_ FATAL .. TRACE
/// 
#if !defined(IS_LOGGED_FATAL)
#define IS_LOGGED_FATAL(__message__) XOS_IS_LOGGED_FATAL(__message__)
#endif /// !defined(IS_LOGGED_FATAL)

#if !defined(IS_LOGGED_ERROR)
#define IS_LOGGED_ERROR(__message__) XOS_IS_LOGGED_ERROR(__message__)
#endif /// !defined(IS_LOGGED_ERROR)

#if !defined(IS_LOGGED_WARN)
#define IS_LOGGED_WARN(__message__) XOS_IS_LOGGED_WARN(__message__)
#endif /// !defined(IS_LOGGED_WARN)

#if !defined(IS_LOGGED_INFO)
#define IS_LOGGED_INFO(__message__) XOS_IS_LOGGED_INFO(__message__)
#endif /// !defined(IS_LOGGED_INFO)

#if !defined(IS_LOGGED_DEBUG)
#define IS_LOGGED_DEBUG(__message__) XOS_IS_LOGGED_DEBUG(__message__)
#endif /// !defined(IS_LOGGED_DEBUG)

#if !defined(IS_LOGGED_TRACE)
#define IS_LOGGED_TRACE(__message__) XOS_IS_LOGGED_TRACE(__message__)
#endif /// !defined(IS_LOGGED_TRACE)

#if !defined(IS_LOGGED_DEBUG_TRACE)
#define IS_LOGGED_DEBUG_TRACE(__is_debug__, __message__) \
    if (__is_debug__) { IS_LOGGED_DEBUG(__message__); } else { XOS_IS_LOGGED_TRACE(__message__); }
#endif /// !defined(IS_LOGGED_TRACE)

#if !defined(IF_LOGGED_DEBUG_TRACE)
#define IF_LOGGED_DEBUG_TRACE(__is_debug__, __is_logged__, __message__) \
    if (__is_logged__) { if (__is_debug__) { IS_LOGGED_DEBUG(__message__); } else { IS_LOGGED_TRACE(__message__); } }
#endif /// !defined(IF_LOGGED_DEBUG_TRACE)

///
/// IS_ERR_LOGGED_ FATAL .. TRACE
/// 
#if !defined(IS_ERR_LOGGED_FATAL)
#define IS_ERR_LOGGED_FATAL(__message__) XOS_IS_ERR_LOGGED_FATAL(__message__)
#endif /// !defined(IS_ERR_LOGGED_FATAL)

#if !defined(IS_ERR_LOGGED_ERROR)
#define IS_ERR_LOGGED_ERROR(__message__) XOS_IS_ERR_LOGGED_ERROR(__message__)
#endif /// !defined(IS_ERR_LOGGED_ERROR)

#if !defined(IS_ERR_LOGGED_WARN)
#define IS_ERR_LOGGED_WARN(__message__) XOS_IS_ERR_LOGGED_WARN(__message__)
#endif /// !defined(IS_ERR_LOGGED_WARN)

#if !defined(IS_ERR_LOGGED_INFO)
#define IS_ERR_LOGGED_INFO(__message__) XOS_IS_ERR_LOGGED_INFO(__message__)
#endif /// !defined(IS_ERR_LOGGED_INFO)

#if !defined(IS_ERR_LOGGED_DEBUG)
#define IS_ERR_LOGGED_DEBUG(__message__) XOS_IS_ERR_LOGGED_DEBUG(__message__)
#endif /// !defined(IS_ERR_LOGGED_DEBUG)

#if !defined(IS_ERR_LOGGED_TRACE)
#define IS_ERR_LOGGED_TRACE(__message__) XOS_IS_ERR_LOGGED_TRACE(__message__)
#endif /// !defined(IS_ERR_LOGGED_TRACE)

#if !defined(IF_ERR_LOGGED_DEBUG_TRACE)
#define IF_ERR_LOGGED_DEBUG_TRACE(__is_debug__, __is_logged__, __is_err_logged__, __message__) \
    if (__is_logged__) { if (__is_debug__) { IS_LOGGED_DEBUG(__message__); } else { IS_LOGGED_TRACE(__message__); } } \
    else { if (__is_err_logged__) { if (__is_debug__) { IS_ERR_LOGGED_DEBUG(__message__); } else { IS_ERR_LOGGED_TRACE(__message__); } } }
#endif /// !defined(IF_ERR_LOGGED_DEBUG_TRACE)

///
/// IS_LOGGING_ FATAL .. TRACE
/// 
#if !defined(IS_LOGGING)
#define IS_LOGGING
#endif /// !defined(IS_LOGGING)

#if !defined(IS_LOGGING_FATAL)
#define IS_LOGGING_FATAL(__message__) IS_LOGGED_FATAL(__message__)
#endif /// !defined(IS_LOGGING_FATAL)

#if !defined(IS_LOGGING_ERROR)
#define IS_LOGGING_ERROR(__message__) IS_LOGGED_ERROR(__message__)
#endif /// !defined(IS_LOGGING_ERROR)

#if !defined(IS_LOGGING_WARN)
#define IS_LOGGING_WARN(__message__) IS_LOGGED_WARN(__message__)
#endif /// !defined(IS_LOGGING_WARN)

#if !defined(IS_LOGGING_INFO)
#define IS_LOGGING_INFO(__message__) IS_LOGGED_INFO(__message__)
#endif /// !defined(IS_LOGGING_INFO)

#if !defined(IS_LOGGING_DEBUG)
#define IS_LOGGING_DEBUG(__message__) IS_LOGGED_DEBUG(__message__)
#endif /// !defined(IS_LOGGING_DEBUG)

#if !defined(IS_LOGGING_TRACE)
#define IS_LOGGING_TRACE(__message__) IS_LOGGED_TRACE(__message__)
#endif /// !defined(IS_LOGGING_TRACE)

///
/// IS_ERR_LOGGING_ FATAL .. TRACE
/// 
#if !defined(IS_ERR_LOGGING)
#define IS_ERR_LOGGING
#endif /// !defined(IS_ERR_LOGGING)

#if !defined(IS_ERR_LOGGING_FATAL)
#define IS_ERR_LOGGING_FATAL(__message__) IS_ERR_LOGGED_FATAL(__message__)
#endif /// !defined(IS_ERR_LOGGING_FATAL)

#if !defined(IS_ERR_LOGGING_ERROR)
#define IS_ERR_LOGGING_ERROR(__message__) IS_ERR_LOGGED_ERROR(__message__)
#endif /// !defined(IS_ERR_LOGGING_ERROR)

#if !defined(IS_ERR_LOGGING_WARN)
#define IS_ERR_LOGGING_WARN(__message__) IS_ERR_LOGGED_WARN(__message__)
#endif /// !defined(IS_ERR_LOGGING_WARN)

#if !defined(IS_ERR_LOGGING_INFO)
#define IS_ERR_LOGGING_INFO(__message__) IS_ERR_LOGGED_INFO(__message__)
#endif /// !defined(IS_ERR_LOGGING_INFO)

#if !defined(IS_ERR_LOGGING_DEBUG)
#define IS_ERR_LOGGING_DEBUG(__message__) IS_ERR_LOGGED_DEBUG(__message__)
#endif /// !defined(IS_ERR_LOGGING_DEBUG)

#if !defined(IS_ERR_LOGGING_TRACE)
#define IS_ERR_LOGGING_TRACE(__message__) IS_ERR_LOGGED_TRACE(__message__)
#endif /// !defined(IS_ERR_LOGGING_TRACE)

#endif /// _XOS_LOGGER_INTERFACE_HPP 
