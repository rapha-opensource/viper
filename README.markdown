# Vision
Viper is modern C++ header-only template library that provides a simplified and practical zero-overhead interface for working with 
C++ Standard Library containers.

Viper should help you get to the result you want now and go home.

. What does 'modern C++' mean?
It means C++14 or later.
Viper aims to use all the new features of the language it can in order achieve its goals.
That is the reason why we produce multiple versions of the header file, so a later version is not encumbered 
by a missing feature in a previous version of C++.

. What does 'header-only' mean?
It means not separate compilation steps needed.
It means trivial integration with your project, just copy the header file and build.

. What does 'simplified' mean?
It means less fighting with the system and more getting stuff done now.
For instance, to test value membership in a container, instead of this:
```c++
std::vector<int> vi = {1,2,3,4};

if(std::find(vi.cbegin(), vi.cend(), 3) != vi.cend()) {
  std::cout<<"3 is in vi"<<std::endl;
}
// with Viper:
if( in(vi, 3) ) {
  std::cout<<"3 is in vi"<<std::endl;
}
```

. What does 'practical' mean?
It means when making arbitrary decision about a design compromise, Viper favors practicality over purity.
If something works better for 99% of use cases, let's optimize for that.

. What does 'zero-overhead' mean?
It means your compiler should compile away the Viper layer, so your code is as fast as if you had written
the STL logic by hand, leaving your source code small and readable and your binary fast.



# How to use Viper in your project
Simply copy the header file into your project.
We produce several versions of the header, one for each C++ version.
```bash
viper_14.hpp
viper_17.hpp
viper_20.hpp
```

# How to build this project with CMake
This will 'build out of source'.
Note that .gitignore ignores Release & Debug directories so as long
as we build inside Release & Debug we won't pollute the repo with build byproducts.

```bash
cd viper
mkdir Debug
cd Debug
# that should populate Debug with the subprojects
cmake -DCMAKE_BUILD_TYPE=Debug ..

# should make a 'tests' binary with debug symbols
cd tests
make

# to make a Release version, same instructions, but use Release wherever Debug is used.

# to launch the tests:
./tests

# to debug the tests (assuming you're using LLVM's lldb)
lldb ./tests
```
