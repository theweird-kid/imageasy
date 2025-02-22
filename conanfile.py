from conan import ConanFile
from conan.tools.cmake import CMakeToolchain

class ImageasyConan(ConanFile):
    name = "imageasy"
    version = "0.1"
    license = "MIT"
    author = "gaurav theweirdki9@gmail.com"
    url = "https://github.com/theweird-kid/imageasy"
    description = "A simple image processing application"
    topics = ("image-processing", "fftw", "opengl", "imgui")

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("glfw/3.3.4")
        self.requires("glad/0.1.36", options={"gl_profile": "core", "gl_version": "4.6"}) # Force 4.6 core profile
        self.requires("glm/0.9.9.8")
        self.requires("imgui/1.88")
        self.requires("fftw/3.3.10")

    def configure(self):
        self.options["glad"].gl_profile = "core"
        self.options["glad"].gl_version = "4.6"
