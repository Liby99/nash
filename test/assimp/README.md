# Note

Notice how we are using `CMakeLists.txt` in the current directory. Inside this
file we only have one line:

```
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res/model/teapot.obj" DESTINATION "${temp_dir}/res/")
```

This says we are going to copy the root directory (`CMAKE_CURRENT_SOURCE_DIR`)'s
`/res/model/teapot.obj` to the target locations' `res/` folder. Then inside our
`.cpp` file we can write loading path to be

``` c++
AssimpObject teapot("./res/teapot.obj");
```

Note that the executable must be ran at exactly the place it is located in: which
means that you must go to the directory and run the executable. In this
particular example, you are going to do the following:

```
$ cd <YOUR_NASH_DIRECTORY>/build/test/assimp/
$ ./teapot_renderer
```

to run the executable
