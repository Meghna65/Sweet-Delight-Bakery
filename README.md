# Sweet-Delight-Bakery

# Cake Shop Management System | CLI-Based C Project
Sweet Delight Bakery is a terminal-based Cake Shop Management System developed in the C programming language. The project is designed to simplify and organize the daily operations of a small personal cake business named Meghna Cake Shop.
The system provides a simple, menu-driven interface where customers can view available cakes and place orders. It also includes management features that allow authorized managers to add new cake items, review sales history, and maintain system security using a manager PIN.

# Project Information
Project Name: Sweet Delight Bakery
Project Type: Management System
Interface: Command Line Interface (CLI)
Programming Language: C
Business Name: Meghna Cake Shop

# Project Overview
Small cake shops often rely on notebooks, spreadsheets, or manual records to manage products, customer orders, and sales. These traditional methods can be time-consuming and may lead to calculation errors, missing information, and difficulties when tracking previous transactions.

Updating the cake menu when new products are introduced can also become inconvenient without a centralized management system.

Sweet Delight Bakery addresses these challenges by bringing essential cake shop operations into a single terminal-based application. Customers can easily browse the available cake menu and place new orders, while managers can manage products, review sales records, and maintain system security.

The project provides a simple, organized, and efficient computerized solution for managing the basic operations of a small cake shop.

# Project Objectives
The main objectives of this project are:
Develop a terminal-based cake shop management system for Meghna Cake Shop.
Implement a cake menu management system for viewing and adding cake items.
Provide an efficient ordering system where customers can select cakes and specify quantities.
Store and manage sales records for reviewing previous transactions.
Implement a basic security mechanism using a manager PIN.
Provide a simple and user-friendly menu-driven interface.

# Features
1. View Cake Menu
Customers can view the list of available cakes, including relevant product information such as cake names and prices.

2. Place New Order
Customers can select cake items from the menu, specify quantities, and place their orders through the system.

3. Add New Item (Manager)
Authorized managers can add new cake items to the available cake menu.

4. Sales History (Manager)
Managers can review previously recorded sales and transaction information.

5. Change Manager PIN
The system allows the authorized manager to change the security PIN for management access.

6. Exit System
Users can safely exit the application.

# Main Menu

The system provides a menu-driven interface similar to the following:

====================================
       SWEET DELIGHT BAKERY
        Meghna Cake Shop
====================================

1. View Cake Menu
2. Place New Order
3. Add New Item (Manager)
4. Sales History (Manager)
5. Change Manager PIN
6. Exit System

Enter your choice:

# Manager Access
Certain features of the system are restricted to authorized managers.

Manager-only features include:
Adding new cake items
Viewing sales history
Changing the manager PIN

The manager must enter the correct PIN before accessing protected management features.

# Technologies Used
Programming Language: C
Interface: Command Line Interface (CLI)
Development Type: Console-Based Application

# Project Structure
Sweet-Delight-Bakery/
│
├── cakeshop.c
├── README.md
└── bakery_data.txt
├── cakeshop.exe
└── cakeshop.o
├── sales_history.txt
└── .gitignore

The project structure may be expanded as the system develops.

# How to Compile and Run
Requirements
You need a C compiler installed on your computer, such as:
GCC
MinGW
Code::Blocks
Dev-C++
Visual Studio Code with a C compiler
Compile Using GCC
gcc main.c -o sweet_delight_bakery
Run the Program
Windows
sweet_delight_bakery.exe
Linux/macOS
./sweet_delight_bakery

# User Roles
# Customer
Customers can:
View the cake menu
Select cake items
Specify quantities
Place new orders

# Manager
Managers can:
Add new cake items
View sales history
Change the manager PIN
Manage basic shop operations

# Future Improvements
The following features may be added in future versions:
Edit and delete cake items
Search for specific cakes
Automatic bill generation
Customer information management
Daily and monthly sales reports
Low-stock notifications
File handling for permanent data storage
Inventory management
Discount and promotional offers
Multiple manager accounts
Improved authentication and security

# Academic Purpose
This project was developed as an academic programming project to demonstrate fundamental concepts of the C programming language, including:

Variables and data types
Conditional statements
Loops
Functions
Arrays
Structures
Menu-driven programming
Basic authentication
Record management

# Contribution
Contributions, suggestions, and improvements are welcome. You can fork this repository, make improvements, and submit a pull request.

# License
This project is developed for educational and academic purposes.

# Author
Developed as a C Programming Project for academic purposes.

If you find this project useful, consider giving the repository a star!