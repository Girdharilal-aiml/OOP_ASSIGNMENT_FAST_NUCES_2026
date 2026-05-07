#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

const int MAX = 20;
const int MAX_FAV = 10;
const int MAX_MSG = 50;


class Address {
private:
    string city;
    string area;
    const string country; // always Pakistan, never changes
    string province;
    int postalCode;

public:
    Address() : country("Pakistan") {
        city = "Unknown";
        area = "Unknown";
        province = "Unknown";
        postalCode = 0;
    }

    Address(string c, string a, string p, int pc) : country("Pakistan") {
        city = c;
        area = a;
        province = p;
        postalCode = pc;
    }

    Address(const Address& obj) : country("Pakistan") {
        city = obj.city;
        area = obj.area;
        province = obj.province;
        postalCode = obj.postalCode;
    }

    Address& operator=(const Address& obj) {
        city = obj.city;
        area = obj.area;
        province = obj.province;
        postalCode = obj.postalCode;
        return *this;
    }

    void setCity(string c) { city = c; }
    void setArea(string a) { area = a; }
    string getCity() { return city; }
    string getArea() { return area; }
    string getCountry() { return country; }

    void display() {
        cout << area << ", " << city << ", " << province << ", " << country << endl;
    }

    bool sameCity(Address& other) {
        return city == other.city;
    }

    string fullAddress() {
        return area + ", " + city + ", " + province;
    }

    void update(string c, string a) {
        city = c;
        area = a;
    }
};


// abstract - forces every class to make its own display()
class IDisplayable {
public:
    virtual void display() = 0;
    virtual string getType() = 0;
    virtual ~IDisplayable() {}
};


// abstract - forces searchable classes to implement keyword and budget check
class ISearchable {
public:
    virtual bool matchesKeyword(string kw) = 0;
    virtual bool inBudget(double mn, double mx) = 0;
    virtual ~ISearchable() {}
};


// abstract - Seller, Buyer, Admin each report differently
class IReportable {
public:
    virtual void showReport() = 0;
    virtual int getID() = 0;
    virtual ~IReportable() {}
};


// abstract base class for Car and Bike
// never instantiated directly
class Vehicle : public IDisplayable, public ISearchable {
protected:
    string brand;
    string model;
    int year;
    int mileage;
    string color;

public:
    Vehicle() {
        brand = "Unknown";
        model = "Unknown";
        year = 0;
        mileage = 0;
        color = "White";
    }

    Vehicle(string b, string m, int y, int km, string c) {
        brand = b;
        model = m;
        year = y;
        mileage = km;
        color = c;
    }

    Vehicle(const Vehicle& obj) {
        brand = obj.brand;
        model = obj.model;
        year = obj.year;
        mileage = obj.mileage;
        color = obj.color;
    }

    void setBrand(string b) { brand = b; }
    void setModel(string m) { model = m; }
    void setYear(int y) { year = y; }
    void setMileage(int km) { mileage = km; }

    string getBrand() { return brand; }
    string getModel() { return model; }
    int getYear() { return year; }
    int getMileage() { return mileage; }
    string getColor() { return color; }

    bool isOld() { return (2025 - year) > 10; }

    string summary() {
        return to_string(year) + " " + brand + " " + model;
    }

    virtual void display() = 0;
    virtual string getType() = 0;
    virtual bool matchesKeyword(string kw) = 0;
    virtual bool inBudget(double mn, double mx) = 0;

    // checks if two vehicles are the same model
    bool operator==(const Vehicle& other) const {
        return brand == other.brand && model == other.model;
    }

    virtual ~Vehicle() {}
};


class Car : public Vehicle {
private:
    string fuelType;

public:
    Car() : Vehicle() {
        fuelType = "Petrol";
    }

    Car(string b, string m, int y, int km, string c, string f) : Vehicle(b, m, y, km, c) {
        fuelType = f;
    }

    Car(const Car& obj) : Vehicle(obj) {
        fuelType = obj.fuelType;
    }

