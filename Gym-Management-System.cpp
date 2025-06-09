#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <iomanip>

using namespace std;

struct TrainerNode {
    string name;
    string qualifications;
    string contact;
    int fee;
    TrainerNode* next;

    TrainerNode(string n, string q, string c, int f) : name(n), qualifications(q), contact(c), fee(f), next(nullptr) {}
};

class Member {
public:
    int regNo;
    string name;
    int lockerNo;
    float weight, height, age;
    int gender;
    double bmi, bodyFat;
    char membershipPlan;

    Member(int r = 0, string n = "", int l = 0, char plan = '\0') 
        : regNo(r), name(n), lockerNo(l), weight(0), height(0), age(0), gender(0), bmi(0), bodyFat(0), membershipPlan(plan) {}
};

class Gym {
private:
    vector<Member> members;
    unordered_map<int, Member> memberTable;
    TrainerNode* trainerHead;
    static const int MAX_MEMBERS = 100;
    int nextLockerNumber;

    // Helper function to truncate strings with "..."
    string fitString(const string& str, int maxLength) {
        if (str.length() <= maxLength) {
            return str;
        }
        return str.substr(0, maxLength - 3) + "...";
    }

public:
    Gym() : trainerHead(nullptr), nextLockerNumber(6) {
        addTrainer("Albert", "Degree in Health Sciences, 50+ medals, UAE qualified", "03XXXXXXXXX", 7000);
        addTrainer("Smith", "Degree in Health Sciences, 50+ medals, UAE qualified", "03XXXXXXXXX", 7500);
        addTrainer("Sami", "Degree in Health Sciences, 50+ medals, UAE qualified", "03XXXXXXXXX", 8000);
    }

    void addTrainer(string name, string qual, string contact, int fee) {
        TrainerNode* newNode = new TrainerNode(name, qual, contact, fee);
        newNode->next = trainerHead;
        trainerHead = newNode;
    }

    void displayMembershipPlans() {
        cout << "=== The Iron Heaven Gym ===" << endl;
        cout << "Welcome to our Membership Programs\n";
        cout << "Available Plans:\n";
        cout << "a ~ 1 month (Rs 2000)\n";
        cout << "b ~ 1 month + treadmill (Rs 2500)\n";
        cout << "c ~ 3 months (Rs 3000, Rs 1000 relief)\n";
        cout << "d ~ 3 months + treadmill (Rs 4500, Rs 1500 relief)\n";
        cout << "e ~ 6 months (Rs 6500, Rs 3500 relief)\n";
        cout << "f ~ 6 months + treadmill (Rs 8500, Rs 4000 relief)\n";
        cout << "g ~ 1 year (Rs 9500, Rs 12500 relief)\n";
        cout << "h ~ 1 year + treadmill (Rs 13500, Rs 15000 relief)\n";
        cout << "----------------------\n";
    }

    int calculateMembershipCost(char choice) {
        int baseCost = 2000;
        switch (choice) {
            case 'a': return baseCost;
            case 'b': return baseCost + 500;
            case 'c': return baseCost + 3000;
            case 'd': return baseCost + 4000;
            case 'e': return baseCost + 6500;
            case 'f': return baseCost + 8000;
            case 'g': return baseCost + 9500;
            case 'h': return baseCost + 13000;
            default: return 0;
        }
    }

    int linearSearchLocker() {
        while (nextLockerNumber <= MAX_MEMBERS + 5) {
            bool taken = false;
            for (const auto& member : members) {
                if (member.lockerNo == nextLockerNumber) {
                    taken = true;
                    break;
                }
            }
            if (!taken) {
                int assignedLocker = nextLockerNumber;
                nextLockerNumber++;
                return assignedLocker;
            }
            nextLockerNumber++;
        }
        return -1;
    }

    void registerAndBuyMembership() {
        displayMembershipPlans();
        cout << "Enter membership plan (a-h): ";
        char membershipChoice;
        cin >> membershipChoice;
        int cost = calculateMembershipCost(membershipChoice);
        if (cost == 0) {
            cout << "Invalid plan choice\n";
            return;
        }
        cout << "Selected package amount: Rs " << cost << endl;

        int regNo;
        string name;
        float weight, height, age;
        int gender;
        cout << "Enter registration number: ";
        cin >> regNo;
        if (memberTable.find(regNo) != memberTable.end()) {
            cout << "Registration number " << regNo << " already exists!\n";
            return;
        }
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter weight (kg): ";
        cin >> weight;
        cout << "Enter height (cm): ";
        cin >> height;
        cout << "Enter age (years): ";
        cin >> age;
        cout << "Enter gender (1-male, 2-female): ";
        cin >> gender;

        int locker = linearSearchLocker();
        if (locker == -1) {
            cout << "No lockers available!\n";
            return;
        }
        if (members.size() >= MAX_MEMBERS) {
            cout << "Gym is at full capacity!\n";
            return;
        }

        Member newMember(regNo, name, locker, membershipChoice);
        newMember.weight = weight;
        newMember.height = height;
        newMember.age = age;
        newMember.gender = gender;
        newMember.bmi = calculateBMI(newMember);
        members.push_back(newMember);
        memberTable[regNo] = newMember;
        cout << "Member registered successfully with locker number: " << locker << endl;
        cout << "Membership plan '" << membershipChoice << "' purchased for " << name << endl;
    }

