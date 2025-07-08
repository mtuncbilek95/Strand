import sys
import os
import re

# This path has been excluded, since this path is here to generate the 
# macros and function for the reflection system.
excludedPaths = [
    "/Source/Runtime/Data/Definitions/ReflectionNames.h",
    "/External",
    "/Resources",
    "/Shaders",
    "/Build",
    "/Tools",
    "/.git",
    "/.vs",
    "/.idea"
]

# This generator will look for those items below and use those to generate
# reflection code automatically.
includedItems = [
    "[[Reflection::Method]]",
    "[[Reflection::Field]]"
]

# Global list to collect matched files.
matchedFiles = []
requestedFiles = []

# Checks if the path is in the excludedPaths list.
def checkExcluded(path):
    for ex in excludedPaths:
        if os.path.normpath(ex) in os.path.normpath(path):
            return True
    return False

# Checks if the file contains any of the reflection macros.
def containsReflection(filePath):
    try:
        with open(filePath, 'r', encoding='utf-8') as f:
            content = f.read()
            for macro in includedItems:
                if macro in content:
                    return True
    except Exception as e:
        print(f"Error reading {filePath}: {e}")
    return False

# main definition
def main():
    if len(sys.argv) < 2:
        print("Reflection Generator Path: There is no path!")
        sys.exit(-1)

    argPath = sys.argv[1]
    print("Reflection Generator Path:", argPath)

    for root, dirs, files in os.walk(argPath):
        dirs[:] = [d for d in dirs if not checkExcluded(os.path.join(root, d))]

        for file in files:
            fullPath = os.path.join(root, file)
            if not checkExcluded(fullPath) and containsReflection(fullPath):
                matchedFiles.append(fullPath)

    for fPath in matchedFiles:
        if fPath.endswith(".h"):
            cppPath = os.path.splitext(fPath)[0] + ".cpp"
            if os.path.exists(cppPath):
                requestedFiles.append(cppPath)

    for cpp in requestedFiles:
        print(cpp)

if __name__ == "__main__":
    main()