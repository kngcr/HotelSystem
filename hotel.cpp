/*
* Fall 2023, ICS 212, Final Project: Hotel Management System
* Group Members: Rolando, Ciara, Sierra, Jason, Ashton, Ethan
* This code is a C++ program that was collaboratively written by all group members. Specifications for who completed which parts of the code are commented throughout the code along with short descriptions for what certain lines of code should be.
* The purpose of this code is to implement a basic hotel management system that allows users to add new rooms with features and search available rooms, check in and check out, search customer, and generate guest reports. The output of this solution should be nearly identical to the sample output provided in the PDF on Laulima. Our group's intention was to replicate the expectations for our solution.
* There are some bugs or issues present with the check out function. We are currently working on fixing these issues but as of 12/8/2023, the validation for the phone number can sometimes fail even though a valid number is entered. Additionally, the program terminates with 'std::bad_alloc' thrown at the end of the check out function after line 359 is called to print the total payable amount "/only". I, @Ciara, believe the issue is happening due to how the following lines 361 to 366 may be overloading the compiler. As such, we are unable to tell if the customer is deleted from the customers vector after check out or if the customer is still in the vector because the program is terminating with 'std::bad_alloc'.

UPDATE: 12/9/2023 - checkOut function fixed, phone number validation issue fixed. @Rolando

*/

#include <stdio.h>
#include <iostream>
#include <vector> // @Rolando modified the code for vectors instead of arrays, taking inspiration from @Ashton's vectors
#include <string>
#include <sstream> // needed to check if user input is valid - @Ciara

using namespace std;

/* @Ashton finished Customer class */
//////////////////////////////////////////////Beginning of Customer Class
class Customer {
  public:
    string name;
    string address;
    string phoneNumber;
    string advancePaid;
    string bookingID; // it is only used once in checkIn
    string checkInDate; 
    string checkOutDate;
    int roomCheckedInto; //used to link a room object and a customer object (ie. if(rooms[i].getRoomNumber() == customers[i].roomCheckedInto) ) - @Rolando

    Customer() {} // default contructor

    Customer(string n, string id, string addr, string phone, string ap, string checkin, string checkout) {
      name = n;
      bookingID = id;
      address = addr;
      phoneNumber = phone;
      advancePaid = ap;
      checkInDate = checkin;
      checkOutDate = checkout;
    }

    // Displays Customers details - @Rolando
    void displayCustomerDetails() {
      cout << "Customer First Name: " << name << endl;
      cout << "Room Number: " << roomCheckedInto << endl;
      cout << "Address (city only): " << address << endl;
      cout << "Phone: " << phoneNumber << endl;
    }

    // setters - @Sierra
    void setName(string n) { name = n; }
    void setAddress(string a) { address = a; }
    void setPhone(string p) { phoneNumber = p; }
    void setAdvancePaid(string ap) { advancePaid = ap; }
    void setRoomCheckedInto(int roomNum){roomCheckedInto = roomNum; }

    // getters - @Sierra
    string getName() { return name; }
    string getAddress() { return address; }
    string getPhone() { return phoneNumber; }
    string getAdvancePaid() { return advancePaid; }
    int getRoomCheckedInto() { return roomCheckedInto; }
};
//////////////////////////////////////////////end of Customer Class

/* @Ethan finished Room class */
////////////////////////////////////////////////begining of Room Class
class Room {
  protected:
    string type, comfort, size;
    int roomNum, dailyRate;
    bool available;

  public:
    Room() {} // default constructor - @Ciara

    // @Ashton's constructor, @Ciara changed dailyRate
    Room(int number, string ac, string c, string s, int dr) {
        roomNum = number;
        available = true;
        type = ac;
        comfort = c;
        size = s;
        dailyRate = dr;
        //setDailyRate(ac, c, s);
    }

    // setters - @Ethan
    void setRoomNumber(int rn) { roomNum = rn; }
    void setType(string t) { type = t; }
    void setComfort(string c) { comfort = c; }
    void setSize(string s) { size = s; }
    void setAvailability(bool a) { available = a; }
    void setDailyRate(int dr){
        dailyRate = dr;
    }
    // getters - @Ethan
    string getType() { return type; }
    string getComfort() { return comfort; }
    string getSize() { return size; }
    int getDailyRate() { return dailyRate; }
    int getRoomNumber() { return roomNum; }
    bool getAvailability() { return available; }
};
//////////////////////////////////////////////end of Room Class

/* @everyone in our group worked on various methods of this class */
//////////////////////////////////////////////Begining of HotelManagement Class
class HotelManagement : public Room {
  public:
    HotelManagement() {} // default constructor

