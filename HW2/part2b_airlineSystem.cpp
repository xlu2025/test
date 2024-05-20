#include "airlineSystem.h"

//Initialize all seats available
void initializeSeatingChart(vector<vector<Seat> >& seatingChart) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 6; ++j) {
            seatingChart[i][j].isAssigned = false;
        }
    }
}

void loadSeatAssignments(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest) {
    ifstream inFile("seatAssignments.txt");
    if (!inFile) {
        cout << "Error loading seat assignments from file." << endl;
        return;
    }

    // Clear current seating chart and passenger manifest
    for (auto& row : seatingChart) {
        for (auto& seat : row) {
            seat.isAssigned = false;
            seat.passengerName = "";
        }
    }
    passengerManifest.clear();

    string name, seat;
    while (inFile >> name >> seat) {
        int row = stoi(seat.substr(1)) - 1;
        char colChar = seat[0];
        int col = -1;

        // Map seat letters to column indices
        switch (colChar) {
        case 'A': col = 0; break;
        case 'B': col = 1; break;
        case 'D': col = 2; break;
        case 'E': col = 3; break;
        case 'F': col = 4; break;
        case 'H': col = 5; break;
        default:
            cout << "Invalid seat found in file: " << seat << endl;
            continue;
        }

        if (row >= 0 && row < seatingChart.size() && col >= 0 && col < seatingChart[row].size()) {
            seatingChart[row][col].isAssigned = true;
            seatingChart[row][col].passengerName = name;
            passengerManifest.push_back({ name, seat });
        }
        else {
            cout << "Invalid seat found in file: " << seat << endl;
        }
    }

    inFile.close();
    cout << "Seat assignments and passenger manifest loaded successfully." << endl;
}

void saveSeatAssignments(const vector<vector<Seat> >& seatingChart, const vector<Passenger>& passengerManifest) {
    ofstream outFile("seatAssignments.txt");
    if (!outFile) {
        cout << "Error saving seat assignments to file." << endl;
        return;
    }

    // Save passenger manifest to file
    for (const auto& passenger : passengerManifest) {
        outFile << passenger.name << " " << passenger.seat << endl;
    }

    outFile.close();
    cout << "Seat assignments and passenger manifest saved successfully." << endl;
}

void displaySeatingChart(const vector<vector<Seat> >& seatingChart) {
    cout << "The seating is as follows:\n";
    cout << "A B D E F H\n";
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (seatingChart[i][j].isAssigned) {
                cout << "1 ";
            }
            else {
                cout << "O ";
            }
        }
        cout <<endl;
    }
}

void chooseAutomatedSeat(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest, const string& passengerName) {
    
    char seatClass;

    // Prompt the user for the class of seat they want
    cout << "Please type ¡®F¡¯ for first class\nPlease type ¡®B¡¯ for business class\nOthers will be economy class: ";
    cin >> seatClass;

    // Determine the range of rows based on seat class
    int startRow, endRow;
    if (seatClass == 'F' || seatClass == 'f') {
        startRow = 0;
        endRow = 1;
    }
    else if (seatClass == 'B' || seatClass == 'b') {
        startRow = 1;
        endRow = 4;
    }
    else {
        startRow = 4;
        endRow = 12;
    }

    bool seatAssigned = false;
    int row, col;

    // Seed the random number generator
    srand(time(0));

    // Check if there are any available seats in the specified range
    bool availableSeatFound = false;
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (!seatingChart[i][j].isAssigned) {
                availableSeatFound = true;
                break;
            }
        }
        if (availableSeatFound) {
            break;
        }
    }

    // If no available seat found, print the message and return
    if (!availableSeatFound) {
        cout << "No available seats in the chosen class. Next flight leaves in 3 hours." << endl;
        return;
    }
    // Try to find an available seat randomly within the specified range
    while (!seatAssigned) {
        row = startRow + rand() % (endRow - startRow);
        col = rand() % 6;

        if (!seatingChart[row][col].isAssigned) {
            seatingChart[row][col].isAssigned = true;
            seatingChart[row][col].passengerName = passengerName;

            string seatNumber;
            switch (col) {
            case 0: seatNumber = "A" + to_string(row + 1); break;
            case 1: seatNumber = "B" + to_string(row + 1); break;
            case 2: seatNumber = "D" + to_string(row + 1); break;
            case 3: seatNumber = "E" + to_string(row + 1); break;
            case 4: seatNumber = "F" + to_string(row + 1); break;
            case 5: seatNumber = "H" + to_string(row + 1); break;
            }

            Passenger newPassenger = { passengerName, seatNumber };
            passengerManifest.push_back(newPassenger);

            cout << "Seat " << seatNumber << " assigned to " << passengerName << "." << endl;
            seatAssigned = true;
        }
    }

}

