#pragma once
#include <Runtime/FileSystem/Service/VirtualFileService.h>
#include <Runtime/FileSystem/IVirtualFileNode.h>
#include <Runtime/FileSystem/IFileStream.h>
#include <Runtime/FileSystem/DiskFile/DiskFileSystem.h>
#include <Runtime/Resources/Assets/Scene/SceneMetadata.h>
#include <Runtime/Resources/Assets/Scene/SceneImporter.h>
#include <Runtime/Resources/Assets/AssetMetadataRegistry.h>
#include <Runtime/Scene/Scene.h>
#include <Runtime/Scene/Component.h>

#include <iostream>

using namespace Flax;

// Recursive function to print the scene hierarchy with their component names
void RecursiveScenePrint(Scene* scene)
{

}

int main()
{
	auto vfm = RuntimeService::Get<VirtualFileService>();
	vfm->Initialize(R"(D:\Projects\FlaxTestProject)");
	vfm->Mount("Assets", NewRef<DiskFileSystem>());
	vfm->Mount("Caches", NewRef<DiskFileSystem>());
	vfm->Mount("Scripts", NewRef<DiskFileSystem>());
	vfm->Mount("Intermediate", NewRef<DiskFileSystem>());

	/*
	auto aim = RuntimeService::Get<AssetService>();
	aim->ReadAsset("Assets/TestFolder2/TestScene.scene");
	
	
	
	
	*/
}