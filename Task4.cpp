#include <iostream>
using namespace std;

class WaitingRoom {
    int patients[100];
    int front;
    int rear;
    int count;

public:
    WaitingRoom() {
        front = 0;
        rear = -1;
        count = 0;
    }

    // Register a patient using the ID entered by the user
    void RegisterPatient(int id) {
        if (count == 100) {
            cout << "Waiting room is full.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            int index = (front + i) % 100;
            if (patients[index] == id) {
                cout << "That patient ID is already waiting.\n";
                return;
            }
        }

        rear = (rear + 1) % 100;
        patients[rear] = id;
        count++;

        cout << "Patient " << id << " registered.\n";
    }

    // Serve the patient who registered first
    void ServePatient() {
        if (count == 0) {
            cout << "No patients waiting.\n";
            return;
        }

        cout << "Patient " << patients[front] << " is being served.\n";
        front = (front + 1) % 100;
        count--;
    }

    // Cancel all waiting patients
    void CancelAll() {
        front = 0;
        rear = -1;
        count = 0;

        cout << "All waiting appointments cancelled.\n";
    }

    // Check whether the doctor can go home
    bool CanDoctorGoHome() {
        return count == 0;
    }

    // Display waiting patient IDs in sorted order
    void ShowAllPatient() {
        if (count == 0) {
            cout << "No patients waiting.\n";
            return;
        }

        cout << "Waiting patient IDs: ";

        // IDs are assigned in increasing order and served FIFO
        for (int i = 0; i < count; i++) {
            int index = (front + i) % 100;
            cout << patients[index] << " ";
        }

        cout << endl;
    }
};

int main() {
    WaitingRoom room;
    int choice;

    do {
        cout << "\n--- Waiting Room Management ---\n";
        cout << "1. Register Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Cancel All\n";
        cout << "4. Can Doctor Go Home?\n";
        cout << "5. Show All Patients\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cerr << "Invalid input. Please enter a menu number.\n";
            return 1;
        }

        switch (choice) {
            case 1: {
                int patientID;
                cout << "Enter patient ID: ";
                if (!(cin >> patientID)) {
                    cerr << "Invalid patient ID.\n";
                    return 1;
                }
                room.RegisterPatient(patientID);
                break;
            }

            case 2:
                room.ServePatient();
                break;

            case 3:
                room.CancelAll();
                break;

            case 4:
                if (room.CanDoctorGoHome())
                    cout << "Yes, the doctor can go home.\n";
                else
                    cout << "No, patients are still waiting.\n";
                break;

            case 5:
                room.ShowAllPatient();
                break;

            case 0:
                cout << "Program ended.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
