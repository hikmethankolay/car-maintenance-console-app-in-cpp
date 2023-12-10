/**
 * @file car_maintenance_lib.cpp
 * @brief Implementation file for car maintenance library functions.
 */

#include "../include/car_maintenance_lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
using namespace std;

fstream myFile;  /**< File stream object for file operations. */

/**
 * @brief Opens a binary file, deletes all of its content and write given text to it.
 *
 *
 * @param file_name The name of the file to write.
 * @param text The text to write.
 * @return 0 on success.
 */
int file_write(string file_name, string text) {
  text = "0-)" + text + "\n";
  myFile.open(file_name, ios::out | ios::binary | ios::trunc); // Opens file with output tag
  myFile.write(text.c_str(), text.length()); // Deletes everything inside file and writes text variable
  myFile.close();
  return 0;
}

/**
 * @brief Opens a binary file, Reads all of its content, seperate line with "\n" and write them to console, also returns a string for unit tests.
 *
 *
 * @param file_name The name of the file to read from.
 * @return The contents of the file as a string.
 */
string file_read(string file_name) {
  string line;
  myFile.open(file_name, ios::in | ios::binary); // Opens file with input tag

  if (myFile.is_open()) {
    char i;

    while (myFile.get(i)) { // Takes all lines one by one and prints them to the console
      if (i == '\r') {
        continue;
      }

      line = line + i;
    }

    cout << line;
    myFile.close();
  } else {
    cout << "File operation failed, There is no record\n";
    return "-1";
  }

  return line; // This is a variable for tests to run since the function needs to return something for them to run properly
}

/**
 * @brief Appends given text to a binary file with a automatic calculated line number. Calcultes new lines line number by finding last lines line number.
 *
 *
 * @param file_name The name of the file to append to.
 * @param text The text to append to the file.
 * @return 0 on success.
 */
int file_append(string file_name, string text) {
  myFile.open(file_name, ios::in | ios::binary); // Opens file with input tag
  string lastLine;
  string currentLine;
  char i;

  if (myFile.is_open()) {
    while (myFile.get(i)) {
      if (i == '\n') {
        currentLine = currentLine + i;
        lastLine = currentLine;
        currentLine = "";
        continue;
      }

      currentLine = currentLine + i;
    }

    myFile.close();
  } else {
    cout << "File operation failed\n";
    return -1;
  }

  size_t pos = lastLine.find("-)"); // Finds the location of "-)" in the last line
  int lineNumber = stoi(lastLine.substr(0, pos)) + 1; // Finds the number for the appended line
  text = to_string(lineNumber) + "-)" + text + "\n";
  myFile.open(file_name, ios::app | ios::binary); // Opens file with append tag
  myFile.write(text.c_str(), text.length()); // Appends text with its line number
  myFile.close();
  return 0;
}

/**
 * @brief This function Opens a binary file, finds the line that user wants to edit and replace it wih new text.
 *
 *
 * @param file_name The name of the file to edit.
 * @param line_number_to_edit The line number to edit.
 * @param new_line The new text to replace the existing line.
 * @return 0 on success.
 */
int file_edit(string file_name, int line_number_to_edit, string new_line) {
  const int max_line_count = 100; // A variable for array
  char i;
  myFile.open(file_name, ios::in | ios::binary); // Opens file with read tag

  if (myFile.is_open()) {
    string lines[max_line_count]; // An array to store lines
    string line;
    int line_count = 0; // A variable for an if statement to check if the line that the user wants to edit exists

    while (myFile.get(i)) {
      if (i == '\n') {
        line = line + i;
        lines[line_count++] = line;
        line = "";
        continue;
      }

      line = line + i;
    }

    myFile.close();

    if (line_number_to_edit > 0 && line_number_to_edit <= line_count) {
      lines[line_number_to_edit] = to_string(line_number_to_edit) + "-)" + new_line + "\n"; // Changes a member of Lines array to a new line with its line number
    } else {
      cout << "You can only edit existing lines\n";
      return -1;
    }

    myFile.open(file_name, ios::out | ios::binary); // Opens file in write mode

    for (const string &updated_lines : lines) {  // Writes every member of the lines array to the file
      if (updated_lines == "") {
        break; // Stops if there is nothing on the next line since arrays have fixed slots inside them from the start
      }

      myFile.write(updated_lines.c_str(), updated_lines.length());
    }

    myFile.close();
    cout << "\nData successfully edited\n\n";
    return 0;
  } else {
    cout << "File operation failed" << endl;
    return -1;
  }
}

