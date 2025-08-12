# InTarget: Where to read
# OutTarget: Where to write
function(ExecuteReflection InTarget OutTarget)
	set(INPUT_PATH "${CMAKE_SOURCE_DIR}/${InTarget}")
	set(OUTPUT_PATH "${CMAKE_SOURCE_DIR}/${OutTarget}")
   
	set(PYTHON_SCRIPT "${CMAKE_SOURCE_DIR}/Tools/ReflectionGenerator/ReflectionGenerator.py")
   
	execute_process(
   		COMMAND python "${PYTHON_SCRIPT}" "${INPUT_PATH}" "${OUTPUT_PATH}"
   		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
   		RESULT_VARIABLE RESULT
   		OUTPUT_VARIABLE OUTPUT
   		ERROR_VARIABLE ERROR)
   
   if(NOT RESULT EQUAL 0)
   	message(FATAL_ERROR "Reflection generation failed: ${ERROR}")
   else()
   	message(STATUS "Reflection generated successfully: ${InTarget} -> ${OutTarget}")
   endif()

endfunction()