void manualSeatSelection(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest, const string& passengerName) {
    char seatClass;
    string seatInput;

    // Display current seating chart
    displaySeatingChart(seatingChart);

    // Prompt the user for the class of seat they want
    cout << "Please type ¡®F¡¯ for first class\nPlease type ¡®B¡¯ for business class\nOthers will be economy class: ";
    cin >> seatClass;

    // Determine the range of rows based on seat class
    int startRow, endRow;
    if (seatClass == 'F' || seatClass == 'f') {
        startRow = 0;
        endRow = 1;
    }
    else if (seatClass == 'B' || seatClass == 'b') {
        startRow = 1;
        endRow = 4;
    }
    else {
        startRow = 4;
        endRow = 12;
    }
    // Check if there are any available seats in the specified range
    bool availableSeatFound = false;
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (!seatingChart[i][j].isAssigned) {
                availableSeatFound = true;
                break;
            }
        }
        if (availableSeatFound) {
            break;
        }
    }

    // If no available seat found, print the message and return
    if (!availableSeatFound) {
        cout << "No available seats in the chosen class. Next flight leaves in 3 hours." << endl;
        return;
    }

    bool seatAssigned = false;

    while (!seatAssigned) {
        cout << "Enter seat number (e.g., A1): ";
        cin >> seatInput;

        if (seatInput.length() < 2 || seatInput.length() > 3) {
            cout << "Invalid seat number format. Please try again." << endl;
            continue;
        }

        int row = seatInput[1] - '1'; // Convert row number to index
        if (seatInput.length() == 3) {
            row = (seatInput[1] - '0') * 10 + (seatInput[2] - '1');
        }

        int col;
        // Convert seat letter to column index
        switch (seatInput[0]) {
        case 'A': col = 0; break;
        case 'B': col = 1; break;
        case 'D': col = 2; break;
        case 'E': col = 3; break;
        case 'F': col = 4; break;
        case 'H': col = 5; break;
        default: cout << "Invalid seat letter." << endl; continue;
        }

        if (row < startRow || row >= endRow || col < 0 || col >= 6) {
            cout << "Seat number out of range for the selected class. Please try again." << endl;
            continue;
        }

        if (seatingChart[row][col].isAssigned) {
            cout << "Seat " << seatInput << " is already taken. Please choose another seat." << endl;
        }
        else {
            seatingChart[row][col].isAssigned = true;
            seatingChart[row][col].passengerName = passengerName;

            Passenger newPassenger = { passengerName, seatInput };
            passengerManifest.push_back(newPassenger);

            cout << "Seat " << seatInput << " assigned to " << passengerName << "." << endl;
            seatAssigned = true;
        }
    }
}

