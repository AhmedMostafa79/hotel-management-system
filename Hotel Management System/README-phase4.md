Hotel Management System — Phase 4
=================================

Summary
-------
Console-based Hotel Management System written in modern C++ (C++17). Phase 4 focuses on completing the app's repository and database wiring, improving the console UI flows, and adding inline documentation (Doxygen/Oxygen style) to public headers.

Highlights in Phase 4
---------------------
- Database configuration loader: `DatabaseConfig::loadFromFile` reads a CSV-style line (schema,server,username,password) from `DatabaseConfig.txt`.
- Database abstraction: `IDatabase` provides a minimal adapter; `MySQLDatabase` is the provided implementation using MySQL Connector/C++.
- Repository layer: `RoomRepository`, `BookingRepository`, and `CustomerRepository` encapsulate CRUD operations and map rows to domain objects.
- Business logic: `HotelManager` coordinates validation, availability checking and orchestrates repositories.
- Console UI: `HotelUI` provides menu-driven flows for admins and receptionists (add/update/delete rooms/customers/bookings and view reports).
- Documentation: Several public headers were annotated with Doxygen/Oxygen-style comments to make generated docs clearer.

Files changed (documentation added)
----------------------------------
- `DatabaseConfig.h` — documented the config container and loader.
- `IDatabase.h` — documented the database adapter interface.
- `RoomRepository.h` — documented repository API, helpers and CRUD methods.
- `BookingRepository.h` — documented repository API and operations.
- `CustomerRepository.h` — documented repository API and operations.
- `MySQLDatabase.h` — documented the MySQL adapter.
- `IGenericStatement.h` — documented the generic prepared-statement adapter.
- (Several other headers such as `Room.h`, `Booking.h`, `Customer.h`, `HotelUI.h`, `HotelManager.h`, `HotelSystem.h` already included comments or were previously reviewed.)

Quick build & run
-----------------
Prerequisites
- Visual Studio 2022 (or newer) with C++ workload.
- MySQL server (optional for real DB runs) and MySQL Connector/C++ development libraries if you use the MySQL adapter.

Build (VS)
1. Open `Hotel_ManagementSystem.vcxproj` in Visual Studio.
2. Build the solution in `Release | x64` (or `Debug | x64`).

Build (command line)
```powershell
# From a Visual Studio Developer Prompt (x64)
msbuild Hotel_ManagementSystem.vcxproj /p:Configuration=Release /p:Platform=x64
```

Run
- After a successful build run the produced executable (for Release x64):
  - `x64\Release\Hotel_ManagementSystem.exe`

Configuration
- Edit `DatabaseConfig.txt` (single-line CSV: `schema,server,username,password`) to point to your database if you plan to use MySQL.
- If you do not have a DB engine available, the project can still be inspected and run for non-DB logic; repository adapters will raise connection errors when used.

How the code is organized (quick map)
- Core app: `HotelSystem.*`, `HotelUI.*`, `HotelManager.*` — main loop and UI.
- Domain: `Room.*` (and derived `StandardRoom/DeluxeRoom/Suite`), `Booking.*`, `Customer.*`.
- Persistence: `RoomRepository.*`, `BookingRepository.*`, `CustomerRepository.*`.
- DB adapters: `IDatabase.h`, `MySQLDatabase.*`, `IGenericStatement.*`, `IGenericResultSet.*`.
- Config: `DatabaseConfig.*`, `DatabaseConfig.txt`.

Notes & suggestions
-------------------
- The codebase uses C++ standard library smart pointers and RAII but still depends on the MySQL Connector/C++ types in database adapters. Consider adding an in-memory/mock adapter for unit testing (small change).
- The Doxygen comments added follow Oxygen-style tags (brief/param/return) and are intentionally conservative — they document contracts and side effects. Running Doxygen or a compatible generator will produce usable API docs.

Next steps I can do for you
--------------------------
- Add `README.md` (root) formatted for GitHub and include Phase‑1..4 changelog (if you provide `README-phase3.md` or a short summary of previous phases).
- Generate a Doxygen config (`Doxyfile`) and run it locally to produce HTML docs and include them under `docs/`.
- Add a lightweight in-memory DB adapter and a small unit-test harness that exercises core `HotelManager` logic (availability checks, booking creation).

If you want a GitHub-ready `README.md` now, I can create it using the content above and expand it to include a short Phase history and contribution notes. Would you like that? (If yes, tell me whether to name it `README.md` or `README-phase4.md` and whether to include full API docs links.)
