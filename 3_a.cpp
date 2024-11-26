#include <iostream>
#include <vector>
#include <climits>
#include <ctime>

using namespace std;

// Structure to store user data
struct User {
    string name;
    string dob;  // Date of birth in YYYY-MM-DD format
    int num_comments;
    vector<int> friends;  // List of friend indices (adjacency list)

    User(string name, string dob, int comments)
        : name(name), dob(dob), num_comments(comments) {}
};

class SocialNetwork {
private:
    vector<User> users;

public:
    // Add a user to the network
    void addUser() {
        string name, dob;
        int comments;
        cout << "Enter user name: ";
        cin >> name;
        cout << "Enter date of birth (YYYY-MM-DD): ";
        cin >> dob;
        cout << "Enter number of comments: ";
        cin >> comments;
        
        users.push_back(User(name, dob, comments));
    }

    // Add a friendship (undirected graph)
    void addFriendship() {
        int user1, user2;
        cout << "Enter two user indices (0-based) to add friendship: ";
        cin >> user1 >> user2;

        // Ensure valid indices
        if (user1 >= 0 && user1 < users.size() && user2 >= 0 && user2 < users.size()) {
            users[user1].friends.push_back(user2);
            users[user2].friends.push_back(user1);
            cout << "Friendship added between " << users[user1].name << " and " << users[user2].name << endl;
        } else {
            cout << "Invalid user indices!" << endl;
        }
    }

    // 1. Find user with maximum friends
    int maxFriends() {
        int maxFriendsIndex = -1;
        int maxCount = -1;
        for (int i = 0; i < users.size(); ++i) {
            // Check the size of friends list for each user
            int friendCount = users[i].friends.size();
            if (friendCount > maxCount) {
                maxCount = friendCount;
                maxFriendsIndex = i;
            }
        }
        return maxFriendsIndex;
    }

    // 2. Find user with max and min number of comments
    pair<int, int> maxMinComments() {
        int maxCommentsIndex = -1, minCommentsIndex = -1;
        int maxComments = INT_MIN, minComments = INT_MAX;
        
        for (int i = 0; i < users.size(); ++i) {
            if (users[i].num_comments > maxComments) {
                maxComments = users[i].num_comments;
                maxCommentsIndex = i;
            }
            if (users[i].num_comments < minComments) {
                minComments = users[i].num_comments;
                minCommentsIndex = i;
            }
        }
        return {maxCommentsIndex, minCommentsIndex};
    }

    // 3. Find users having birthday in the current month
    vector<int> usersWithBirthdayThisMonth() {
        vector<int> birthdayUsers;
        time_t t = time(0);
        struct tm* now = localtime(&t);

        int currentMonth = now->tm_mon + 1;  // Months are 0-based, so add 1
        
        for (int i = 0; i < users.size(); ++i) {
            // Extract month from the date of birth (format YYYY-MM-DD)
            int birthMonth = stoi(users[i].dob.substr(5, 2));
            
            if (birthMonth == currentMonth) {
                birthdayUsers.push_back(i);
            }
        }
        return birthdayUsers;
    }

    // Utility function to display the user details
    void displayUserDetails(int index) {
        if (index >= 0 && index < users.size()) {
            cout << "Name: " << users[index].name << endl;
            cout << "Date of Birth: " << users[index].dob << endl;
            cout << "Number of Comments: " << users[index].num_comments << endl;
            cout << "Friends: ";
            for (int friendIndex : users[index].friends) {
                cout << users[friendIndex].name << " ";
            }
            cout << endl;
        }
    }

    // Utility function to display the list of all users
    void displayAllUsers() {
        for (int i = 0; i < users.size(); ++i) {
            displayUserDetails(i);
            cout << "---------------------------" << endl;
        }
    }
};

int main() {
    SocialNetwork sn;

    int numUsers;
    cout << "Enter the number of users to add: ";
    cin >> numUsers;

    // Add users to the network
    for (int i = 0; i < numUsers; ++i) {
        sn.addUser();
    }

    int numFriendships;
    cout << "Enter the number of friendships to add: ";
    cin >> numFriendships;

    // Add friendships
    for (int i = 0; i < numFriendships; ++i) {
        sn.addFriendship();
    }
    cout<<"--------------------------------------------"<<endl;
    // Task 1: Find user with maximum friends
    int maxFriendIndex = sn.maxFriends();
    cout << "User with maximum friends: " << endl;
    if (maxFriendIndex != -1) {
        sn.displayUserDetails(maxFriendIndex);  // Display details of the user with the maximum friends
    } else {
        cout << "No users found!" << endl;
    }
    cout<<"--------------------------------------------"<<endl;

    // Task 2: Find user with maximum and minimum comments
    pair<int, int> result = sn.maxMinComments();
    int maxCommentUser = result.first;
    int minCommentUser = result.second;
    cout<<"--------------------------------------------"<<endl;

    cout << "User with maximum comments: " << endl;
    sn.displayUserDetails(maxCommentUser);
    cout<<"--------------------------------------------"<<endl;

    cout << "User with minimum comments: " << endl;
    sn.displayUserDetails(minCommentUser);
    cout<<"--------------------------------------------"<<endl;

    // Task 3: Find users with birthday in the current month
    cout<<"--------------------------------------------"<<endl;

    vector<int> birthdayUsers = sn.usersWithBirthdayThisMonth();
    cout << "Users with birthday this month: " << endl;
    for (int index : birthdayUsers) {
        sn.displayUserDetails(index);
    }
    cout<<"--------------------------------------------"<<endl;

    return 0;
}



// Enter the number of users to add: 3
// Enter user name: Alice
// Enter date of birth (YYYY-MM-DD): 2000-11-25
// Enter number of comments: 50
// Enter user name: Bob
// Enter date of birth (YYYY-MM-DD): 1998-12-10
// Enter number of comments: 30
// Enter user name: Charlie
// Enter date of birth (YYYY-MM-DD): 2001-11-02
// Enter number of comments: 70
// Enter the number of friendships to add: 2
// Enter two user indices (0-based) to add friendship: 0 1
// Enter two user indices (0-based) to add friendship: 1 2
