#include <iostream>
#include <string>
#include<stdlib.h>
#include<stdexcept>
#include<stdio.h>
#include <random>
using namespace std;
class Restaurant {
private:
     string name;
    int floorNumber;
    vector<string> menu = {"Pasta", "Pizza", "Burger", "Salad", "Steak"};
    vector<double> prices = {8.99, 9.99, 5.49, 6.99, 12.99};
public:
   Restaurant(const string& restaurantName, int floorNum)
        : name(restaurantName), floorNumber(floorNum) {}
    void displayMenu() const {
        cout << "\nWelcome to " << name << " (Floor Number : " << floorNumber << ")" << endl;
        cout << "Menu:" << endl;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << menu[i] << " - $" << prices[i] << endl;
        }
    }

    void takeOrder() {
        int choice;
        double totalBill = 0.0;
        do {
            displayMenu();
            cout << "Enter the item number you want to order (0 to finish): ";
            cin >> choice;

            if (choice > 0 && choice <= 5) {
                totalBill += prices[choice - 1];
            } else if (choice != 0) {
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
 int gst=0.18*totalBill;
 totalBill+=gst;
        cout << "Thank you for ordering from " << name << "!" << endl;
        cout << "Total Bill with added gst amout of "<< gst << " is " << totalBill <<" $"  <<endl;
    }
};
class Guest {
private:
    string name;
    string aadharNumber;

public:
Guest() : name(""), aadharNumber("") {}

    Guest(const string& guestName, const string& guestAadharNumber)
        : name(guestName) {
        setAadharNumber(guestAadharNumber);
    }

    string getName() const {
        return name;
    }

    string getAadharNumber() const {
        return aadharNumber;
    }
    void setAadharNumber(const string& guestAadharNumber) {
        if (guestAadharNumber.length() != 12) {
            throw invalid_argument("Aadhar number must be 12 digits long.");
        }
        aadharNumber = guestAadharNumber;
    }
};

class Room {
protected:
    int roomNumber;
    double price;
    bool isAvailable;
    string* features;
    int numFeatures;
    string roomType;

public:
Room() : roomNumber(0), price(0.0), isAvailable(true), numFeatures(0), roomType("") {
        features = nullptr;
    }
    Room(int number, double cost, string* roomFeatures, int numRoomFeatures, string type)
        : roomNumber(number), price(cost), isAvailable(true), numFeatures(numRoomFeatures), roomType(type) {
        features = new string[numRoomFeatures];
        for (int i = 0; i < numRoomFeatures; i++) {
            features[i] = roomFeatures[i];
        }
    }

    int getRoomNumber() const {
        return roomNumber;
    }

    double getPrice() const {
        return price;
    }

    bool getAvailability() const {
        return isAvailable;
    }

    void setAvailability(bool availability) {
        isAvailable = availability;
    }

    string getRoomType() const {
        return roomType;
    }

    void displayFeatures() const {
        cout << "Features of Room " << roomNumber << ":" << endl;
        for (int i = 0; i < numFeatures; i++) {
            cout << features[i] << endl;
        }
    }

    ~Room() {
        delete[] features;
    }
    void requestServices() const {
    cout << "Do you want housekeeping or laundry services or food service for Room " << roomNumber << "?" << endl;
    cout << "1. Housekeeping" << endl;
    cout << "2. Laundry" << endl;
    cout << "3. Restaurant Services" << endl; // Added option for restaurant services
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Housekeeping service requested for Room " << roomNumber << "." << endl;
            cout << "Charges: $30" << endl;
            break;
        case 2:
            cout << "Laundry service requested for Room " << roomNumber << "." << endl;
            cout << "Charges: $20" << endl;
            break;
        case 3: {
            Restaurant restaurant("Grand Restaurant", 5);
            restaurant.takeOrder();
            break;
        }
        case 4: {
            Restaurant restaurant("Grand Restaurant", 5);
cout << "For no services....\n";
break;
        }
        default:
            cout << "Invalid choice. No services requested." << endl;
            break;
    }
}


};

class SingleRoom : public Room {
public:
    SingleRoom(int number, double cost)
        : Room(number, cost, new string[2]{"AC", "TV"}, 2, "single") {}
};

class DoubleRoom : public Room {
public:
    DoubleRoom(int number, double cost)
        : Room(number, cost, new string[3]{"AC", "TV", "Mini-bar"}, 3, "double") {}
};

class Suite : public Room {
public:
    Suite(int number, double cost)
        : Room(number, cost, new string[4]{"AC", "TV", "Mini-bar", "Jacuzzi"}, 4, "suite") {}
};

