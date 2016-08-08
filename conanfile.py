from conans import ConanFile, CMake

class EngineConan(ConanFile):
    name = "engine"
    version = "1.0.0-beta6"
    url = "https://github.com/DEGoodmanWilson/engine.git"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    requires = "cpr/1.2.0@DEGoodmanWilson/testing"
    options = {"build_engine_tests":    [True, False],
               "build_engine_coverage": [True, False],
               "build_engine_examples": [True, False]}
    default_options = "build_engine_tests=False", "build_engine_coverage=False", "build_engine_examples=False", "cpr:use_system_curl=True"
    generators = "cmake"
    exports = ["*"]

    def config(self):
        if self.options.build_engine_coverage:
            self.options.build_engine_tests=True

        if self.options.build_engine_tests:
            self.requires.add("gtest/1.7.0@lasote/stable", private=False)
            self.options["gtest"].shared = False
        else:
            if "gtest" in self.requires:
                del self.requires["gtest"]

    def build(self):
        cmake = CMake(self.settings)
        build_engine_tests = "-DBUILD_ENGINE_TESTS=ON" if self.options.build_engine_tests else "-DBUILD_ENGINE_TESTS=OFF"
        build_engine_coverage = "-DBUILD_ENGINE_COVERAGE=ON" if self.options.build_engine_coverage else "-DBUILD_ENGINE_COVERAGE=OFF"
        build_engine_examples = "-DBUILD_ENGINE_EXAMPLES=ON" if self.options.build_engine_examples else "-DBUILD_ENGINE_EXAMPLES=OFF"


        self.run('cmake %s %s %s %s' % (build_engine_tests, build_engine_coverage, build_engine_examples, cmake.command_line))
        self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include/slack", src="slack")
        self.copy("*.lib", dst="lib", src="lib")
        self.copy("*.a", dst="lib", src="lib")

    def package_info(self):
        self.cpp_info.libs = ["engine"]
