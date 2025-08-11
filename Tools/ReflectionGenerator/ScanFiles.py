#
# Licensed under the terms specified in the LICENSE.md file 
# located in the root directory of this source tree.
#
# Copyright (c) 2024 Metehan Tuncbilek
#

import sys
import os
import re

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
   					print(f"\n=== Found Class in: {filePath} ===")
   	                
   					classInfo = parserInfo.getClassInfo(headerFile, objectInfo)
   	                
   					print(f"Class Name: {classInfo.className}")
   					print(f"Fields ({len(classInfo.fields)}):")
   					for field in classInfo.fields:
   						print(f"  - {field.typePrimitive} {field.typeName}")
   	                
   					print(f"Constructors ({len(classInfo.constructors)}):")
   					for i, constructor in enumerate(classInfo.constructors):
   						paramsStr = ", ".join(constructor.params) if constructor.params else "no params"
   						print(f"  - Constructor {i+1}: ({paramsStr})")

   					allClassInfos.append(classInfo)
   	                
   			except Exception as e:
   				print(f"Error reading {filePath}: {e}")
   return allClassInfos