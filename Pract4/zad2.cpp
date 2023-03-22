#include <iostream>
#include <fstream>

using namespace std;

void strCopy(char arr[50], const char* ptr)
{
    int i = 0;
    while (arr[i] != '\0' && ptr[i] != '\0')
        arr[i] = ptr[i++];
}

class Task
{
private:
    char name[20];
    char condition[50];
    unsigned points;

public:
    const char* getName() const {
        return name;
    }

    void setName(const char* name) {
        strCopy(this->name, name);
    }

    const char* getCondition() const {
        return condition;
    }

    void setCondition (const char* newCondition) {
        strCopy(this->condition, condition);
    }

    unsigned getPoints() const {
        return points;
    }

    void setPoints(const unsigned points) {
        this->points = points;
    }
};

void taskCopy(Task t1[50], Task t2[50])
{
    for (int i = 0; i < 50; ++i)
    {
        t1[i].setName(t2[i].getName());
        t1[i].setCondition(t2[i].getCondition());
        t1[i].setPoints(t2[i].getPoints());
    }
}

class Exam
{
private:
    Task tasks[50];
    unsigned minPoints;

public:
    void writeToFile(const char* fpath)
    {
        ofstream streamWriter(fpath,  ios::binary | ios::app);

        if (streamWriter.is_open())
        {
            streamWriter.write((char*)tasks, 50 * sizeof(Task));
            streamWriter.write((char*)&minPoints, sizeof(unsigned));
        }

        streamWriter.close();
    }

    void readFromFile(const char* fpath)
    {
        ifstream streamReader(fpath, ios::binary);

        if (streamReader.is_open())
            streamReader.read((char*)this, sizeof(Exam));

        streamReader.close();
    }

    void changeMin(const unsigned minPoints) {
        this->minPoints = minPoints;
    }

    unsigned getMax() const
    {
        int total = 0;

        for (int i = 0; i < 50; ++i)
            total += tasks[i].getPoints();

        return total;
    }

    void setTasks(Task tasks[50])
    {
        taskCopy(this->tasks, tasks);
    }

    const Task* getTasks() const
    {
        return tasks;
    }

    unsigned getMinPoints() const
    {
        return minPoints;
    }
};

int main()
{
    Task t[50];
    t[0].setName("test po OOP");
    t[0].setCondition("SURVIVE");
    t[0].setPoints(1337);

    Exam e;
    e.setTasks(t);

    e.writeToFile("C:\\Users\\grade\\Desktop\\exam.dat");
  //e.readFromFile("C:\\Users\\grade\\Desktop\\exam.dat");

  //cout << e.getTasks()[0].getName() << ' ' << e.getTasks()[0].getCondition() << ' ' << e.getTasks()[0].getPoints() << '\n';
}
