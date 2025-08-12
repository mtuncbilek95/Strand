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
import ScanFiles as scanner
import WriteFiles as writer
allClassInfos: List[parserInfo.ClassInfo] = []

if __name__ == "__main__":
	if len(sys.argv) != 3:
		print("Usage: python script.py <source_path> <output_path>")
		sys.exit(1)
   
	sourcePath = sys.argv[1]
	outputPath = sys.argv[2]
   
	if not os.path.exists(sourcePath):
		print(f"Error: Path '{sourcePath}' does not exist")
		sys.exit(1)
   
	allClassInfos = scanner.scanSourceFolder(sourcePath)
	for classInfo in allClassInfos:
		fileString = writer.generateFileString(classInfo)
		writer.writeFile(fileString, outputPath)