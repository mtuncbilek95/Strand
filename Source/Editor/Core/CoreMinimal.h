/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

#include <Runtime/FileSystem/IFileStream.h>
#include <Runtime/FileSystem/IVirtualFileNode.h>
#include <Runtime/FileSystem/IVirtualFileSystem.h>
#include <Runtime/FileSystem/Service/VirtualFileService.h>

#include <Editor/Data/Registry/ViewModelBase.h>
#include <Editor/Data/Registry/ViewModelRegistry.h>

#include <Editor/Data/Controller/ControllerBase.h>
#include <Editor/Data/Controller/ControllerManager.h>

#define EDITOR_NOT_IMPLEMENTED_YET(returnType) \
	{ \
		Log::Error(LogType::Editor, "'{}' This function is not implemented yet!", __FUNCTION__); \
		return returnType; \
	}
