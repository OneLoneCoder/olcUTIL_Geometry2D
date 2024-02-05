function(add_coverage_target exclude)

    find_program(GCOV gcov)
    if (NOT GCOV)
        message(WARNING "program gcov not found")
    endif()

    find_program(LCOV lcov)
    if (NOT LCOV)
        message(WARNING "program lcov not found")
    endif()

    find_program(GENHTML genhtml)
    if (NOT GENHTML)
        message(WARNING "program genhtml not found")
    endif()

    if (LCOV AND GCOV AND GENHTML)
        set(covname cov.info)
        # the original file set all compile options here, but I prefer to set them in the CMakeLists.txt
        #add_compile_options(-fprofile-arcs -ftest-coverage)
        #add_link_options(--coverage)
        add_custom_target(cov DEPENDS ${covname})

        # lcov on ubuntu 22 doesn't support --branch-coverage
        set(COV_OPT 
            #"--branch-coverage"
            "--rc lcov_branch_coverage=1"
        )
        add_custom_command(
            OUTPUT  ${covname}
            COMMAND ${LCOV} -c -o ${covname} ${COV_OPT} -d . -b . --gcov-tool ${GCOV} --ignore-errors mismatch
            # In the following I explicitly exclude system headers from the coverage report
            COMMAND ${LCOV} -r ${covname} ${COV_OPT}  -o ${covname} ${exclude}  "\*/googletest/\*" "\*/g++\*/bits/\*" "'*/g++-v13/*'"
            COMMAND ${LCOV} -l ${covname} ${COV_OPT} 
            COMMAND ${GENHTML} ${covname} --branch-coverage -output coverage
            COMMAND ${LCOV} -l ${covname} ${COV_OPT}  2>/dev/null | grep Total | sed 's/|//g' | sed 's/Total://g' | awk '{print $1}' | sed s/%//g > coverage/total
        )
        set_directory_properties(PROPERTIES
            ADDITIONAL_CLEAN_FILES ${covname}
        )
    else()
        message(WARNING "unable to add target `cov`: missing coverage tools")
    endif()

endfunction()