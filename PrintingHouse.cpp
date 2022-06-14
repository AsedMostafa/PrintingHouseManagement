#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

const vector<string> commands = {"add_printer", "add_order", "advance_time", "show_process_info", "finish"};

class Order {
public:
    Order(int _id, int rd, int grn, int blu, int blck, int ppr, string pri){
        redInkNeed = rd;
        blueInkNeed = blu;
        greenInkNeed = grn;
        blackInkNeed = blck;
        papersNeed = ppr;
        priority = pri;
        id = _id;
    }
    Order() {}
    void printInfo();
    void printFinishInfo();
    int getBlueInkNeed(){ return blueInkNeed; }
    int getBlackInkNeed(){ return blackInkNeed; }
    int getRedInkNeed(){ return redInkNeed; }
    int getGreenInkNeed(){ return greenInkNeed; }
    int paperNeedToFinish(){ return papersNeed; }
    void setRemainingPaper(int rm){ papersNeed = rm;}
    void updatePaperNeed();
    int setTimeStepsNeed(int spd){ return papersNeed/spd ;};
    int getTimeStepNeeds(){ return timeStepsNeed;};
    void setFinished(){ isFinished = true;}
    bool getFinished(){ return isFinished; }
    void timePassing(){timeStep += 1;}
    int getTimePassed(){ return timeStep;}
private:
    int id;
    int redInkNeed;
    int blueInkNeed;
    int greenInkNeed;
    int blackInkNeed;
    int papersNeed;
    string priority;
    int startTime;
    int finishTime;
    int timeStepsNeed;
    bool isFinished;
    int timeStep = 0;
};

class Printer {
public:
    Printer(int _speed, int _id){
        redInkStorage = 1000;
        blueInkStorage = 1000;
        greenInkStorage = 1000;
        blackInkStorage = 1000;
        paperStorage = 100;
        status = "Idle";
        speed = _speed;
        id = _id;
    }
    void printInfo();
    string getPrinterStatus();
    void setPrinterOrder(Order* ord);
    void setPrinterStatus(string sts);
    Order* getCurrentOrder();
    int getCurrentPaper(){ return paperStorage; };
    int getPrinterSpeed(){ return speed; };
    void setRefillInkTime(int currTime){ whenInkStorageIsRefilled = currTime + 5 ;}
    int getRefillInkTime(){ return whenInkStorageIsRefilled; }
    void setRefillPaperTime(int currTime){ whenPaperStorageIsRefilled = currTime + 10;}
    int getRefillPaperTime(){ return whenPaperStorageIsRefilled;}
    bool haveNotEnoughInk(Order* ord);
    void updateInkStorage(Order* ord);
    void updatePaperStorage(Order* ord);
private:
    int id;
    int speed;
    int redInkStorage;
    int blueInkStorage;
    int greenInkStorage;
    int blackInkStorage;
    int paperStorage;
    int whenPaperStorageIsRefilled;
    int whenInkStorageIsRefilled;
    string status;
    Order* currentOrder;
};

class PrintingHouse {
    public:
        PrintingHouse() {
            printerId = 1;
            orderId = 1;
            passedTime = 0;
        }
        void addPrinter(int printerSpeed);
        void addOrder(int redInk, int greenInk, int blueInk, int blackInk, int papersNeed, string priority);
        void advanceTime(int timeStep);
        void setVipOrder();
        void setRegularOrder();
        void setPrinterAvailibility();
        void showProcessInfo();
        void finish();
    private:
        vector<Printer*> printers;
        vector<Order*> vipOrdersQue;
        vector<Order*> regularOrdersQue;
        vector<Order*> finishedOrders;
        int printerId;
        int orderId;
        int passedTime;
};

class Utils {
    public:
        Utils() {}
        vector<string> stringToVectorCovertor(string toBeConverted);
};

class CommandHandler {
    public:
        CommandHandler() {}
        void getCommand();
        int whatIsTheCommand(string cmd);
        void runTheCommand(int cmd, vector<string> cmdArgs);
    private:
        PrintingHouse printingHouse;
        Utils utils;
};

int main(){

    //int timeNeededForfillingInkStorage = 10;
    //int timeNeededForfillingPaperStorage = 5;
    CommandHandler commandHandler = CommandHandler();
    commandHandler.getCommand();
}

void CommandHandler::getCommand() {
    while(true) {
        string cmd;
        getline(cin, cmd);
        vector<string> cmdArgs = utils.stringToVectorCovertor(cmd);
        int command = whatIsTheCommand(cmdArgs[0]);
        runTheCommand(command, cmdArgs);
    }
}

int CommandHandler::whatIsTheCommand(string cmd) {
    int position{0};
    for(string c : commands){
        if(c == cmd){
            break;
        }
        position++;
    }
    return position;
}

void CommandHandler::runTheCommand(int cmd, vector<string> cmdArgs) {
    switch (cmd) {
        case 0:
            printingHouse.addPrinter(stoi(cmdArgs[1]));
            break;

        case 1:
            printingHouse.addOrder(stoi(cmdArgs[1]), stoi(cmdArgs[2]), stoi(cmdArgs[3]), 
                                    stoi(cmdArgs[4]), stoi(cmdArgs[5]), cmdArgs[6]);
            break;
        
        case 2:
            printingHouse.advanceTime(stoi(cmdArgs[1]));
            break;
        
        case 3:
            printingHouse.showProcessInfo();
            break;

        case 4:
            printingHouse.finish();

        default:
            break;
    }
    
}

vector<string> Utils::stringToVectorCovertor(string toBeConverted) {
    stringstream ss(toBeConverted);
    string word;
    vector<string> stringVector;
    while (ss >> word)
        stringVector.push_back(word);
    return stringVector;
}

