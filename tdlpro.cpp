#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

// Task structure
struct Task {
    string title;
    string description;
    string priority; // High, Medium, Low
    string dueDate;  // Format: DD-MM-YYYY
    bool completed;
};

// Function prototypes
void displayMenu();
void createTask(vector<Task> &tasks);
void displayTasks(const vector<Task> &tasks);
void editTask(vector<Task> &tasks);
void deleteTask(vector<Task> &tasks);
void markTaskCompleted(vector<Task> &tasks);
void filterTasks(const vector<Task> &tasks);
void saveTasksToFile(const vector<Task> &tasks);
void loadTasksFromFile(vector<Task> &tasks);
bool isValidDate(const string &date);

int main() {
    vector<Task> tasks;
    loadTasksFromFile(tasks); // Load tasks from file

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:
                createTask(tasks);
                break;
            case 2:
                displayTasks(tasks);
                break;
            case 3:
                editTask(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                markTaskCompleted(tasks);
                break;
            case 6:
                filterTasks(tasks);
                break;
            case 7:
                saveTasksToFile(tasks);
                cout << "Tasks saved successfully!\n";
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}

// Display menu options
void displayMenu() {
    cout << "\n===== TO-DO LIST MENU =====\n";
    cout << "1. Create Task\n";
    cout << "2. Display Tasks\n";
    cout << "3. Edit Task\n";
    cout << "4. Delete Task\n";
    cout << "5. Mark Task as Completed\n";
    cout << "6. Filter Tasks\n";
    cout << "7. Save Tasks\n";
    cout << "8. Exit\n";
}

// Create a new task
void createTask(vector<Task> &tasks) {
    Task newTask;
    cout << "Enter task title: ";
    getline(cin, newTask.title);
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    cout << "Enter task priority (High/Medium/Low): ";
    getline(cin, newTask.priority);
    cout << "Enter due date (DD-MM-YYYY): ";
    getline(cin, newTask.dueDate);

    // Validate due date
    if (!isValidDate(newTask.dueDate)) {
        cout << "Invalid date format! Please use DD-MM-YYYY.\n";
        return;
    }

    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task created successfully!\n";
}

// Display all tasks
void displayTasks(const vector<Task> &tasks) {
    if (tasks.empty()) {
        cout << "No tasks found!\n";
        return;
    }

    cout << "\n===== TASKS =====\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << "Task #" << i + 1 << ":\n";
        cout << "Title: " << tasks[i].title << "\n";
        cout << "Description: " << tasks[i].description << "\n";
        cout << "Priority: " << tasks[i].priority << "\n";
        cout << "Due Date: " << tasks[i].dueDate << "\n";
        cout << "Status: " << (tasks[i].completed ? "Completed" : "Pending") << "\n";
        cout << "----------------------------\n";
    }
}

// Edit an existing task
void editTask(vector<Task> &tasks) {
    displayTasks(tasks);
    if (tasks.empty()) return;

    int taskNumber;
    cout << "Enter task number to edit: ";
    cin >> taskNumber;
    cin.ignore();

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!\n";
        return;
    }

    Task &task = tasks[taskNumber - 1];
    cout << "Enter new title: ";
    getline(cin, task.title);
    cout << "Enter new description: ";
    getline(cin, task.description);
    cout << "Enter new priority (High/Medium/Low): ";
    getline(cin, task.priority);
    cout << "Enter new due date (DD-MM-YYYY): ";
    getline(cin, task.dueDate);

    if (!isValidDate(task.dueDate)) {
        cout << "Invalid date format! Please use DD-MM-YYYY.\n";
        return;
    }

    cout << "Task updated successfully!\n";
}

// Delete a task
void deleteTask(vector<Task> &tasks) {
    displayTasks(tasks);
    if (tasks.empty()) return;

    int taskNumber;
    cout << "Enter task number to delete: ";
    cin >> taskNumber;
    cin.ignore();

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!\n";
        return;
    }

    tasks.erase(tasks.begin() + taskNumber - 1);
    cout << "Task deleted successfully!\n";
}

