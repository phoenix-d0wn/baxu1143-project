#include <iostream>
#include <string>
#include <limits> // FOR PREVENTING INFINITE LOOPS ON INVALID INPUTS

using namespace std;

// ==========================================
// CLASS DEFINITION
// ==========================================

class Locker {
private:
    int lockerId;
    string memberName;
    string duration;
    bool isReserved;

public:
    //  Constructor
    Locker() {
        lockerId = 0;
        memberName = "";
        duration = "";
        isReserved = false;
    }

    void setLockerDetails(int id, string name, string dur) {
        lockerId = id;
        memberName = name;
        duration = dur;
        isReserved = true;
    }

    int getLockerId() { return lockerId; }
    string getMemberName() { return memberName; }
    string getDuration() { return duration; }
    bool getReservationStatus() { return isReserved; }
};

// ==========================================
// FUNCTION DECLARATIONS 
// ==========================================

void addLockerReservation(Locker lockers[], int& currentCount, int maxCapacity);
void displayLockers(Locker lockers[], int currentCount);
void sortLockerId(Locker locker[], const int& low, const int& high);
int partition(Locker locker[], const int& low, const int& high);
int getValidatedInteger();
void searchReservation(Locker lockers[], int currentCount);

// ==========================================
// MAIN FUNCTION
// ==========================================

int main() {
    const int MAX_LOCKERS = 50;
    Locker gymLockers[MAX_LOCKERS]; // Array
    int currentReservations = 0; //  current  reserved lockers
    int choice;

    do {
        // System Menu List 
        cout << "\n=====================================" << endl;
        cout << "  GYM LOCKER RESERVATION SYSTEM      " << endl;
        cout << "=====================================" << endl;
        cout << "1. Add Locker Reservation" << endl;
        cout << "2. Display Locker Reservations" << endl; 
        cout << "3. Sort Reservations" << endl;
        cout << "4. Search Reservations" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";

        // Verify menu choice input
        choice = getValidatedInteger();

        switch (choice) {
        case 1:
            addLockerReservation(gymLockers, currentReservations, MAX_LOCKERS);
            break;
        case 2:
            displayLockers(gymLockers, currentReservations);
            break;
        case 3:
            sortLockerId(gymLockers, 0, currentReservations - 1);
            // Tambah mesej berjaya supaya user tahu proses sort telah selesai
            cout << "\nSuccess: Lockers have been sorted by ID (Ascending)." << endl;
            break;
        case 4:
            searchReservation(gymLockers, currentReservations);
            break;
        case 5:
            cout << "\nExiting system. Thank you!" << endl;
            break;
        default:
            cout << "\nInvalid choice! Please enter a number between 1 and 5." << endl;
        }
    } while (choice != 5);

    return 0;
}

// ==========================================
// FUNCTION DEFINITIONS
// ==========================================

int getValidatedInteger() {
    int input;
    while (true) {
        cin >> input;

        // Check if the input is valid (e.g., user typed a letter/symbol)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the bad input completely
            cout << "Invalid input! Please enter a valid number: ";
        }
        else {
            // Check if there is extra trailing garbage after the number (e.g., "123xyz")
            if (cin.peek() != '\n' && cin.peek() != EOF) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the rest of the line
                cout << "Invalid format! Please enter a pure number: ";
                continue;
            }
            return input;
        }
    }
}

/**
 * Made by MUHAMMAD AIZAT AQMAL BIN ZAINUDDIN
 * Function: addLockerReservation
 * user input to create a new gym locker reservation.
 * Prevents array overflow, duplicate IDs, and cleans input streams.
 */