class Employee {
private:
    string name;
    string employeeId;

public:
    Employee(const string& employeeName, const string& id) : name(employeeName), employeeId(id) {}

    string getName() const {
        return name;
    }

    string getEmployeeId() const {
        return employeeId;
    }

    virtual void work() = 0;
};

class Receptionist : public Employee {
public:
    Receptionist(const string& employeeName, const string& id) : Employee(employeeName, id) {}

    void work() override {
        cout << "Receptionist " << getName() << " handles guest check-ins and check-outs." << endl;
    }
};

class Housekeeping : public Employee {
public:
    Housekeeping(const string& employeeName, const string& id) : Employee(employeeName, id) {}

    void work() override {
        cout << "Housekeeping staff " << getName() << " handles cleaning the rooms." << endl;
    }
};

class Manager : public Employee {
public:
    Manager(const string& employeeName, const string& id) : Employee(employeeName, id) {}

    void work() override {
        cout << "Manager " << getName() << " manages hotel operations." << endl;
    }
};

class Bellboy : public Employee {
public:
    Bellboy(const string& employeeName, const string& id) : Employee(employeeName, id) {}

    void work() override {
        cout << "Bellboy " << getName() << " assists guests with their luggage." << endl;
    }
};

class Chef : public Employee {
public:
    Chef(const string& employeeName, const string& id) : Employee(employeeName, id) {}

    void work() override {
        cout << "Chef " << getName() << " prepares delicious meals in the kitchen." << endl;
    }
};

class Reservation {
private:
    Room* room;
    Guest* guest; // Use pointer to Guest object
    int duration;

public:
    Reservation(Room* resRoom, Guest* resGuest, int resDuration)
        : room(resRoom), guest(resGuest), duration(resDuration) {}

    Room* getRoom() const {
        return room;
    }

    Guest* getGuest() const {
        return guest;
    }

    int getDuration() const {
        return duration;
    }
};


class Bill{
private:
    double totalAmount;
    bool isPaid;

public:
    Bill(double amount) : totalAmount(amount), isPaid(false) {}

    double getTotalAmount() const {
        return totalAmount;
    }

    bool getPaymentStatus() const {
        return isPaid;
    }

    void markPaid() {
        isPaid = true;
    }
};

class Hotel {
private:
    string name;
    Room* rooms[8];
    Reservation* reservations[100];
    int numRooms;
    int numReservations;
    Employee* employees[10];
    int numEmployees;
    Bill* bills[100];
    int numBills;

public:
    Hotel(const string& hotelName) : name(hotelName), numRooms(0), numReservations(0), numEmployees(0), numBills(0) {}
    int getNumAvailableRooms() const {
        int numAvailable = 0;
        for (int i = 0; i < numRooms; i++) {
            if (rooms[i]->getAvailability()) {
                numAvailable++;
            }
        }
        return numAvailable;
    }
    void addRoom(Room* room) {
        if (numRooms < 8) {
            rooms[numRooms++] = room;
        } else {
            cout << "Cannot add more rooms. Room capacity reached." << endl;
        }
    }

    string getname(){
        return name;
    }

    Room** getRooms() {
        return rooms;
    }

    int getNumRooms() const {
        return numRooms;
    }

    void addEmployee(Employee* employee) {
        if (numEmployees < 10) {
            employees[numEmployees++] = employee;
        } else {
            cout << "Cannot add more employees. Employee capacity reached." << endl;
        }
    }

