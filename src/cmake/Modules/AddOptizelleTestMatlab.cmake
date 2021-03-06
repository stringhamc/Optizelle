# Sets up and runs Optizelle unit tests 
macro(add_optizelle_test_matlab name)

    # Make sure that tests are enabled
    if(ENABLE_MATLAB_UNIT)
        # Figure out whether we have MATLAB or Octave.  If is_matlab is
        # negative we have Octave, otherwise we have MATLAB. 
        string(TOLOWER ${MATLAB_EXECUTABLE} prog)
        string(FIND ${prog} "matlab" is_matlab)

        if(${is_matlab} LESS 0)
            add_test( "Execution_of_matlab_${name}"
                ${MATLAB_EXECUTABLE} "--eval" 
                "${executable}${name}(),exit")
        else()
            add_test( "Execution_of_matlab_${name}"
                ${MATLAB_EXECUTABLE} "-nosplash -nodesktop -r" 
                "\"${executable}${name}(),exit\"")
        endif()
        set_tests_properties("Execution_of_matlab_${name}"
            PROPERTIES ENVIRONMENT
                "MATLABPATH=${CMAKE_BINARY_DIR}/src/matlab:${CMAKE_CURRENT_SOURCE_DIR}")
        set_property(TEST "Execution_of_matlab_${name}"
            APPEND PROPERTY ENVIRONMENT
                "OCTAVE_PATH=${CMAKE_BINARY_DIR}/src/matlab:${CMAKE_CURRENT_SOURCE_DIR}")
    endif()

endmacro()