    string getFuel() { return fuelType; }
    void setFuel(string f) { fuelType = f; }

    void display() override {
        cout << "  [Car]" << endl;
        cout << "  Brand   : " << brand << endl;
        cout << "  Model   : " << model << endl;
        cout << "  Year    : " << year << endl;
        cout << "  Mileage : " << mileage << " km" << endl;
        cout << "  Color   : " << color << endl;
        cout << "  Fuel    : " << fuelType << endl;
    }

    string getType() override { return "Car"; }

    bool matchesKeyword(string kw) override {
        return brand == kw || model == kw;
    }

    bool inBudget(double mn, double mx) override {
        return true;
    }
};


class Bike : public Vehicle {
private:
    string bikeType;

public:
    Bike() : Vehicle() {
        bikeType = "Standard";
    }

    Bike(string b, string m, int y, int km, string c, string bt) : Vehicle(b, m, y, km, c) {
        bikeType = bt;
    }

    Bike(const Bike& obj) : Vehicle(obj) {
        bikeType = obj.bikeType;
    }

    string getBikeType() { return bikeType; }

    void display() override {
        cout << "  [Bike]" << endl;
        cout << "  Brand   : " << brand << endl;
        cout << "  Model   : " << model << endl;
        cout << "  Year    : " << year << endl;
        cout << "  Mileage : " << mileage << " km" << endl;
        cout << "  Color   : " << color << endl;
        cout << "  Type    : " << bikeType << endl;
    }

    string getType() override { return "Bike"; }

    bool matchesKeyword(string kw) override {
        return brand == kw || model == kw || bikeType == kw;
    }

    bool inBudget(double mn, double mx) override {
        return true;
    }
};


class Listing : public IDisplayable, public ISearchable {
private:
    int id;
    Car car;        // composition
    Address location; // composition
    double price;
    string condition;
    bool isApproved;
    bool isActive;
    int sellerID;

    static int totalListings; // shared across all objects, used for ID generation

public:
    Listing() : car(), location() {
        id = 0;
        price = 0;
        condition = "Used";
        isApproved = false;
        isActive = true;
        sellerID = -1;
    }

    Listing(Car c, Address a, double p, string cond, int sid) : car(c), location(a) {
        id = ++totalListings;
        price = p;
        condition = cond;
        isApproved = false;
        isActive = true;
        sellerID = sid;
    }

    Listing(const Listing& obj) : car(obj.car), location(obj.location) {
        id = obj.id;
        price = obj.price;
        condition = obj.condition;
        isApproved = obj.isApproved;
        isActive = obj.isActive;
        sellerID = obj.sellerID;
    }

    Listing& operator=(const Listing& obj) {
        id = obj.id;
        car = obj.car;
        location = obj.location;
        price = obj.price;
        condition = obj.condition;
        isApproved = obj.isApproved;
        isActive = obj.isActive;
        sellerID = obj.sellerID;
        return *this;
    }

    bool operator==(const Listing& other) const { return id == other.id; }
    bool operator<(const Listing& other) const { return price < other.price; }

    void setPrice(double p) { price = p; }
    void setApproved(bool a) { isApproved = a; }
    void setActive(bool a) { isActive = a; }

    int getID() { return id; }
    double getPrice() { return price; }
    bool getIsApproved() { return isApproved; }
    bool getIsActive() { return isActive; }
    int getSellerID() { return sellerID; }
    Car& getCar() { return car; }
    string getCity() { return location.getCity(); }
    string getType() { return "Listing"; }

    static int getTotal() { return totalListings; }

    void display() override {
        cout << "\n--- Listing #" << id << " ---" << endl;
        car.display();
        cout << "  Price    : PKR " << price << endl;
        cout << "  Condition: " << condition << endl;
        cout << "  Location : ";
        location.display();
        cout << "  Approved : " << (isApproved ? "Yes" : "No") << endl;
    }

    void deactivate() {
        isActive = false;
        isApproved = false;
        cout << "Listing #" << id << " removed." << endl;
    }

