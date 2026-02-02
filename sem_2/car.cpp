#include "Header2.h"

using namespace std;

Car::Car() : brand("Íåèçâåñòíî"), model("Íåèçâåñòíî"), VIN("00000000000000000"),
state_number("A777AA777"), mileage(0), isOperationResult(false)
{
    cout << "êîíñòðóêòîð ïî óìîë÷àíèþ" << endl;
}

Car::Car(const Car& other) : brand(other.brand), model(other.model), VIN(other.VIN),
state_number(other.state_number), mileage(other.mileage), things(other.things),
isOperationResult(other.isOperationResult)
{
}

Car::Car(string br, string m, string V, string st_n, int mil, vector<string> th) {
    brand = br;
    model = m;
    mileage = mil;
    setVIN(V);
    setStateNumber(st_n);
    SetThings(th);
    cout << "ïàðàìåòðèçèðîâàííûé êîíñòðóêòîð" << endl;
}

Car::~Car() {
    cout << "Äåñòðóêòîð" << endl;
}

string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
string Car::get_VIN() const { return VIN; }
string Car::getState_number() const { return state_number; }
int Car::getMileage() const { return mileage; }
vector<string> Car::getThings() const { return things; }

bool Car::isValidVINChar(char c) const {
    return isdigit(c) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Car::isValidStateNumberChar(char c) const {
    if (c >= '0' && c <= '9') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'À' && c <= 'ß') return true;
    if (c >= 'à' && c <= 'ÿ') return true;
    return false;
}

bool Car::isLetter(char c) const {
    unsigned char uc = static_cast<unsigned char>(c);
    if ((uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z')) return true;
    if (uc >= 0xC0 && uc <= 0xFF) return true;
    return false;
}

string Car::RandomStateNumber() const {
    random_device rd;
    mt19937 gen(rd());

    
    string letters = "ÀÂÅÊÌÍÎÐÑÒÓÕ"; 
    if (letters.empty()) {
        throw runtime_error("Letters string is empty");
    }

    string result;
    uniform_int_distribution<int> letterDist(0, static_cast<int>(letters.size()) - 1);


    result += letters[letterDist(gen)];
    uniform_int_distribution<int> digitDist(1, 999);
    int num = digitDist(gen);
    if (num < 10) {
        result += "00" + to_string(num);
    }
    else if (num < 100) {
        result += "0" + to_string(num);
    }
    else {
        result += to_string(num);
    }

  
    result += letters[letterDist(gen)];
    result += letters[letterDist(gen)];

 
    uniform_int_distribution<int> regionDist(1, 99);
    int region = regionDist(gen);
    if (region < 10) {
        result += "0" + to_string(region);
    }
    else {
        result += to_string(region);
    }

    return result;
}
//Îïåðàòîðû
Car Car::operator+(const Car& other) const {
    Car newCar;
    newCar.markAsOperationResult();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1);

    if (dist(gen) == 0) {
        newCar.brand = this->brand;
        cout << "Âûáðàíà ìàðêà ïåðâîãî àâòîìîáèëÿ: " << this->brand << endl;
    }
    else {
        newCar.brand = other.brand;
        cout << "Âûáðàíà ìàðêà âòîðîãî àâòîìîáèëÿ: " << other.brand << endl;
    }

    string newStateNumber;
    do {
        newStateNumber = newCar.RandomStateNumber();
        cout << "Ñãåíåðèðîâàí íîìåð: " << newStateNumber << " (äëèíà: " << newStateNumber.length() << ")" << endl;
    } while (newStateNumber == this->state_number || newStateNumber == other.state_number);


    vector<string> combinedThings = this->things;
    combinedThings.insert(combinedThings.end(), other.things.begin(), other.things.end());
    newCar.SetThings(combinedThings);

    cout << "Ñîçäàí íîâûé àâòîìîáèëü!" << endl;
    return newCar;
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        brand = other.brand;
        state_number = other.state_number;
        things = other.things;
        isOperationResult = other.isOperationResult; 
        cout << "Âûïîëíåíî ïðèñâàèâàíèå" << endl;
    }
    return *this;
}
Car Car::operator-(const Car& other) const {
    Car newCar;
    newCar.markAsOperationResult();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1);

    // Ñëó÷àéíûé âûáîð ìàðêè
    if (dist(gen) == 0) {
        newCar.brand = this->brand;
        cout << "Âûáðàíà ìàðêà ïåðâîãî àâòîìîáèëÿ: " << this->brand << endl;
    }
    else {
        newCar.brand = other.brand;
        cout << "Âûáðàíà ìàðêà âòîðîãî àâòîìîáèëÿ: " << other.brand << endl;
    }

    string newStateNumber;
    do {
        newStateNumber = newCar.RandomStateNumber(); 
    } while (newStateNumber == this->state_number || newStateNumber == other.state_number);
    newCar.setStateNumber(newStateNumber);
    vector<string> combinedThings = this->things;
    combinedThings.insert(combinedThings.end(), other.things.begin(), other.things.end());

    // óäàëÿþ ïîâòîðêè
    if (!combinedThings.empty()) {
        sort(combinedThings.begin(), combinedThings.end());
        auto last = unique(combinedThings.begin(), combinedThings.end());
        combinedThings.erase(last, combinedThings.end());
    }

    newCar.SetThings(combinedThings);

    return newCar;
}
Car Car::operator/(const Car & other) const {
        Car newCar;
        newCar.markAsOperationResult();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, 1);

        if (dist(gen) == 0) {
            newCar.brand = this->brand;
            cout << "Âûáðàíà ìàðêà ïåðâîãî àâòîìîáèëÿ: " << this->brand << endl;
        }
        else {
            newCar.brand = other.brand;
            cout << "Âûáðàíà ìàðêà âòîðîãî àâòîìîáèëÿ: " << other.brand << endl;
        }

        string newStateNumber;
        do {
            newStateNumber = newCar.RandomStateNumber();
        } while (newStateNumber == this->state_number || newStateNumber == other.state_number);
        newCar.setStateNumber(newStateNumber);


        vector<string> commonThings;
        for (const auto& item1 : this->things) {
            for (const auto& item2 : other.things) {
                if (item1 == item2) {
                    commonThings.push_back(item1);
                    break;
                }
            }
        }

        if (!commonThings.empty()) {
            sort(commonThings.begin(), commonThings.end());
            auto last = unique(commonThings.begin(), commonThings.end());
            commonThings.erase(last, commonThings.end());
        }

        newCar.SetThings(commonThings);

        cout << "Ñîçäàí íîâûé àâòîìîáèëü (îïåðàòîð /)!" << endl;
        return newCar;
    }
