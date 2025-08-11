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

allClassInfos: List[parserInfo.ClassInfo] = []

if __name__ == "__main__":
   if len(sys.argv) != 2:
       print("Usage: python script.py <source_path>")
       sys.exit(1)
   
   sourcePath = sys.argv[1]
   
   if not os.path.exists(sourcePath):
       print(f"Error: Path '{sourcePath}' does not exist")
       sys.exit(1)
   
   allClassInfos = scanner.scanSourceFolder(sourcePath)