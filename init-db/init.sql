-- Initialize Hotel Management Database Schema

USE hotelmanagement;

-- Create rooms table
CREATE TABLE IF NOT EXISTS `rooms` (
  `room_number` int NOT NULL AUTO_INCREMENT,
  `room_type` enum('standard','deluxe','suite') NOT NULL,
  `status` varchar(50) DEFAULT 'available',
  `base_price` decimal(10,2) NOT NULL,
  `extra_fees` decimal(10,2) DEFAULT '0.00',
  `has_jacuzzi` tinyint(1) DEFAULT '0',
  `jacuzzi_cost` decimal(10,2) DEFAULT '0.00',
  `created_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`room_number`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Create customers table
CREATE TABLE IF NOT EXISTS `customers` (
  `customer_id` int NOT NULL AUTO_INCREMENT,
  `age` int NOT NULL,
  `name` varchar(100) NOT NULL,
  `phone_number` varchar(20) NOT NULL,
  `email` varchar(100) NOT NULL,
  PRIMARY KEY (`customer_id`),
  UNIQUE KEY `phone_number` (`phone_number`),
  UNIQUE KEY `email` (`email`),
  CONSTRAINT `chk_age` CHECK (((`age` >= 0) and (`age` <= 120))),
  CONSTRAINT `chk_email` CHECK (regexp_like(`email`,_utf8mb4'^[A-Za-z0-9_]+@[A-Za-z0-9_]+.[A-Za-z0-9_]+$')),
  CONSTRAINT `chk_phone` CHECK (((length(`phone_number`) between 8 and 15) and regexp_like(`phone_number`,_utf8mb4'^[+]?[0-9]+$')))
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Create bookings table
CREATE TABLE IF NOT EXISTS `bookings` (
  `booking_id` int NOT NULL AUTO_INCREMENT,
  `room_number` int NOT NULL,
  `customer_id` int NOT NULL,
  `check_in` datetime NOT NULL,
  `check_out` datetime NOT NULL,
  `cost` decimal(10,2) NOT NULL,
  `status` varchar(20) NOT NULL,
  PRIMARY KEY (`booking_id`),
  CONSTRAINT `chk_cost` CHECK ((`cost` >= 0)),
  CONSTRAINT `chk_dates` CHECK ((`check_in` < `check_out`)),
  CONSTRAINT `chk_status` CHECK ((`status` in (_utf8mb4'pending',_utf8mb4'done',_utf8mb4'cancelled')))
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
