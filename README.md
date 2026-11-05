# Final Project: `env-gui+` Application

**Course:** SP2000
**Week:** 5

## Overview

This final project is your opportunity to synthesize the C++ and Qt development skills you've acquired throughout this course. You will design and implement a complete graphical user interface (GUI) application named **`env-gui+`**. This tool will serve as an enhanced, GUI-based version of the standard command-line `env` utility, allowing users to manage environment variables and launch applications within custom environments.

The core functionality involves providing an interface to define a set of environment variables, select an executable program using a file dialog, and then launch that program using `QProcess`, ensuring it runs with the specified custom environment. The application must also capture and display the `stdout` and `stderr` output from the launched process in real-time.

## Learning Objectives

Upon successful completion of this project, you will have demonstrated your ability to:

* Design and implement a functional Qt GUI application.
* Integrate core Qt widgets for user interaction, including `QFileDialog` and `QTableWidget` (or `QListWidget`).
* Utilize `QProcess` to manage external processes, including setting custom environments and capturing output.
* Apply Qt's signals and slots mechanism for event handling and component communication.
* Implement robust error handling and user feedback within a GUI application.
* Structure and document a Qt/C++ project effectively.

-------

## **Working with Dev Container**

To complete this assignment in a reliable and fully configured environment, please refer to the instructions in the file: **`README-devcontainer.md`**. This guide walks you through opening the assignment in **Visual Studio Code** using a **Dev Container**, which automatically installs all necessary Python libraries and tools. Following that setup ensures that the notebook runs smoothly without manual configuration or missing dependencies. Make sure to open the **main assignment folder** in VS Code and follow the steps outlined in the Dev Container guide before starting the notebook.

--------

## Project Requirements

Your `env-gui+` application must meet the following core requirements:

1. **Graphical User Interface (GUI):**
   
   * The application must have a clear, intuitive, and well-organized main window.
   * Use appropriate Qt widgets and layout managers (`QVBoxLayout`, `QHBoxLayout`, `QGridLayout`, `QGroupBox`, `QTabWidget`, etc.) to structure the UI.

2. **Environment Variable Management:**
   
   * Display a list of environment variables that will be used for the custom environment. This list should be editable by the user.
   * Provide functionality to **Add** a new environment variable (key-value pair).
   * Provide functionality to **Edit** an existing environment variable in the list.
   * Provide functionality to **Remove** an environment variable from the list.
   * *(Consider using a `QTableWidget` for a clear key-value display and easy editing).*

3. **Executable Selection:**
   
   * Include a "Browse..." button (or similar) that opens a `QFileDialog`.
   * The user must be able to select an executable file from their system using this dialog.
   * The path to the selected executable must be displayed in the GUI (e.g., in a `QLineEdit`).

4. **Process Execution with Custom Environment:**
   
   * Include a "Launch" or "Run" button.
   * When clicked, and if an executable is selected, the application must use `QProcess` to start the selected program.
   * **Crucially:** The launched process must execute within the environment defined by the user in the environment variable management section of your GUI. You will need to construct a `QProcessEnvironment` object and use `QProcess::setProcessEnvironment()`.
   * (Optional) Decide whether the custom environment *replaces* the system environment or *augments* it. Augmenting is often more useful (e.g., `QProcessEnvironment::systemEnvironment()` then `insert()`).

5. **Process Output Display:**
   
   * Provide a text area (e.g., `QTextEdit` or `QPlainTextEdit`, set to read-only) to display the **live `stdout` and `stderr` output** from the launched `QProcess`.
   * The UI should clearly indicate when the process has started, when it has finished, and its exit code/status.

6. **User Feedback and Error Handling:**
   
   * Implement basic input validation (e.g., environment variable keys should not be empty).
   * Handle potential errors gracefully (e.g., executable not found, permissions issues to run executable, process crashes).
   * Display informative error messages to the user (e.g., using `QMessageBox` or updating a status bar).
   * The "Launch" button should probably be disabled if no executable is selected or if a process is already running.

7. **Documentation (`README.md`):**
   
   * Create a `README.md` file in the root of your project.
   * Include:
     * Your name/author.
     * A brief description of the application.
     * Clear instructions on how to **build** the project (e.g., Qt version needed, dependencies beyond standard Qt, `qmake && make` or CMake commands).
     * A list of **features implemented**.
     * A **usage guide** explaining how to use the application's main functionalities.
     * (Optional) Screenshots of your application's UI.

## Key Project Features (Summary)

Your application should allow a user to:

* Visually manage a list of key-value environment variable pairs.
* Browse for and select an executable program.
* Launch the selected program with the user-defined environment variables.
* View the real-time standard output and standard error streams from the launched program.
* Receive feedback on process status and any errors.

## Suggested Qt Components:

* **Main Window:** `QMainWindow`
* **Layouts:** `QVBoxLayout`, `QHBoxLayout`, `QGridLayout`, `QGroupBox`, `QSplitter`, `QTabWidget`
* **Environment Variables:** `QTableWidget` (ideal for key-value) or `QListWidget`, `QPushButton` (Add, Edit, Remove), `QLineEdit` (for input), `QInputDialog` (for getting key/value).
* **Executable:** `QLineEdit` (to display path), `QPushButton` (to trigger `QFileDialog`).
* **File Dialog:** `QFileDialog::getOpenFileName()`.
* **Process Management:** `QProcess`, `QProcessEnvironment`.
* **Output Display:** `QTextEdit` or `QPlainTextEdit`.
* **Feedback:** `QLabel` (for status messages), `QMessageBox`.

## Project Deliverables

1. **Complete Qt/C++ Application Source Code:**
   * All `.h` and `.cpp` files.
   * The Qt project file (`.pro` or `CMakeLists.txt`).
   * Your code should be well-organized and include comments where necessary to explain complex logic.
2. **`README.md` File:** As described in the "Project Requirements" section.
3. **Short Demo/Presentation (2–3 minutes):** Be prepared to briefly demonstrate your application's core functionalities during the final session.

## Grading

Your project will be evaluated based on:

* **Functionality:** Successful implementation of all core requirements.
* **Correctness:** Proper use of Qt classes, C++ constructs, and correct behavior.
* **UI/UX Design:** Clarity, intuitiveness, and organization of the user interface.
* **Error Handling:** Graceful handling of common errors and user feedback.
* **Code Quality:** Readability, organization, and comments.
* **Documentation:** Completeness and clarity of the `README.md`.
* **Presentation:** Effective demonstration of your application.

*(Refer to the detailed grading rubric provided separately for specific point allocations.)*

## Tips for Success

* **Start Early:** This is a significant project. Break it down into smaller, manageable tasks.
* **Iterate:** Implement one feature at a time and test it thoroughly before moving to the next.
  1. Phase 1: Basic UI layout and static display.
  2. Phase 2: Environment variable list management (display, add, edit, remove).
  3. Phase 3: Executable selection with `QFileDialog`.
  4. Phase 4: `QProcess` integration: launching *without* custom env first, then adding custom env.
  5. Phase 5: Output capturing and display.
  6. Phase 6: Error handling and UI polish.
* **Consult Qt Documentation:** The official Qt documentation is an excellent resource.
* **Use Qt Creator's Debugger:** It will be invaluable for troubleshooting.
* **Keep it Simple First:** Focus on meeting the core requirements before adding optional enhancements.
* **Ask Questions:** Don't hesitate to ask the instructor or TAs for clarification or help if you get stuck.

Good luck, and have fun building your `env-gui+` application!
