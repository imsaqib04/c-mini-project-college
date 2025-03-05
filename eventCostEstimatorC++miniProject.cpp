#include <iostream>
#include <iomanip>  // For formatting output
#include <string>
#include <limits>   // For input validation
#include <ctime>    // For date and time handling

using namespace std;

// Function to get valid input for choices within a range
int getValidChoice(int min, int max, const string& prompt) {
    int choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        if (!cin.fail() && choice >= min && choice <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
            return choice; // Valid input
        }
        cin.clear();  // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        cout << "Invalid input. Please try again.\n";
    }
}

// Function to get valid customer name
string getValidCustomerName() {
    string name;
    while (true) {
        cout << "Please enter your name (letters only): ";
        getline(cin, name);
        
        bool valid = true;
        for (char c : name) {
            if (!isalpha(c) && c != ' ') { // Check if each character is a letter or space
                valid = false;
                break;
            }
        }

        if (valid && !name.empty()) {
            return name; // Valid input
        } else {
            cout << "Invalid input. Please enter letters only.\n";
        }
    }
}

// Function to get venue selection
double getVenueCost() {
    cout << "\n-- Select a Venue for Your Event --\n";
    cout << "1. Banquet Hall (Rupees 50,000)\n";
    cout << "2. Outdoor Garden (Rupees 30,000)\n";
    cout << "3. Conference Room (Rupees 20,000)\n";

    int choice = getValidChoice(1, 3, "Please enter the number of your choice: ");
    if (choice == 1) return 50000.00;
    if (choice == 2) return 30000.00;
    return 20000.00; // Conference Room
}

// Function to get catering selection
double getCateringCost(int guests) {
    cout << "\n-- Choose a Catering Service --\n";
    cout << "1. Basic Buffet (Rupees 200 per guest)\n";
    cout << "2. Premium Buffet (Rupees 350 per guest)\n";
    cout << "3. Plated Dinner (Rupees 500 per guest)\n";

    int choice = getValidChoice(1, 3, "Please enter the number of your choice: ");
    if (choice == 1) return guests * 200.00;
    if (choice == 2) return guests * 350.00;
    return guests * 500.00; // Plated Dinner
}

// Function to get decorations cost
double getDecorationsCost() {
    cout << "\n-- Decorations Options --\n";
    cout << "1. Basic (Rupees 12,000)\n";
    cout << "2. Premium (Rupees 22,000)\n";
    cout << "3. No Decoration\n";

    int choice = getValidChoice(1, 3, "Please enter the number of your choice: ");
    if (choice == 1) return 12000.00;
    if (choice == 2) return 22000.00;
    return 0.00;  // No decoration
}

// Function to get entertainment cost
double getEntertainmentCost() {
    cout << "\n-- Entertainment Options --\n";
    cout << "1. DJ (Rupees 10,000)\n";
    cout << "2. Live Band (Rupees 20,000)\n";
    cout << "3. No Entertainment\n";

    int choice = getValidChoice(1, 3, "Please enter the number of your choice: ");
    if (choice == 1) return 10000.00;
    if (choice == 2) return 20000.00;
    return 0.00;  // No entertainment
}

// Function to get photography cost
double getPhotographyCost() {
    cout << "\n-- Photography Options --\n";
    cout << "1. Standard Package (Rupees 15,000)\n";
    cout << "2. Premium Package with Video (Rupees 25,000)\n";
    cout << "3. No Photography\n";

    int choice = getValidChoice(1, 3, "Please enter the number of your choice: ");
    if (choice == 1) return 15000.00;
    if (choice == 2) return 25000.00;
    return 0.00;  // No photography
}

// Function to apply guest-based discounts
double applyGuestDiscount(int guests, double totalCost) {
    if (guests >= 200) {
        cout << "\nCongratulations! You qualify for a 10% discount for 200 or more guests.\n";
        return totalCost * 0.90;  // 10% discount
    } 
    else {
        cout << "\nNo discount available for fewer than 50 guests.\n";
        return totalCost;  // No discount
    }
}

// Function to display the final cost breakdown
void displayFinalCost(double totalCost, double taxRate, const string& customerName, const string& contactDetails) {
    double tax = totalCost * taxRate;
    double grandTotal = totalCost + tax;

    cout << "\n----- Final Cost Breakdown -----\n";
    cout << "Subtotal: Rupees " << fixed << setprecision(2) << totalCost << endl;
    cout << "Tax (" << (taxRate * 100) << "%): Rupees " << fixed << setprecision(2) << tax << endl;
    cout << "Grand Total: Rupees " << fixed << setprecision(2) << grandTotal << endl;
}