  void displayAvailableRooms() const {
    cout << "Available rooms in " << name << ":" << endl;
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i]->getAvailability()) {
            cout << "Room Number: " << rooms[i]->getRoomNumber() << " | Type: " << rooms[i]->getRoomType() << " | Price: $" << rooms[i]->getPrice() << endl;
            // Display special features for each room type
            if (rooms[i]->getRoomType() == "single") {
                cout << "Special Features: " << endl;
                cout << " - " << "AC" << endl;
                cout << " - " << "TV" << endl;
            } else if (rooms[i]->getRoomType() == "double") {
                cout << "Special Features: " << endl;
                cout << " - " << "AC" << endl;
                cout << " - " << "TV" << endl;
                cout << " - " << "Mini-bar" << endl;
            } else if (rooms[i]->getRoomType() == "suite") {
                cout << "Special Features: " << endl;
                cout << " - " << "AC" << endl;
                cout << " - " << "TV" << endl;
                cout << " - " << "Mini-bar" << endl;
                cout << " - " << "Jacuzzi" << endl;
            }
        }
    }
}


    void bookRoom(int roomNumber, Guest* guest, int duration) {
        for (int i = 0; i < numRooms; i++) {
            if (rooms[i]->getRoomNumber() == roomNumber && rooms[i]->getAvailability()) {
                rooms[i]->setAvailability(false);
                reservations[numReservations++] = new Reservation(rooms[i], guest, duration);
                cout << "Room " << roomNumber << " has been booked successfully." << endl;
                return;
            }
        }
        cout << "Room " << roomNumber << " is not available." << endl;
    }

    void checkoutRoom(int roomNumber) {
        for (int i = 0; i < numReservations; i++) {
            if (reservations[i]->getRoom()->getRoomNumber() == roomNumber) {
                double totalBill = reservations[i]->getRoom()->getPrice() * reservations[i]->getDuration();
                bills[numBills++] = new Bill(totalBill);

                cout << "Room " << roomNumber << " has been checked out successfully." << endl;
                cout << "Total Bill: $" << totalBill << endl;

                bills[numBills - 1]->markPaid();

                reservations[i]->getRoom()->setAvailability(true);
                delete reservations[i];
                return;
            }
        }
        cout << "Room " << roomNumber << " is not booked." << endl;
    }

    void displayEmployees() const {
        cout << "Employees in " << name << ":" << endl;
        for (int i = 0; i < numEmployees; i++) {
            cout << "Name: " << employees[i]->getName() << " | Employee ID: " << employees[i]->getEmployeeId() << endl;
        }
    }

    void performWork() const {
        for (int i = 0; i < numEmployees; i++) {
            employees[i]->work();
        }
    }

    virtual void displayCustomers() const {
        cout << "Customer details in " << name << ":" << endl;
        for (int i = 0; i < numReservations; i++) {
            Reservation* reservation = reservations[i];
            if (reservation) {
                cout << "Reservation Details: " << endl;
                cout << "Room Number: " << reservation->getRoom()->getRoomNumber() << endl;
                cout << "Guest Name: " << reservation->getGuest()->getName() << endl;
                cout << "Duration of Stay: " << reservation->getDuration() << " days" << endl;
                cout << "--------------------------------" << endl;
            }
        }
    }


    ~Hotel() {
        for (int i = 0; i < numRooms; i++) {
            delete rooms[i];
        }

        for (int i = 0; i < numReservations; i++) {
            delete reservations[i];
        }

        for (int i = 0; i < numEmployees; i++) {
            delete employees[i];
        }

        for (int i = 0; i < numBills; i++) {
            delete bills[i];
        }
    }
};




template <typename T>
string generateWelcomeMessage(const T& hotelName) {
    return "Welcome to " + hotelName + "!";
}


