//
// dsa is a utility library of data structures and algorithms built with C++11.
// This file (spinlock.hpp) is part of the dsa project.
//
// spinlock; a user-space spinlock implementation for C++11 or later.
//
// A description of a spinlock can be found here:
//
//      https://en.wikipedia.org/wiki/Spinlock
//
// author: Dalton Woodard
// contact: daltonmwoodard@gmail.com
// repository: https://github.com/daltonwoodard/spinlock.hpp
// license:
//
// Copyright (c) 2016 DaltonWoodard. See the COPYRIGHT.md file at the top-level
// directory or at the listed source repository for details.
//
//      Licensed under the Apache License. Version 2.0:
//          https://www.apache.org/licenses/LICENSE-2.0
//      or the MIT License:
//          https://opensource.org/licenses/MIT
//      at the licensee's option. This file may not be copied, modified, or
//      distributed except according to those terms.
//

#ifndef DSA_SPINLOCK_HPP
#define DSA_SPINLOCK_HPP

#include <atomic>       // std::atomic_flag, std::memory_order_{acquire,release}
#include <chrono>       // std::chrono::duration
#include <thread>       // std::this_thread::yield
#include <type_traits>  // std::common_type


namespace dsa
{
    /*
     * Description
     * -----------
     *
     * dsa::spinlock<> is a busy-wait synchronization primitive for protecting
     * shared data on (relatively) short time scales. The semantics are the same
     * as a std::mutex object:
     *
     *  - A calling thread owns a spinlock from the time it successfully
     *  calls either lock or try_lock until it calls unlock.
     *
     *  - When a thread owns a spinlock, all other threads will block for calls
     *  to lock or recieve a false return value for try_lock if they attempt to
     *  claim ownership of the spinlock.
     *
     *  - A calling thread must not own the spinlock prior to calling lock or
     *  try_lock.
     *
     *  - A call to lock waits on the calling thread for a user specified time-
     *  length, polling the status of the spinlock prior to invoking
     *  std::this_thread::yield. This process repeats until the calling thread
     *  acquires ownership of the spinlock.
     *
     *  - A call to try_lock either successfully claims ownership of the
     *  spinlock and returns a true value or immediately returns a false value.
     *
     * A description of a spinlock can be found here:
     *
     *      https://en.wikipedia.org/wiki/Spinlock
     *
     * A dsa::spinlock<> is compatible with std::unique_lock<> and
     * std::lock_guard<> objects.
     *
     * A dsa::spinlock<> is neither copyable nor movable.
     *
     * Template Parameters
     * -------------------
     *
     *  - WaitDurationType: a std::chrono::duration type specifying the type of
     *  the busy-wait delay time period.
     *
     *  - wait_count: a rep value of type WaitDurationType::rep specifying the
     *  default value of the time of type DelayDurationType to busy-wait delay
     *  during a call to lock.
     *
     * Member Types
     * ------------
     *
     *  - duration_type: a type given by std::common_type between the template
     *  typename DelayDurationType and std::chrono::nanoseconds.
     *
     * Member Functions
     * ----------------
     *
     *  - spinlock: constructs the spinlock.
     *
     *  - ~spinlock: destroys the spinlock.
     *
     *  - lock: locks the spinlock, blocking if the spinlock is not available.
     *
     *  - try_lock: tries to lock the spinlock, returns a boolean value
     *  depending on the success of the call.
     *
     *  - unlock: unlocks the spinlock.
     */
    template <
        typename WaitDurationType,
        typename WaitDurationType::rep wait_count
    >
    class spinlock
    {
    public:
        static_assert (wait_count > 0, "default wait count must be nonzero");

        using duration_type = typename std::common_type <
            WaitDurationType,
            std::chrono::nanoseconds
        >::type;

    private:
        static constexpr duration_type default_wait_time {
            std::chrono::duration_cast <duration_type> (
                WaitDurationType {wait_count}
            )
        };

        /* guaranteed initialization to false */
        std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;

    public:
        constexpr spinlock (void) noexcept = default;
        ~spinlock (void) noexcept          = default;

        spinlock (spinlock &&)      = delete;
        spinlock (spinlock const &) = delete;

        spinlock & operator= (spinlock &&)      = delete;
        spinlock & operator= (spinlock const &) = delete;

        void lock (duration_type wait_time = default_wait_time) & noexcept
        {
            while (true) {
                auto const start {std::chrono::steady_clock::now ()};

                while (lock_flag.test_and_set (std::memory_order_acquire)) {
                    auto const now {std::chrono::steady_clock::now ()};
                    auto const elapsed {
                        std::chrono::duration_cast <duration_type> (now - start)
                    };

                    if (elapsed >= wait_time) {
                        goto yield;
                    }
                }

                return;
            yield:
                std::this_thread::yield ();
            }
        }

        bool try_lock (void) & noexcept
        {
            return !lock_flag.test_and_set (std::memory_order_acquire);
        }

        void unlock (void) & noexcept
        {
            lock_flag.clear (std::memory_order_release);
        }
    };
} // namespace dsa

#endif // ifndef DSA_SPINLOCK_HPP
