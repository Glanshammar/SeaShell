# SeaShell: Enhancing the Command-Line Experience
SeaShell is a console application, and it aims to enhance the command-line interface experience. While drawing inspiration from established shells, it's currently a work-in-progress, striving to integrate familiar functionalities with a sleek interface and formidable capabilities. Though not fully realized yet, SeaShell is on a path toward revolutionizing the command-line experience.

# Features (Work-in-Progress)
* **Cross-Platform Compatibility:** Works seamlessly across various operating systems.
* **Sleek Interface:** A visually appealing shell enhancing user interaction.
* **Powerful Scripting:** Empowers users to craft and execute robust scripts effortlessly.
* **IDE:** An intuitive and simple IDE catering to both seasoned developers and newcomers.
* **Terminal Emulator:** SeaShell aims to become a fully fledged terminal emulator with its own shell.

# Build Instructions
The CMake file in this (root) directory is for building the project.
Under the "Libraries" directory, there's another CMakeLists file for helping with the dependencies.
Run the CMake file to build the whole project.

## Dependencies
***Standalone Dependencies***
* **CMake:** 3.28 or higher
* **C++ Compiler:** GCC 14 (Linux), MSVC latest (Windows)
* **MySQL:** 8.4 or higher (Optional, install Server community edition from https://dev.mysql.com/downloads/mysql/)
* **Python 3.13**

***vcpkg dependencies.***
* **POCO 1.13.3**
* **OpenSSL 3.4.0**
* **curl 8.11.0**
* **libssh-2 1.11**

# License
Distributed under the MIT License. See LICENSE for more information.

# Contact
For any inquiries or feedback, reach out to me at glanshammar70@gmail.com.