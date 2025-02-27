# AcademicRecordManager

**AcademicRecordManager** is a desktop application built using Qt and C++ for managing student records. It allows users to add, edit, delete, and view student information, with data stored in text files for easy management.

## Features

- **Add Student**: Add a new student with details like name, study status, level, mode, and field of study.
- **Edit Student**: Modify existing student information.
- **Delete Student**: Remove a student from the database with confirmation.
- **View Student Details**: Display additional information about a selected student.
- **Filter and Search**: Filter students by index, first name, or last name.
- **Save and Load Data**: Save student data to text files and load from existing files.
- **User-Friendly Interface**: Intuitive GUI for easy navigation and management.

## Code Structure

- **`Person` Class**: Base class for storing basic information like first and last name.
- **`Student` Class**: Inherits from `Person` and adds student-specific details (index, study status, level, mode, field of study).
- **`DataFileReader` Class**: Reads student data from text files.
- **`DataWriter` Class**: Writes student data to text files.
- **`DataProcessing` Class**: Manages core logic (adding, editing, deleting, filtering students).
- **`Katalog_JIPP_Project` Class**: Handles the GUI and user interactions.

## Technologies Used

- **Qt**
- **C++**
