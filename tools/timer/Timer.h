/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef Timer_DEFINED
#define Timer_DEFINED

#include "SkString.h"
#include "SkTime.h"
#include "SkTypes.h"

class WallTimer {
public:
    WallTimer() : fWall(-1) {}

    void start() { fWall = SkTime::GetNSecs(); }
    // ns -> ms
    // GetNSecs 是纳秒
    // 1e-6：10的-6次方，即小数点往前移6位
    void end()   { fWall = (SkTime::GetNSecs() - fWall) * 1e-6; }

    double fWall;  // Milliseconds.
                   // ms,毫秒。wall time：实际时钟时间(end clock time - start clock time)
                   // Elapsed real time, real time, wall-clock time, or wall time is the actual time taken from the start of a computer program to the end. 
                   // In other words, it is the difference between the time at which a task finishes and the time at which the task started.
                   // TODO: wangdong https://blog.csdn.net/zhangxinrun/article/details/25722059 (只看讲wall time 和 monotonic time)
                   //                https://blog.csdn.net/aganlengzi/article/details/21888351  (只看讲cpu time[process time])
};

// format time，让时间更能让人看懂
SkString HumanizeMs(double);

#endif