void PrintingHouse::addPrinter(int printerSpeed) {
    Printer *printer = new Printer(printerSpeed, printerId);
    printers.push_back(printer);
    printerId++;
    cout << "printer added successfully" << endl;
}

void PrintingHouse::addOrder(int redInk, int greenInk, int blueInk, int blackInk, int papersNeed, string priority) {
    Order *order = new Order(orderId, redInk, greenInk, blueInk, blackInk, papersNeed, priority);
    if(priority == "vip")
        vipOrdersQue.push_back(order);
    else if(priority == "regular")
        regularOrdersQue.push_back(order);
    orderId++;
    cout << "order added successfully" << endl;
}

string Printer::getPrinterStatus(){
    return status;
}

void Printer::setPrinterOrder(Order* ord){
    currentOrder = ord;
}

void Printer::setPrinterStatus(string sts){
    status = sts;
}

Order* Printer::getCurrentOrder(){
    return currentOrder;
}

bool Printer::haveNotEnoughInk(Order* ord){
    int blue = ord->getBlueInkNeed();
    int green = ord->getGreenInkNeed();
    int red = ord->getRedInkNeed();
    int black = ord->getBlackInkNeed();
    if(blueInkStorage < blue || greenInkStorage < green || blackInkStorage < black || redInkStorage < red){
        return true;
    }
    else{
        return false;
    }
}

void Printer::updateInkStorage(Order* ord){
    blackInkStorage -= ord->getBlackInkNeed();
    blueInkStorage -= ord->getBlueInkNeed();
    greenInkStorage -= ord->getGreenInkNeed();
    redInkStorage -= ord->getRedInkNeed();
}

void Printer::updatePaperStorage(Order* ord){
    paperStorage -= speed;
    if(ord->paperNeedToFinish() - speed < 0){
        ord->setFinished();
    }
    else{
        ord->setRemainingPaper(ord->paperNeedToFinish() - speed);
    }
}

void PrintingHouse::setVipOrder(){
    for(Order* vipOrder: vipOrdersQue){
        for(Printer* printer: printers){
            if(printer->getPrinterStatus() == "Idle"){
                printer->setPrinterOrder(vipOrder);
                printer->setPrinterStatus("busy");
                vipOrdersQue.erase(vipOrdersQue.begin());
                break;
            }
        }
    }
}

void PrintingHouse::setRegularOrder(){
    for(Order* regularOrder: regularOrdersQue){
        for(Printer* printer: printers){
            if(printer->getPrinterStatus() == "Idle"){
                printer->setPrinterOrder(regularOrder);
                printer->setPrinterStatus("busy");
                regularOrdersQue.erase(regularOrdersQue.begin());
                break;
            }
        }
    }
}

void PrintingHouse::setPrinterAvailibility(){
    for(Printer* printer: printers){
        Order* ord = printer->getCurrentOrder();
        if(printer->getCurrentPaper() < printer->getPrinterSpeed()){
            printer->setPrinterStatus("not available");
            printer->setRefillPaperTime(passedTime);
        }
        if(printer->haveNotEnoughInk(ord)){
            printer->setPrinterStatus("not available");
            printer->setRefillInkTime(passedTime);
        }
    }
}

void PrintingHouse::advanceTime(int timeStep) {
    int passingTime = 1;
    while(passingTime <= timeStep){
        setVipOrder();
        setRegularOrder();
        setPrinterAvailibility();
        for(Printer* printer:printers){
            if(printer->getPrinterStatus() == "busy"){
                printer->updateInkStorage(printer->getCurrentOrder());
                printer->updatePaperStorage(printer->getCurrentOrder());
                int spd = printer->getPrinterSpeed();
                printer->getCurrentOrder()->setTimeStepsNeed(spd);
                printer->getCurrentOrder()->timePassing();
            }
            if(printer->getCurrentOrder()->getFinished()){
                finishedOrders.push_back(printer->getCurrentOrder());
                printer->setPrinterStatus("Idle");
            }
        }
        passingTime++;
        passedTime++;
    }
    cout << "ok" << endl;
}

void PrintingHouse::showProcessInfo() {
    cout << "passed time: " << passedTime << endl;
    cout << "VIP orders queue:" << endl;
    for(Order* vipOrder: vipOrdersQue)
        vipOrder->printInfo();
    cout << "\nregular orders queue:" << endl;
    for(Order* regularOrder: regularOrdersQue)
        regularOrder->printInfo();
    cout << "\nprinters:" << endl;
    for(Printer* printer: printers) {
        printer->printInfo();
        cout << endl;
    }
    cout << "orders finished:" << endl;
    for(Order* finishedOrder: finishedOrders) {
        finishedOrder->printFinishInfo();
        cout << endl;
    }
        
}

void PrintingHouse::finish() {
    //todo
    cout << endl;
}

void Order::printInfo() {
    cout << id << " " << papersNeed << endl;
}

void Order::printFinishInfo() {
    cout << id << " " << timeStep << endl;
}

void Printer::printInfo() {
    cout << "printer ID: " << id << endl;
    cout << "status: " << status << endl;
    if(status == "busy") {
        cout << "current order: "; 
        currentOrder->printInfo();
    }
    cout << "ink left:" << endl;
    cout << "black: " << blackInkStorage << endl;
    cout << "red: " << redInkStorage << endl;
    cout << "blue: " << blueInkStorage << endl;
    cout << "green: " << greenInkStorage << endl;
    cout << "black: " << blackInkStorage << endl;
    cout << "papers left: " << paperStorage << endl;
}