int main() {
    string hotelName = "SA Grand Hotel & Restaurant...";
    string welcomeMessage = generateWelcomeMessage(hotelName);
    cout << welcomeMessage << endl;

    cout << "Choose an option: " << endl;
    cout << "1. Hotel" << endl;
    cout << "2. Restaurant" << endl;
    cout << "Enter your choice: ";
    int option;
    cin >> option;

    if (option == 1) {
    Hotel hotel("SA Grand Hotel");

    SingleRoom room1(102, 100.0);
    DoubleRoom room2(103, 150.0);
    Suite room3(201, 200.0);
    DoubleRoom room4(202, 150.0);
    Suite room5(301, 250.0);
    DoubleRoom room6(302, 180.0);
    SingleRoom room7(401, 120.0);
    SingleRoom room8(402, 120.0);

    hotel.addRoom(&room1);
    hotel.addRoom(&room2);
    hotel.addRoom(&room3);
    hotel.addRoom(&room4);
    hotel.addRoom(&room5);
    hotel.addRoom(&room6);
    hotel.addRoom(&room7);
    hotel.addRoom(&room8);

    Receptionist receptionist1("Rebecca Johnson", "R001");
    Housekeeping housekeeping1("Emily Davis", "H001");

    hotel.addEmployee(&receptionist1);
    hotel.addEmployee(&housekeeping1);

    int choice;
    do {
        cout << "\nWelcome to " << hotel.getname() << endl;
        cout << "1. Display Available Rooms" << endl;
        cout << "2. Book a Room" << endl;
        cout << "3. Check-out from a Room" << endl;
        cout << "4. Display Employees" << endl;
        cout << "5. Add an Employee" << endl;
        cout << "6. Perform Employee Work" << endl;
        cout << "7. Display Customer Details" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.displayAvailableRooms();
                break;
            case 2: {
                cout << "How many rooms do you need? ";
                int numRooms;
                cin >> numRooms;

                int numAvailableRooms = hotel.getNumAvailableRooms();
                if (numRooms > numAvailableRooms) {
                    cout << "Error: Requested number of rooms (" << numRooms
                         << ") exceeds available rooms (" << numAvailableRooms << ")." << endl;
                exit(0);}
                double totalCost = 0.0;

                for (int i = 0; i < numRooms; i++) {
                    cout << "Please enter the required room id: ";
                    int roomId;
                    cin >> roomId;
cin.ignore(); // Ignore newline character from previous input

 cout << "Please enter guest name: ";
string guestName;
cin >> guestName;
cout << "Please enter the Aadhar number: ";
string guestAadharNumber;
cin >> guestAadharNumber;



                try {
                    Guest* guest = new Guest(guestName, guestAadharNumber);
                        cout << "Please enter guest phone number: ";
                        string guestPhoneNumber;
                        cin.ignore();
                        getline(cin, guestPhoneNumber);
                        while (guestPhoneNumber.length() !=10) {
                        cout << "Invalid phone number. Please enter a valid phone number (10 digits): ";
                        getline(cin, guestPhoneNumber);
                     }

                        cout << "Please enter the number of days required for the room: ";
                        int numDays;
                        cin >> numDays;

                        Room* room = nullptr;
                        for (int j = 0; j < hotel.getNumRooms(); j++) {
                            if (hotel.getRooms()[j]->getRoomNumber() == roomId) {
                                room = hotel.getRooms()[j];
                                break;
                            }
                        }
if (room) {
                                totalCost += room->getPrice() * numDays;
                                hotel.bookRoom(roomId, guest, numDays);
                                cout << roomId << " " << room->getRoomType() << endl;
                                room->requestServices();
                            }  else {
                            cout << "Invalid room ID. Please try again." << endl;
                        }
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                        cout << "Please provide a valid 12-digit Aadhar number." << endl;
                        exit(0);
                    }
                }
                cout << "\nTotal cost: $" << totalCost << endl;

                cout << "Paid money: ";
                double paidAmount;
                cin >> paidAmount;

                if (paidAmount >= totalCost) {
                    cout << "Receivable change: $" << (paidAmount - totalCost) << endl;
                } else {
                    cout << "Insufficient payment. Please pay the remaining amount: $" << (totalCost - paidAmount) << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter Room Number to Check-out: ";
                int roomNumber;
                cin >> roomNumber;
                hotel.checkoutRoom(roomNumber);
                break;
            }
            case 4:
                hotel.displayEmployees();
                break;
            case 5: {
                cout << "Enter Employee Name: ";
                string employeeName;
                cin.ignore();
                getline(cin, employeeName);

                cout << "Enter Employee ID (Ex: R001 for Receptionist, H001 for Housekeeping, M001 for Manager, B001 for Bellboy, C001 for Chef): ";
                string employeeId;
                getline(cin, employeeId);

                cout << "Choose the Employee Type:" << endl;
                cout << "1. Receptionist" << endl;
                cout << "2. Housekeeping" << endl;
                cout << "3. Manager" << endl;
                cout << "4. Bellboy" << endl;
                cout << "5. Chef" << endl;
                cout << "Enter your choice: ";
                int employeeType;
                cin >> employeeType;

                Employee* newEmployee = nullptr;
                switch (employeeType) {
                    case 1:
                        newEmployee = new Receptionist(employeeName, employeeId);
                        cout << "Receptionist added successfully." << endl;
                        break;
                    case 2:
                        newEmployee = new Housekeeping(employeeName, employeeId);
                        cout << "Housekeeping staff added successfully." << endl;
                        break;
                    case 3:
                        newEmployee = new Manager(employeeName, employeeId);
                        cout << "Manager added successfully." << endl;
                        break;
                    case 4:
                        newEmployee = new Bellboy(employeeName, employeeId);
                        cout << "Bellboy added successfully." << endl;
                        break;
                    case 5:
                        newEmployee = new Chef(employeeName, employeeId);
                        cout << "Chef added successfully." << endl;
                        break;
                    default:
                        cout << "Invalid choice. No employee added." << endl;
                        break;
                }

                if (newEmployee) {
                    hotel.addEmployee(newEmployee);
                }
                break;
            }
            case 6:
                hotel.performWork();
                break;
            case 7:
                hotel.displayCustomers();
                break;
            case 0:
                cout << "Thank you for using " << hotel.getname() << "!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 0);
}else if (option == 2) {
        // Create a Restaurant object and take orders
        Restaurant restaurant("Grand Restaurant", 5);
        restaurant.takeOrder();
    } else {
        cout << "Invalid choice. Exiting program." << endl;
    }

    return 0;
}
