# Bunuel Libraries, Modules, and Layers

## using these libraries in linux

Set up environment variables so the compiler can find these libraries

add the library folders to the following environment variables in your `.bash_rc` or similar.

```
C_INCLUDE_PATH
LIBRARY_PATH
LD_LIBRARY_PATH
```

Then in projects `#include <bunuel/lib.h>`

## Using thse libraries outside of linux

Not supported. Please help add support if you'd like support for other platforms