    double calculateBMI(const Member& member) {
        double heightM = member.height / 100;
        return member.weight / (heightM * heightM);
    }

    void searchMember(int regNo) {
        auto it = memberTable.find(regNo);
        if (it != memberTable.end()) {
            const Member& member = it->second;
            cout << "Member Found:\n";
            cout << "Registration No: " << member.regNo << endl;
            cout << "Name: " << member.name << endl;
            cout << "Locker No: " << member.lockerNo << endl;
            cout << "Membership Plan: " << member.membershipPlan << endl;
            cout << "Weight: " << member.weight << " kg\n";
            cout << "Height: " << member.height << " cm\n";
            cout << "Age: " << member.age << " years\n";
            cout << "Gender: " << (member.gender == 1 ? "Male" : "Female") << endl;
            cout << "BMI: " << member.bmi << endl;
        } else {
            cout << "Member with registration number " << regNo << " not found.\n";
        }
    }

    void displayAllMembers() {
        if (members.empty()) {
            cout << "No members registered.\n";
            return;
        }
        cout << "\nAll Members:\n";
        cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;
        cout << "* Reg No * " << setw(14) << left << "Name" << " * Locker * Plan * "
             << setw(9) << "Weight" << " * " << setw(9) << "Height" << " * "
             << setw(5) << "Age" << " * " << setw(8) << "Gender" << " * "
             << setw(8) << "BMI" << " *" << endl;
        cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;

        for (const auto& member : members) {
            cout << "* " << setw(6) << right << member.regNo << " * " 
                 << setw(14) << left << fitString(member.name, 14) << "* "
                 << setw(6) << right << member.lockerNo << " *  " 
                 << member.membershipPlan << "  * "
                 << fixed << setprecision(1) << setw(7) << right << member.weight << "kg * "
                 << setw(7) << right << member.height << "cm * "
                 << setw(4) << right << (int)member.age << " * "
                 << setw(8) << left << (member.gender == 1 ? "Male" : "Female") << "* "
                 << setprecision(2) << setw(7) << right << member.bmi << " *" << endl;
            cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;
        }
    }

    void insertMember(int regNo, string name, float weight, float height, int age, int gender, char membershipPlan) {
        if (memberTable.find(regNo) != memberTable.end()) {
            cout << "Registration number " << regNo << " already exists!\n";
            return;
        }
        int locker = linearSearchLocker();
        if (locker == -1) {
            cout << "No lockers available!\n";
            return;
        }
        if (members.size() >= MAX_MEMBERS) {
            cout << "Gym is at full capacity!\n";
            return;
        }
        Member newMember(regNo, name, locker, membershipPlan);
        newMember.weight = weight;
        newMember.height = height;
        newMember.age = age;
        newMember.gender = gender;
        newMember.bmi = calculateBMI(newMember);
        members.push_back(newMember);
        memberTable[regNo] = newMember;
        cout << "Member inserted successfully with locker number: " << locker << endl;
    }

    void deleteMember(int regNo) {
        auto it = memberTable.find(regNo);
        if (it != memberTable.end()) {
            auto vecIt = find_if(members.begin(), members.end(), 
                [regNo](const Member& m) { return m.regNo == regNo; });
            if (vecIt != members.end()) {
                if (vecIt->lockerNo < nextLockerNumber) {
                    nextLockerNumber = vecIt->lockerNo;
                }
                members.erase(vecIt);
            }
            memberTable.erase(it);
            cout << "Member with registration number " << regNo << " deleted.\n";
        } else {
            cout << "Member with registration number " << regNo << " not found.\n";
        }
    }

