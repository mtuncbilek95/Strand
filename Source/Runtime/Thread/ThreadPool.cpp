#include "ThreadPool.h"

namespace Flax
{
    ThreadPool::ThreadPool(usize count)
    {
        if(count == 0 || (u32)count > Thread::hardware_concurrency())
            count = Thread::hardware_concurrency() / 4;

        Log::Debug(LogType::Thread, "ThreadPool: Creating {} threads", count);

        m_isRunning.store(true);

        for (usize i = 0; i < count; i++)
            m_threads.emplace_back([this]() { WorkerLoop(); });
    }

    ThreadPool::~ThreadPool()
    {
        m_isRunning.store(false);

        for (std::size_t i = 0; i < m_threads.size(); ++i)
            EnqueueJob([] {});

        for (auto& thread : m_threads)
        {
            if (thread.joinable())
                thread.join();
        }

        m_threads.clear();
    }

    void ThreadPool::EnqueueJob(const voidFunc& job)
    {
        m_queue.PushJob(job);
    }

    void ThreadPool::WaitForIdle()
    {
        while (!m_queue.Empty())
        {
            std::this_thread::yield();
        }
    }

    void ThreadPool::WorkerLoop()
    {
        while (m_isRunning.load())
        {
            voidFunc job = m_queue.PopJob();
            job(); // Execute
        }
    }
}