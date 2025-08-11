#
# Licensed under the terms specified in the LICENSE.md file 
# located in the root directory of this source tree.
#
# Copyright (c) 2024 Metehan Tuncbilek
#

from typing import List, Dict, NamedTuple, Optional
from enum import Enum

class ObjectType(NamedTuple):
	objectName : str
	objectType : str

class TypeInfo(NamedTuple):
	typePrimitive : str
	typeName : str

class ConstructorInfo(NamedTuple):
	params : List[str]

class ClassInfo(NamedTuple):
	className : str
	fields : List[TypeInfo]
	constructors : List[ConstructorInfo]

def getObjectType(headerFile : List[str]) -> ObjectType:
	for i, line in enumerate(headerFile):
		if "STRAND_ENUM()" in line or "[[Reflection::Enum]]" in line:
			objectName = headerFile[i + 1].strip().split()[-1]
			objectType = "Enum"
			return ObjectType(objectName, objectType)
		elif "STRAND_CLASS()" in line or "[[Reflection::Class]]" in line:
			objectName = headerFile[i + 1].strip().split()[-1]
			objectType = "Class"
			return ObjectType(objectName, objectType)
		elif "STRAND_STRUCT()" in line or "[[Reflection::Struct]]" in line:
			objectName = headerFile[i + 1].strip().split()[-1]
			objectType = "Struct"
			return ObjectType(objectName, objectType)

	return None

def getClassInfo(headerFile : List[str], objectInfo : ObjectType) -> ClassInfo:
	className = objectInfo.objectName
	constructors = []
	fields = []
	for i, line in enumerate(headerFile):
		if f"{className}(" in line and not line.strip().startswith(f"~{className}"):
   			endParenthesis = line.rfind(")")
   			startParenthesis = line.rfind("(", 0, endParenthesis)
   			paramsStr = line[startParenthesis+1:endParenthesis]
   		
   			if paramsStr.strip() == "":
   				params = []
   			else:
   				paramList = paramsStr.split(",")
   				params = []
   				
   				for param in reversed(paramList):
   					paramType = param.strip().rsplit(" ", 1)[0]
   					params.append(paramType)
   			
   			constructors.append(ConstructorInfo(params))
		
		elif "STRAND_FIELD()" in line or "[[Reflection::Field]]" in line:
			fieldLine = headerFile[i + 1].strip().rstrip(';')
			fieldParts = fieldLine.split()
   
			if len(fieldParts) >= 2:
			    typePrimitive = fieldParts[0]
			    typeName = fieldParts[1]
			    
			    fields.append(TypeInfo(typePrimitive, typeName))

	return ClassInfo(className, fields, constructors)