/**
 * @brief This function Opens a binary file, deletes the line user wanted and make adjustments on line number acordingly.
 *
 *
 * @param file_name The name of the file to delete the line from.
 * @param line_number_to_delete The line number to delete.
 * @return 0 on success.
 */
int file_line_delete(string file_name, int line_number_to_delete) {
  const int max_line_count = 100; // A variable for an array to work properly
  char i;
  myFile.open(file_name, ios::in | ios::binary); // Opens file in read mode

  if (myFile.is_open()) {
    string lines[max_line_count]; // An array to store lines
    string line;
    int line_count = 0; // A variable for an if statement to check if there is a line that the user wants to delete

    while (myFile.get(i)) {// Gets lines one by one and assigns them to the line variable
      if (i == '\n') {
        line = line + i;
        lines[line_count++] = line; // Adds the line variable to the lines array and increases line_count after the operation
        line = "";
        continue;
      }

      line = line + i;
    }

    if (line_number_to_delete > 0 && line_number_to_delete < line_count) {
      // Shift elements to "erase" the line at line_number_to_delete
      for (int i = line_number_to_delete; i < line_count - 1; ++i) {
        lines[i] = lines[i + 1];
      }

      lines[line_count - 1] = ""; // Clears the last element of lines so the same thing wouldn't write to the file twice
    } else {
      cout << "You can only erase existing lines" << endl;
      myFile.close();
      return -1;
    }

    myFile.close();
    myFile.open(file_name, ios::out | ios::binary); // Opens the file in write mode

    for (const string &updated_lines : lines) {
      if (updated_lines == "") {
        break; // Stops if there is nothing on the next line since arrays have fixed slots inside them from the start
      }

      size_t pos = updated_lines.find("-)"); // Finds the position of "-)"
      int lineNumber = stoi(updated_lines.substr(0, pos)); // Finds each line's line number

      if (lineNumber > line_number_to_delete) { // Decreases a line's line number if it's bigger than the deleted line's line number
        string updated_line_with_new_number = to_string(lineNumber - 1) + updated_lines.substr(pos);
        myFile.write(updated_line_with_new_number.c_str(), updated_line_with_new_number.length());
      } else {
        myFile.write(updated_lines.c_str(), updated_lines.length());
      }
    }

    cout << "\nData successfully deleted\n\n";
    myFile.close();
    return 0;
  } else {
    cout << "File operation failed\n";
    return -1;
  }
}

/**
 * @brief This function is for user register
 *
 * Function creates a user.bin file and writes inputted username and password in it.
 *
 * @return 0 on success.
 * @return -1 on faill.
 */
int user_register(string new_username = "None", string new_password = "None", string new_recovery_key = "None", string user_file = "user.bin", string choice = "None") {
  string login_info;

  if (choice == "None") {
    cout << "Do you understand that if you create a new account all the records that have been saved so far will be deleted?[Y/N]";
    cin >> choice;
  }

  if (choice == "Y") {
    if (new_username == "None" && new_password == "None" && new_recovery_key == "None") {
      cout << "Please enter a new username:";
      cin >> new_username;
      cout << "Please enter a new password:";
      cin >> new_password;
      cout << "\nWARNING!!!\nYou will use this to change password if neeeded, if you lost this you cant access logs without them being completely deleted\nWARNING!!!\n";
      cout << "Please enter a new recovery key:";
      cin >> new_recovery_key;
    }

    login_info = new_username + "/" + new_password + "/" + new_recovery_key;
    myFile.open(user_file, ios::out | ios::binary | ios::trunc); // Opens file with output tag
    myFile.write(login_info.c_str(), login_info.length()); // Deletes everything inside file and writes login_info variable
    myFile.close();
    remove("service_history_records.bin");
    remove("maintenance_reminder_records.bin");
    remove("expense_records.bin");
    remove("fuel_efficiency_records.bin");
    return 0;
  } else {
    return -1;
  }
}