// Mark a task as completed
void markTaskCompleted(vector<Task> &tasks) {
    displayTasks(tasks);
    if (tasks.empty()) return;

    int taskNumber;
    cout << "Enter task number to mark as completed: ";
    cin >> taskNumber;
    cin.ignore();

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!\n";
        return;
    }

    tasks[taskNumber - 1].completed = true;
    cout << "Task marked as completed!\n";
}

// Filter tasks by status, due date, or priority
void filterTasks(const vector<Task> &tasks) {
    cout << "\n===== FILTER OPTIONS =====\n";
    cout << "1. Pending Tasks\n";
    cout << "2. Completed Tasks\n";
    cout << "3. Tasks by Due Date\n";
    cout << "4. Tasks by Priority\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: {
            cout << "\n===== PENDING TASKS =====\n";
            for (const auto &task : tasks) {
                if (!task.completed) {
                    cout << "Title: " << task.title << "\n";
                    cout << "Description: " << task.description << "\n";
                    cout << "Priority: " << task.priority << "\n";
                    cout << "Due Date: " << task.dueDate << "\n";
                    cout << "----------------------------\n";
                }
            }
            break;
        }
        case 2: {
            cout << "\n===== COMPLETED TASKS =====\n";
            for (const auto &task : tasks) {
                if (task.completed) {
                    cout << "Title: " << task.title << "\n";
                    cout << "Description: " << task.description << "\n";
                    cout << "Priority: " << task.priority << "\n";
                    cout << "Due Date: " << task.dueDate << "\n";
                    cout << "----------------------------\n";
                }
            }
            break;
        }
        case 3: {
            string dueDate;
            cout << "Enter due date (DD-MM-YYYY): ";
            getline(cin, dueDate);

            if (!isValidDate(dueDate)) {
                cout << "Invalid date format! Please use DD-MM-YYYY.\n";
                return;
            }

            cout << "\n===== TASKS DUE ON " << dueDate << " =====\n";
            for (const auto &task : tasks) {
                if (task.dueDate == dueDate) {
                    cout << "Title: " << task.title << "\n";
                    cout << "Description: " << task.description << "\n";
                    cout << "Priority: " << task.priority << "\n";
                    cout << "Due Date: " << task.dueDate << "\n";
                    cout << "----------------------------\n";
                }
            }
            break;
        }
        case 4: {
            string priority;
            cout << "Enter priority (High/Medium/Low): ";
            getline(cin, priority);

            cout << "\n===== TASKS WITH PRIORITY " << priority << " =====\n";
            for (const auto &task : tasks) {
                if (task.priority == priority) {
                    cout << "Title: " << task.title << "\n";
                    cout << "Description: " << task.description << "\n";
                    cout << "Priority: " << task.priority << "\n";
                    cout << "Due Date: " << task.dueDate << "\n";
                    cout << "----------------------------\n";
                }
            }
            break;
        }
        default:
            cout << "Invalid choice!\n";
    }
}

// Save tasks to a file
void saveTasksToFile(const vector<Task> &tasks) {
    ofstream file("tasks.txt");
    if (!file.is_open()) {
        cout << "Error saving tasks!\n";
        return;
    }

    for (const auto &task : tasks) {
        file << task.title << "\n";
        file << task.description << "\n";
        file << task.priority << "\n";
        file << task.dueDate << "\n";
        file << task.completed << "\n";
        file << "\n";
    }

    file.close();
}

// Load tasks from a file
void loadTasksFromFile(vector<Task> &tasks) {
    ifstream file("tasks.txt");
    if (!file.is_open()) return;

    Task task;
    string line;
    while (getline(file, task.title)) {
        getline(file, task.description);
        getline(file, task.priority);
        getline(file, task.dueDate);
        file >> task.completed;
        file.ignore(); // Clear newline
        tasks.push_back(task);
    }

    file.close();
}

// Validate date format (DD-MM-YYYY)
bool isValidDate(const string &date) {
    if (date.length() != 10 || date[2] != '-' || date[5] != '-') return false;

    int year = stoi(date.substr(6, 4));
    int month = stoi(date.substr(4, 2));
    int day = stoi(date.substr(0, 2));

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}