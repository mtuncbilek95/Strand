# InTarget: Where to read
# OutTarget: Where to write
function(ExecuteReflection TargetName InTarget OutTarget)
	set(INPUT_PATH "${CMAKE_SOURCE_DIR}/${InTarget}")
	set(OUTPUT_PATH "${CMAKE_SOURCE_DIR}/${OutTarget}")
   
	set(PYTHON_SCRIPT "${CMAKE_SOURCE_DIR}/Tools/ReflectionGenerator/ReflectionGenerator.py")
   
	add_custom_command(
		TARGET ${TargetName}
		PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E echo "Generating reflection for ${INPUT_PATH}..."
		COMMAND python "${PYTHON_SCRIPT}" "${INPUT_PATH}"
		COMMENT "Running reflection generator: ${InTarget} -> ${OutTarget}"
		VERBATIM)
endfunction()