void addLockerReservation(Locker lockers[], int& currentCount, int maxCapacity) {
    // PREVENT OVERFLOW:
    if (currentCount >= maxCapacity) {
        cout << "\nError: All gym lockers are fully reserved! (Capacity reached: " << maxCapacity << ")" << endl;
        return;
    }

    int id;
    string name;
    string dur;
    bool isTaken; // Pembolehubah untuk semak status ID

    cout << "\n--- ADD NEW LOCKER RESERVATION ---" << endl;
    
    // Semakan Duplicate ID menggunakan gelung (loop)
    do {
        isTaken = false; // Reset status setiap kali loop
        cout << "Enter Locker ID Number (numeric only): ";
        id = getValidatedInteger(); // Safely gets integer and clears stream up to the newline

        // Loop untuk semak setiap locker yang dah ada
        for (int i = 0; i < currentCount; i++) {
            if (lockers[i].getLockerId() == id) {
                cout << "Error: Locker ID " << id << " is already taken! Please choose another ID.\n" << endl;
                isTaken = true; // Tandakan ID ini dah diambil
                break; // Berhenti semak dan ulang semula do-while
            }
        }
    } while (isTaken); // Akan ulang minta ID selagi ID itu 'isTaken'

    cin.ignore(); // Clear the \n left by cin >> input before using getline

    cout << "Enter Member Full Name: ";
    getline(cin, name);

    cout << "Enter Rental Duration (e.g., 1 Month, 1 Week): ";
    getline(cin, dur);

    // Save data into the current available index of the object array
    lockers[currentCount].setLockerDetails(id, name, dur);

    // Increment the counter safely
    currentCount++;

    cout << "\nSuccess: Locker reservation added successfully!" << endl;
}

/**
 * Made by (B152510010) ARIFF SANUSI
 * Function: sortLockerId
 * Sorts the list of lockers by Locker ID in ASCENDING order
 * Uses the Quick Sort technique
 */
void sortLockerId(Locker locker[], const int& low, const int& high) {

    if (low < high) {

        int pivotIndex = partition(locker, low, high);
        sortLockerId(locker, low, pivotIndex - 1);
        sortLockerId(locker, pivotIndex + 1, high);
    }
}

// helper function for sortLockerId()
int partition(Locker locker[], const int& low, const int& high) {

    Locker pivot = locker[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (locker[j].getLockerId() < pivot.getLockerId()) {

            i++;

            // swap elements in index i & j
            Locker temp = locker[i];
            locker[i] = locker[j];
            locker[j] = temp;
        }
    }

    // move the last element to index i+1
    Locker temp = locker[i + 1];
    locker[i + 1] = locker[high];
    locker[high] = temp;

    return i + 1;
}

/**
 * Made by (B152510061) MUHAMMAD ADIB DARWISY BIN SHARIZUL
 * Function: displayLockers
 * Displays all active locker reservations.
 * If no lockers are reserved, an appropriate message is shown.
 */

void displayLockers(Locker lockers[], int currentCount) {
    // Check if the array is empty 
    if (currentCount == 0) {
        cout << "\n[Notice] No locker reservations found in the system." << endl;
        return;
    }

    cout << "\n--- LIST OF CURRENT LOCKER RESERVATIONS ---" << endl;
    cout << "Total Active Reservations: " << currentCount << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int i = 0; i < currentCount; i++) {
        cout << "Reservation #" << (i + 1) << endl;
        cout << "Locker ID       : " << lockers[i].getLockerId() << endl;
        cout << "Member Name     : " << lockers[i].getMemberName() << endl;
        cout << "Rental Duration : " << lockers[i].getDuration() << endl;
        cout << "--------------------------------------------------------" << endl;
    }
}

/**
 * Made by (B152510138) MUHAMMAD DARWISY BIN SHAMSOLANOR
 * Function: searchReservation
 * Searches for a specific locker reservation by Locker ID.
 * Use Linear Search technique to find the locker.
 * If no lockers are matched, an appropriate message is shown.
 */

void searchReservation(Locker lockers[], int currentCount) {
    if (currentCount == 0) {
        cout << "\n[Notice] No locker reservations found in the system." << endl;
        return;
    }
    int lockerId;
    bool found = false;

    cout << "\nEnter Locker ID to search: ";
    lockerId = getValidatedInteger();

    for (int i = 0; i < currentCount; i++) {
        if (lockers[i].getLockerId() == lockerId) {
            cout << "\n--- LOCKER RESERVATION FOUND ---" << endl;
            cout << "Locker ID       : " << lockers[i].getLockerId() << endl;
            cout << "Member Name     : " << lockers[i].getMemberName() << endl;
            cout << "Rental Duration : " << lockers[i].getDuration() << endl;
            found = true;
            break; // Exit loop after finding the first match
        }
    }
    if (!found) {
        cout << "\n[Notice] No reservation found for Locker ID: " << lockerId << endl;
    }
}