/**
 * @brief This function is for user login
 *
 * Function read user.bin file and checks if username and password matchs with inputted username and password
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_login(string username = "None", string password = "None", string user_file = "user.bin") {
  string username_read;
  string password_read;
  string recovery_key_read;
  int count = 0;
  myFile.open(user_file, ios::in | ios::binary); // Opens file with input tag

  if (myFile.is_open()) {
    char i;

    while (myFile.get(i)) {
      if (i == '/') {
        count++;
        continue;
      }

      if (count == 0) {
        username_read = username_read + i;
      } else if (count == 1) {
        password_read = password_read + i;
      } else if (count == 2) {
        break;
      }
    }

    myFile.close();
  } else {
    cout << "There is no user info, Please register first.\n";
    return -1;
  }

  if (username == "None" && password == "None") {
    cout << "Please enter username:";
    cin >> username;
    cout << "Please enter password:";
    cin >> password;
  }

  if (username == username_read && password == password_read) {
    cout << "Login Succesfull";
    return 0;
  } else if (username != username_read || password != password_read) {
    cout << "Wrong username or password";
    return -1;
  }
}


/**
 * @brief This function changes password of user.
 *
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_change_password(string recovery_key = "None", string new_password = "None", string user_file = "user.bin") {
  string username_read;
  string password_read;
  string recovery_key_read;
  string new_login_info;
  int count = 0;
  myFile.open(user_file, ios::in | ios::binary); // Opens file with input tag

  if (myFile.is_open()) {
    char i;

    while (myFile.get(i)) {
      if (i == '/') {
        count++;
        continue;
      }

      if (count == 0) {
        username_read = username_read + i;
      } else if (count == 1) {
        continue;
      } else if (count == 2) {
        recovery_key_read = recovery_key_read + i;
      }
    }

    myFile.close();
  } else {
    cout << "There is no user info, Please register first.\n";
    return -1;
  }

  if (recovery_key_read == "None") {
    cout << "Please enter your recovery key:";
    cin >> recovery_key;
  }

  if (recovery_key_read == recovery_key) {
    cout << "Recovey Key Approved\n";

    if (new_password == "None") {
      cout << "Please enter a new password:";
      cin >> new_password;
    }

    new_login_info = username_read + "/" + new_password + "/" + recovery_key_read;
    myFile.open(user_file, ios::out | ios::binary | ios::trunc); // Opens file with output tag
    myFile.write(new_login_info.c_str(), new_login_info.length()); // Deletes everything inside file and writes login_info variable
    myFile.close();
    cout << "Password changed succesfully";
    return 0;
  } else if (recovery_key_read != recovery_key) {
    cout << "Wrong Recovery Key";
    return -1;
  }
}

/**
 * @brief This function prints main menu and lets user to make choice with arrow keys.
 *
 *
 * @return 0,1,2 or 3 depending on user choice.
 */
int main_menu() {
  int selectedOption;
  cout << "----------Main Menu----------\n";
  cout << "1)User Authentication\n";
  cout << "2Service History Tracking\n";
  cout << "3)Maintenance Reminders\n";
  cout << "4)Expense Logging:\n";
  cout << "5)Fuel Efficiency Reports\n";
  cout << "6)Exit\n";
  cout << "Make a choice(1-6)";

  for (int i = 1; i <= 6; i++) {
    if (i == selectedOption) {
      cout << i << ".Option" << i << "\n";
    }

    return selectedOption;
  }

  int navigateMenu(int selectedOption) {
    char input;
    cin >> input;

    switch (input) {
      case 'w'; //Up arrow key

        if (selectedOption > 1) {
          return selectedOption - 1;
        }

        break;

      case 's'; //Down arrow key

        if (selectedOption < 6) {
          return selectedOption + 1;
        }

        break;

      case '\n'; //Enter key
        return selectedOption; //Return the selected option.
    }

    return selectedOption;
  }
  int performAction(int choice) {
    cout << "Option" << choice << "selected\n";
    //Add code for the selected option's action
    return choice; //Return the choice to continue or exit
  }
  int main() {
    int choice = 1;

    do {
      choice = disPlayMenu(choice);

      if (choice != 6) {
        choice = performAction(choice);
        cout << "Press enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max, '\n');
        cin.get();
      }
    } while (choice != 6);
  }
  return 0;
}