void changeOrCancelSeat(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest) {
    string passengerName;
    string seatInput;
    char action;

    cout << "Enter passenger name: ";
    cin >> passengerName;
    cout << "Enter seat number (e.g., A1): ";
    cin >> seatInput;

    int row = seatInput[1] - '1'; // Convert row number to index
    int col;

    // Convert seat letter to column index
    switch (seatInput[0]) {
    case 'A': col = 0; break;
    case 'B': col = 1; break;
    case 'D': col = 2; break;
    case 'E': col = 3; break;
    case 'F': col = 4; break;
    case 'H': col = 5; break;
    default: cout << "Invalid seat." << endl; return;
    }

    if (row < 0 || row >= 12 || col < 0 || col >= 6) {
        cout << "Invalid seat." << endl;
        return;
    }

    // Verify the seat is assigned to the given passenger
    if (seatingChart[row][col].isAssigned && seatingChart[row][col].passengerName == passengerName) {
        cout << "Enter 'C' to cancel the seat or 'M' to move to another seat: ";
        cin >> action;

        if (action == 'C' || action == 'c') {
            // Cancel the seat
            seatingChart[row][col].isAssigned = false;
            seatingChart[row][col].passengerName = "";

            // Remove passenger from the manifest
            auto it = remove_if(passengerManifest.begin(), passengerManifest.end(),
                [passengerName, seatInput](const Passenger& p) {
                    return p.name == passengerName && p.seat == seatInput;
                });
            passengerManifest.erase(it, passengerManifest.end());

            cout << "Seat " << seatInput << " canceled for " << passengerName << "." << endl;
        }
        else if (action == 'M' || action == 'm') {
            // Move to another seat
            cout << "Enter new seat number (e.g., A1): ";
            string newSeat;
            cin >> newSeat;

            int newRow = newSeat[1] - '1'; // Convert row number to index
            int newCol;

            // Convert seat letter to column index
            switch (newSeat[0]) {
            case 'A': newCol = 0; break;
            case 'B': newCol = 1; break;
            case 'D': newCol = 2; break;
            case 'E': newCol = 3; break;
            case 'F': newCol = 4; break;
            case 'H': newCol = 5; break;
            default: cout << "Invalid seat." << endl; return;
            }

            if (newRow < 0 || newRow >= 12 || newCol < 0 || newCol >= 6) {
                cout << "Invalid seat." << endl;
                return;
            }

            if (seatingChart[newRow][newCol].isAssigned) {
                cout << "Seat " << newSeat << " is already taken." << endl;
                return;
            }

            // Move to the new seat
            seatingChart[newRow][newCol].isAssigned = true;
            seatingChart[newRow][newCol].passengerName = passengerName;

            // Update the old seat
            seatingChart[row][col].isAssigned = false;
            seatingChart[row][col].passengerName = "";

            // Update the passenger manifest
            for (auto& p : passengerManifest) {
                if (p.name == passengerName && p.seat == seatInput) {
                    p.seat = newSeat;
                    break;
                }
            }

            cout << passengerName << " moved to seat " << newSeat << "." <<endl;
        }
        else {
            cout << "Invalid action." << endl;
        }
    }
    else {
        cout << "Seat " << seatInput << " is not assigned to " << passengerName << "." << endl;
    }
}

void printBoardingPass(const vector<Passenger>& passengerManifest) {
    if (passengerManifest.empty()) {
        cout << "No passengers to display." << endl;
        return;
    }

    cout << "Do you want to search by (1) Passenger Name or (2) Seat Number? ";
    int choice;
    cin >> choice;
    cin.ignore(); // Ignore any leftover newline characters in the input buffer

    string query;
    bool found = false;

    switch (choice) {
    case 1: {
        cout << "Enter passenger name: ";
        getline(cin, query);
        for (const auto& passenger : passengerManifest) {
            if (passenger.name == query) {
                found = true;
                printBoardingPassDetails(passenger);
            }
        }
        break;
    }
    case 2: {
        cout << "Enter seat number (e.g., A1): ";
        getline(cin, query);
        for (const auto& passenger : passengerManifest) {
            if (passenger.seat == query) {
                found = true;
                printBoardingPassDetails(passenger);
            }
        }
        break;
    }
    default:
        cout << "Invalid choice." << endl;
        return;
    }

    if (!found) {
        cout << "Seat Unassigned - No Boarding pass available. Try Again!" << endl;
    }
}

void printBoardingPassDetails(const Passenger& passenger) {
    string seatClass;
    int row = stoi(passenger.seat.substr(1)) - 1;

    if (row == 0) {
        seatClass = "First Class";
    }
    else if (row >= 1 && row < 4) {
        seatClass = "Business Class";
    }
    else {
        seatClass = "Economy Class";
    }

    cout << "------------------------------" << endl;
    cout << "BOARDING PASS" << endl;
    cout << "Name: " << passenger.name << endl;
    cout << "Seat: " << passenger.seat << endl;
    cout << "Class: " << seatClass << endl;
    cout << "------------------------------" << endl;
}

// Helper functions to compare passengers
bool compareBySeatNumber(const Passenger& a, const Passenger& b) {
    return a.seat < b.seat;
}

bool compareByName(const Passenger& a, const Passenger& b) {
    return a.name < b.name;
}

