# testing-repository

## A testing repository

\[Experimental]:  1. The rust programming language is imported for some codes

2. A test of building Xe Release with Rust is going on.

\[News]: After gtk112 and gtk113, the submodule GCR_CMake is imported

Thanks for the project author https://github.com/Makman2/GCR_CMake

and the author of json: https://github.com/nlohmann/json[GitHub - nlohmann/json: JSON for Modern C++](https://github.com/nlohmann/json)

The test for Qt5 is starting, and some example from the Qt opensource example.

(Actually, I forked the project for convenience)

### These contents are outdated:

Note: To minimize the repeated files,I put the same files as public resource

The file name is above:

public\_res\<filename\>\_\<file extension\> or public\_res\<filename\>\_\<file extension\>

Please compile with g++ or gcc (Clang is also supported)

(Visual Studio may have issues)

Ege dircitory need ege 19.01 and above to complie

C/C++ code using gtk2 needs gtk 2.24.10

#### For Gtk3 codes:

before gtk17 supports Gtk3.6.4

gtk17 and above removed support for gtk3.18 and below

Win32 exe supports WinXP and above

The Sample Code to get current dir

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char ** argv){
    //argv[0] for full application running path
    const char * src = *argv;

    //Get Size and store the content
    int len = strlen(src); 
    char * tmp = malloc(len);

    //The Name of application is "args.exe" for windows
    //And named "args" for linux
#ifdef _WIN32
    strncpy(tmp,src,len-8);
    tmp[len-8]='\0';
#else
    strncpy(tmp,src,len-4);
    tmp[len-4]='\0';
#endif

    printf("%s\n",tmp);
    free(tmp);
    return 0;
}
```

Java version

```java
public class Args{
    public static void main(String[] args){ 
        System.out.println(System.getProperty("user.dir"));
    }
}
```

Rust Version

```rust
use std::env;

fn main() {
    // Get executive path
    let args: Vec<String> = env::args().collect();
    let execpath: String = args[0].clone();

    // Handle the path string
    let exec_len: usize = 13;
    let length: usize;
    if cfg!(target_os = "windows") {
        length = execpath.len() - exec_len - 4;
    } else {
        length = execpath.len() - exec_len;
    }
    let path: &str = &execpath[0..length];

    // Print the path of executive
    println!("{}", path);
}
```

### Thanks:

Json lib for C++: https://github.com/nlohmann/json
