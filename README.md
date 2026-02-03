# Bunuel Libraries, Modules, Tools and Layers

## using these libraries in linux

Set up environment variables so the compiler can find these libraries

add the following to `.bashrc`

```
export CPATH=/path/to/bunuel:CPATH
export LIBRARY_PATH=/path/to/bunuel/_build:$LIBRARY_PATH
```

Then in projects `#include <bunuel/lib.h>`


## Using thse libraries outside of linux

Not supported. Please help add support if you'd like support for other platforms

## Tools

**pin**: Generate the correct #BUNUEL_PIN_API_N #ifdef blocks for the bunuel versioning strategy

**rtm**: Requirements Tracability Matrix tooling. Write links ad hoc, rtm generates a matrix and reports gaps

**namer**: Adds [tym-xpo/namer](https://github.com/tym-xqo/namer) names to your files


