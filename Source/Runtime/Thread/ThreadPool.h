/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Thread/JobQueue.h>

namespace Flax
{
    class ThreadPool
    {
    public:
        ThreadPool(usize count = 2);
        ~ThreadPool();

        void EnqueueJob(const voidFunc& job);
        void WaitForIdle();

    private:
        void WorkerLoop();

    private:
        Atomic<b8> m_isRunning;
        Vector<Thread> m_threads;

        JobQueue m_queue;
    };
}