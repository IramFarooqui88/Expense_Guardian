#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Person {
    string name;
    double expense;
};

// Function to calculate the average spending
double calculateAverage(const vector<Person>& people) {
    double total = 0;
    for (const Person& person : people) {
        total += person.expense;
    }
    return total / people.size();
}

// Function to manage and settle expenses
void settleExpenses(const vector<Person>& people) {
    double average = calculateAverage(people);

    // Max heaps (using priority_queue with custom comparison for min heap)
    priority_queue<pair<double, string>> maxHeapReceivers;  // People who will receive money
    priority_queue<pair<double, string>> maxHeapPayers;     // People who will pay money

    for (const Person& person : people) {
        double balance = person.expense - average;
        if (balance > 0) {
            maxHeapReceivers.push({balance, person.name});
        } else if (balance < 0) {
            maxHeapPayers.push({-balance, person.name});  // Insert the negative balance as positive in payers heap
        }
    }

    // Process the heaps to settle the debts
    while (!maxHeapReceivers.empty() && !maxHeapPayers.empty()) {
        pair<double, string> topReceiver = maxHeapReceivers.top();
        pair<double, string> topPayer = maxHeapPayers.top();

        maxHeapReceivers.pop();
        maxHeapPayers.pop();

        double topReceiverAmount = topReceiver.first;
        string topReceiverName = topReceiver.second;

        double topPayerAmount = topPayer.first;
        string topPayerName = topPayer.second;

        double settlementAmount = min(topReceiverAmount, topPayerAmount);

        cout << topPayerName << " pays " << settlementAmount << " to " << topReceiverName << endl;

        if (topReceiverAmount > topPayerAmount) {
            maxHeapReceivers.push({topReceiverAmount - settlementAmount, topReceiverName});
        } else if (topReceiverAmount < topPayerAmount) {
            maxHeapPayers.push({topPayerAmount - settlementAmount, topPayerName});
        }
    }
}

int main() {
    int numPeople;
    cout << "Enter the number of people: ";
    cin >> numPeople;

    // Input validation
    if (numPeople <= 0) {
        cout << "The number of people must be greater than zero." << endl;
        return 1;
    }

    vector<Person> people(numPeople);

    for (int i = 0; i < numPeople; ++i) {
        cout << "Enter name of person " << i + 1 << ": ";
        cin >> people[i].name;
        cout << "Enter expense for " << people[i].name << ": ";
        cin >> people[i].expense;
    }

    settleExpenses(people);

    return 0;
}