    // @Ethan finished addRoom function
    void addRoom(vector<Room>& rooms) {
      int roomNum, DailyRate, num;
      string inputType, inputComfort, inputSize, inputDailyRate;
      cout << "\nEnter Room Number: ";
      cin >> roomNum;
      cin.ignore();
      for (int i = 0; i < rooms.size(); i++) { //main loop that starts at begining  
           //check each if room number already exists
              if (rooms[i].getRoomNumber() == roomNum) {
                  cout << "Room Number Already Exists";
                  return; //if exists exit function without adding room
              }
          }
      cout << "\nType AC/No AC (A/N) : ";
      getline(cin,inputType);
      if (inputType != "A" && inputType != "N") {
        cout << "\nInvalid Input.\n";
        return;
      }
      cout << "\nType Comfort (S/N) : ";
      getline(cin,inputComfort);
      if (inputComfort != "S" && inputComfort != "N") {
        cout << "\nInvalid Input.\n";
        return;
      }
      cout << "\nType Size (B/S) : ";
      getline(cin, inputSize);
      if (inputSize != "B" && inputSize != "S") {
        cout << "\nInvalid Input.\n";
        return;
      }
      // @Ciara - added this because it was missing
      cout << "\nDaily Rate: ";
      cin >> inputDailyRate;
      istringstream dr(inputDailyRate);
      if (!(dr >> num)) {
        cout << "Invalid input. Please enter an integer." << endl;
        return;
      }
      DailyRate = stoi(inputDailyRate);
      cout << "Room successfully added!\n";
      Room newRoom(roomNum, inputType, inputComfort, inputSize, DailyRate); //new room object
      newRoom.setAvailability(true);
      rooms.push_back(newRoom); //add new room object to end of room vector
    }

