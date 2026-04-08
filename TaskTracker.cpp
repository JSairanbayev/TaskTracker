#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum Status {
    NEW, IN_PROGRESS, DONE
};

class Task {
private:
    string title;
    Status status;

public:
    string getTitle() {
        return title;
    }

    Status getStatus() {
        return status;
    }

    Task(string t) {
        title = t;
        status = NEW;
    }
    void setStatus(Status s) {
        status = s;
    }

    string getStatusText() {
        if (status == NEW) return "[NEW]";
        else if (status == IN_PROGRESS) return "[IN_PROGRESS]";
        else return "[DONE]";
    }

};
int main()
{
    vector<Task>tasks;
    
    ifstream fin("tasks.txt");
    if (fin.is_open()) {
        string title;
        int s;
        while (getline(fin, title)) {
            fin >> s;
            fin.ignore();
            Task t(title);
            if (s == 1) t.setStatus(IN_PROGRESS);
            else if (s == 2) t.setStatus(DONE);
            tasks.push_back(t);
        }
        fin.close();
        cout << "Loaded " << tasks.size() << " tasks." << endl;
    }
    int choice;

    while (true) {
            
        cout << "1. Add task" << endl;
        cout << "2. Show all tasks" << endl;
        cout << "3. Change status" << endl;
        cout << "4. Filter by status" << endl;
        cout << "5. Save tasks" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose:";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            string title;
            cout << "Enter task: ";
            cin.ignore();
            getline(cin, title);
            tasks.push_back(Task(title));
            cout << "Task added!" << endl;
        }
        else if (choice == 2) {
            if (tasks.empty()) {
                cout << "No tasks yet." << endl;
            }
            else {
                for (int i = 0; i < tasks.size(); i++) {
                    cout << i + 1 << ". " << tasks[i].getTitle()
                        << " " << tasks[i].getStatusText() << endl;
                }
            }
        }
        else if (choice == 3) {
            if (tasks.empty()) {
                cout << "No tasks to change." << endl;
            }
            else {
                for (int i = 0; i < tasks.size(); i++) {
                    cout << i + 1 << ". " << tasks[i].getTitle()
                        << " " << tasks[i].getStatusText() << endl;
                }
                cout << "Enter task number: ";
                int num;
                cin >> num;

                if (num >= 1 && num <= tasks.size()) {
                    cout << "1 = NEW, 2 = IN PROGRESS, 3 = DONE" << endl;
                    cout << "New status: ";
                    int s;
                    cin >> s;

                    if (s == 1) tasks[num - 1].setStatus(NEW);
                    else if (s == 2) tasks[num - 1].setStatus(IN_PROGRESS);
                    else if (s == 3) tasks[num - 1].setStatus(DONE);
                    cout << "Status changed!" << endl;
                }
                else {
                    cout << "Wrong number." << endl;
                }
            }
        }
        else if (choice == 4) {
            if (tasks.empty()) {
                cout << "No tasks yet." << endl;
            }
            else {
                cout << "1 = NEW, 2 = IN PROGRESS, 3 = DONE" << endl;
                cout << "Filter by: ";
                int s;
                cin >> s;

                Status filter;
                if (s == 1) filter = NEW;
                else if (s == 2) filter = IN_PROGRESS;
                else filter = DONE;

                bool found = false;
                for (int i = 0; i < tasks.size(); i++) {
                    if (tasks[i].getStatus() == filter) {
                        cout << i + 1 << ". " << tasks[i].getTitle()
                            << " " << tasks[i].getStatusText() << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "No tasks with this status." << endl;
                }
            }
        }
        else if (choice == 5) {
            ofstream fout("tasks.txt");
            for (int i = 0; i < tasks.size(); i++) {
                fout << tasks[i].getTitle() << endl;
                fout << tasks[i].getStatus() << endl;
            }
            fout.close();
            cout << "Tasks saved!" << endl;
        }
        else if (choice == 0) {
            cout << "Bye!" << endl;
            break;
        }
    }
    return 0;
}
