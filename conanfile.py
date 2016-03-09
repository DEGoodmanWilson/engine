from conans import ConanFile, CMake

class LunaConan(ConanFile):
    name = "luna"
    version = "1.0.0-beta5"
    url = "https://github.com/DEGoodmanWilson/luna.git"
    license = "Apache 2.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = "cpr/1.2.0@cpr/testing"
    options = {"build_engine_tests":    [True, False]}
    default_options = "build_engine_tests=True"
    generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/DEGoodmanWilson/luna.git --branch conan") #v%s" % (self.version))

    def config(self):
        if self.options.build_engine_tests:
            self.requires.add("gtest/1.7.0@lasote/stable", private=False)
            self.options["gtest"].shared = False
        else:
            if "gtest" in self.requires:
                del self.requires["gtest"]

    def build(self):
        cmake = CMake(self.settings)
        build_engine_tests = "-DBUILD_ENGINE_TESTS=OFF" if not self.options.build_engine_tests else ""

        self.run('cmake %s "%s/luna" %s' % (build_engine_tests, self.conanfile_directory, cmake.command_line))
        self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include/slack", src="include/slack")
        self.copy("*.h", dst="include/slack/base", src="include/slack/base")
        self.copy("*.h", dst="include/slack/event", src="include/slack/event")
        self.copy("*.lib", dst="lib", src="lib")
        self.copy("*.a", dst="lib", src="lib")

    def package_info(self):
        self.cpp_info.libs = ["engine", "cpr"]