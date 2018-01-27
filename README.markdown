# Vision
Viper is modern C++ header-only template library that provides a simplified and practical zero-overhead interface for working with 
C++ Standard Library containers.

Viper should help you get to the result you want now and go home.

* What does 'modern C++' mean?
It means C++14 or later.
Viper aims to use all the new features of the language it can in order achieve its goals.
That is the reason why we produce multiple versions of the header file, so a later version is not encumbered 
by a missing feature in a previous version of C++.

* What does 'header-only' mean?
It means no separate compilation steps needed.
It means trivial integration with your project, just copy the header file and build.

* What does 'simplified' mean?
It means less fighting with the system and more getting stuff done now.
For instance, to test value membership in a container, instead of this:
```c++
std::vector<int> vi = {1,2,3,4};

if(std::find(vi.cbegin(), vi.cend(), 3) != vi.cend()) {
  std::cout<<"3 is in vi"<<std::endl;
}
```

with Viper you would write:

```c++
std::vector<int> vi = {1,2,3,4};

if( in(vi, 3) ) {
  std::cout<<"3 is in vi"<<std::endl;
}
```

* What does 'practical' mean?
It means when making arbitrary decision about a design compromise, Viper favors practicality over purity.
If something works better for 99% of use cases, let's optimize for that.

* What does 'zero-overhead' mean?
It means your compiler should compile away the Viper layer, so your code is as fast as if it had been
written using the most idiomatic C++ with STL, only more verbose.
It some instances where Viper is return a lazy-evaluation object, it can even be faster.

# Examples

## Enumerate elements of an Container
```c++
std::vector<char> vc = {'a', 'b', 'c'};

// this is C++17 syntax
for( auto&& [index, character] : enumerate(puzzle) ) {
    printf(" vc[%lu] = '%c' \n", index, character);
}
```
prints out:

vc[0] = 'a'

vc[1] = 'b'

vc[2] = 'c'


## Filter elements of a Container
```c++
std::vector<int> vi = {1,2,3,4,5};
auto odd = [](int i) { return i % 2 == 1; };

decltype(vi) odd_numbers = filter(odd, vi);
```

## Test membership to a Container
```c++
std::vector<int> vi = {1,2,3,4};

if( in(vi,3) ) {
   // do something if 3 is in vi
}
```

## Transform a Container into another Container
```c++
std::vector<int> vi = {1,2,3,4};
auto ascii = [](int i) { return i+48; };

auto numbers = into<std::string>(ascii, vi);

std::cout<< numbers <<std::endl;

// prints:
// 1234
//
```


# How to use Viper in your project
Simply copy the header file into your project.
We produce several versions of the header, one for each C++ version.
```bash
viper.hpp
```

# Design
Loosely inspired by Python's iterator interface.
While not catering to Python developers specifically, viper should feel natural for them and help transition to C++.

# License
MIT License. 

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

make

# should make a 'tests' binary with debug symbols
cd 17/tests
make # if you run make in 17/tests it will only build 17/tests/tests

# to launch the tests:
./tests17

# to debug the tests (assuming you're using LLVM's lldb)
lldb ./tests17

# to make a Release version, same instructions, but use Release wherever Debug is used.
```
