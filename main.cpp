#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Device {
protected:
    string name;
    string macAddress;

public:
    Device(const string& name, const string& macAddress)
        : name(name), macAddress(macAddress) {}

    virtual void displayInfo() const = 0;

    string getName() const {
        return name;
    }
};

class PC : public Device {
private:
    string ipAddress;

public:
    PC(const string& name, const string& ipAddress, const string& macAddress)
        : Device(name, macAddress), ipAddress(ipAddress) {}

    void sendpktfromPc(const PC& source, const PC& destination, string& path) const {
        path += "leaving " + source.getName() + " > ";
    }

    void checkMacTable(const PC& source, const PC& destination, string& path) const {
        path += "arrived at switch > ";
    }

    void receivepkt(const PC& source, const PC& destination, string& path) const {
        path += "leaving switch > ";
        path += "and arrived " + destination.getName() + " > ";
    }

    void displayInfo() const override {
        cout << "PC " << name << " - IP: " << ipAddress << ", MAC: " << macAddress << endl;
    }
};

class Switch : public Device {
public:
    Switch(const string& name, const string& macAddress)
        : Device(name, macAddress) {}

    void displayInfo() const override {
        cout << "Switch " << name << " - MAC: " << macAddress << endl;
    }
};

class Router : public Device {
private:
    vector<string> interfaces;

public:
    Router(const string& name, const string& macAddress)
        : Device(name, macAddress) {}

    void addInterface(const string& ipAddress) {
        interfaces.push_back(ipAddress);
    }

    void displayInfo() const override {
        cout << "Router " << name << " - MAC: " << macAddress << endl;
        cout << "Interfaces:" << endl;
        for (const string& ip : interfaces) {
            cout << "  " << ip << endl;
        }
    }
};

void sendpckt(const Device& source, const Device& destination, string& path) {
    if (dynamic_cast<const PC*>(&source) != nullptr) {
        path += "leaving " + source.getName() + " > ";
        source.displayInfo();
        if (dynamic_cast<const Switch*>(&destination) != nullptr) {
            path += "arrived at " + destination.getName() + " > ";
            destination.displayInfo();
        } else if (dynamic_cast<const Router*>(&destination) != nullptr) {
            path += "arrived at " + destination.getName() + " > ";
            destination.displayInfo();
        }
    } else if (dynamic_cast<const Switch*>(&source) != nullptr) {
        path += "leaving " + source.getName() + " > ";
        source.displayInfo();
        if (dynamic_cast<const PC*>(&destination) != nullptr) {
            path += "arrived at " + destination.getName() + " > ";
            destination.displayInfo();
        } else if (dynamic_cast<const Router*>(&destination) != nullptr) {
            path += "arrived at " + destination.getName() + " > ";
            destination.displayInfo();
        }
    } else if (dynamic_cast<const Router*>(&source) != nullptr) {
        path += "leaving " + source.getName() + " > ";
        source.displayInfo();
        if (dynamic_cast<const PC*>(&destination) != nullptr) {
            path += "arrived at " + destination.getName() + " > ";
            destination.displayInfo();
        } else if (dynamic_cast<const Switch*>(&destination) != nullptr) {
            path += "arrived at " + destination.getName() + " > ";
            destination.displayInfo();
        }
    }
}


int main() {
    ifstream inputFile("devices.txt");
    if (!inputFile) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    vector<Device*> devices;

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string type;
        string name;
        string param1;
        string param2;

        if (iss >> type >> name) {
            if (type == "PC") {
                if (iss >> param1 >> param2) {
                    devices.push_back(new PC(name, param1, param2));
                }
            } else if (type == "Switch") {
                if (iss >> param1) {
                    devices.push_back(new Switch(name, param1));
                }
            } else if (type == "Router") {
                if (iss >> param1 >> param2) {
                    Router* router = new Router(name, param1);
                    router->addInterface(param2);
                    if (iss >> param2) {
                        router->addInterface(param2);
                    }
                    devices.push_back(router);
                }
            }
        }
    }

    inputFile.close();

    string source;
    string destination;

    cout << "Source (e.g., PC1_Subnet1): ";
    cin >> source;
    cout << "Destination (e.g., PC2_Subnet2): ";
    cin >> destination;

    string path = "";

    const Device* sourceDevice = nullptr;
    const Device* destinationDevice = nullptr;

    for (const Device* device : devices) {
        if (device->getName() == source) {
            sourceDevice = device;
        } else if (device->getName() == destination) {
            destinationDevice = device;
        }
    }

    if (sourceDevice && destinationDevice) {
        sendpckt(*sourceDevice, *destinationDevice, path);
        cout << "Path: " << path << endl;
    } else {
        cout << "Invalid source or destination." << endl;
    }

    // Clean up dynamically allocated memory
    for (Device* device : devices) {
        delete device;
    }

    return 0;
}