    bool matchesKeyword(string kw) override {
        if (car.getBrand() == kw) return true;
        if (car.getModel() == kw) return true;
        if (location.getCity() == kw) return true;
        return false;
    }

    bool inBudget(double mn, double mx) override {
        return price >= mn && price <= mx;
    }

    friend void printCheaper(Listing& a, Listing& b); // needs private price
};

int Listing::totalListings = 0;

// friend: accesses private price of both Listing objects
void printCheaper(Listing& a, Listing& b) {
    if (a.price <= b.price)
        cout << "Cheaper listing is #" << a.id << " at PKR " << a.price << endl;
    else
        cout << "Cheaper listing is #" << b.id << " at PKR " << b.price << endl;
}


class Message {
private:
    int msgID;
    int senderID;
    int receiverID;
    int listingID;
    string text;
    bool isRead;

    static int totalMessages;

public:
    Message() {
        msgID = 0;
        senderID = -1;
        receiverID = -1;
        listingID = -1;
        text = "";
        isRead = false;
    }

    Message(int sid, int rid, int lid, string t) {
        msgID = ++totalMessages;
        senderID = sid;
        receiverID = rid;
        listingID = lid;
        text = t;
        isRead = false;
    }

    void setRead(bool r) { isRead = r; }
    int getMsgID() { return msgID; }
    int getSenderID() { return senderID; }
    int getReceiverID() { return receiverID; }
    bool getIsRead() { return isRead; }

    static int getTotal() { return totalMessages; }

    void display() {
        cout << "[Msg #" << msgID << "] From User#" << senderID
             << " to User#" << receiverID << " (Listing #" << listingID << ")" << endl;
        cout << "  Text: " << text << endl;
        cout << "  Read: " << (isRead ? "Yes" : "No") << endl;
    }

    void markRead() { isRead = true; }

    bool isForUser(int uid) {
        return senderID == uid || receiverID == uid;
    }

    string preview() {
        if (text.length() > 25)
            return text.substr(0, 25) + "...";
        return text;
    }
};

int Message::totalMessages = 0;


class Review {
private:
    int reviewID;
    int buyerID;
    int sellerID;
    int listingID;
    int stars;
    string comment;
    const string platform; // const - platform name never changes

    static int totalReviews;

public:
    Review() : platform("PakWheels Clone") {
        reviewID = 0;
        buyerID = -1;
        sellerID = -1;
        listingID = -1;
        stars = 0;
        comment = "";
    }

    Review(int bid, int sid, int lid, int s, string c) : platform("PakWheels Clone") {
        reviewID = ++totalReviews;
        buyerID = bid;
        sellerID = sid;
        listingID = lid;
        stars = s;
        comment = c;
    }

    // copy constructor required because of const member
    Review(const Review& obj) : platform(obj.platform) {
        reviewID = obj.reviewID;
        buyerID = obj.buyerID;
        sellerID = obj.sellerID;
        listingID = obj.listingID;
        stars = obj.stars;
        comment = obj.comment;
    }

    Review& operator=(const Review& obj) {
        reviewID = obj.reviewID;
        buyerID = obj.buyerID;
        sellerID = obj.sellerID;
        listingID = obj.listingID;
        stars = obj.stars;
        comment = obj.comment;
        return *this;
    }

    void setStars(int s) { stars = s; }
    void setComment(string c) { comment = c; }
    int getReviewID() { return reviewID; }
    int getBuyerID() { return buyerID; }
    int getSellerID() { return sellerID; }
    int getStars() { return stars; }

    static int getTotal() { return totalReviews; }

    void display() {
        cout << "[Review #" << reviewID << "] Buyer#" << buyerID
             << " -> Seller#" << sellerID << " | Stars: " << stars << "/5" << endl;
        cout << "  Comment: " << comment << endl;
        cout << "  Rating : " << starString() << endl;
    }

