# 🏨 Hotel Management System

A robust, console-based Hotel Management System built in C++ to demonstrate advanced Object-Oriented Programming (OOP), Object-Oriented Design (OOD), and modern software engineering practices. This system efficiently manages rooms, customers, and bookings through a well-architected, multi-layered design with full **MySQL database persistence**. It is **thread-safe** and supports **transaction processing** for atomic, consistent operations.

## ⬇️ Download (Windows release)
- Direct ZIP: https://github.com/user-attachments/files/22804771/Hotel_ManagementSystem_Release.zip

## ▶ Quick Run (Windows release)
- Extract the ZIP and double‑click `Hotel_ManagementSystem.exe` (keep `DatabaseConfig.txt` in the same folder)
- If needed, edit `DatabaseConfig.txt` (schema, server, user, password):
  - Local MySQL (3306): `hotelmanagement,tcp://127.0.0.1:3306,root,root`
  - Docker MySQL (3307): `hotelmanagement,tcp://127.0.0.1:3307,root,root`
- If the database is empty, import `init-hotel-lowercase.sql` once into the `hotelmanagement` schema (Workbench or mysql CLI)
- On a clean PC you may need MySQL Connector/C++ DLLs or the VC++ Redistributable next to the `.exe`

## 🚀 Features

* **Room Management**: Add, delete, update, and view room details with database persistence.
  * **Standard Room**: Basic amenities at a budget-friendly price.
  * **Deluxe Room**: Premium amenities with extra fees.
  * **Suite**: Luxury rooms with optional features like a jacuzzi.
* **Customer Management**: Maintain customer records with contact information, stored in MySQL database.
* **Booking System**: Create, cancel, and modify bookings with automatic conflict detection to prevent double-booking.
* **Database Persistence**: Full MySQL integration with prepared statements and connection pooling.
* **Transaction Processing**: Atomic multi-step operations with commit/rollback guarantees via RAII-based `ScopedTransaction`.
* **Thread-Safety**: Concurrency-safe managers and repositories using synchronization primitives to prevent data races.
* **Date & Time Handling**: Custom DateTime class for accurate booking period calculations and overlap checks.
* **Role-Based UI**: Separate menus for Administrators (managing rooms) and Receptionists (managing bookings and customers).
* **Data Validation**: Comprehensive input validation (email, phone number, date conflicts, database constraints).
* **Configuration Management**: CSV-based database configuration with `DatabaseConfig.txt`.

## 🧱 Architecture & OOD Highlights

This project is a textbook example of clean software architecture, built upon core OOP principles and enhanced with **enterprise-grade design patterns**.

### 1. Layered Design

The system is structured into **four distinct layers** for clear separation of concerns:

* **Model Layer**: Core entity classes (`Room`, `StandardRoom`, `DeluxeRoom`, `Suite`, `Customer`, `Booking`, `DateTime`).
* **Repository Layer**: `RoomRepository`, `CustomerRepository`, `BookingRepository` handle database interactions with **MySQL persistence**.
* **Database Abstraction Layer**: `IDatabase`, `MySQLDatabase`, `IGenericStatement`, `IGenericResultSet` provide **database-agnostic interfaces**.
* **Orchestration Layer**: `HotelManager` coordinates repositories and enforces business rules.
* **View/UI Layer**: The `HotelUI` class handles all user input and output, keeping the core logic clean.

### 2. Key Design Patterns Implemented

* **Repository Pattern**: Abstracts data access logic and provides a uniform interface for data operations.
* **Adapter Pattern**: `MySQLDatabase`, `MySQLStatementWrapper`, `MySQLResultSetWrapper` adapt MySQL Connector/C++ to generic interfaces.
* **Dependency Injection**: All components receive their dependencies through constructors, promoting testability.
* **Strategy Pattern**: Different room types implement specialized behavior through inheritance.
* **Factory Pattern**: `HotelManager` acts as a factory for creating room instances.

### 3. Key Object-Oriented Principles Applied

* **Encapsulation**: All class member variables are private, exposed through well-defined public interfaces.
* **Single Responsibility**: Each class has a clear, singular purpose (separation of data access, business logic, and presentation).
* **Open/Closed Principle**: Easy to extend with new room types or database implementations without modifying existing code.
* **Interface Segregation**: Clean, minimal interfaces (`IDatabase`, `IGenericStatement`, `IGenericResultSet`).
* **Composition over Inheritance**: Managers and repositories are composed to create higher-level functionality.
* **Inheritance & Polymorphism**: A polymorphic `Room` hierarchy allows specialized room types to define their own behavior.
* **RAII & Smart Pointers**: `std::unique_ptr` ensures automatic cleanup of dynamically allocated objects.

### 4. Modern C++ Practices

* **Smart Memory Management**: Explicit ownership semantics with `std::unique_ptr` and `std::make_unique`.
* **Standard Library Usage**: Heavy use of `std::vector`, `std::string`, `std::optional`, and `<chrono>`.
* **Exception Handling**: Robust use of exceptions for error handling, caught at the UI layer.
* **RAII**: Resource management through constructors/destructors for database connections.
* **Move Semantics**: Efficient resource transfer in repository operations.

### 5. Iterative Development Timeline

