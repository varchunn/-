#include <iostream>
using namespace std;

class Reservoir {
    char* name;
    double width;
    double length;
    double maxDepth;
    char* type;

public:
    Reservoir() 
    {
        name = new char[1];
        name[0] = '\0';
        width = 0;
        length = 0;
        maxDepth = 0;
        type = new char[1];
        type[0] = '\0';
    }

    explicit Reservoir(const char* n, double w, double l, double d, const char* t) 
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        width = w;
        length = l;
        maxDepth = d;
        type = new char[strlen(t) + 1];
        strcpy(type, t);
    }

    Reservoir(const Reservoir& other) 
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        width = other.width;
        length = other.length;
        maxDepth = other.maxDepth;
        type = new char[strlen(other.type) + 1];
        strcpy(type, other.type);
    }

    ~Reservoir()
    {
        delete[] name;
        delete[] type;
    }

    void setName(const char* n) 
    {
        delete[] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    void setWidth(double w) 
    {
        width = w;
    }

    void setLength(double l)
    {
        length = l;
    }

    void setMaxDepth(double d) 
    {
        maxDepth = d;
    }

    void setType(const char* t) 
    {
        delete[] type;
        type = new char[strlen(t) + 1];
        strcpy(type, t);
    }

    const char* getName() const 
    {
        return name;
    }

    double getWidth() const 
    {
        return width;
    }

    double getLength() const 
    {
        return length;
    }

    double getMaxDepth() const 
    {
        return maxDepth;
    }

    const char* getType() const 
    {
        return type;
    }

    double calculateVolume() const
    {
        return width * length * maxDepth;
    }

    double calculateSurfaceArea() const 
    {
        return width * length;
    }

    bool isSameType(const Reservoir& other) const 
    {
        return strcmp(type, other.type) == 0;
    }

    bool compareSurfaceArea(const Reservoir& other) const 
    {
        if (isSameType(other)) {
            return calculateSurfaceArea() > other.calculateSurfaceArea();
        }
        return false;
    }

    void display() const 
    {
        cout << "Reservoir Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Width: " << width << endl;
        cout << "Length: " << length << endl;
        cout << "Max Depth: " << maxDepth << endl;
        cout << "Volume: " << calculateVolume() << endl;
        cout << "Surface Area: " << calculateSurfaceArea() << endl;
    }

    void copyFrom(const Reservoir& other) {
        setName(other.getName());
        setWidth(other.getWidth());
        setLength(other.getLength());
        setMaxDepth(other.getMaxDepth());
        setType(other.getType());
    }
};

class ReservoirArray 
{
    Reservoir* reservoirs;
    int size;

public:
    ReservoirArray() 
    {
        reservoirs = nullptr;
        size = 0;
    }

    ~ReservoirArray()
    {
        delete[] reservoirs;
    }

    void addReservoir(const Reservoir& res) 
    {
        Reservoir* temp = new Reservoir[size + 1];
        for (int i = 0; i < size; ++i) 
        {
            temp[i].copyFrom(reservoirs[i]);
        }
        temp[size].copyFrom(res);
        delete[] reservoirs;
        reservoirs = temp;
        ++size;
    }

    void removeReservoir(int index) 
    {
        if (index < 0 || index >= size) return;
        Reservoir* temp = new Reservoir[size - 1];
        for (int i = 0, j = 0; i < size; ++i)
        {
            if (i != index)
            {
                temp[j].copyFrom(reservoirs[i]);
                ++j;
            }
        }
        delete[] reservoirs;
        reservoirs = temp;
        --size;
    }

    void displayAll() const 
    {
        for (int i = 0; i < size; ++i) 
        {
            reservoirs[i].display();
            cout << endl;
        }
    }
};

int main() 
{
    Reservoir res1("Lake1", 10, 20, 5, "lake");
    Reservoir res2("Ocean", 50, 100, 30, "ocean");
    ReservoirArray array;
    array.addReservoir(res1);
    array.addReservoir(res2);
    cout << "Displaying all reservoirs:\n";
    array.displayAll();

    return 0;
}

