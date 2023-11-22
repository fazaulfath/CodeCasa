#include <iostream>
#include <fstream>
#include <iomanip>

class HotelManagementSystem 
{
private:
    struct Customer 
    {
        int roomNumber;
        std::string customerName;
        std::string phoneNumber;
        std::string checkInDate;
        std::string checkOutDate;
        double billAmount;
        std::string roomType;
    };

    static const int MAX_CUSTOMERS = 100;
    Customer customerList[MAX_CUSTOMERS];
    int customerCount = 0;

    void saveDataToFile() 
    {
        std::ofstream file("customer_data.txt");
        if (file.is_open()) 
        {
            for (int i = 0; i < customerCount; ++i) 
            {
                file << customerList[i].roomNumber << ' '
                     << customerList[i].customerName << ' '
                     << customerList[i].phoneNumber << ' '
                     << customerList[i].checkInDate << ' '
                     << customerList[i].checkOutDate << ' '
                     << customerList[i].billAmount << ' '
                     << customerList[i].roomType << '\n';
            }
            file.close();
            std::cout << "Data saved to file successfully.\n";
        } 
        else 
        {
            std::cerr << "Unable to open file for writing.\n";
        }
    }

    void loadDataFromFile() 
    {
        std::ifstream file("customer_data.txt");
        if (file.is_open()) 
        {
            customerCount = 0;
            while (file >> customerList[customerCount].roomNumber
                     >> customerList[customerCount].customerName
                     >> customerList[customerCount].phoneNumber
                     >> customerList[customerCount].checkInDate
                     >> customerList[customerCount].checkOutDate
                     >> customerList[customerCount].billAmount
                     >> customerList[customerCount].roomType && customerCount < MAX_CUSTOMERS) {
                ++customerCount;
            }
            file.close();
            std::cout << "Data loaded from file successfully.\n";
        } 
        else 
        {
            std::cerr << "Unable to open file for reading. Starting with an empty database.\n";
        }
    }

    int calculateNumberOfDays(const std::string& checkInDate, const std::string& checkOutDate) 
    {
        int checkInYear, checkInMonth, checkInDay;                     // Simplified calculation assuming each month has 30 days
        int checkOutYear, checkOutMonth, checkOutDay;
        
        std::istringstream(checkInDate) >> checkInYear >> checkInMonth >> checkInDay;
        std::istringstream(checkOutDate) >> checkOutYear >> checkOutMonth >> checkOutDay;

        int daysInBetween = (checkOutYear - checkInYear) * 12 * 30 + (checkOutMonth - checkInMonth) * 30 + (checkOutDay - checkInDay);

        return std::abs(daysInBetween);
    }

public:
    HotelManagementSystem() 
    {
        loadDataFromFile();
    }

    ~HotelManagementSystem() 
    {
        saveDataToFile();
    }

    void bookRoom(int roomNumber, const std::string& customerName, const std::string& phoneNumber, const std::string& checkInDate, const std::string& checkOutDate) 
    {
        if (customerCount < MAX_CUSTOMERS) 
        {
            Customer& newCustomer = customerList[customerCount];
            newCustomer.roomNumber = roomNumber;
            newCustomer.customerName = customerName;
            newCustomer.phoneNumber = phoneNumber;
            newCustomer.checkInDate = checkInDate;
            newCustomer.checkOutDate = checkOutDate;

            std::cout << "Enter Room Type (e.g., Standard, Deluxe, Suite): ";
            std::cin >> newCustomer.roomType;

            int numberOfDays = calculateNumberOfDays(checkInDate, checkOutDate);           // I am calculating bill based on room type and number of days
            double roomRate = 0.0;

            if (newCustomer.roomType == "Standard")           // Setting the rate based on the room type
            {
                roomRate = 1000.0;
            } 
            else if (newCustomer.roomType == "Deluxe") 
            {
                roomRate = 1500.0;
            } 
            else if (newCustomer.roomType == "Suite") 
            {
                roomRate = 2000.0;
            } 
            else 
            {
                std::cerr << "Invalid room type. Using default rate.\n";
                roomRate = 1000.0; // Default rate for unknown room type
            }

            newCustomer.billAmount = numberOfDays * roomRate;

            ++customerCount;
            std::cout << "Room booked successfully.\n";
            saveDataToFile(); 
        } 
        else 
        {
            std::cout << "Cannot book room. Maximum capacity reached.\n";
        }
    }

    void searchCustomer(const std::string& customerName) 
    {
        bool found = false;
        for (int i = 0; i < customerCount; ++i) 
        {
            if (customerList[i].customerName == customerName) 
            {
                std::cout << "Customer found:\n";
                std::cout << "Room Number: " << customerList[i].roomNumber << '\n';
                std::cout << "Check-in Date: " << customerList[i].checkInDate << '\n';
                std::cout << "Check-out Date: " << customerList[i].checkOutDate << '\n';
                std::cout << "Room Type: " << customerList[i].roomType << '\n';
                std::cout << "Total Bill: INR. " << std::fixed << std::setprecision(2) << customerList[i].billAmount << '\n';
                found = true;
                break;
            }
        }
        if (!found) 
        {
            std::cout << "Customer not found.\n";
        }
    }

