#include <iostream>
#include <vector>
#include <algorithm>

struct Task {
    int id;
    std::string description;
    int priority;

    // Constructor for easy task creation
    Task(int id, const std::string& description, int priority)
        : id(id), description(description), priority(priority) {}
};

// Comparator to sort tasks by priority
bool compareByPriority(const Task& a, const Task& b) {
    return a.priority > b.priority; // Higher priority first
}

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;

public:
    TaskManager() : nextId(1) {}

    void addTask(const std::string& description, int priority) {
        Task newTask(nextId++, description, priority);
        tasks.push_back(newTask);
        std::sort(tasks.begin(), tasks.end(), compareByPriority);
    }

    void removeHighestPriorityTask() {
        if (!tasks.empty()) {
            tasks.erase(tasks.begin());
            std::cout << "Removed the highest priority task." << std::endl;
        } else {
            std::cout << "No tasks to remove." << std::endl;
        }
    }

    void removeTaskById(int id) {
        auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
            return task.id == id;
        });
        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            std::cout << "Removed task with ID: " << id << std::endl;
        } else {
            std::cout << "No task found with ID: " << id << std::endl;
        }
    }

    void viewTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks available." << std::endl;
            return;
        }
        std::cout << "Tasks:" << std::endl;
        for (const auto& task : tasks) {
            std::cout << "ID: " << task.id << ", Description: " << task.description << ", Priority: " << task.priority << std::endl;
        }
    }
};

void showMenu() {
    std::cout << "Task Manager Menu:" << std::endl;
    std::cout << "1. Add a new task" << std::endl;
    std::cout << "2. View all tasks" << std::endl;
    std::cout << "3. Remove highest priority task" << std::endl;
    std::cout << "4. Remove task by ID" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

int main() {
    TaskManager taskManager;
    int choice;

    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string description;
                int priority;
                std::cout << "Enter task description: ";
                std::cin.ignore(); // Clear newline from input buffer
                std::getline(std::cin, description);
                std::cout << "Enter task priority: ";
                std::cin >> priority;
                taskManager.addTask(description, priority);
                break;
            }
            case 2:
                taskManager.viewTasks();
                break;
            case 3:
                taskManager.removeHighestPriorityTask();
                break;
            case 4: {
                int id;
                std::cout << "Enter task ID to remove: ";
                std::cin >> id;
                taskManager.removeTaskById(id);
                break;
            }
            case 5:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
