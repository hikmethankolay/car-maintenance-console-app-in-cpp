# Car Maintenance Project Library: Generation and Testing

## Overview

This project provides a suite of modules designed to demonstrate how to use **CMake** with **CTest**, while integrating **Doxygen** documentation and test coverage reports.

## Requirements

- **CMake** >= 3.12
- **C++ Standard** >= 11
- **GoogleTest** (for testing modules)
- **Visual Studio Community Edition** (Windows generator)
- **Ninja** (for WSL/Linux)

---

## Setup Development Environment

### Step 1: Configure Pre-Commit Hooks (Windows/WSL)
Run `1-configure-pre-commit.bat` to copy the pre-commit script to `.git/hooks`. This ensures:
- **Validation**: Checks `README.md`, `.gitignore`, and Doxygen files.
- **Code Formatting**: Formats code using the **Astyle** tool.

### Step 2: Generate `.gitignore` (Windows/WSL)
If `.gitignore` is missing, run `2-create-git-ignore.bat` to generate it.

### Step 3: Install Package Managers (Windows)
Run `3-install-package-manager.bat` to install **choco** and **scoop** package managers.

### Step 4: Install Development Tools (Windows)
Run `4-install-windows-environment.bat` to install the required tools.

### Step 5: Setup WSL Environment (WSL Only)
Open PowerShell as Administrator, enter **WSL**, navigate to the project folder, and run `4-install-wsl-environment.sh` to configure the WSL environment.

---

## Generate Development Environment

Run `9-clean-configure-app-windows.bat` to generate a Visual Studio Community Edition project. Alternatively, use **CMake** to create the project for Visual Studio.

---

## Build, Test, and Package

### On Windows

- **Complete Build**: Run `7-build-app-windows.bat` to:
  - Build the project.
  - Run tests.
  - Generate packaged binaries.

- **Generate Documentation**: Run `7-build-doc-windows.bat`.

- **Run Tests Only**: Run `8-build-test-windows.bat`.

### On WSL/Linux

Run `7-build-app-linux.sh` to build, test, and generate packaged binaries for the WSL environment.

---

## Clean Project
Run `9-clean-project.bat` to clean all project outputs.

---

## Functionalities

### Car Management System:

1. **Service History Tracking**
   - Vehicle Model
   - Service Kilometers
   - Service Provider
   - Service Cost

2. **Maintenance Reminders**
   - Vehicle Model
   - Service Kilometers
   - Service Type

3. **Expense Logging**
   - Vehicle Model
   - Expense Type
   - Expense Date
   - Cost

4. **Fuel Efficiency Reports**
   - Vehicle Model
   - L/100KM Fuel Consumption

### User Authentication
- Provides secure access to records through username and password verification.
- Allows the user to view, register, update, or delete records easily.

---

## Testing and Validation

- Tested using **GoogleTest** and **CTest**.
- Achieves **100% test coverage** with successful unit tests.

---

## Supported Platforms

- ![Ubuntu](assets/badge-ubuntu.svg)
- ![macOS](assets/badge-macos.svg)
- ![Windows](assets/badge-windows.svg)

### Test Coverage Ratios

| Coverage Type | Windows                                                              | Linux (WSL-Ubuntu 20.04)                                                |
| ------------- | -------------------------------------------------------------------- | ------------------------------------------------------------------------ |
| Line Based    | ![Line Coverage](assets/codecoveragelibwin/badge_linecoverage.svg)  | ![Line Coverage](assets/codecoverageliblinux/badge_linecoverage.svg)    |
| Branch Based  | ![Branch Coverage](assets/codecoveragelibwin/badge_branchcoverage.svg) | ![Branch Coverage](assets/codecoverageliblinux/badge_branchcoverage.svg) |
| Method Based  | ![Method Coverage](assets/codecoveragelibwin/badge_methodcoverage.svg) | ![Method Coverage](assets/codecoverageliblinux/badge_methodcoverage.svg) |

### Documentation Coverage Ratios

| Platform       | Coverage Ratio                                                    |
| -------------- | ----------------------------------------------------------------- |
| Windows        | ![Documentation Coverage](assets/doccoveragelibwin/badge_linecoverage.svg) |
| Linux          | ![Documentation Coverage](assets/doccoverageliblinux/badge_linecoverage.svg) |

### Known Issue
- Doxygen may overwrite badge images due to identical filenames. For correct visuals, refer to the `README.md` or webpage.

---

## Build Processes

### On Windows

Run `7-build-app-windows.bat` for a complete build in **11-15 minutes**, including:

1. Cleaning project outputs.
2. Generating required folders.
3. Running Doxygen for documentation.
4. Generating coverage reports using **Coverxygen**.
5. Configuring the project for Visual Studio Community Edition.
6. Building Debug and Release versions.
7. Running tests and collecting coverage data using **OpenCppCoverage**.
8. Generating reports for test coverage and documentation.
9. Building the website with **MkDocs**.
10. Compressing outputs to the release folder.

### On WSL/Linux

Run `7-build-app-linux.sh` to perform similar tasks as the Windows script and generate release-ready outputs.

---

## Resources

- [VS-Docker-WSL C++ Development](https://github.com/coruhtech/vs-docker-wsl-cpp-development)
- [NS3 WSL Setup](https://github.com/ucoruh/ns3-wsl-win10-setup)

---

$End-Of-File$