//Êîíåö îïåðàòîðîâ
void Car::SetThings(const vector<string>& thing) {
    things = thing;
}

void Car::setVIN(const string& newVIN) {
    if (newVIN.length() != 17) {
        throw length_error("Äëèíà äîëæíà áûòü ðîâíî 17 ñèìâîëîâ");
    }

    for (char c : newVIN) {
        if (!isValidVINChar(c)) {
            throw invalid_argument("Íàéäåí íåäîïóñòèìûé ñèìâîë");
        }
    }

    VIN = newVIN;
}

void Car::setStateNumber(const string& newNumber) {
    if (newNumber.empty()) {
        throw invalid_argument("Ãîñóäàðñòâåííûé íîìåð íå ìîæåò áûòü ïóñòûì");
    }

    if (newNumber.length() < 6 || newNumber.length() > 9) {
        throw length_error("Ãîñóäàðñòâåííûé íîìåð äîëæåí ñîäåðæàòü îò 6 äî 9 ñèìâîëîâ");
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (char c : newNumber) {
        if (isdigit(c)) {
            hasDigit = true;
        }
        else if (isLetter(c)) {
            hasLetter = true;
        }
    }

    if (!hasLetter || !hasDigit) {
        throw invalid_argument("Ãîñóäàðñòâåííûé íîìåð äîëæåí ñîäåðæàòü õîòÿ áû îäíó áóêâó è îäíó öèôðó");
    }

    state_number = newNumber;
}

void Car::displayInfo() const {
    cout << "Èíôîðìàöèÿ îá àâòîìîáèëå" << endl;
    cout << "Ìàðêà: " << brand << endl;

    if (!isOperationResult) {
        cout << "Ìîäåëü: " << model << endl;
        cout << "Íîìåð êóçîâà: " << VIN << endl;
        cout << "Ïðîáåã: " << mileage << " êì" << endl;
    }

    cout << "Ãîñ. íîìåð: " << state_number << endl;
    cout << "Ñïèñîê âåùåé â áàãàæíèêå:" << endl;

    if (things.empty()) {
        cout << "  Áàãàæíèê ïóñò" << endl;
    }
    else {
        for (size_t i = 0; i < things.size(); ++i) {
            cout << "  " << i + 1 << ". " << things[i] << endl;
        }
    }
    cout << endl;
}

void Car::updateMileage(int prob) {
    if (prob > 0) {
        if (mileage - prob < 0) {
            throw invalid_argument("Ïðîáåã äîëæåí áûòü íåîòðèöàòåëüíûì");
        }
    }
    if (prob < 0)
    {
        throw invalid_argument("Ñêðóòêà íà îòðèöàòåëüíûé ïðîáåã íåâîçìîæíà");
    }

    mileage -= prob;



}
