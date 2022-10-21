[![CMake](https://github.com/teknostom/cpp/actions/workflows/cmake.yml/badge.svg?branch=master)](https://github.com/teknostom/cpp/actions/workflows/cmake.yml)
# Remedy
<details>
  <summary>Basic Usage</summary>

## Basic Usage:
  the basic syntax is: <br />
  ```console
  remedy [flags] [file (.tex)]
  ```
  this can only be done if the application is in your path list. <br />
  alternativley you can have the executable in your working directory:<br />
  (remedy) = (Linux: remedy) (Windows: remedy.exe)
  ```console
  (remedy) [flags] [file (.tex)]
  ```
  OR
  ```console
  /path/to/storage/for/program/(remedy) [flags] [file (.tex)]
  ```

| Flags | Meaning |
|:-----:|:-----:|
| -o    | Enter a filename after this flag to specify output.
| -c    | Enter a filename after this flag to specify config.
| -t    | This flag allows timer to be shown.
| -d    | This flag allows debug mode to be set.
| -h    | This flag shows the help menu, it cannot be used along with execution.
</details>

<details>
  <summary>Advanced Usage</summary>

A config file is generated when running the code for the first time.

### Configuring:
| Problem type           | Fix type:          | Stoptype:     |
|:----------------------:|:------------------:|:-------------:|
| READ_ALL               | FIX_AT_PROBLEM     | STOP_AT_MATCH |
| READ_ALL_RUNNING_COUNT | FIX_AT_START       | SKIP_AT_MATCH |
|                        | FIX_AT_END         | DONT_STOP     |
|                        | REPLACE_AT_PROBLEM |               |
</details>