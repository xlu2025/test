#ifndef AIRLINESYSTEM_H
#define AIRLINESYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
struct Seat {
    string passengerName;
    bool isAssigned;
};

struct Passenger {
    string name;
    string seat;
};

void initializeSeatingChart(vector<vector<Seat> >& seatingChart);
void loadSeatAssignments(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest);
void saveSeatAssignments(const vector<vector<Seat> >& seatingChart, const vector<Passenger>& passengerManifest);
void displaySeatingChart(const vector<vector<Seat> >& seatingChart);
void chooseAutomatedSeat(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest, const string& passengerName);
void manualSeatSelection(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest, const string& passengerName);
void changeOrCancelSeat(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest);
void printBoardingPass(const vector<Passenger>& passengerManifest);
void printBoardingPassDetails(const Passenger& passenger);
void printPassengerManifest(const vector<Passenger>& passengerManifest, const vector<vector<Seat> >& seatingChart);
void mainMenuPassenger(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest);
void mainMenuEmployee(vector<vector<Seat> >& seatingChart, vector<Passenger>& passengerManifest);
int getUserType();
//void clearInputBuffer();

#endif // AIRLINE_RESERVATION_SYSTEM_H
