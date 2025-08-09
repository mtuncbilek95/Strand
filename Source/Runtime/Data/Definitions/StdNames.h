/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>

#include <string>
using String = std::string;
using WString = std::wstring;
using StringStream = std::stringstream;

#include <string_view>
using StringView = std::string_view;

#include <queue>
template<typename T>
using Queue = std::queue<T>;

#include <span>
template<typename T>
using Span = std::span<T>;

#include <array>
template<typename T, usize N>
using Array = std::array<T, N>;

#include <vector>
template<typename T>
using Vector = std::vector<T>;

#include <map>
template<typename K, typename V>
using Map = std::map<K, V>;

template<typename K, typename V>
using Pair = std::pair<K, V>;

#include <list>
template<typename T>
using List = std::list<T>;

#include <set>
template<typename T>
using Set = std::set<T>;

#include <filesystem>
namespace FileSys = std::filesystem;

using Path = FileSys::path;

#include <fstream>
using FileStream = std::fstream;
using OutFileStream = std::ofstream;
using InFileStream = std::ifstream;

#include <unordered_map>
template<typename K, typename V, typename...Args>
using HashMap = std::unordered_map<K, V, Args...>;

template<typename T>
using Hash = std::hash<T>;

#include <variant>
template<typename... Args>
using Variant = std::variant<Args...>;

#include <memory>
template<typename T>
using Owned = std::unique_ptr<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using Weak = std::weak_ptr<T>;

#include <typeindex>
using TypeIndex = std::type_index;

#include <any>
using Any = std::any;

#include <bitset>
template<usize T>
using Bitset = std::bitset<T>;

#include <initializer_list>
template<typename T>
using InitList = std::initializer_list<T>;

template<typename T, typename... Args>
Owned<T> NewOwn(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
Ref<T> NewRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#include <thread>
using Thread = std::thread;
namespace CurrentThread = std::this_thread;

#include <mutex>
using Mutex = std::mutex;
using CondVar = std::condition_variable;

template<typename T>
using LockGuard = std::lock_guard<T>;

#include <shared_mutex>
using SharedMutex = std::shared_mutex;

template<typename T>
using SharedLock = std::shared_lock<T>;

template<typename T>
using UniqueLock = std::unique_lock<T>;

#include <atomic>
template<typename T>
using Atomic = std::atomic<T>;

#include <functional>
template<typename T>
using function = std::function<T>;
using voidPtrFunc = std::function<void*>;
using voidFunc = std::function<void()>;

template<typename T>
using NumericLimits = std::numeric_limits<T>;

using OpenMode = std::ios_base::openmode;
using IosBase = std::ios_base;

template<typename T>
using RemoveRef = std::remove_reference_t<T>;

template<typename T>
using RemoveCVRef = std::remove_cvref_t<T>;