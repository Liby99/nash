# Applications

You can create new applications under this directory. Every `.cpp` file will be compiled to an
executable linking the `nash` library as well as `nanogui` and `assimp`. You must have a main
function for each of the `.cpp` file under this directory. A potential template for a program
would be

``` c++
#include <nash/nash.h> // Include the header file from nash

using namespace nash; // Use the namespace to avoid repeatedly adding `nash::`

int main(int argc, char * argv[]) {
  Nash::init(argc, argv); // Remember to initialize the library,

  // Do Anything

  Nash::shutdown(); // ...and also shutdown
}
```

Feel free to add other sub-directories and it's find to add them to anywhere.
