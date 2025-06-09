#include "VkMemoryUtils.h"

#include <magic_enum/magic_enum.hpp>

namespace Flax
{
    VmaMemoryUsage VmaUtils::GetVmaUsage(MemoryUsage usage)
    {
        VmaMemoryUsage flags = VMA_MEMORY_USAGE_UNKNOWN;

        for (auto u : magic_enum::enum_values<MemoryUsage>())
        {
            if (HasFlag(usage, u))
            {
                switch (u)
                {
                case MemoryUsage::GpuLazy:
                    flags = VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED;
                    break;
                case MemoryUsage::Auto:
                    flags = VMA_MEMORY_USAGE_AUTO;
                    break;
                case MemoryUsage::AutoPreferDevice:
                    flags = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;
                    break;
                case MemoryUsage::AutoPreferHost:
                    flags = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
                    break;
                default:
                    break;
                }
            }
        }

        return flags;
    }

    VmaAllocationCreateFlags VmaUtils::GetVmaFlags(MemoryAllocation alloc)
    {
        VmaAllocationCreateFlags flags = 0;

        for (auto a : magic_enum::enum_values<MemoryAllocation>())
        {
            if (HasFlag(alloc, a))
            {
                switch (a)
                {
                case MemoryAllocation::DedicatedMemory:
                    flags |= VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
                    break;
                case MemoryAllocation::NeverAllocate:
                    flags |= VMA_ALLOCATION_CREATE_NEVER_ALLOCATE_BIT;
                    break;
                case MemoryAllocation::Mapped:
                    flags |= VMA_ALLOCATION_CREATE_MAPPED_BIT;
                    break;
                case MemoryAllocation::UpperAddress:
                    flags |= VMA_ALLOCATION_CREATE_UPPER_ADDRESS_BIT;
                    break;
                case MemoryAllocation::DontBind:
                    flags |= VMA_ALLOCATION_CREATE_DONT_BIND_BIT;
                    break;
                case MemoryAllocation::WithinBudget:
                    flags |= VMA_ALLOCATION_CREATE_WITHIN_BUDGET_BIT;
                    break;
                case MemoryAllocation::CanAlias:
                    flags |= VMA_ALLOCATION_CREATE_CAN_ALIAS_BIT;
                    break;
                case MemoryAllocation::SequentialWrite:
                    flags |= VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
                    break;
                case MemoryAllocation::HostAccessRandom:
                    flags |= VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;
                    break;
                case MemoryAllocation::AllowTransferInstead:
                    flags |= VMA_ALLOCATION_CREATE_HOST_ACCESS_ALLOW_TRANSFER_INSTEAD_BIT;
                    break;
                case MemoryAllocation::StrategyMinMemory:
                    flags |= VMA_ALLOCATION_CREATE_STRATEGY_MIN_MEMORY_BIT;
                    break;
                case MemoryAllocation::StrategyMinTime:
                    flags |= VMA_ALLOCATION_CREATE_STRATEGY_MIN_TIME_BIT;
                    break;
                case MemoryAllocation::StrategyMinOffset:
                    flags |= VMA_ALLOCATION_CREATE_STRATEGY_MIN_OFFSET_BIT;
                    break;
                default:
                    break;
                }
            }
        }

        return flags;
    }

}