    bool isPositive() { return stars >= 4; }
    bool isForSeller(int sid) { return sellerID == sid; }

    string starString() {
        string s = "";
        for (int i = 0; i < stars; i++)
            s += "*";
        return s;
    }
};

int Review::totalReviews = 0;


// abstract base for Seller, Buyer, Admin - holds common data
class User : public IReportable {
protected:
    int id;
    string name;
    string phone;
    bool isActive;

    static int totalUsers;

public:
    User() {
        id = 0;
        name = "";
        phone = "";
        isActive = true;
    }

    User(string n, string p) {
        id = ++totalUsers;
        name = n;
        phone = p;
        isActive = true;
    }

    User(const User& obj) {
        id = obj.id;
        name = obj.name;
        phone = obj.phone;
        isActive = obj.isActive;
    }

    void setPhone(string p) { phone = p; }
    void setActive(bool a) { isActive = a; }
    string getName() { return name; }
    string getPhone() { return phone; }
    int getID() override { return id; }
    bool getIsActive() { return isActive; }

    static int getTotal() { return totalUsers; }

    virtual void showReport() override = 0;

    virtual void display() {
        cout << "User: " << name << " | ID: " << id << endl;
    }

    bool operator==(const User& other) const { return id == other.id; }

    virtual ~User() {}
};

int User::totalUsers = 0;


class Seller : public User {
private:
    int myListings[MAX]; // aggregation - stores IDs not objects
    int listingCount;
    double rating;

    static int totalSellers;

public:
    Seller() : User() {
        listingCount = 0;
        rating = 0.0;
        for (int i = 0; i < MAX; i++) myListings[i] = -1;
    }

    Seller(string n, string p, string city) : User(n, p) {
        listingCount = 0;
        rating = 0.0;
        totalSellers++;
        for (int i = 0; i < MAX; i++) myListings[i] = -1;
    }

    void setRating(double r) { rating = r; }
    double getRating() { return rating; }

    static int getTotal() { return totalSellers; }

    void addListingID(int lid) {
        if (listingCount < MAX)
            myListings[listingCount++] = lid;
    }

    void removeListingID(int lid) {
        for (int i = 0; i < listingCount; i++) {
            if (myListings[i] == lid) {
                for (int j = i; j < listingCount-1; j++)
                    myListings[j] = myListings[j+1];
                listingCount--;
                return;
            }
        }
    }

    void display() override {
        cout << "\n=== Seller ===" << endl;
        cout << "ID    : " << id << endl;
        cout << "Name  : " << name << endl;
        cout << "Phone : " << phone << endl;
        cout << "Rating: " << rating << "/5" << endl;
        cout << "Posted: " << listingCount << " listings" << endl;
    }

    void showReport() override {
        cout << "[Seller] " << name << " | Rating: " << rating
             << " | Listings: " << listingCount << endl;
    }

    void showMyListings() {
        cout << name << "'s listings: ";
        for (int i = 0; i < listingCount; i++)
            cout << "#" << myListings[i] << " ";
        cout << endl;
    }

    friend void compareSellerRatings(Seller& a, Seller& b); // needs private rating
};

int Seller::totalSellers = 0;

// friend: accesses private rating of both Seller objects
void compareSellerRatings(Seller& a, Seller& b) {
    cout << a.name << " (" << a.rating << ") vs " << b.name << " (" << b.rating << ")" << endl;
    if (a.rating >= b.rating)
        cout << "  Better seller: " << a.name << endl;
    else
        cout << "  Better seller: " << b.name << endl;
}


class Buyer : public User {
private:
    int favorites[MAX_FAV]; // aggregation - stores IDs not objects
    int favCount;
    double budget;

    static int totalBuyers;

public:
    Buyer() : User() {
        favCount = 0;
        budget = 0;
        for (int i = 0; i < MAX_FAV; i++) favorites[i] = -1;
    }

    Buyer(string n, string p, double b) : User(n, p) {
        favCount = 0;
        budget = b;
        totalBuyers++;
        for (int i = 0; i < MAX_FAV; i++) favorites[i] = -1;
    }

