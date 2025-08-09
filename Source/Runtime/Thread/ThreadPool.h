/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Thread/JobQueue.h>

namespace Strand
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