    void deleteRoom(vector<Room>& rooms){
      int roomNum;
      cout << "Enter room number to delete: ";
      cin >> roomNum;
      cin.ignore();
      for(int i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomNumber() == roomNum){
          cout << "\nRoom Details to Delete\n\n";
          cout << "Room number: " << rooms[i].getRoomNumber() << "\n";
          cout << "Room with AC/No AC (A/N): " << rooms[i].getType() << "\n";
          cout << "Type of Comfort (S/N): " << rooms[i].getComfort() << "\n";
          cout << "Room Size (B/S): " << rooms[i].getSize() << "\n";
          cout << "Daily Rate: " << rooms[i].getDailyRate() << "\n";

          rooms.erase(rooms.begin()+i);
          cout << "Room Deleted Successfully!";
          return;
        }
      }
      cout << "Room Not Found";

    }

    // @Ethan finished search room funcion
    void searchRoom(vector<Room>& rooms) {
      int roomNum;
      cin.ignore();
      cout << "\nEnter Room Number: ";
      cin >> roomNum;
      cin.ignore();

      bool roomFound = false;  // Flag to check if the room is found
      for (int i = 0; i < rooms.size(); i++) {
          if (rooms[i].getRoomNumber() == roomNum) {
              roomFound = true;  // Set the flag to true if the room is found
              cout << "Room Details" << endl;
              if (rooms[i].getAvailability()) {
                  cout << "\nRoom is available" << endl;
              } else {
                  cout << "\nRoom is not available" << endl;
              }

              cout << "Room Number: " << rooms[i].getRoomNumber() << endl;
              cout << "Type AC/No AC (A/N) " << rooms[i].getType() << endl;
              cout << "Comfort (S/N) " << rooms[i].getComfort() << endl;
              cout << "Size (B/S) " << rooms[i].getSize() << endl;
              cout << "Daily Rate: " << rooms[i].getDailyRate() << endl;
              break;
          }
      }

      // Print the "not found" message only if the room is not found
      if (!roomFound) {
          cout << "\nRoom does not exist, try again." << endl;
      }
  } 
    // @Sierra's code
    bool isRoomAvailable(vector<Room>& rooms, int roomNum) {
      int available = 0;
        for (int i = 0; i < rooms.size(); i++) {
          if (rooms[i].getRoomNumber() == roomNum) {
            if (rooms[i].getAvailability()) {
            
              available = 1;
            }
          }
        }
          if (available == 0) {
            //nothing but im afraid to delete this if statement XD
          }   
          return available;
    }
    // @Ciara's getter, it returns the total number of available rooms that exist
    int getAvailableRooms(vector<Room>& rooms){
      int roomCount = 0;
      for(int i = 0; i < rooms.size(); i++){
        if(rooms[i].getAvailability() == true){
          roomCount++; // counts number of available rooms
      }
    }
      return roomCount;
    }
    // @Ciara's getter, it returns the list of available room numbers
    string getAvailableRoomNumbers(vector<Room>& rooms){
        string roomNum;
        int room;
        for(int i = 0; i < rooms.size(); i++){
            room = rooms[i].getRoomNumber();
            if(rooms[i].getAvailability() == true){
                roomNum += to_string(rooms[i].getRoomNumber()) + " ";
            }
        }
        return roomNum;
    }
    // @Rolando's part
    void printGuestSummary(vector<Customer>& customers) {
      for (int i = 0; i < customers.size(); i++) {
        customers[i].displayCustomerDetails();
        cout << "\n";
      }

      // @Ciara - I added this if statement in case no guests are on the list
      if(customers.size() == 0){
        cout << "There are no guests.";
      }
      cout << "\n";
    }
    // @Sierra's part, @Ciara added in code to verify if user input is valid using istringstream
    void checkInRoom(vector<Room>& rooms, vector<Customer>& customers) {
      string name, address, phoneNumber, advancePaid, bookingID, checkInDate, checkOutDate, roomNum,
      token; // @Ciara - used to verify if string
      int roomNumber, 
      num; // @Ciara - used to verify if int

      cout << "\nEnter Room number : ";
      cin >> roomNum;
      istringstream rn(roomNum);
      if (!(rn >> num)) {
        cout << "Invalid input. Please enter an integer." << endl;
        return;
      }
      roomNumber = stoi(roomNum);
      if (!isRoomAvailable(rooms, roomNumber)) {
          cout << "\nRoom not available or does not exist." << endl;
          return;
      }

      cout << "Enter Customer Name (First name): ";
      cin >> name;
      istringstream n(name);
      if (n >> num) {
        cout << "Invalid input. Please enter a string." << endl;
        return;
      }

      cout << "Enter Address (city only): ";
      cin >> address;
      istringstream a(address);
      if (a >> num) {
        cout << "Invalid input. Please enter a string." << endl;
        return;
      }

      cout << "Enter Phone: ";
      cin >> phoneNumber;
      for (char ch : phoneNumber) {
        if (!std::isdigit(ch)) {
          cout << "Invalid input. Please enter an integer." << endl;
            return;
        }
    }
      /*istringstream pn(phoneNumber); // removed because this caused errors when using a phonenumber with zero's in it
      
      if (!(pn >> num)) {
        cout << "Invalid input. Please enter an integer." << endl;
        return;
      }
      */
      cout << "Check-in date: ";
      cin >> checkInDate;
      istringstream cid(checkInDate);
      if (!(cid >> token)) {
        cout << "Invalid input. Please enter a string." << endl;
        return;
      }

      cout << "Check-out date: ";
      cin >> checkOutDate;
      istringstream cod(checkOutDate);
      if (!(cod >> token)) {
        cout << "Invalid input. Please enter a string." << endl;
        return;
      }

      cout << "Enter Advance Payment: ";
      cin >> advancePaid;
      istringstream ap(advancePaid);
      if (!(ap >> num)) {
        cout << "Invalid input. Please enter an integer." << endl;
        return;
      }

      cout << "\nCustomer Checked-In Successfully..\n";
      for(int i = 0; i < rooms.size(); i++){
          if(rooms[i].getRoomNumber() == roomNumber){
              rooms[i].setAvailability(false); //if guest is checked in to this room, make it unavailable.
          }
      }
      Customer newCustomer(name, bookingID, address, phoneNumber, advancePaid, checkInDate, checkOutDate);
      newCustomer.setRoomCheckedInto(roomNumber);
      customers.push_back(newCustomer); // adds new customer object to customers vector
  } // END of check in method

  // @Jason's part, @Ciara fixed the code
    void checkOutRoom(vector<Room>& rooms, vector<Customer>& customers) {
      string totalAmount;
      int roomNum,numDays, advancePaidInt, totalAmountInt, finalAmountInt; // @Ciara - I added the finalAmountInt
      cout << "\nEnter Room Number: ";
      cin >> roomNum;
      bool roomExists = false;
      for(int j = 0; j < rooms.size(); j++){
        if(rooms[j].getRoomNumber() == roomNum){
          roomExists = true;
            if(rooms[j].getAvailability() == true){
                cout << "Room is available for check-in."; // if someone tries to check out of a room that is not checked in
                return;
            }
        }
      }
      if(!roomExists){
          cout << "No room number found.\n";
          return;
        } 
      cout << "\nEnter Number of Days: ";
      cin >> numDays;
      for(int j = 0; j < rooms.size(); j++){
        if(rooms[j].getRoomNumber() == roomNum){
            rooms[j].setAvailability(true); // sets room to available
            dailyRate = rooms[j].getDailyRate();
            // not deleting room data because the room can be cleaned up and available for new customers
        }
      }
      cout << "\n\n######## Checkout Details ########\n\n";
      for(int i = 0; i < customers.size(); i++) {
        if(customers[i].getRoomCheckedInto() == roomNum) {
          cout << "Customer Name: " << customers[i].getName() << endl;
          cout << "Room Number: " << roomNum << endl;
          cout << "Address: " << customers[i].getAddress() << endl;
          cout << "Phone: " << customers[i].getPhone() << endl;
          totalAmountInt = dailyRate * numDays; // @Ciara - I changed this, lmk if it works
          cout << "Total Amount Due: " << totalAmountInt << endl;
          cout << "Advance Paid: " << customers[i].advancePaid << endl;
          advancePaidInt = std::stoi(customers[i].advancePaid);
          finalAmountInt = totalAmountInt - advancePaidInt; // @Ciara - I changed it to the int form of final amount, in case errors happen with calculations using string = int - int , so it's int = int - int instead
          cout << "*** Total Payable: " << finalAmountInt << "/ only" << endl; // prints string
          //@Ciara - I added the rest of the code in this loop to remove customer data
          customers.erase(customers.begin()+i); // erase customer info at the element 0+i
          
    
        }
      }
   }

    // @Ciara rewrote the cout of @Rolando's code, it was in the wrong format based on the pdf
    void searchCustomer(vector<Customer>& customers){
      string searchName;
       cout << "Enter Customer Name: ";
          cin >> searchName;
          bool guestExists = false;
          for(int i = 0; i < customers.size(); i++){
            if(customers[i].getName() == searchName){
              guestExists = true;
              cout << "\nCustomer Name: " << customers[i].getName() << "\nRoom Number: " << customers[i].getRoomCheckedInto() << endl;

            }
          }
          if(!guestExists){
            cout << "Guest does not exist\n";
            return;
          }
    }
};
//////////////////////////////////////////////end of HotelManagement Class

