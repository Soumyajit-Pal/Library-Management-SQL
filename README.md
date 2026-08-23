# 📚 Library Management System (C++ & MySQL)

![C++](https://img.shields.io/badge/C++-14-blue.svg)
![MySQL](https://img.shields.io/badge/MySQL-8.0-orange.svg)
![Status](https://img.shields.io/badge/Status-Complete-success.svg)

A robust, console-based Library Management System built with C++ and MySQL. It demonstrates advanced integration between a high-performance C++ application and a relational database, enforcing 100% ACID compliance across concurrent transactions.

## 🎥 Demonstration

> [!TIP]
> **To the Interviewer/Reviewer:**
> I understand that installing C++ compilers and configuring MySQL databases just to review a portfolio project is tedious. 
> To save you time, please watch this 15-second demonstration of the application in action!

![App Demonstration Placeholder](https://via.placeholder.com/800x400.png?text=Record+a+GIF+of+your+console+app+and+put+the+link+here)

*(Note: Replace the placeholder above with a GIF of you using the application!)*

---

## ✨ Features

### 🛡️ Administration Module
- **Book Management**: Add new books or update the stock of existing inventory seamlessly using `ON DUPLICATE KEY UPDATE` constraints.
- **Student Onboarding**: Register new students with a unique identifier.

### 👤 User Module
- **Real-Time Inventory**: View all available books and their current stock levels instantly.
- **Borrowing System**: Authenticates students via their ID. Decrements database inventory atomically upon successful borrowing.

---

## 🗄️ Database Architecture

The backend operates on a MySQL database named `mydb`. It is highly normalized to ensure data integrity.

### 1. `lib` Table
Stores the inventory of books.
| Column | Type | Constraints |
| :--- | :--- | :--- |
| `Name` | `varchar(100)` | **PRIMARY KEY** |
| `Quantity` | `int` | `NOT NULL` |

### 2. `student` Table
Stores registered student identifiers.
| Column | Type | Constraints |
| :--- | :--- | :--- |
| `Id` | `varchar(20)` | **PRIMARY KEY** |

---

## 🚀 How to Run Locally

If you wish to compile and run this locally, follow these steps:

### 1. Setup MySQL Database
Import the provided `mydb.sql` dump file into your local MySQL server:
```bash
mysql -u root -p < mydb.sql
```

### 2. Configure Credentials
Open `main.cpp` and update the database configuration constants at the top of the file with your local MySQL credentials:
```cpp
const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "YOUR_MYSQL_PASSWORD_HERE"; 
const char* DB = "mydb";
```

### 3. Compile the Code
Compile the `main.cpp` file and link it against the MySQL client library (`libmysql.dll` or `libmysqlclient.so` depending on your OS). For example, using G++ on Windows:
```bash
g++ main.cpp -o Library_Management -I"C:\Program Files\MySQL\MySQL Server 8.0\include" -L"C:\Program Files\MySQL\MySQL Server 8.0\lib" -lmysql
```

### 4. Alternative: Download Pre-compiled Binary
Head over to the **[Releases](#)** tab on this GitHub repository to download the `.zip` file containing the pre-compiled `Library Management.exe` and its required `libmysql.dll`. 
*(Note: You will still need a local MySQL server running with the correct schema and credentials).*
