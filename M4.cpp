// File: ParkingTicketSimulator.cpp
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class ParkedCar {
private:
    string make, model, color, license;
    int parkedMinutes;
public:
    ParkedCar(string mk, string mdl, string clr, string lic, int min)
        : make(mk), model(mdl), color(clr), license(lic), parkedMinutes(min) {
    }

    int getParkedMinutes() const { return parkedMinutes; }
    string getCarDetails() const {
        return "Make: " + make + ", Model: " + model + ", Color: " + color + ", License: " + license;
    }
};

class ParkingMeter {
private:
    int purchasedMinutes;
public:
    ParkingMeter(int min) : purchasedMinutes(min) {}
    int getPurchasedMinutes() const { return purchasedMinutes; }
};

class ParkingTicket {
private:
    string carDetails, officerName, badge;
    int minutesOver;
    double fine;

    double calculateFine(int minutes) {
        if (minutes <= 0) return 0;
        int hours = ceil(minutes / 60.0);
        return 25.0 + (hours - 1) * 10.0;
    }

public:
    ParkingTicket(const ParkedCar& car, const string& officer, const string& badgeNum, int over)
        : officerName(officer), badge(badgeNum), minutesOver(over) {
        carDetails = car.getCarDetails();
        fine = calculateFine(minutesOver);
    }

    void printTicket() const {
        cout << "\n*** Parking Ticket ***" << endl;
        cout << "Officer: " << officerName << " Badge: " << badge << endl;
        cout << carDetails << endl;
        cout << "Minutes Over: " << minutesOver << endl;
        cout << "Fine: $" << fine << endl;
    }
};

class PoliceOfficer {
private:
    string name, badgeNumber;
public:
    PoliceOfficer(string n, string b) : name(n), badgeNumber(b) {}

    void inspect(const ParkedCar& car, const ParkingMeter& meter) {
        int parked = car.getParkedMinutes();
        int purchased = meter.getPurchasedMinutes();
        int over = parked - purchased;
        if (over > 0) {
            ParkingTicket ticket(car, name, badgeNumber, over);
            ticket.printTicket();
        }
        else {
            cout << "\nCar is legally parked. No ticket issued.\n";
        }
    }
};

int main() {
    cout << "--- Scenario 1: Legally Parked ---" << endl;
    ParkedCar car1("Toyota", "Camry", "Red", "XYZ123", 30);
    ParkingMeter meter1(40);
    PoliceOfficer officer1("John Doe", "5678");
    officer1.inspect(car1, meter1);

    cout << "\n--- Scenario 2: 10 Min Over ---" << endl;
    ParkedCar car2("Honda", "Accord", "Blue", "ABC987", 70);
    ParkingMeter meter2(60);
    PoliceOfficer officer2("Jane Smith", "1234");
    officer2.inspect(car2, meter2);

    cout << "\n--- Scenario 3: 130 Min Over ---" << endl;
    ParkedCar car3("Ford", "Mustang", "Black", "LMN456", 190);
    ParkingMeter meter3(60);
    PoliceOfficer officer3("James Brown", "4321");
    officer3.inspect(car3, meter3);

    cout << "\n--- Scenario 4: Multiple Cars ---" << endl;
    ParkedCar cars[] = {
        ParkedCar("Mazda", "3", "Grey", "DEF111", 45),
        ParkedCar("BMW", "X5", "Black", "GHI222", 90),
        ParkedCar("Tesla", "Model 3", "White", "JKL333", 59)
    };
    ParkingMeter meters[] = {
        ParkingMeter(45),
        ParkingMeter(60),
        ParkingMeter(60)
    };
    PoliceOfficer officer4("Emily Davis", "7890");
    for (int i = 0; i < 3; ++i) {
        officer4.inspect(cars[i], meters[i]);
    }

    return 0;
}
