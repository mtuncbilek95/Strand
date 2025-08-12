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

def generateFileString(classInfo: parserInfo.ClassInfo) -> str:
   className = classInfo.className
   relativePath = classInfo.relativePath
   
   result = f"""#include <{relativePath}>

namespace Strand
{{
   template<>
   class TypeAccessor<{className}>
   {{
   public:
   	TypeAccessor()
   	{{
   		ReflectionRegistry::Get().RegisterClassInfo<{className}>();
"""
   
   for constructor in classInfo.constructors:
   	if constructor.params:
   		paramsStr = ", ".join(constructor.params)
   		result += f"\t\tReflectionRegistry::Get().RegisterConstructor<{className}, {paramsStr}>();\n"
   	else:
   		result += f"\t\tReflectionRegistry::Get().RegisterConstructor<{className}>();\n"
   
   for field in classInfo.fields:
   	fieldName = field.typeName
   	fieldType = field.typePrimitive
   	if fieldName.startswith('m_'):
   		cleanFieldName = fieldName[2:]
   		displayFieldName = cleanFieldName[0].upper() + cleanFieldName[1:] if cleanFieldName else ""
   	else:
   		displayFieldName = fieldName[0].upper() + fieldName[1:] if fieldName else ""

   	result += f"""\t\tReflectionRegistry::Get().RegisterFieldInfo<{className}>("{displayFieldName}", 
\t\t\toffsetof({className}, {fieldName}), *ReflectionRegistry::Get().GetTypeInfo<{fieldType}>());
"""
   
   result += f"""\t}}
   }};

   static TypeAccessor<{className}> gb_{className.lower()}Accessor;
}}"""
   
   return result


def extractPath(generatedString: str) -> str:
   lines = generatedString.split('\n')
   firstLine = lines[0]
   
   startIndex = firstLine.find('<') + 1
   endIndex = firstLine.find('>')
   relativePath = firstLine[startIndex:endIndex]
   
   pathParts = relativePath.split('/')
   firstDir = pathParts[0]
   fileName = pathParts[-1]
   
   baseFileName = fileName.rsplit('.', 1)[0]
   generatedPath = firstDir + "/" + baseFileName + ".generated.cpp"
   
   return generatedPath


def writeFile(fileString : str, outputPath : str):
	fileRelativePath = extractPath(fileString)
	try:
		absPath = os.path.join(outputPath, fileRelativePath)
		
		if not os.path.exists(os.path.dirname(absPath)):
			os.makedirs(os.path.dirname(absPath))
		
		if os.path.exists(absPath):
			with open(absPath, 'r', encoding='utf-8') as file:
				existingContent = file.read()
			if fileString != existingContent:
				with open(absPath, 'w', encoding='utf-8') as file:
					file.write(fileString)
				print(f"File {absPath} updated.")
			else:
				print(f"File {absPath} already exists and is up to date.")
		else:
			with open(absPath, 'w', encoding='utf-8') as file:
				file.write(fileString)
			print(f"File {absPath} created.")
			
	except Exception as e:
		print(f"Error writing file {absPath}: {e}")