| Phase                                                   | Focus                                                                              | Key Achievements                                                                                             |
| ------------------------------------------------------- | ---------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------ |
| **Phase 1 – Core OOP & In-Memory Storage**              | Implemented core entities and HotelManager orchestration                           | Applied encapsulation, inheritance for Room hierarchy, and basic business rules                              |
| **Phase 2 – Manager Layer & CRUD Operations**           | Added RoomsManager, CustomersManager, BookingsManager                              | Applied Single Responsibility, dependency injection, and smart pointers                                      |
| **Phase 3 – Console UI & Role-Based Interaction**       | Built HotelUI with separate menus for Admin and Receptionist                       | Introduced input validation, conflict detection, and clean separation of UI from logic                       |
| **Phase 4 – Repository Pattern & Database Integration** | **Added full MySQL persistence with Repository and Adapter patterns**             | **Demonstrated Repository Pattern, Adapter Pattern, prepared statements, and enterprise-grade database design** |

## 📦 Class Structure

```
HotelSystem
│
├── Model Layer
│ ├── DateTime.*
│ ├── Room.*
│ ├── StandardRoom.*
│ ├── DeluxeRoom.*
│ ├── Suite.*
│ ├── Customer.*
│ └── Booking.*
│
├── Database Abstraction Layer
│ ├── IDatabase.h (Interface)
│ ├── IGenericStatement.h (Interface)
│ ├── IGenericResultSet.h (Interface)
│ ├── MySQLDatabase.* (Adapter)
│ ├── MySQLStatementWrapper.* (Adapter)
│ ├── MySQLResultSetWrapper.* (Adapter)
│ └── DatabaseConfig.*
│
├── Repository Layer
│ ├── RoomRepository.*
│ ├── CustomerRepository.*
│ └── BookingRepository.*
│
├── Orchestration Layer
│ └── HotelManager.*
│
└── View Layer
  └── HotelUI.*
```

## 🔧 Build & Run (developers)
This repository includes full source code. If you’re reviewing the design and not building locally, you can skip this section and use the Windows release above.

## 👨‍💻 Usage

### Getting Started
1. **Configure Database**: Ensure `DatabaseConfig.txt` contains valid MySQL connection details
2. **Launch Application**: Run the executable to start the hotel management system
3. **Choose Role**: Select between **Admin** (password: `admin`) or **Receptionist** (password: `reception`)

### Role-Based Operations
* **Administrators**: 
  - Add, update, and delete rooms
  - Manage room types, prices, and status
  - View comprehensive reports
* **Receptionists**: 
  - Manage customer records and bookings
  - Check room availability in real-time
  - Handle check-ins, check-outs, and modifications
  - Generate booking reports

### Key Features in Action
* **Real-time Availability**: Database-backed room availability checking prevents double-booking
* **Data Persistence**: All changes are immediately saved to MySQL database
* **Input Validation**: Comprehensive validation with clear error messages
* **Transaction Safety**: Database operations use prepared statements for security

## 🏗️ Technical Highlights

### Database Architecture
- **Connection Management**: Automated connection handling with proper cleanup
- **Prepared Statements**: All database operations use prepared statements for security
- **Result Set Mapping**: Clean mapping from database rows to C++ objects
- **Transaction Safety**: RAII ensures database resources are properly managed
- **Transaction Processing**: Begin/commit/rollback across multi-statement workflows ensure ACID-like behavior

### Design Pattern Implementation
- **Repository Pattern**: Clean separation between business logic and data access
- **Adapter Pattern**: Database-agnostic interfaces allow easy switching between database providers
- **Dependency Injection**: Loose coupling through constructor injection
- **Strategy Pattern**: Polymorphic room types with specialized behavior
- **Unit of Work / Transaction**: `ScopedTransaction` groups multiple database operations into a single atomic unit with commit/rollback

### API Documentation
Comprehensive **Doxygen-style** documentation throughout the codebase:
- All public interfaces documented with `@brief`, `@param`, `@return` tags
- Clear contracts and side effects specified
- Ready for automated documentation generation

## 🔮 Future Enhancements

* **Graphical User Interface (GUI)**: Replace the console UI with a Qt or web-based interface
* **Advanced Patterns**: Apply additional design patterns (Observer, Command, Factory Method)
* **Unit Testing**: Add mock database adapter for comprehensive testing
* **API Layer**: RESTful API for external integrations
* **Reporting System**: Advanced analytics and reporting capabilities

## 📋 Learning Outcomes

This project demonstrates mastery of:

### Core Programming Concepts
* **Advanced C++17**: Modern language features, smart pointers, RAII
* **Object-Oriented Design**: Encapsulation, inheritance, polymorphism, composition
* **SOLID Principles**: Single Responsibility, Open/Closed, Interface Segregation, Dependency Inversion

### Software Engineering Practices
* **Design Patterns**: Repository, Adapter, Strategy, Dependency Injection
* **Database Design**: Relational modeling, prepared statements, connection management
* **Layered Architecture**: Clean separation of concerns across multiple layers
* **Documentation**: Professional-grade code documentation and API design

### Professional Development Skills
* **Iterative Development**: Systematic feature development across multiple phases
* **Error Handling**: Robust exception handling and input validation
* **Resource Management**: Proper cleanup and memory management
* **Maintainable Code**: Clean, well-structured, and easily extensible codebase
