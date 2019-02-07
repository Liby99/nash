# Tests

You can create new tests under this directory. Similar to `/app` folder, you can add `.cpp` files
anywhere under this (or sub-) directory(ies). Make sure every `.cpp` file you are adding contains
a `main` function.

## Testing Infrastructure

Not Built Yet

## Nash Viewer Application Tests

Just like the `.cpp` files in `/app`, you can follow this kind of template to create tests:

``` c++
#include <nash/nash.h> // Include the header file from nash

using namespace nash; // Use the namespace to avoid repeatedly adding `nash::`

int main(int argc, char * argv[]) {
  Nash::init(argc, argv); // Remember to initialize the library,

  // Do Anything

  Nash::shutdown(); // ...and also shutdown
}
```
