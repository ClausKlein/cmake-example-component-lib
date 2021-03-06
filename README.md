<p align="center">
  <img src="https://repository-images.githubusercontent.com/254842585/4dfa7580-7ffb-11ea-99d0-46b8fe2f4170" height="175" width="auto" />
</p>

# ModernCppComponentLibraryExample

Setting up a new C++ project usually requires a significant amount of
preparation and boilerplate code, even more so for modern C++ projects
with tests, executables and continuous integration.  This template is the
result of learnings from many previous projects and should help reduce
the work required to setup up a modern C++ project.

This repository is intended as a template to show the "proper" way to
setup a "Modern CMake" project with `components`. The required usage (for a
downstream library) should be nothing more than:

```cmake
  find_package(
    MathFunctions 1
    COMPONENTS Addition SquareRoot
    REQUIRED
  )

  /#..

  target_link_libraries(
    MathFunctionsTests Boost::ut MathFunctions::Addition MathFunctions::SquareRoot
  )
```


## Features

- [Modern CMake practices](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/)
- [CMake for library authors: Best practice](https://crascit.com/2019/10/16/cppcon-2019-deep-cmake-for-library-authors/)
- [Modernize C++ using clang-tidy](https://www.kdab.com/clang-tidy-part-1-modernize-source-code-using-c11c14/)
- [CMake Importing Exporting Guilde](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html?highlight=components#adding-components)
- [Prevents clang-tidy to check sources added with FetchContents](https://discourse.cmake.org/t/how-to-prevent-clang-tidy-to-check-sources-added-with-fetchcontents/2871)
- Suited for single header libraries and projects of any scale
- Clean separation of library and executable code
- Integrated test suite
- Continuous integration via [GitHub Actions](https://help.github.com/en/actions/)
- Code coverage via [gcovr](https://gcovr.com)
- Code coverage via [codecov](https://codecov.io)
- Code formatting enforced by [clang-format](https://clang.llvm.org/docs/ClangFormat.html) and [cmake-format](https://github.com/cheshirekow/cmake_format)
- Reproducible dependency management via [CPM.cmake](https://github.com/TheLartians/CPM.cmake)
- Installable target with automatic versioning information and header generation via [PackageProject.cmake](https://github.com/TheLartians/PackageProject.cmake)
- Automatic [documentation](https://thelartians.github.io/ModernCppStarter) and deployment with [Doxygen](https://www.doxygen.nl) and [GitHub Pages](https://pages.github.com)
- Support for [sanitizer tools, and more](#additional-tools)


## Tips

- Use [Gitflow Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow)
- Use [Ninja](https://cmake.org/cmake/help/latest/generator/Ninja.html)
  and [ccache](https://ccache.dev) to speed up your round trip time
- Use [Boost::ut ](https://boost-ext.github.io/ut/) A pure C++20 μ(micro)/Unit Testing Framework if possible
- Try [Qt Creator](https://www.qt.io/download-open-source) as [IDE](#IDE)
  ... or simply use [gvim](https://packages.ubuntu.com/bionic/gvim) and type `:make test`


## Usage

### Adjust the template to your needs

- Use this repo [as a template](https://help.github.com/en/github/creating-cloning-and-archiving-repositories/creating-a-repository-from-a-template) and replace all occurrences of "MathFunctions" in the relevant `CMakeLists.txt` with the name of your project
- Replace the source files with your own
- Happy coding!

Eventually, you can remove any unused files, such as the standalone
directory or irrelevant github workflows for your project.  Feel free to
replace the [License](License) with one suited for your project.

To cleanly separate the library and subproject code, the outer
[CMakeLists.txt](CMakeLists.txt) only defines the library itself while
the tests and other subprojects are self-contained in their own
directories.  During development it is usually convenient to [build all
subprojects at once](#build-everything-at-once).


### Use the makefile wrapper on unix bash or with GVIM

There is a [makefile](GNUmakefile) to wrap the
[CMake](https://cmake.org/cmake/help/latest/manual/cmake.1.html)
command-line interface for esay use at bash shell.


### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
make standalone

# or
cmake --build build/standalone
build/standalone/MathFunctionsStandalone 2.0
```

### Build and run test suite

Use the following commands from the project's root directory to run the
test suite.

```bash
make test

# or
cmake -S test -B build/test
cmake --build build/test
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test

# or simply call the executable:
build/test/MathFunctionsTest
```

To collect code coverage information, run CMake with the
`-DENABLE_TEST_COVERAGE=1` option.


### Generate a GCC Code Coverage Report

To generate or update with `gcovr` the html files
[reports/gcov/index.html](https://clausklein.github.io/cmake-example-component-lib/):

`make gcov`


### Run clang-tidy

The [.clang-tidy](.clang-tidy)
[checks](https://clang.llvm.org/extra/clang-tidy/) supports you to write
clean code!

To check your project with _clang-tidy_ simply do

`make tidy`


### Run clang-format

Use the following commands from the project's root directory to check and
fix C++ and CMake source style.  This requires _clang-format_,
_cmake-format_ and _pyyaml_ to be installed on the current system.

```bash
make format

# or
cmake -S test -B build/test

# view changes
cmake --build build/test --target format

# apply changes
cmake --build build/test --target fix-format
```

See [Format.cmake](https://github.com/TheLartians/Format.cmake) for details.


### Build the documentation

To manually build documentation, call the following command.

```bash
make doc

# or
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
# view the docs
open build/doc/doxygen/html/index.html
```

To build the documentation locally, you will need Doxygen, jinja2 and
Pygments on installed your system.


### Build everything at once

The project also includes an `all` directory that allows building all
targets at the same time.  This is useful during development, as it
exposes all subprojects to your IDE and avoids redundant builds of the
library.


## IDE

Use [Qt Creator](https://www.qt.io/download-open-source) as IDE

It creates the best usable results when open the project via
[all/CMakeLists.txt](all/CMakeLists.txt).  And it supports to direct
import a existing CMake build directory create with:


```bash
make all

# or
cmake -S all -B build
cmake --build build

# run tests
build/test/MathFunctionsTest
# format code
cmake --build build --target fix-format
# run standalone
build/standalone/MathFunctionsStandalone 42.0
# build docs
cmake --build build --target GenerateDocs
```


## Additional tools

The test and standalone subprojects include the
[tools.cmake](cmake/tools.cmake) file which is used to import additional
tools on-demand through CMake configuration arguments.  The following are
currently supported.

#### Sanitizers

Sanitizers can be enabled by configuring CMake with
`-DUSE_SANITIZER=<Address | Memory | MemoryWithOrigins | Undefined | Thread | Leak | 'Address;Undefined'>`.

#### Static Analyzers

Static Analyzers can be enabled by setting
`-DUSE_STATIC_ANALYZER=<clang-tidy | iwyu | cppcheck>`, or a combination
of those in quotation marks, separated by semicolons.  By default,
analyzers will automatically find configuration files such as
`.clang-format`.  Additional arguments can be passed to the analyzers by
setting the `CLANG_TIDY_ARGS`, `IWYU_ARGS` or `CPPCHECK_ARGS` variables.

#### Ccache

Ccache can be enabled by configuring with `-DUSE_CCACHE=<ON | OFF>`.


## FAQ

> Can I use this for header-only libraries?

Yes, however you will need to change the library type to an `INTERFACE`
library as documented in the [CMakeLists.txt](CMakeLists.txt).  See
[here](https://github.com/TheLartians/StaticTypeInfo) for an example
header-only library based on the template.

> I don't need a standalone target / documentation. How can I get rid of it?

Simply remove the standalone / documentation directory and according
github workflow file.

> Can I build the standalone and tests at the same time? / How can I tell my IDE about all subprojects?

To keep the template modular, all subprojects derived from the library
have been separated into their own CMake modules.  This approach makes it
trivial for third-party projects to re-use the projects library code.  To
allow IDEs to see the full scope of the project, the template includes
the `all` directory that will create a single build for all subprojects.
Use this as the main directory for best IDE support.

> I see you are using `GLOB` to add source files in `CMakeLists.txt`. Isn't that evil?

Glob is considered bad because any changes to the source file structure
[might not be automatically
caught](https://cmake.org/cmake/help/latest/command/file.html#filesystem)
by CMake's builders and you will need to manually invoke CMake on
changes.  I personally prefer the `GLOB` solution for its simplicity, but
feel free to change it to explicitly listing sources.

> I want create additional targets that depend on my library. Should I modify the main `CMakeLists.txt` to include them?

Avoid including derived projects from the libraries `CMakeLists.txt` (even
though it is a common sight in the C++ world), as this effectively
inverts the dependency tree and makes the build system hard to reason
about.  Instead, create a new directory or project with a `CMakeLists.txt` that
adds the library as a dependency (e.g. like the
[standalone](standalone/CMakeLists.txt) directory).  Depending type it
might make sense move these components into a separate repositories and
reference a specific commit or version of the library.  This has the
advantage that individual libraries and components can be improved and
updated independently.

> You recommend to add external dependencies using CPM.cmake. Will this force users of my library to use CPM as well?

[CPM.cmake](https://github.com/TheLartians/CPM.cmake) should be invisible
to library users as it's a self-contained CMake Script.  If problems do
arise, users can always opt-out by defining `CPM_USE_LOCAL_PACKAGES`,
which will override all calls to `CPMAddPackage` with `find_package`.
Alternatively, you could use `CPMFindPackage` instead of `CPMAddPackage`,
which will try to use `find_package` before calling `CPMAddPackage` as a
fallback.  Both approaches should be compatible with common C++ package
managers without modifications, however come with the cost of
reproducible builds.

> Can I configure and build my project offline?

Using CPM, all missing dependencies are downloaded at configure time.  To
avoid redundant downloads, it's recommended to set a CPM cache directory,
e.g.: `export CPM_SOURCE_CACHE=$HOME/.cache/CPM`.  This will also allow
offline configurations if all dependencies are present.  No internet
connection is required for building.

> Can I use CPack to create a package installer for my project?

As there are a lot of possible options and configurations, this is not
(yet) in the scope of this template. See the [CPack
documentation](https://cmake.org/cmake/help/latest/module/CPack.html) for
more information on setting up CPack installers.

> This is too much, I just want to create a singe C++ library.

Perhaps the [ModernCppStarter](https://github.com/ClausKlein/ModernCppStarter)

> This is too much, I just want to play with C++ code and test some libraries.

Perhaps the [MiniCppStarter](https://github.com/TheLartians/MiniCppStarter) is something for you!

