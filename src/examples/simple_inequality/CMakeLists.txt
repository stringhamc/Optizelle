project(simple_inequality)

# Compile and install the example
add_optizelle_example_cpp(${PROJECT_NAME})
add_optizelle_example_python(${PROJECT_NAME})
add_optizelle_example_matlab(${PROJECT_NAME})

# Installs the supporting files 
add_optizelle_example_supporting(${PROJECT_NAME}
    newton_cg.json
    newton_cg_backtracking.json
    sr1.json
    tr_newton.json
    tr_newton_predictor_corrector.json)

# Add some unit tests
add_optizelle_json_test_cpp("*.json" ${PROJECT_NAME})
add_optizelle_json_test_python("*.json" ${PROJECT_NAME})
add_optizelle_json_test_matlab("*.json" ${PROJECT_NAME})