void printPassengerManifest(const vector<Passenger>& passengerManifest, const vector<vector<Seat> >& seatingChart) {
    if (passengerManifest.empty()) {
        cout << "No passengers to display." << endl;
        return;
    }

    int choice;
    cout << "Choose sorting option for passenger manifest:" << endl;
    cout << "1. By seat numbers (Ascending)" << endl;
    cout << "2. By seat numbers (Descending)" << endl;
    cout << "3. Alphabetically by name (A-Z)" << endl;
    cout << "4. Alphabetically by name (Z-A)" << endl;
    cout << "5. By class (first, business, economy) sorted by seat numbers" << endl;
    cin >> choice;

    // Create a copy of passenger manifest to sort
    vector<Passenger> sortedManifest = passengerManifest;

    switch (choice) {
    case 1:
        sort(sortedManifest.begin(), sortedManifest.end(), compareBySeatNumber);
        break;
    case 2:
        sort(sortedManifest.begin(), sortedManifest.end(), compareBySeatNumber);
        reverse(sortedManifest.begin(), sortedManifest.end());
        break;
    case 3:
        sort(sortedManifest.begin(), sortedManifest.end(), compareByName);
        break;
    case 4:
        sort(sortedManifest.begin(), sortedManifest.end(), compareByName);
        reverse(sortedManifest.begin(), sortedManifest.end());
        break;
    case 5: {
        // Define a custom comparator for sorting by class and then by seat number
        auto compareByClassAndSeat = [&](const Passenger& a, const Passenger& b) {
            int rowA = stoi(a.seat.substr(1)) - 1;
            int rowB = stoi(b.seat.substr(1)) - 1;

            if (rowA < 1 && rowB >= 1) return true;     // First class before others
            if (rowA >= 1 && rowA < 4 && rowB >= 4) return true; // Business class before economy
            if (rowA >= 4 && rowB >= 4) return compareBySeatNumber(a, b); // Both in economy, compare seat numbers

            return false;
            };
        sort(sortedManifest.begin(), sortedManifest.end(), compareByClassAndSeat);
        break;
    }
    default:
        cout << "Invalid choice. Displaying unsorted manifest." << endl;
        break;
    }

    // Print the sorted manifest
    cout << "Passenger Manifest:" << endl;
    cout << "Name\tSeat" << endl;
    for (const auto& passenger : sortedManifest) {
        cout << passenger.name << "\t" << passenger.seat << endl;
    }
}

void mainMenuPassenger(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest) {
    int choice;
    do {
        cout << "Passenger Menu\n";
        cout << "1. Display seating chart\n2. Choose automated seat\n3. Manually choose seat\n4. Change or cancel seat assignment\n5. Print boarding pass\n6. Quit\n";
        cout << "Please enter your choice:";
        cin >> choice;
        switch (choice) {
        case 1: displaySeatingChart(seatingChart); break;
        case 2: {
            string name;
            cout << "Please enter your name: ";
            cin >> name;
            chooseAutomatedSeat(seatingChart, passengerManifest, name);
            break;
        }
        case 3: {
            string name;
            cout << "Please enter your name: ";
            cin >> name;
            manualSeatSelection(seatingChart, passengerManifest,name);
            break;
        }
        case 4: {
            changeOrCancelSeat(seatingChart, passengerManifest);
            break;
        }
        case 5: {
            printBoardingPass(passengerManifest);
            break;
        }
        case 6: {
            cout << "Exit the passenger menu successfully!\n";
            break;
        }
        default: {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (choice != 6);
}

void mainMenuEmployee(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest) {
    int choice;
    do {
        cout << "1. Display seating chart\n2. Print passenger manifest\n3. Load previous assignments\n4. Save current assignments\n5. Re-assign or cancel seat\n6. Quit\n";
        cout << "Please enter your choice:";
        cin >> choice;
        switch (choice) {
        case 1: displaySeatingChart(seatingChart); break;
        case 2: {
            printPassengerManifest(passengerManifest,seatingChart);
            break;
        }
        case 3: {
            loadSeatAssignments(seatingChart,passengerManifest);
            break;
        }
        case 4: {
            saveSeatAssignments(seatingChart, passengerManifest);
            break;
        }
        case 5: {
            changeOrCancelSeat(seatingChart,passengerManifest);
            break;
        }
        case 6: {
            cout << "Exit the employee menu successfully!\n";
            break;
        }
        default: {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (choice != 6);
}

int getUserType() {
    int userType;
    while (1) {
        cout << "Main Menu\n";
        cout << "1. Passenger\n2. Employee\n3. Exit\n";
        cout << "Please enter your choice:";
        cin >> userType;
        if (1 == userType || 2 == userType||3==userType) { break; }
        else { cout << "Input does not meet the requirements, please re-enter\n"; }
    }
    return userType;
}

//void clearInputBuffer() {
//    cin.clear();
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//}