    void setBudget(double b) { budget = b; }
    double getBudget() { return budget; }

    static int getTotal() { return totalBuyers; }

    bool saveFavorite(int lid) {
        if (favCount >= MAX_FAV) { cout << "Favorites full!" << endl; return false; }
        for (int i = 0; i < favCount; i++)
            if (favorites[i] == lid) { cout << "Already saved!" << endl; return false; }
        favorites[favCount++] = lid;
        cout << name << " saved listing #" << lid << " to favorites." << endl;
        return true;
    }

    bool removeFavorite(int lid) {
        for (int i = 0; i < favCount; i++) {
            if (favorites[i] == lid) {
                for (int j = i; j < favCount-1; j++)
                    favorites[j] = favorites[j+1];
                favCount--;
                cout << "Removed from favorites." << endl;
                return true;
            }
        }
        return false;
    }

    void showFavorites() {
        cout << name << "'s favorites: ";
        if (favCount == 0) { cout << "None" << endl; return; }
        for (int i = 0; i < favCount; i++)
            cout << "#" << favorites[i] << " ";
        cout << endl;
    }

    void display() override {
        cout << "\n=== Buyer ===" << endl;
        cout << "ID    : " << id << endl;
        cout << "Name  : " << name << endl;
        cout << "Phone : " << phone << endl;
        cout << "Budget: PKR " << budget << endl;
        cout << "Saved : " << favCount << " favorites" << endl;
    }

    void showReport() override {
        cout << "[Buyer] " << name << " | Budget: PKR " << budget
             << " | Favorites: " << favCount << endl;
    }

    friend bool canAfford(Buyer& buyer, Listing& lst); // needs private budget
};

int Buyer::totalBuyers = 0;

// friend: accesses private budget of Buyer directly
bool canAfford(Buyer& buyer, Listing& lst) {
    if (buyer.budget >= lst.getPrice()) {
        cout << buyer.name << " can afford this (Budget: " << buyer.budget
             << " >= Price: " << lst.getPrice() << ")" << endl;
        return true;
    }
    cout << buyer.name << " cannot afford this (Budget: " << buyer.budget
         << " < Price: " << lst.getPrice() << ")" << endl;
    return false;
}


class Admin : public User {
private:
    const string role; // const - role is fixed at creation
    int approved;
    int removed;

public:
    Admin() : User(), role("Moderator") {
        approved = 0;
        removed = 0;
    }

    Admin(int i, string n, string r) : User(n, "N/A"), role(r) {
        id = i;
        approved = 0;
        removed = 0;
    }

    // copy constructor required because of const member
    Admin(const Admin& obj) : User(obj), role(obj.role) {
        approved = obj.approved;
        removed = obj.removed;
    }

    Admin& operator=(const Admin& obj) {
        approved = obj.approved;
        removed = obj.removed;
        return *this;
    }

    string getRole() { return role; }

    void approveListing(Listing& lst) {
        lst.setApproved(true);
        approved++;
        cout << "Admin " << name << " approved listing #" << lst.getID() << endl;
    }

    void removeListing(Listing& lst) {
        lst.deactivate();
        removed++;
    }

    void banBuyer(Buyer& b) {
        cout << "Admin " << name << " banned: " << b.getName() << endl;
    }

    void display() override {
        cout << "\n=== Admin ===" << endl;
        cout << "ID      : " << id << endl;
        cout << "Name    : " << name << endl;
        cout << "Role    : " << role << endl;
        cout << "Approved: " << approved << endl;
        cout << "Removed : " << removed << endl;
    }

    void showReport() override {
        cout << "[Admin] " << name << " | Role: " << role
             << " | Approved: " << approved << " | Removed: " << removed << endl;
    }
};


class SearchFilter {
private:
    string brand;
    string city;
    double minPrice;
    double maxPrice;
    int minYear;
    int maxYear;

public:
    SearchFilter() {
        brand = "";
        city = "";
        minPrice = 0;
        maxPrice = 99999999;
        minYear = 0;
        maxYear = 9999;
    }

