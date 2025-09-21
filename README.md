# 🏨 Hotel Management System
A robust, console-based Hotel Management System built in C++ to demonstrate advanced Object-Oriented Programming (OOP) and Design (OOD) principles. This system efficiently manages rooms, customers, and bookings through a well-architected, multi-layered design.

## 🚀 Features
- **Room Management**: Add, delete, update, and view room details (Standard, Deluxe, Suite).
- **Customer Management**: Maintain customer records with contact information.
- **Booking System**: Create, cancel, and modify bookings with automatic conflict detection to prevent double-booking.
- **Date & Time Handling**: Custom DateTime class for accurate booking period calculations and overlap checks.
- **Role-Based UI**: Separate menus for Administrators (managing rooms) and Receptionists (managing bookings and customers).
- **Data Validation**: Comprehensive input validation (email, phone number, date conflicts).

## 🧱 Architecture & OOD Highlights
This project is a textbook example of clean software architecture, built upon core OOP principles.

### 1. Layered Design
The system is structured into three distinct layers for clear separation of concerns:

- **Model Layer**: Core entity classes (Room, Customer, Booking, DateTime).
- **Service/Manager Layer**: Classes that manage object lifecycles and business logic (RoomsManager, CustomersManager, BookingsManager, HotelManager).
- **View/UI Layer**: The HotelUI class handles all user input and output, keeping the core logic clean.

### 2. Key Object-Oriented Principles Applied
- **Encapsulation**: All class member variables are private, exposed through well-defined public interfaces.
- **Single Responsibility**: Each class has a clear, singular purpose (e.g., BookingsManager only manages bookings).
- **Composition over Inheritance**: The system is built by composing managers and entities. Inheritance is thoughtfully used for a future Room hierarchy.
- **RAII**: Manual memory management is handled correctly with destructors cleaning up dynamic memory, following the Rule of Five.
- **Dependency Injection**: The HotelUI is injected with a HotelManager reference, promoting loose coupling and testability.

### 3. Modern C++ Practices
- **Smart Memory Management**: Use of raw pointers with explicit ownership semantics in managers, ensuring no memory leaks.
- **Standard Library Usage**: Heavy use of `std::vector`, `std::string`, `std::optional` for safe function returns, and the `<chrono>` library within the DateTime class.
- **Exception Handling**: Robust use of exceptions for error handling (e.g., invalid email format) caught at the UI layer.

### High-Level Overview
![Simplified Class Diagram](Hotel%20Management%20System/Class%20Diagram%20Simplified.png)
*Simplified view of the core architecture showing main components and relationships*

### Detailed Class Structure  
![Comprehensive Class Diagram](Hotel%20Management%20System/Class%20Diagram%20Comprehensive.png)
*Detailed UML class diagram showing all attributes, methods, and relationships*

## 📦 Class Structure
```
HotelSystem
│
├── Model Layer
│   ├── DateTime.*    # Handles all date-time logic and operations
│   ├── Room.*        # Entity class for room data
│   ├── Customer.*    # Entity class for customer data
│   └── Booking.*     # Entity class for booking data and conflict detection
│
├── Manager Layer
│   ├── RoomsManager.*        # CRUD operations for Room objects
│   ├── CustomersManager.*    # CRUD operations for Customer objects
│   ├── BookingsManager.*     # CRUD operations for Booking objects
│   └── HotelManager.*        # Facade that orchestrates all other managers
│
└── View Layer
    └── HotelUI.*             # Handles all console I/O and user interaction
```

## 🔧 Build & Run
### Prerequisites
- A C++17 compatible compiler (GCC, Clang, MSVC)

### Compilation
```bash
# Clone the repository
git clone https://github.com/AhmedMostafa79/hotel-management-system.git
cd hotel-management-system
cd "Hotel Management System"

# Compile using G++
g++ -std=c++17 *.cpp -o hotel_system

# Run the program
./hotel_system
```

## 👨‍💻 Usage
Upon running, you will be presented with the main menu.

- Choose between **Admin** (password: `admin`) or **Receptionist** (password: `reception`) roles.
- Admins can manage the room inventory.
- Receptionists can manage customer records, check room availability, and create/modify bookings.
- The system guides you through each operation with clear prompts.

## 🔮 Future Enhancements
- **Persistence**: Save and load data to/from files (JSON/CSV).
- **Polymorphic Room Hierarchy**: Fully implement DeluxeRoom and Suite classes with specialized pricing.
- **Graphical User Interface (GUI)**: Replace the console UI with a Qt or web-based interface.
- **Database Integration**: Use SQLite or MySQL for data storage.

## 📋 Learning Outcomes
This project demonstrates mastery of:
- Designing and implementing a complex, multi-class system in C++.
- Applying SOLID principles and classic design patterns (Factory, Facade).
- Writing clean, maintainable, and well-documented code.
- Managing object lifetimes and resources without smart pointers for educational purposes.
- Creating a robust and user-friendly console interface.