// Function to get payment method
double getPaymentMethod(double totalCost) {
    cout << "\n-- Payment Options --\n";
    cout << "1. Cash\n";
    cout << "2. Credit Card (2% processing fee)\n";
    cout << "3. Online Payment\n";

    int choice = getValidChoice(1, 3, "Please enter the number of your choice: ");
    
    if (choice == 2) {
        cout << "A 2% processing fee will be applied to credit card payments.\n";
        return totalCost * 1.02;  // 2% fee for credit card payments
        
    }
    return totalCost;// Return unmodified cost for other payment methods
}

// Function to get the current date as a string
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    ostringstream oss;
    oss << 1900 + ltm->tm_year << "-" 
        << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-" 
        << setw(2) << setfill('0') << ltm->tm_mday;
    return oss.str();
}

// Function to capture the event date from the user
string getEventDate() {
    string eventDate;
    cout << "\nToday's date is: " << getCurrentDate() << endl;
    cout << "Please enter the event date (DD-MM-YYYY): ";
    getline(cin, eventDate);
    return eventDate;
}

// Function to confirm booking and collect mobile number
bool confirmBooking(string& customerName, string& mobileNumber) {
    string choice;
    cout << "\nWould you like to confirm the booking? (yes/no): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer

    if (choice == "yes" || choice == "Yes") {
        // Collect additional information (name and mobile number)
        cout << "\nPlease confirm your name: ";
        getline(cin, customerName);

        cout << "Please enter your mobile number: ";
        getline(cin, mobileNumber);

        cout << "\nBooking confirmed! Thank you for choosing us.\n";
        return true;  // Proceed with booking
    } else {
        cout << "\nBooking has been canceled. We hope to serve you in the future.\n";
        return false;  // Cancel booking
    }
}

int main() {
    string customerName, contactDetails, mobileNumber, eventDate;
    int numGuests;
    const double taxRate = 0.10;  // 10% tax rate
    const int MAX_GUESTS = 500;    // Define maximum number of guests

    // Welcome message
    cout << "----- Welcome to the Event Cost Estimator -----\n";
    cout << "We are excited to help you to plan your event!\n";

    // Customer Information
    customerName = getValidCustomerName(); // Get validated customer name

    cout << "Please provide your contact details (email or phone): ";
    getline(cin, contactDetails);

    // Number of Guests
    cout << "\nHow many guests will be attending? (Maximum: " << MAX_GUESTS << ") ";
    while (true) {
        cin >> numGuests;
        if (cin.fail() || numGuests <= 0 || numGuests > MAX_GUESTS) {
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            cout << "Invalid input. Please enter a positive number of guests (up to " << MAX_GUESTS << "): ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
            break;  // Valid input, exit the loop
        }
    }

    // Get the event date
    eventDate = getEventDate();

    // Venue, catering, and additional services
    double venueCost = getVenueCost();
    double cateringCost = getCateringCost(numGuests);

    // Additional services
    double decorationsCost = getDecorationsCost();
    double entertainmentCost = getEntertainmentCost();
    double photographyCost = getPhotographyCost();
    double additionalCost = decorationsCost + entertainmentCost + photographyCost;

    // Total cost calculation before discount
    double totalCost = venueCost + cateringCost + additionalCost;
    //cout<<"Total cost without discount :"<<totalCost;

    // Apply guest discount
    totalCost = applyGuestDiscount(numGuests, totalCost);
   // cout<<"Total cost with discount :"<<totalCost;

    // Get payment method and adjust total cost if necessary
    totalCost = getPaymentMethod(totalCost);

    // Display final cost breakdown
    displayFinalCost(totalCost, taxRate, customerName, contactDetails);

    // Confirm booking and get additional details
    if (confirmBooking(customerName, mobileNumber)) {
        cout << "\n----- Booking Details -----\n";
        cout << "Customer Name: " << customerName << endl;
        cout << "Mobile Number: " << mobileNumber << endl;
        cout << "Event Date: " << eventDate << endl;
        cout << "Total Amount: Rupees " << fixed << setprecision(2) << totalCost << endl;
    }
    cout <<"   THANK YOU ! ";

    return 0;
}