    SearchFilter(string b, string c, double mn, double mx) {
        brand = b;
        city = c;
        minPrice = mn;
        maxPrice = mx;
        minYear = 0;
        maxYear = 9999;
    }

    void setBrand(string b) { brand = b; }
    void setCity(string c) { city = c; }
    void setMinPrice(double p) { minPrice = p; }
    void setMaxPrice(double p) { maxPrice = p; }
    void setYearRange(int a, int b) { minYear = a; maxYear = b; }

    bool passes(Listing& lst) {
        if (brand != "" && lst.getCar().getBrand() != brand) return false;
        if (city != "" && lst.getCity() != city) return false;
        if (lst.getPrice() < minPrice || lst.getPrice() > maxPrice) return false;
        if (lst.getCar().getYear() < minYear || lst.getCar().getYear() > maxYear) return false;
        return true;
    }

    void showFilter() {
        cout << "Filter: Brand=" << brand << " City=" << city
             << " Price=" << minPrice << "-" << maxPrice << endl;
    }

    void clear() {
        brand = "";
        city = "";
        minPrice = 0;
        maxPrice = 99999999;
    }
};


class Marketplace {
private:
    const string name; // const - platform name never changes
    Listing listings[MAX];
    Seller sellers[MAX];
    Buyer buyers[MAX];
    Message messages[MAX_MSG];
    Review reviews[MAX_MSG];
    Admin admin;
    int lCount, sCount, bCount, mCount, rCount;

public:
    Marketplace(string n, Admin a) : name(n), admin(a) {
        lCount = 0;
        sCount = 0;
        bCount = 0;
        mCount = 0;
        rCount = 0;
    }

    string getName() { return name; }

    void addSeller(Seller s) {
        if (sCount < MAX) {
            sellers[sCount++] = s;
            cout << "Seller registered: " << s.getName() << endl;
        }
    }

    void addBuyer(Buyer b) {
        if (bCount < MAX) {
            buyers[bCount++] = b;
            cout << "Buyer registered : " << b.getName() << endl;
        }
    }

    int addListing(Listing lst) {
        if (lCount >= MAX) { cout << "No space." << endl; return -1; }
        listings[lCount++] = lst;
        cout << "Listing #" << lst.getID() << " posted. Waiting for approval." << endl;
        return lst.getID();
    }

