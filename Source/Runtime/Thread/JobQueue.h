/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	class JobQueue final
	{
	public:
		JobQueue() = default;
		~JobQueue() = default;

		void PushJob(const voidFunc& func)
		{
			{
				LockGuard<Mutex> lock(m_mutex);
				m_jobs.push(func);
			}
			m_condition.notify_one();
		}

		voidFunc PopJob()
		{
			UniqueLock<Mutex> lock(m_mutex);
			m_condition.wait(lock, [this]() { return !m_jobs.empty(); });

			voidFunc job = m_jobs.front();
			m_jobs.pop();
			return job;
		}

		b8 TryPopJob(voidFunc& job)
		{
			LockGuard<Mutex> lock(m_mutex);
			if (m_jobs.empty())
				return false;

			job = m_jobs.front();
			m_jobs.pop();
			return true;
		}

		b8 Empty() const
		{
			LockGuard<Mutex> lock(m_mutex);
			return m_jobs.empty();
		}

		usize Size() const
		{
			LockGuard<Mutex> lock(m_mutex);
			return m_jobs.size();
		}

	private:
		mutable Mutex m_mutex;
		CondVar m_condition;
		Queue<voidFunc> m_jobs;
	};
}