# Gym Management System

## Project Overview

This is a C++ console-based Gym Management System designed to manage gym members and trainers efficiently. The system allows for registration, updating, deletion, and searching of members and trainers, as well as sorting and displaying their details. It includes features such as membership plan selection, BMI calculation, and locker assignment.

---

## Authors

* Masum Abbas

* Omer Jabbar

* Bilal Ahmed

* Syed Bilal Ahmed

---

## Features

### Membership Management:

* Register new members with details like registration number, name, weight, height, age, gender, and membership plan.

* Update or delete existing members.

* Search members by registration number.

* Sort members by registration number.

* Display all members with formatted output including BMI.


### Trainer Management:

* Add, update, or delete trainers with details like name, qualifications, contact, and fee.

* Search trainers by name.

* Sort trainers by monthly fee.

* Display all trainers with formatted output.

### Membership Plans:

* Offers various plans (1-month, 3-month, 6-month, 1-year, with or without treadmill access) with associated costs and discounts.


### Locker Assignment:

* Automatically assigns available locker numbers to new members.

---

## Data Structures:


* Uses a vector for storing members and an unordered_map for quick lookup by registration number.

* Uses a linked list (TrainerNode) for storing trainer information.

---

## Requirements

### Compiler

* A C++ compiler (e.g., `g++` with `C++11` or later)


### Standard C++ libraries: 

`<iostream>`  `<string>` `<vector>` `<cmath>` `<algorithm>` `<unordered_map>` `<iomanip>`


---

## How to Run

Clone or download the project files.

**Step 1:** Compile the code using a C++ compiler:

    g++ -o gym_management main.cpp

**Step 2:** Run the executable:

    ./gym_management

**Step 3:** Use the program

Follow the console menu to interact with the system (options 1–14).

---

## Usage

### Main Menu Options:

* Display and buy membership plans.

* Insert a new member.

* Delete a member by registration number.

* Update a member’s details.

* Search for a member by registration number.

* Sort members by registration number.

* Display all members.

* Insert a new trainer.

* Delete a trainer by name.

* Update a trainer’s details.

* Search for a trainer by name.

* Sort trainers by fee.

* Display all trainers.

* Exit the system.

---

## Input Guidelines:

* Membership plans are selected using letters (a–h).

* Gender is input as 1 (male) or 2 (female).

* Ensure valid inputs to avoid errors (e.g., valid registration numbers, membership plans).

---

## Code Structure

### Classes and Structures:

**TrainerNode:** A structure for the linked list storing trainer details (name, qualifications, contact, fee).

**Member:** A class for storing member details (registration number, name, locker number, weight, height, age, gender, BMI, membership plan).

**Gym:** The main class managing all operations, including member and trainer management, locker assignment, and sorting.


### Key Methods:

**registerAndBuyMembership():** Handles member registration and plan purchase.


**calculateBMI():** Computes BMI based on weight and height.

**linearSearchLocker():** Assigns an available locker number.

**sortMembersByRegNo():** Sorts members by registration number.

**sortTrainersByFee():** Sorts trainers by their monthly fee.

**displayAllMembers() and displayAllTrainers():** Display formatted tables of members and trainers.

---

## Limitations

* The system supports a maximum of 100 members.

* Some features (e.g., displayTrainer, displayExercisePlan, calculateBMR, displayNutritionalNeeds, calculateBodyFat, displayDietPlan) are declared but not implemented in the provided code.

* Input validation is minimal; users must ensure correct input formats.

---

## Future Improvements

* Implement the unimplemented methods for exercise plans, BMR, body fat, and nutritional needs.

* Add input validation for robustness.

* Include file I/O to persist member and trainer data.

* Enhance the UI with a graphical interface (e.g., using a library like Qt).

---

## License

This project is for educational purposes and does not include a specific license.