    void updatePrice(int lid, double newPrice) {
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getID() == lid) {
                listings[i].setPrice(newPrice);
                cout << "Listing #" << lid << " price updated to PKR " << newPrice << endl;
                return;
            }
        }
        cout << "Listing not found." << endl;
    }

    void deleteListing(int lid) {
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getID() == lid) {
                listings[i].deactivate();
                return;
            }
        }
        cout << "Listing not found." << endl;
    }

    void searchByKeyword(string kw) {
        cout << "\n-- Search: " << kw << " --" << endl;
        int found = 0;
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getIsActive() && listings[i].getIsApproved()
                && listings[i].matchesKeyword(kw)) {
                listings[i].display();
                found++;
            }
        }
        if (found == 0) cout << "No results found." << endl;
        else cout << found << " result(s) found." << endl;
    }

    void searchWithFilter(SearchFilter& f) {
        cout << "\n-- Filtered Search --" << endl;
        f.showFilter();
        int found = 0;
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getIsActive() && listings[i].getIsApproved()
                && f.passes(listings[i])) {
                listings[i].display();
                found++;
            }
        }
        if (found == 0) cout << "No results found." << endl;
        else cout << found << " result(s) found." << endl;
    }

    void saveFavorite(int buyerIndex, int lid) {
        if (buyerIndex < bCount)
            buyers[buyerIndex].saveFavorite(lid);
    }

    void showFavorites(int buyerIndex) {
        if (buyerIndex < bCount)
            buyers[buyerIndex].showFavorites();
    }

    void sendMessage(int sid, int rid, int lid, string text) {
        if (mCount >= MAX_MSG) { cout << "Message limit." << endl; return; }
        Message msg(sid, rid, lid, text);
        messages[mCount++] = msg;
        cout << "Message sent! (Msg #" << msg.getMsgID() << ")" << endl;
    }

    void showMessages(int uid) {
        cout << "\n-- Messages for User #" << uid << " --" << endl;
        int found = 0;
        for (int i = 0; i < mCount; i++) {
            if (messages[i].isForUser(uid)) {
                messages[i].display();
                found++;
            }
        }
        if (found == 0) cout << "No messages." << endl;
    }

    void approveListing(int lid) {
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getID() == lid) {
                admin.approveListing(listings[i]);
                return;
            }
        }
        cout << "Listing not found." << endl;
    }

    void removeListing(int lid) {
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getID() == lid) {
                admin.removeListing(listings[i]);
                return;
            }
        }
        cout << "Listing not found." << endl;
    }

    void showAllListings() {
        cout << "\n===== All Listings on " << name << " =====" << endl;
        int count = 0;
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getIsActive() && listings[i].getIsApproved()) {
                listings[i].display();
                count++;
            }
        }
        cout << "Total: " << count << " listing(s)" << endl;
    }

    void addReview(int bid, int sid, int lid, int stars, string comment) {
        if (rCount >= MAX_MSG) { cout << "Review limit." << endl; return; }
        Review r(bid, sid, lid, stars, comment);
        reviews[rCount++] = r;
        cout << "Review #" << r.getReviewID() << " submitted! (" << stars << "/5)" << endl;
    }

    void showReviewsForSeller(int sid) {
        cout << "\n-- Reviews for Seller#" << sid << " --" << endl;
        int found = 0;
        for (int i = 0; i < rCount; i++) {
            if (reviews[i].isForSeller(sid)) {
                reviews[i].display();
                found++;
            }
        }
        if (found == 0) cout << "No reviews yet." << endl;
    }

    void showAllReports() {
        cout << "\n===== User Reports =====" << endl;
        admin.showReport();
        for (int i = 0; i < sCount; i++) sellers[i].showReport();
        for (int i = 0; i < bCount; i++) buyers[i].showReport();
    }

    void showStats() {
        cout << "\n===== Platform Stats =====" << endl;
        cout << "Platform : " << name << endl;
        cout << "Listings : " << Listing::getTotal() << " total" << endl;
        cout << "Sellers  : " << Seller::getTotal() << endl;
        cout << "Buyers   : " << Buyer::getTotal() << endl;
        cout << "Messages : " << Message::getTotal() << endl;
        cout << "Reviews  : " << Review::getTotal() << endl;
    }

    Listing& getListing(int i) { return listings[i]; }
    Seller& getSeller(int i) { return sellers[i]; }
    Buyer& getBuyer(int i) { return buyers[i]; }
};


