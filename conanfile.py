from conans import ConanFile, CMake

class EngineConan(ConanFile):
    name = "engine"
    version = "1.0.0-beta1"
    url = "https://github.com/DEGoodmanWilson/engine.git"
    license = "Apache 2.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = "cpr/1.2.0@DEGoodmanWilson/testing", "OpenSSL/1.0.2h@lasote/stable", "Boost/1.60.0@lasote/stable"
    options = {"build_engine_tests":    [True, False]}
    default_options = "build_engine_tests=True", "Boost:shared=False"
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
