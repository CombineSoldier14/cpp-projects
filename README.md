# Random C++ Projects I made
Some random C++ projects by me for fun and learning. 

Includes:
- **BattleEngine**: A heavily customizable turn-based battle game.

# Build from Source
**BattleEngine**
  * You will need a C++ compiler. I recommend G++, but any should work fine.
  * You will need [vcpkg](https://vcpkg.io) and install that on your system. You can find instructions on their page linked.
  * Install [Git](https://git-scm.com/) on your system.
  * Install [CMake](https://cmake.org/).
  * Run `git clone https://github.com/CombineSoldier14/cpp-projects.git` in a free directory.
  * In the directory, run `vcpkg install`. If you run into errors, install any dependencies that are needed.
  * In the `battle-engine` directory, create a new directory called `build`
  * Enter the `build` directory and run `cmake ..` (you may need administrator privileges)
      * If you get an error about missing CMake configs, you will need to locate the `nlohmann_jsonConfig.cmake` file yourself, located somewhere in your vcpkg directory depending on your OS. For me, it's `~/vcpkg/buildtrees/nlohmann-json/x64-linux-dbg/`. On Windows it may be different. Once you find the directory, run CMake again but as `cmake .. -DCMAKE_PREFIX_PATH=<config-directory>`.
  * Then run `make` in the build directory. (again you may need administrator privileges)
  * After that finishes, you now have a compiled binary of BattleEngine! You will need a `settings.json` in the same directory as it for it to work correctly.
