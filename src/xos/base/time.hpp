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
///   File: time.hpp
///
/// Author: $author$
///   Date: 4/24/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_TIME_HPP
#define _XOS_BASE_TIME_HPP

#include "xos/base/timezone.hpp"

namespace xos {

typedef implement_base time_implementt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: time_implementt
///////////////////////////////////////////////////////////////////////
template <class TImplements = time_implementt_implements>
class _EXPORT_CLASS time_implementt: virtual public TImplements {
public:
    typedef TImplements implements;
};
typedef time_implementt<> time_implement;

typedef time_implement timet_implements;
typedef base timet_extends;
///////////////////////////////////////////////////////////////////////
///  Class: timet
///////////////////////////////////////////////////////////////////////
template <class TImplements = timet_implements, class TExtends = timet_extends>
class _EXPORT_CLASS timet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    timet(hours_t hour, minutes_t minute, seconds_t second)
    : hour_(hour), minute_(minute), second_(second),
      msecond_(0), usecond_(0), nsecond_(0), 
      timezone_(0), is_local_(false), is_12_(false), is_pm_(false) {
    }
    timet(const timet &copy)
    : hour_(copy.hour()), minute_(copy.minute()), second_(copy.second()),
      msecond_(copy.msecond()), usecond_(copy.usecond()), nsecond_(copy.nsecond()), 
      timezone_(copy.timezone()), is_local_(copy.is_local()), is_12_(copy.is_12()), is_pm_(copy.is_pm()) {
    }
    timet()
    : hour_(0), minute_(0), second_(0),
      msecond_(0), usecond_(0), nsecond_(0), 
      timezone_(0), is_local_(false), is_12_(false), is_pm_(false) {
    }
    virtual ~timet() {
    }

    virtual int compare(const timet& to) const {
        return compare_time(to);
    }
    virtual int compare_time(const timet& to) const {
        int unequal = 0;
        if (!(unequal = compare_hour(to.hour()))) {
            if (!(unequal = compare_minute(to.minute()))) {
                if (!(unequal = compare_second(to.second()))) {
                    if (!(unequal = compare_msecond(to.msecond()))) {
                        if (!(unequal = compare_usecond(to.usecond()))) {
                            unequal = compare_nsecond(to.nsecond());
                        }
                    }
                }
            }
        }
        return unequal;
    }
    virtual int compare_hour(hours_t to) const {
        if ((hour_ < to)) {
            return -1;
        } else {
            if ((hour_ > to)) {
                return 1;
            }
        }
        return 0;
    }
    virtual int compare_minute(minutes_t to) const {
        if ((minute_ < to)) {
            return -1;
        } else {
            if ((minute_ > to)) {
                return 1;
            }
        }
        return 0;
    }
    virtual int compare_second(seconds_t to) const {
        if ((second_ < to)) {
            return -1;
        } else {
            if ((second_ > to)) {
                return 1;
            }
        }
        return 0;
    }
    virtual int compare_msecond(mseconds_t to) const {
        if ((msecond_ < to)) {
            return -1;
        } else {
            if ((msecond_ > to)) {
                return 1;
            }
        }
        return 0;
    }
    virtual int compare_usecond(useconds_t to) const {
        if ((usecond_ < to)) {
            return -1;
        } else {
            if ((usecond_ > to)) {
                return 1;
            }
        }
        return 0;
    }
    virtual int compare_nsecond(nseconds_t to) const {
        if ((nsecond_ < to)) {
            return -1;
        } else {
            if ((nsecond_ > to)) {
                return 1;
            }
        }
        return 0;
    }
    virtual int operator != (const timet& to) const {
        return this->compare(to);
    }
    virtual operator bool () const {
        const timet to;
        return ((this->compare(to)) != 0);
    }

    virtual timet& clear() {
        set_hour(0);
        set_timezone(0);
        set_is_local(false);
        set_is_12(false);
        set_is_pm(false);
        return *this;
    }
    virtual hours_t set_24_hour_to_12_hour() {
        is_12_ = true;
        if ((is_pm_ = (11 < (hour_)))) {
            hour_ -= 12;
        }
        if (!(hour_)) {
            hour_ = 12;
        }
        return hour_;
    }
    virtual hours_t set_hour(hours_t to) {
        hour_= to;
        set_minute(0);
        return hour_;
    }
    virtual hours_t hour() const {
        return hour_;
    }
    virtual minutes_t set_minute(minutes_t to) {
        minute_= to;
        set_second(0);
        return minute_;
    }
    virtual minutes_t minute() const {
        return minute_;
    }
    virtual seconds_t set_second(seconds_t to) {
        second_= to;
        set_msecond(0);
        return second_;
    }
    virtual seconds_t second() const {
        return second_;
    }
    virtual mseconds_t set_msecond(mseconds_t to) {
        msecond_= to;
        set_usecond(0);
        return msecond_;
    }
    virtual mseconds_t msecond() const {
        return msecond_;
    }
    virtual useconds_t set_usecond(useconds_t to) {
        usecond_= to;
        set_nsecond(0);
        return usecond_;
    }
    virtual useconds_t usecond() const {
        return usecond_;
    }
    virtual nseconds_t set_nsecond(nseconds_t to) {
        nsecond_= to;
        return nsecond_;
    }
    virtual nseconds_t nsecond() const {
        return nsecond_;
    }

    virtual timezone_t set_timezone(timezone_t to) {
        timezone_= to;
        return timezone_;
    }
    virtual timezone_t timezone() const {
        return timezone_;
    }

    virtual bool set_is_local(bool is_true = true) {
        is_local_ = is_true;
        return is_local_;
    }
    virtual bool is_local() const {
        return is_local_;
    }
    virtual bool set_is_12(bool is_true = true) {
        is_12_ = is_true;
        return is_12_;
    }
    virtual bool is_12() const {
        return is_12_;
    }
    virtual bool set_is_pm(bool is_true = true) {
        is_pm_ = is_true;
        return is_pm_;
    }
    virtual bool is_pm() const {
        return is_pm_;
    }

protected:
    hours_t hour_;
    minutes_t minute_;
    seconds_t second_;
    mseconds_t msecond_;
    useconds_t usecond_;
    nseconds_t nsecond_;
    timezone_t timezone_;
    bool is_local_, is_12_, is_pm_;
};
typedef timet<> time;

} /// namespace xos

#endif /// _XOS_BASE_TIME_HPP 
