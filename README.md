# SeaShell

SeaShell is a modular command-line interface application written in C++ that provides various utilities for file operations, networking, and system management.

## Architecture

SeaShell uses a modular architecture with the following components:

1. **Core Library (libseashell_core)**: Contains common functionality shared across all modules
2. **Module Libraries**:
   - **libseashell_files**: File operations (encryption, compression, file management)
   - **libseashell_networking**: Network operations (interfaces, client/server)
   - **libseashell_system**: System operations (process management)
3. **Executables**:
   - **seashell**: Main CLI application
   - **seashell_files_exe**: File operations executable
   - **seashell_net_exe**: Network operations executable
   - **seashell_sys_exe**: System operations executable

This modular approach allows:
- Better separation of concerns
- Improved maintainability
- Ability to use modules independently
- Easier extension with new modules

## Dependencies

### System Requirements
- **CMake:** 3.25 or higher
- **C++ Compiler:** Clang 20 (Linux), MSVC latest (Windows)
- **Python 3.13** (Optional, for Python script execution)
- **MySQL:** 8.4 or higher (Optional, for database operations)

### Libraries (via vcpkg)
- **POCO**
- **OpenSSL**
- **curl**
- **libssh-2**

## Building

SeaShell uses CMake for building:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

The main CLI provides a unified interface to all modules:

```bash
# Use the main CLI
./seashell

# Use modules directly
./seashell_files_exe encrypt myfile.txt
./seashell_net_exe ifconfig
./seashell_sys_exe ps
```

## License

Distributed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For any inquiries or feedback, reach out to glanshammar70@gmail.com.