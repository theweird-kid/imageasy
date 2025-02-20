# Function to install dependencies
install_deps() {
    conan install . -s build_type=Debug -s compiler.cppstd=20 --output-folder=build --build missing
}

# Function to configure the project with CMake
configure_project() {
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
}

# Function to build the project
build_project() {
    cmake --build build
}

# Function to run the application (assuming the executable is named 'app' and located in the 'build' directory)
run_app() {
    prime-run ./build/imageasy
}

# Check the input argument and call the corresponding function
case "$1" in
    install)
        install_deps
        ;;
    configure)
        configure_project
        ;;
    build)
        build_project
        ;;
    run)
        run_app
        ;;
    *)
        echo "Usage: $0 {install|configure|build|run}"
        exit 1
        ;;
esac