    void viewAllottedRooms() 
    {
        std::cout << "Allotted Rooms:\n";
        for (int i = 0; i < customerCount; ++i) 
        {
            std::cout << "Room Number: " << customerList[i].roomNumber << '\n';
            std::cout << "Customer Name: " << customerList[i].customerName << '\n';
            std::cout << "Check-in Date: " << customerList[i].checkInDate << '\n';
            std::cout << "Check-out Date: " << customerList[i].checkOutDate << '\n';
            std::cout << "Room Type: " << customerList[i].roomType << '\n';
            std::cout << "Total Bill: INR. " << std::fixed << std::setprecision(2) << customerList[i].billAmount << "\n\n";
        }
    }

    void modifyCustomerRecord(int roomNumber, const std::string& newCheckOutDate) 
    {
        for (int i = 0; i < customerCount; ++i) 
        {
            if (customerList[i].roomNumber == roomNumber) 
            {
                customerList[i].checkOutDate = newCheckOutDate;
                std::cout << "Customer record modified successfully.\n";
                saveDataToFile(); 
                return;
            }
        }
        std::cout << "Customer not found.\n";
    }

    void deleteCustomerRecord(int roomNumber) 
    {
        for (int i = 0; i < customerCount; ++i) 
        {
            if (customerList[i].roomNumber == roomNumber) 
            {
                for (int j = i; j < customerCount - 1; ++j) 
                {
                    customerList[j] = customerList[j + 1];
                }
                --customerCount;
                std::cout << "Customer record deleted successfully.\n";
                saveDataToFile(); 
                return;
            }
        }
        std::cout << "Customer not found.\n";
    }

    void displayTotalBill(const std::string& customerName) 
    {
        for (int i = 0; i < customerCount; ++i) {
            if (customerList[i].customerName == customerName) 
            {
                std::cout << "Total Bill for " << customerName << ": INR." << std::fixed << std::setprecision(2) << customerList[i].billAmount << '\n';
                return;
            }
        }
        std::cout << "Customer not found.\n";
    }
};

int main() 
{
    HotelManagementSystem hotelSystem;

    int choice;
    do 
    {
        std::cout << "\n===== Hotel Management System =====\n";
        std::cout << "1. Book a Room\n";
        std::cout << "2. Search for Customer\n";
        std::cout << "3. View Allotted Rooms\n";
        std::cout << "4. Modify Customer Record\n";
        std::cout << "5. Delete Customer Record\n";
        std::cout << "6. Display Total Bill\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                int roomNumber;
                std::string customerName, phoneNumber, checkInDate, checkOutDate;
                std::cout << "Enter Room Number: ";
                std::cin >> roomNumber;
                std::cout << "Enter Customer Name: ";
                std::cin.ignore(); // Clear the input buffer
                std::getline(std::cin, customerName);
                std::cout << "Enter Phone Number: ";
                std::cin >> phoneNumber;
                std::cout << "Enter Check-in Date (YYYY-MM-DD): ";
                std::cin >> checkInDate;
                std::cout << "Enter Check-out Date (YYYY-MM-DD): ";
                std::cin >> checkOutDate;

                hotelSystem.bookRoom(roomNumber, customerName, phoneNumber, checkInDate, checkOutDate);
                break;
            }
            case 2: 
            {
                std::string searchName;
                std::cout << "Enter Customer Name to Search: ";
                std::cin.ignore(); 
                std::getline(std::cin, searchName);

                hotelSystem.searchCustomer(searchName);
                break;
            }
            case 3:
                hotelSystem.viewAllottedRooms();
                break;
            case 4: 
            {
                int modifyRoomNumber;
                std::string newCheckOutDate;
                std::cout << "Enter Room Number to Modify: ";
                std::cin >> modifyRoomNumber;
                std::cout << "Enter New Check-out Date (YYYY-MM-DD): ";
                std::cin >> newCheckOutDate;

                hotelSystem.modifyCustomerRecord(modifyRoomNumber, newCheckOutDate);
                break;
            }
            case 5: 
            {
                int deleteRoomNumber;
                std::cout << "Enter Room Number to Delete: ";
                std::cin >> deleteRoomNumber;

                hotelSystem.deleteCustomerRecord(deleteRoomNumber);
                break;
            }
            case 6: 
            {
                std::string customerName;
                std::cout << "Enter Customer Name to Display Total Bill: ";
                std::cin.ignore(); 
                std::getline(std::cin, customerName);

                hotelSystem.displayTotalBill(customerName);
                break;
            }
            case 7:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);

    return 0;
}