    void updateMember(int regNo, string name, float weight, float height, int age, int gender, char membershipPlan) {
        auto it = memberTable.find(regNo);
        if (it != memberTable.end()) {
            auto vecIt = find_if(members.begin(), members.end(), 
                [regNo](const Member& m) { return m.regNo == regNo; });
            if (vecIt != members.end()) {
                vecIt->name = name;
                vecIt->weight = weight;
                vecIt->height = height;
                vecIt->age = age;
                vecIt->gender = gender;
                vecIt->membershipPlan = membershipPlan;
                vecIt->bmi = calculateBMI(*vecIt);
            }
            it->second.name = name;
            it->second.weight = weight;
            it->second.height = height;
            it->second.age = age;
            it->second.gender = gender;
            it->second.membershipPlan = membershipPlan;
            it->second.bmi = calculateBMI(it->second);
            cout << "Member with registration number " << regNo << " updated.\n";
        } else {
            cout << "Member with registration number " << regNo << " not found.\n";
        }
    }

    void sortMembersByRegNo() {
        sort(members.begin(), members.end(), 
            [](const Member& a, const Member& b) { return a.regNo < b.regNo; });
        for (size_t i = 1; i < members.size(); ++i) {
            if (members[i].regNo < members[i-1].regNo) {
                cout << "Sorting error detected!\n";
                return;
            }
        }
        memberTable.clear();
        for (const auto& member : members) {
            memberTable[member.regNo] = member;
        }
        cout << "Members sorted by registration number.\n";
        displayAllMembers();
    }

    void insertTrainer(string name, string qual, string contact, int fee) {
        addTrainer(name, qual, contact, fee);
        cout << "Trainer " << name << " inserted successfully.\n";
    }

    void deleteTrainer(string name) {
        TrainerNode* current = trainerHead;
        TrainerNode* prev = nullptr;
        while (current && current->name != name) {
            prev = current;
            current = current->next;
        }
        if (current) {
            if (prev) {
                prev->next = current->next;
            } else {
                trainerHead = current->next;
            }
            cout << "Trainer " << name << " deleted.\n";
            delete current;
        } else {
            cout << "Trainer " << name << " not found.\n";
        }
    }

    void updateTrainer(string name, string qual, string contact, int fee) {
        TrainerNode* current = trainerHead;
        while (current && current->name != name) {
            current = current->next;
        }
        if (current) {
            current->qualifications = qual;
            current->contact = contact;
            current->fee = fee;
            cout << "Trainer " << name << " updated.\n";
        } else {
            cout << "Trainer " << name << " not found.\n";
        }
    }

    void searchTrainer(string name) {
        TrainerNode* current = trainerHead;
        while (current && current->name != name) {
            current = current->next;
        }
        if (current) {
            cout << "\nTrainer Found:\n";
            cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;
            cout << "* " << setw(14) << left << "Name" << " * " << setw(30) << "Qualifications" << " * "
                 << setw(12) << "Contact" << " * " << setw(7) << "Fee" << " *" << endl;
            cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;
            cout << "* " << setw(14) << left << fitString(current->name, 14) << "* "
                 << setw(30) << left << fitString(current->qualifications, 30) << "* "
                 << setw(12) << left << current->contact << "* "
                 << setw(7) << right << current->fee << "* " << endl;
            cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;
        } else {
            cout << "Trainer " << name << " not found.\n";
        }
    }

    void sortTrainersByFee() {
        if (!trainerHead || !trainerHead->next) {
            cout << "No trainers to sort.\n";
            return;
        }
        bool swapped;
        TrainerNode* ptr;
        TrainerNode* last = nullptr;
        do {
            swapped = false;
            ptr = trainerHead;
            while (ptr->next != last) {
                if (ptr->fee > ptr->next->fee) {
                    swap(ptr->name, ptr->next->name);
                    swap(ptr->qualifications, ptr->next->qualifications);
                    swap(ptr->contact, ptr->next->contact);
                    swap(ptr->fee, ptr->next->fee);
                    swapped = true;
                }
                ptr = ptr->next;
            }
            last = ptr;
        } while (swapped);
        cout << "Trainers sorted by fee.\n";
        displayAllTrainers();
    }

    void displayAllTrainers() {
        if (!trainerHead) {
            cout << "No trainers available.\n";
            return;
        }
        cout << "\nAll Trainers:\n";
        cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;
        cout << "* " << setw(14) << left << "Name" << " * " << setw(30) << "Qualifications" << " * "
             << setw(12) << "Contact" << " * " << setw(7) << "Fee" << " *" << endl;
        cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;

        TrainerNode* current = trainerHead;
        while (current) {
            cout << "* " << setw(14) << left << fitString(current->name, 14) << "* "
                 << setw(30) << left << fitString(current->qualifications, 30) << "* "
                 << setw(12) << left << current->contact << "* "
                 << setw(7) << right << current->fee << "* " << endl;
            cout << setfill('*') << setw(99) << "" << setfill(' ') << endl;
            current = current->next;
        }
    }