//////////////////////////////////////////////Begining of Main
/* MAIN - @Ciara rewrote the broken main, @Rolando modified it for vectors */
int main() {
  // initialize the class object
  HotelManagement Hotel;
  vector<Customer> customers = {};
  vector<Room> rooms = {};
  string availableRooms; // @Ciara - I added this to check for the room numbers for available rooms

  int switchInput; // user inputted value variable for the switch statement

  while (true) {
  // switch case for options 1-7
    cout << "---------######### Hotel Management #########---------";
    cout << "\n"
         << "1. Manage Rooms\n"
         << "2. Check-in Room\n"
         << "3. Available Rooms\n"
         << "4. Search Customer\n"
         << "5. Check-Out Room\n"
         << "6. Guest Summary Report\n"
         << "7. Exit\n"
         << "\n"
         << "Enter Option: ";
    cin >> switchInput;
    // start of outer switch case
    switch(switchInput) {
    // option 1: Manage Rooms - @Ciara rewrote this
      case 1:
        while (true) {
          cout << "\n### Manage Rooms ###\n"
               << "1. Add Room\n"
               << "2. Search Room\n"
               << "3. Delete Room\n"
               << "4. Back to Main Menu\n"
               << "\nEnter Option: ";
          cin >> switchInput;
          // start of inner switch case
          switch (switchInput) {
            case 1:
              
              Hotel.addRoom(rooms);
              continue;
            case 2:
              
              Hotel.searchRoom(rooms);
              continue;
            case 3:

              Hotel.deleteRoom(rooms);
              continue; 
            case 4:

              // Back to main menu
              break;  // breaks out of inner switch case
            default:
              cout << "Invalid Input";
              break;
            } // end of inner switch case
          break; // breaks out of infinite while loop
        }
        break; // end of case 1

    // option 2: Check-In Room - @Sierra
      case 2:
        Hotel.checkInRoom(rooms, customers);
        break;

    // option 3: Available Rooms - @Ciara
      case 3:
        cout << "There are " << Hotel.getAvailableRooms(rooms) << " available rooms." << endl;
        if(!(Hotel.getAvailableRooms(rooms)==0)){
            cout << "The available room numbers are ";
            availableRooms = Hotel.getAvailableRoomNumbers(rooms);
            cout << availableRooms << endl;
        }
        cout << "\n" << endl;
        break;

    // option 4: Search Customer - @Rolando
      case 4:
        Hotel.searchCustomer(customers);
        break;

    // option 5: Check-Out Room - @Jason
      case 5:
        Hotel.checkOutRoom(rooms, customers);
        break;

    // option 6: Guest Summary Report - @Rolando
      case 6:
        cout << "\n"; // added to format output based on pdf
        Hotel.printGuestSummary(customers);
        break;

    // option 7: Exit
      case 7:
        cout << "Thanks for using this sick nasty software bro gg no re.\n"; // unique program exit message, leave it.
        exit(1);
        break;

    } // end of outer switch case
  }
  return 0;
}
//////////////////////////////////////////////end of Main
