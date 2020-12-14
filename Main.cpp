

//below pragma used to resolve warning from the real time.
#pragma warning(disable : 4996)

//used libraries
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<ctime>

//Namespace std not used, instead everything listed
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::ios;
using std::string;
using std::vector;
using std::ostream;
using std::ofstream;
using std::ifstream;
using std::istream;

//object assignments
class Assignment {
private:
    string courseId;
    int dueDate;
    string status;
    int assNum;
    string assData;
    vector<Assignment> assignments1;
    vector<Assignment> assignments2;

    //changed to unsigned to get rid of a warning
    unsigned int i = 0;


public:
    //empty constructor
    Assignment() {}

    //constructor
    Assignment(string courseId, int dueDate, string status, int assNum, string assData) {
        this->courseId = courseId;
        this->dueDate = dueDate;
        this->status = status;
        this->assNum = assNum;
        this->assData = assData;
    }

    //adds assignments in to a vector
    void addAssToVector() {

        string course_ID, status, assData;
        int dueDate, assNum;

        cout << "Enter Course ID: ";
        cin >> course_ID;
        cout << endl;
        cout << "Enter Due Day: ";
        cin >> dueDate;
        cout << endl;
        cout << "Enter Status of the assignment: ";
        cin >> status; cout << endl;
        cout << "Enter Assignment Number: ";
        cin >> assNum;
        cout << endl;

        cin.ignore();
        cout << "Enter Question of the Assignment: "; getline(cin, assData); cout << endl;

        assignments1.push_back(Assignment(course_ID, dueDate, status, assNum, assData));

    }

    //reads file and adds it to a vector
    void loadFile() {

        ifstream in("Assignments.txt");
        int count = 0, r = 0;
        string s;
        vector<string> sa;


        while (getline(in, s, ',')) {

            /*cout << s << endl;*/

            sa.push_back(s);

            ++count;

            if (count == r + 5) {
                this->assignments2.push_back(Assignment(sa[r], stoi(sa[r + 1]), sa[r + 2], stoi(sa[r + 3]), sa[r + 4]));
                r += 5;
            }


        }

        in.close();

    }

    //performs search based on course ID or name
    void searchByCourseId(string _name) {

        for (int i = 0; i < assignments2.size(); i++)
        {
            if (assignments2[i].courseId == _name) {
                assignments2[i].print();

            }
        }

    }

    //performs search based assignment status
    void SearchByStatus(string _status) {

        for (int i = 0; i < assignments2.size(); i++)
        {
            if (assignments2[i].status == _status) {
                assignments2[i].print();

            }
        }
    }

    //performs search based on assignment due in number of days. Works based on real time. Please add proper date for proper results
    void SearchBydueDate(int num) {

        time_t now = time(0);
        tm* ltm = localtime(&now);
        int newDate = ltm->tm_mday + num;


        for (int i = 0; i < assignments2.size(); i++)
        {
            if (assignments2[i].dueDate == newDate) {
                assignments2[i].print();

            }
        }

    }

    //updates status of the assignments
    void updateAss(string status, int num) {

        for (int i = 0; i < assignments2.size(); i++)
        {
            if (assignments2[i].assNum == num) {
                assignments2[i].status = status;

            }
        }


    }

    //prints the assignment data when called
    void print() {
        cout << this->courseId << endl;
        cout << this->dueDate << endl;
        cout << this->status << endl;
        cout << this->assNum << endl;
        cout << this->assData << endl << endl;

    }

    //text read and write start**
    friend ostream& operator << (ostream& out, const Assignment& obj) {
        out << obj.courseId << "," << obj.dueDate << "," << obj.status << "," << obj.assNum
            << "," << obj.assData << "," << endl;
        return out;
    }


    //saves the data in to a text file
    void saveFile() {

        ofstream out("Assignments.txt", ios::app);

        for (int i = 0; i < assignments1.size(); i++)
            out << assignments1[i] << endl;

        out.close();

    }

    //displays all the assignments data
    void display() {

        if (i == assignments2.size()) {
            i = 0;
            return;
        }

        cout << assignments2[i].courseId << "\n";
        cout << assignments2[i].dueDate << "\n";
        cout << assignments2[i].status << "\n";
        cout << assignments2[i].assNum << "\n";
        cout << assignments2[i].assData << "\n";
        cout << endl;
        i++;
        display();

    }

};

//sample test code
int main() {

    Assignment A, B;


    A.addAssToVector();

    A.saveFile();


    B.loadFile();

    B.searchByCourseId("Mth");

    B.SearchByStatus("Incomplete");

    B.SearchBydueDate(10); //Works with reference to real time days and shows assignments due within a month. 

    B.updateAss("Complete", 1);

    B.saveFile();

    B.display();

}