    void displayTrainer(int choice) { /* ... */ }
    void displayExercisePlan(char planType, int muscleGroup) { /* ... */ }
    double calculateBMR(const Member& member) { /* ... */ }
    void displayNutritionalNeeds(const Member& member) { /* ... */ }
    void calculateBodyFat(Member& member) { /* ... */ }
    void displayDietPlan(int choice, double protein, double bmr) { /* ... */ }

    void run() {
        while (true) {
            cout << "\n=== Gym Management System ===\n";
            cout << "1. Display and Buy Membership Plan\n";
            cout << "2. Insert Member\n";
            cout << "3. Delete Member\n";
            cout << "4. Update Member\n";
            cout << "5. Search Member\n";
            cout << "6. Sort Members by Reg No\n";
            cout << "7. Display All Members\n";
            cout << "8. Insert Trainer\n";
            cout << "9. Delete Trainer\n";
            cout << "10. Update Trainer\n";
            cout << "11. Search Trainer\n";
            cout << "12. Sort Trainers by Fee\n";
            cout << "13. Display All Trainers\n";
            cout << "14. Exit\n";
            cout << "Enter choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: {
                    registerAndBuyMembership();
                    break;
                }
                case 2: {
                    int regNo;
                    string name;
                    float weight, height;
                    int age, gender;
                    char membershipPlan;
                    cout << "Enter registration number: ";
                    cin >> regNo;
                    cout << "Enter name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter weight (kg): ";
                    cin >> weight;
                    cout << "Enter height (cm): ";
                    cin >> height;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter gender (1-male, 2-female): ";
                    cin >> gender;
                    displayMembershipPlans();
                    cout << "Enter membership plan (a-h): ";
                    cin >> membershipPlan;
                    if (calculateMembershipCost(membershipPlan) == 0) {
                        cout << "Invalid membership plan\n";
                        break;
                    }
                    insertMember(regNo, name, weight, height, age, gender, membershipPlan);
                    break;
                }
                case 3: {
                    int regNo;
                    cout << "Enter registration number to delete: ";
                    cin >> regNo;
                    deleteMember(regNo);
                    break;
                }
                case 4: {
                    int regNo;
                    string name;
                    float weight, height;
                    int age, gender;
                    char membershipPlan;
                    cout << "Enter registration number to update: ";
                    cin >> regNo;
                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter new weight (kg): ";
                    cin >> weight;
                    cout << "Enter new height (cm): ";
                    cin >> height;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter gender (1-male, 2-female): ";
                    cin >> gender;
                    displayMembershipPlans();
                    cout << "Enter new membership plan (a-h): ";
                    cin >> membershipPlan;
                    if (calculateMembershipCost(membershipPlan) == 0) {
                        cout << "Invalid membership plan\n";
                        break;
                    }
                    updateMember(regNo, name, weight, height, age, gender, membershipPlan);
                    break;
                }
                case 5: {
                    int regNo;
                    cout << "Enter registration number to search: ";
                    cin >> regNo;
                    searchMember(regNo);
                    break;
                }
                case 6: {
                    sortMembersByRegNo();
                    break;
                }
                case 7: {
                    displayAllMembers();
                    break;
                }
                case 8: {
                    string name, qual, contact;
                    int fee;
                    cout << "Enter trainer name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter qualifications: ";
                    getline(cin, qual);
                    cout << "Enter contact: ";
                    getline(cin, contact);
                    cout << "Enter monthly fee: ";
                    cin >> fee;
                    insertTrainer(name, qual, contact, fee);
                    break;
                }
                case 9: {
                    string name;
                    cout << "Enter trainer name to delete: ";
                    cin.ignore();
                    getline(cin, name);
                    deleteTrainer(name);
                    break;
                }
                case 10: {
                    string name, qual, contact;
                    int fee;
                    cout << "Enter trainer name to update: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter new qualifications: ";
                    getline(cin, qual);
                    cout << "Enter new contact: ";
                    getline(cin, contact);
                    cout << "Enter new monthly fee: ";
                    cin >> fee;
                    updateTrainer(name, qual, contact, fee);
                    break;
                }
                case 11: {
                    string name;
                    cout << "Enter trainer name to search: ";
                    cin.ignore();
                    getline(cin, name);
                    searchTrainer(name);
                    break;
                }
                case 12: {
                    sortTrainersByFee();
                    break;
                }
                case 13: {
                    displayAllTrainers();
                    break;
                }
                case 14: {
                    cout << "Exiting system.\n";
                    return;
                }
                default: {
                    cout << "Invalid choice\n";
                    break;
                }
            }
        }
    }

    ~Gym() {
        TrainerNode* current = trainerHead;
        while (current) {
            TrainerNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
   
    cout<<"*"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"*GYM MANAGMENT"<<endl;
    Gym gym;
    gym.run();
    return 0;
}