int main() {
    cout << fixed << setprecision(0);
    cout << "=============================" << endl;
    cout << "   Car Marketplace System    " << endl;
    cout << "       Assignment 02         " << endl;
    cout << "=============================" << endl;

    Admin admin(1, "Victor", "Moderator");
    Marketplace market("PakWheels Clone", admin);

    Seller s1("Girdhari Lal", "0300-1111111", "Lahore");
    Seller s2("Sara", "0311-2222222", "Karachi");
    s1.setRating(4.5);
    s2.setRating(3.8);
    market.addSeller(s1);
    market.addSeller(s2);

    Buyer b1("M.AL", "0321-3333333", 2500000);
    Buyer b2("Usmani", "0332-4444444", 1800000);
    market.addBuyer(b1);
    market.addBuyer(b2);

    // polymorphism: same display() call on Vehicle pointer, different output for Car vs Bike
    cout << "\n--- Polymorphism Demo ---" << endl;
    Car testCar("Yamaha", "YBR125", 2022, 8000, "Blue", "Petrol");
    Bike testBike("Honda", "CD70", 2021, 12000, "Black", "Standard");
    Vehicle* v1 = &testCar;
    Vehicle* v2 = &testBike;
    cout << "Type: " << v1->getType() << endl;
    v1->display();
    cout << "Type: " << v2->getType() << endl;
    v2->display();

    Car c1("Toyota", "Corolla", 2019, 45000, "White", "Petrol");
    Car c2("Honda", "Civic", 2021, 30000, "Black", "Petrol");
    Car c3("Suzuki", "Alto", 2020, 20000, "Silver", "Petrol");
    Car c4("Toyota", "Vitz", 2018, 55000, "Red", "Petrol");

    Address a1("Lahore", "Gulberg", "Punjab", 54000);
    Address a2("Karachi", "Clifton", "Sindh", 75000);
    Address a3("Lahore", "DHA", "Punjab", 54600);
    Address a4("Islamabad", "F-10", "ICT", 44000);

    cout << "\n--- Posting Listings ---" << endl;
    Listing l1(c1, a1, 2200000, "Used", s1.getID());
    Listing l2(c2, a2, 3500000, "Used", s1.getID());
    Listing l3(c3, a3, 1600000, "Used", s2.getID());
    Listing l4(c4, a4, 1900000, "Used", s2.getID());

    int id1 = market.addListing(l1);
    int id2 = market.addListing(l2);
    int id3 = market.addListing(l3);
    int id4 = market.addListing(l4);

    cout << "\n--- Admin Approving ---" << endl;
    market.approveListing(id1);
    market.approveListing(id2);
    market.approveListing(id3);
    market.approveListing(id4);

    market.showAllListings();

    cout << "\n--- Keyword Search: Toyota ---" << endl;
    market.searchByKeyword("Toyota");

    SearchFilter f("Toyota", "Lahore", 0, 2500000);
    market.searchWithFilter(f);

    cout << "\n--- Saving Favorites ---" << endl;
    market.saveFavorite(0, id1);
    market.saveFavorite(0, id3);
    market.saveFavorite(1, id2);
    market.showFavorites(0);
    market.showFavorites(1);

    cout << "\n--- Sending Messages ---" << endl;
    market.sendMessage(b1.getID(), s1.getID(), id1, "Hello, is Corolla still available?");
    market.sendMessage(b2.getID(), s1.getID(), id2, "Interested in Civic. Whats the price?");
    market.showMessages(s1.getID());

    cout << "\n--- Updating Price ---" << endl;
    market.updatePrice(id1, 2100000);

    cout << "\n--- Admin Removing Listing ---" << endl;
    market.removeListing(id4);
    market.searchByKeyword("Vitz");

    cout << "\n--- Reviews ---" << endl;
    market.addReview(b1.getID(), s1.getID(), id1, 5, "Very smooth deal. Car was as described!");
    market.addReview(b2.getID(), s1.getID(), id2, 4, "Good seller, quick response.");
    market.showReviewsForSeller(s1.getID());

    cout << "\n--- Operator Overloading ---" << endl;
    Car cx("Toyota", "Corolla", 2023, 5000, "Grey", "Petrol");
    if (c1 == cx)
        cout << "c1 == cx : same car model (Vehicle ==)" << endl;
    if (l1 == l1)
        cout << "l1 == l1 : same listing (Listing ==)" << endl;
    if (l3 < l2)
        cout << "l3 < l2  : Alto is cheaper than Civic (Listing <)" << endl;
    if (s1 == s1)
        cout << "s1 == s1 : same seller (User ==)" << endl;

    cout << "\n--- Friend Functions ---" << endl;
    printCheaper(l1, l3);
    compareSellerRatings(s1, s2);
    canAfford(b1, l2);
    canAfford(b2, l2);

    market.showAllReports();
    market.showStats();

    cout << "\n=============================" << endl;
    cout << "         Program End         " << endl;
    cout << "=============================" << endl;

    return 0;
}
