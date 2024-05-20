#include "part2b_airlineSystem.h"


int main() {
    vector<vector<Seat> > seatingChart(12, vector<Seat>(6));//Definition of a two-bit array of seats
    vector<Passenger> passengerManifest;//Definition of a passenger array
    initializeSeatingChart(seatingChart);
    loadSeatAssignments(seatingChart, passengerManifest);
    while (1) {
        int userType = getUserType();
        if (userType == 1) {
            mainMenuPassenger(seatingChart, passengerManifest);
        }
        else if (userType == 2) {
            string password;
            cout << "Please enter your login password:";
            cin >> password;
            if ("123456" == password) {
                mainMenuEmployee(seatingChart, passengerManifest);
            }
            else {
                cout << "Enter the wrong password.\n";
            }
        }
        else if (userType == 3) {
            cout << "Exit the ariline system successfully!\n";
            break;
        }
    }
    saveSeatAssignments(seatingChart, passengerManifest);
    return 0;
}
