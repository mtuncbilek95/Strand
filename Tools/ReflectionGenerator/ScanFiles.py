#
# Licensed under the terms specified in the LICENSE.md file 
# located in the root directory of this source tree.
#
# Copyright (c) 2024 Metehan Tuncbilek
#

import sys
import os
import re

from pathlib import Path
from typing import List, Dict, NamedTuple, Optional
import Informations as parserInfo

excludedPaths = [
    "/External",
    "/Resources",
	"/Intermediate"
    "/Shaders",
    "/Build",
    "/Tools",
    "/.git",
    "/.vs",
    "/.idea"
	"/Source/Runtime/Reflection"
]

def scanSourceFolder(rootPath: str) -> List[parserInfo.ClassInfo]:
	allClassInfos: List[parserInfo.ClassInfo] = []

	for root, dirs, files in os.walk(rootPath):
		skipFolder = False
		for excluded in excludedPaths:
			if excluded in root:
				skipFolder = True
				break
		
		if skipFolder:
			continue
		    
		for file in files:
			if file.endswith(('.h', '.hpp')):
				filePath = os.path.join(root, file)
		        
				try:
					with open(filePath, 'r', encoding='utf-8') as f:
						headerFile = f.readlines()
		            
					objectInfo = parserInfo.getObjectType(headerFile)
		            
					if objectInfo and objectInfo.objectType == "Class":
						parentPath = Path(rootPath).parent
						relativePath = os.path.relpath(filePath, parentPath)
						classInfo = parserInfo.getClassInfo(headerFile, objectInfo, relativePath)
		                
						allClassInfos.append(classInfo)
		                
				except Exception as e:
					print(f"Error reading {filePath}: {e}")
	return allClassInfos