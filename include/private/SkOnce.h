/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkOnce_DEFINED
#define SkOnce_DEFINED

#include <atomic>
#include <utility>
#include "SkTypes.h"

#include <stdio.h>

// SkOnce provides call-once guarantees for Skia, much like std::once_flag/std::call_once().
//
// There should be no particularly error-prone gotcha use cases when using SkOnce.
// It works correctly as a class member, a local, a global, a function-scoped static, whatever.
//
// SkOnce 提供一个确保只会调用一次的类，类似于std下的once_flag/call_once()
// 当使用SkOnce时，应该没有特别容易出错的陷阱case
// TODO: wangdong https://zh.cppreference.com/w/cpp/thread/call_once  (to see call_once)

class SkOnce {
public:
    // https://zh.cppreference.com/w/cpp/language/constexpr (to see constexpr)
    constexpr SkOnce() = default;

    template <typename Fn, typename... Args>
    void operator()(Fn&& fn, Args&&... args) {
        // TODO: wangdong https://zh.cppreference.com/w/cpp/atomic/memory_order (to see memory_order)
        auto state = fState.load(std::memory_order_acquire);

        //printf("SkOnce state = %d\n", state);

        if (state == Done) {
            //printf("SkOnce return\n");
            return;
        }

        // If it looks like no one has started calling fn(), try to claim that job.
        if (state == NotStarted && fState.compare_exchange_strong(state, Claimed,
                                                                  std::memory_order_relaxed,
                                                                  std::memory_order_relaxed)) {
            //printf("SkOnce call\n");
            // Great!  We'll run fn() then notify the other threads by releasing Done into fState.
            fn(std::forward<Args>(args)...);
            return fState.store(Done, std::memory_order_release);
        }

        // Some other thread is calling fn().
        // We'll just spin here acquiring until it releases Done into fState.
        while (fState.load(std::memory_order_acquire) != Done) { /*spin*/
            //printf("SkOnce while. load memory_order_acquire\n");
        }
    }

private:
    enum State : uint8_t { NotStarted, Claimed, Done};
    // TODO: wangdong https://zh.cppreference.com/w/cpp/atomic/atomic (to see atomic)
    std::atomic<uint8_t> fState{NotStarted};
};

#endif  // SkOnce_DEFINED
