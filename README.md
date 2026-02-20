# 🏦 Internet Banking System (GTK3 - C)

A simple Internet Banking Desktop Application built using C and GTK3.
This project demonstrates GUI development, file handling, user
authentication, and basic banking operations like registration, login,
and withdrawal.

------------------------------------------------------------------------

## 📌 Features

-   User Registration (Sign Up)
-   User Login Authentication
-   Auto-generated Customer ID
-   View User Details (Customer ID, Name, Phone Number, Balance)
-   Withdraw Money (UI implemented)
-   File-based Data Storage
-   GTK Stack Navigation System
-   CSS Styling for Borders

------------------------------------------------------------------------

## 🛠️ Technologies Used

-   Language: C
-   GUI Library: GTK3
-   File Handling: Standard C File I/O
-   OS Compatibility: Linux (Recommended)

------------------------------------------------------------------------

## 📂 Project Structure

. ├── main.c ├── user_datails.txt ├── user_pass.txt ├── last_cus_id.txt
├── current_user.txt ├── danu.png

------------------------------------------------------------------------

## 🗄️ File Storage System

### user_datails.txt

Format: customerID-FirstName LastName-PhoneNumber-Balance

Example: 1001-John Doe-9876543210-5000

### user_pass.txt

Format: customerIDpassword

Example: 1001mypassword

### last_cus_id.txt

Stores last generated customer ID.

### current_user.txt

Stores currently logged-in customer ID.

------------------------------------------------------------------------

## 🖥️ Application Pages

1.  Welcome Page (Sign In / Sign Up)
2.  Login Page (Customer ID & Password)
3.  Signup Page (Register New User)
4.  Home Page (Displays User Details & Balance)
5.  Withdraw Page (Enter Amount to Withdraw)

------------------------------------------------------------------------

## ⚙️ How to Compile & Run

Install GTK3 (Ubuntu/Debian):

sudo apt update sudo apt install libgtk-3-dev

Compile:

gcc main.c `pkg-config --cflags --libs gtk+-3.0` -o banking

Run:

./banking

------------------------------------------------------------------------

## ⚠️ Current Limitations

-   Password stored in plain text
-   Withdraw logic not fully implemented
-   No database integration
-   No deposit functionality logic

------------------------------------------------------------------------

## 👨‍💻 Author

Chandrakant Singh Danu

------------------------------------------------------------------------

## 📜 License

This project is for educational purposes only.
