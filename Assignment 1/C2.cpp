#include<iostream>
#include<string>
using namespace std;

const int MAX     = 20;
const int MAX_FAV = 10;
const int MAX_MSG = 50;

// =============================================
// CLASS 1: Address
// Composition: used inside Listing
// =============================================
class Address {
private:
    string city;
    string area;
    const string country;  // constant - always Pakistan
    string province;
    int postalCode;

public:
    Address() : country("Pakistan") {
        city = "Unknown"; area = "Unknown";
        province = "Unknown"; postalCode = 0;
    }

    Address(string c, string a, string p, int pc) : country("Pakistan") {
        city = c; area = a; province = p; postalCode = pc;
    }

    // Copy constructor
    Address(const Address& obj) : country("Pakistan") {
        city = obj.city; area = obj.area;
        province = obj.province; postalCode = obj.postalCode;
    }

    Address& operator=(const Address& obj) {
        city = obj.city; area = obj.area;
        province = obj.province; postalCode = obj.postalCode;
        return *this;
    }

    void setCity(string c) { city = c; }
    void setArea(string a) { area = a; }
    string getCity()    { return city; }
    string getArea()    { return area; }
    string getCountry() { return country; }

    void display() {
        cout << area << ", " << city << ", " << province << ", " << country << endl;
    }

    bool sameCity(Address& other) { return city == other.city; }

    string fullAddress() { return area + ", " + city + ", " + province; }

    void update(string c, string a) { city = c; area = a; }
};


// =============================================
// CLASS 2: Car
// Composition: used inside Listing
// =============================================
class Car {
private:
    string brand;
    string model;
    int year;
    int mileage;
    string color;
    string fuelType;

public:
    Car() {
        brand = "Unknown"; model = "Unknown";
        year = 0; mileage = 0; color = "White"; fuelType = "Petrol";
    }

    Car(string b, string m, int y, int km, string c, string f) {
        brand = b; model = m; year = y; mileage = km; color = c; fuelType = f;
    }

    // Copy constructor
    Car(const Car& obj) {
        brand = obj.brand; model = obj.model; year = obj.year;
        mileage = obj.mileage; color = obj.color; fuelType = obj.fuelType;
    }

    void setBrand(string b) { brand = b; }
    void setModel(string m) { model = m; }
    void setYear(int y)     { year = y; }
    void setMileage(int km) { mileage = km; }
    void setColor(string c) { color = c; }

    string getBrand()   { return brand; }
    string getModel()   { return model; }
    int    getYear()    { return year; }
    int    getMileage() { return mileage; }
    string getColor()   { return color; }
    string getFuel()    { return fuelType; }

    void display() {
        cout << "  Brand   : " << brand   << endl;
        cout << "  Model   : " << model   << endl;
        cout << "  Year    : " << year    << endl;
        cout << "  Mileage : " << mileage << " km" << endl;
        cout << "  Color   : " << color   << endl;
        cout << "  Fuel    : " << fuelType<< endl;
    }

    bool isOld()              { return (2025 - year) > 10; }
    string summary()          { return to_string(year) + " " + brand + " " + model; }
    bool matchesBrand(string b){ return brand == b; }
};


// =============================================
// CLASS 3: Listing
// Composition: owns Car and Address
// Static member: totalListings
// =============================================
class Listing {
private:
    int id;
    Car car;           // composition
    Address location;  // composition
    double price;
    string condition;
    bool isApproved;
    bool isActive;
    int sellerID;

    static int totalListings;  // WHY STATIC: counts all listings ever made, shared across all objects

public:
    Listing() : car(), location() {
        id = 0; price = 0; condition = "Used";
        isApproved = false; isActive = true; sellerID = -1;
    }

    Listing(Car c, Address a, double p, string cond, int sid) : car(c), location(a) {
        id = ++totalListings; price = p; condition = cond;
        isApproved = false; isActive = true; sellerID = sid;
    }

    // Copy constructor
    Listing(const Listing& obj) : car(obj.car), location(obj.location) {
        id = obj.id; price = obj.price; condition = obj.condition;
        isApproved = obj.isApproved; isActive = obj.isActive; sellerID = obj.sellerID;
    }

    Listing& operator=(const Listing& obj) {
        id = obj.id; car = obj.car; location = obj.location;
        price = obj.price; condition = obj.condition;
        isApproved = obj.isApproved; isActive = obj.isActive; sellerID = obj.sellerID;
        return *this;
    }

    void setPrice(double p)  { price = p; }
    void setApproved(bool a) { isApproved = a; }
    void setActive(bool a)   { isActive = a; }

    int    getID()         { return id; }
    double getPrice()      { return price; }
    bool   getIsApproved() { return isApproved; }
    bool   getIsActive()   { return isActive; }
    int    getSellerID()   { return sellerID; }
    Car&   getCar()        { return car; }
    string getCity()       { return location.getCity(); }

    // WHY STATIC FUNCTION: can be called without creating any object
    static int getTotal() { return totalListings; }

    void display() {
        cout << "\n--- Listing #" << id << " ---" << endl;
        car.display();
        cout << "  Price    : PKR " << price << endl;
        cout << "  Condition: " << condition << endl;
        cout << "  Location : "; location.display();
        cout << "  Approved : " << (isApproved ? "Yes" : "No") << endl;
    }

    void deactivate() {
        isActive = false; isApproved = false;
        cout << "Listing #" << id << " removed." << endl;
    }

    bool matchesKeyword(string keyword) {
        if (car.getBrand() == keyword)    return true;
        if (car.getModel() == keyword)    return true;
        if (location.getCity() == keyword)return true;
        return false;
    }

    bool inBudget(double minP, double maxP) { return price >= minP && price <= maxP; }
};

int Listing::totalListings = 0;


// =============================================
// CLASS 4: Message
// Buyer sends message to Seller
// Static member: totalMessages
// =============================================
class Message {
private:
    int msgID;
    int senderID;
    int receiverID;
    int listingID;
    string text;
    bool isRead;

    static int totalMessages;  // WHY STATIC: platform-wide message count, not per object

public:
    Message() {
        msgID = 0; senderID = -1; receiverID = -1;
        listingID = -1; text = ""; isRead = false;
    }

    Message(int sid, int rid, int lid, string t) {
        msgID = ++totalMessages; senderID = sid; receiverID = rid;
        listingID = lid; text = t; isRead = false;
    }

    void setRead(bool r) { isRead = r; }

    int    getMsgID()      { return msgID; }
    int    getSenderID()   { return senderID; }
    int    getReceiverID() { return receiverID; }
    bool   getIsRead()     { return isRead; }

    static int getTotal() { return totalMessages; }

    void display() {
        cout << "[Msg #" << msgID << "] From User#" << senderID
             << " to User#" << receiverID << " (Listing #" << listingID << ")" << endl;
        cout << "  Text: " << text << endl;
        cout << "  Read: " << (isRead ? "Yes" : "No") << endl;
    }

    void markRead()           { isRead = true; }
    bool isForUser(int uid)   { return senderID == uid || receiverID == uid; }

    string preview() {
        if (text.length() > 25) return text.substr(0, 25) + "...";
        return text;
    }
};

int Message::totalMessages = 0;


// =============================================
// CLASS 5: Review
// Buyer leaves star rating + comment for Seller
// Static member: totalReviews
// =============================================
class Review {
private:
    int    reviewID;
    int    buyerID;
    int    sellerID;
    int    listingID;
    int    stars;
    string comment;
    const string platform;  // constant - platform name never changes

    static int totalReviews;  // WHY STATIC: counts all reviews across platform

public:
    Review() : platform("PakWheels Clone") {
        reviewID = 0; buyerID = -1; sellerID = -1;
        listingID = -1; stars = 0; comment = "";
    }

    Review(int bid, int sid, int lid, int s, string c) : platform("PakWheels Clone") {
        reviewID = ++totalReviews; buyerID = bid; sellerID = sid;
        listingID = lid; stars = s; comment = c;
    }

    // Copy constructor - needed because of const member
    Review(const Review& obj) : platform(obj.platform) {
        reviewID = obj.reviewID; buyerID = obj.buyerID; sellerID = obj.sellerID;
        listingID = obj.listingID; stars = obj.stars; comment = obj.comment;
    }

    Review& operator=(const Review& obj) {
        reviewID = obj.reviewID; buyerID = obj.buyerID; sellerID = obj.sellerID;
        listingID = obj.listingID; stars = obj.stars; comment = obj.comment;
        return *this;
    }

    void setStars(int s)      { stars = s; }
    void setComment(string c) { comment = c; }

    int    getReviewID() { return reviewID; }
    int    getBuyerID()  { return buyerID; }
    int    getSellerID() { return sellerID; }
    int    getStars()    { return stars; }
    string getPlatform() { return platform; }

    static int getTotal() { return totalReviews; }

    void display() {
        cout << "[Review #" << reviewID << "] Buyer#" << buyerID
             << " -> Seller#" << sellerID << " | Stars: " << stars << "/5" << endl;
        cout << "  Comment: " << comment << endl;
        cout << "  Rating : " << starString() << endl;
    }

    bool isPositive()          { return stars >= 4; }
    bool isForSeller(int sid)  { return sellerID == sid; }

    string starString() {
        string s = "";
        for (int i = 0; i < stars; i++) s += "*";
        return s;
    }
};

int Review::totalReviews = 0;


// =============================================
// CLASS 6: Seller
// Posts car listings on the platform
// Aggregation: stores Listing IDs (not objects)
// Static member: totalSellers
// =============================================
class Seller {
private:
    int id;
    string name;
    string phone;
    string city;
    double rating;
    int myListings[MAX];  // aggregation - stores listing IDs only
    int listingCount;

    static int totalSellers;  // WHY STATIC: counts all sellers registered

public:
    Seller() {
        id = 0; name = ""; phone = ""; city = "";
        rating = 0.0; listingCount = 0;
        for (int i = 0; i < MAX; i++) myListings[i] = -1;
    }

    Seller(string n, string p, string c) {
        id = ++totalSellers; name = n; phone = p; city = c;
        rating = 0.0; listingCount = 0;
        for (int i = 0; i < MAX; i++) myListings[i] = -1;
    }

    void setRating(double r) { rating = r; }
    void setPhone(string p)  { phone = p; }

    int    getID()     { return id; }
    string getName()   { return name; }
    string getPhone()  { return phone; }
    string getCity()   { return city; }
    double getRating() { return rating; }

    static int getTotal() { return totalSellers; }

    void addListingID(int lid) {
        if (listingCount < MAX) myListings[listingCount++] = lid;
    }

    void removeListingID(int lid) {
        for (int i = 0; i < listingCount; i++) {
            if (myListings[i] == lid) {
                for (int j = i; j < listingCount - 1; j++)
                    myListings[j] = myListings[j+1];
                listingCount--;
                return;
            }
        }
    }

    void display() {
        cout << "\n=== Seller ===" << endl;
        cout << "ID    : " << id     << endl;
        cout << "Name  : " << name   << endl;
        cout << "Phone : " << phone  << endl;
        cout << "City  : " << city   << endl;
        cout << "Rating: " << rating << "/5" << endl;
        cout << "Posted: " << listingCount << " listings" << endl;
    }

    void showMyListings() {
        cout << name << "'s listings: ";
        for (int i = 0; i < listingCount; i++) cout << "#" << myListings[i] << " ";
        cout << endl;
    }
};

int Seller::totalSellers = 0;


// =============================================
// CLASS 7: Buyer
// Searches listings and saves favorites
// Aggregation: stores favorite Listing IDs
// Static member: totalBuyers
// =============================================
class Buyer {
private:
    int id;
    string name;
    string phone;
    double budget;
    int favorites[MAX_FAV];  // aggregation - stores listing IDs only
    int favCount;

    static int totalBuyers;  // WHY STATIC: counts all buyers registered

public:
    Buyer() {
        id = 0; name = ""; phone = ""; budget = 0; favCount = 0;
        for (int i = 0; i < MAX_FAV; i++) favorites[i] = -1;
    }

    Buyer(string n, string p, double b) {
        id = ++totalBuyers; name = n; phone = p; budget = b; favCount = 0;
        for (int i = 0; i < MAX_FAV; i++) favorites[i] = -1;
    }

    void setBudget(double b) { budget = b; }
    void setPhone(string p)  { phone = p; }

    int    getID()     { return id; }
    string getName()   { return name; }
    double getBudget() { return budget; }

    static int getTotal() { return totalBuyers; }

    bool saveFavorite(int listingID) {
        if (favCount >= MAX_FAV) { cout << "Favorites full!" << endl; return false; }
        for (int i = 0; i < favCount; i++)
            if (favorites[i] == listingID) { cout << "Already saved!" << endl; return false; }
        favorites[favCount++] = listingID;
        cout << name << " saved listing #" << listingID << " to favorites." << endl;
        return true;
    }

    bool removeFavorite(int listingID) {
        for (int i = 0; i < favCount; i++) {
            if (favorites[i] == listingID) {
                for (int j = i; j < favCount - 1; j++) favorites[j] = favorites[j+1];
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
        for (int i = 0; i < favCount; i++) cout << "#" << favorites[i] << " ";
        cout << endl;
    }

    void display() {
        cout << "\n=== Buyer ===" << endl;
        cout << "ID    : " << id     << endl;
        cout << "Name  : " << name   << endl;
        cout << "Phone : " << phone  << endl;
        cout << "Budget: PKR " << budget << endl;
        cout << "Saved : " << favCount << " favorites" << endl;
    }
};

int Buyer::totalBuyers = 0;


// =============================================
// CLASS 8: Admin
// Approves and removes listings
// Constant member: role
// =============================================
class Admin {
private:
    int id;
    string name;
    const string role;  
    int approved;
    int removed;

public:
    Admin() : role("Moderator") {
        id = 0; name = ""; approved = 0; removed = 0;
    }

    Admin(int i, string n, string r) : role(r) {
        id = i; name = n; approved = 0; removed = 0;
    }

    Admin(const Admin& obj) : role(obj.role) {
        id = obj.id; name = obj.name; approved = obj.approved; removed = obj.removed;
    }

    Admin& operator=(const Admin& obj) {
        id = obj.id; name = obj.name; approved = obj.approved; removed = obj.removed;
        return *this;
    }

    string getName() { return name; }
    string getRole() { return role; }
    int    getID()   { return id; }

    void approveListing(Listing& lst) {
        lst.setApproved(true); approved++;
        cout << "Admin " << name << " approved listing #" << lst.getID() << endl;
    }

    void removeListing(Listing& lst) {
        lst.deactivate(); removed++;
    }

    void display() {
        cout << "\n=== Admin ===" << endl;
        cout << "Name    : " << name     << endl;
        cout << "Role    : " << role     << endl;
        cout << "Approved: " << approved << endl;
        cout << "Removed : " << removed  << endl;
    }

    void banBuyer(Buyer& b) {
        cout << "Admin " << name << " banned buyer: " << b.getName() << endl;
    }
};


// =============================================
// CLASS 9: SearchFilter
// Holds search criteria entered by Buyer
// =============================================
class SearchFilter {
private:
    string brand;
    string city;
    double minPrice;
    double maxPrice;
    int    minYear;
    int    maxYear;

public:
    SearchFilter() {
        brand = ""; city = "";
        minPrice = 0; maxPrice = 99999999;
        minYear = 0;  maxYear = 9999;
    }

    SearchFilter(string b, string c, double mn, double mx) {
        brand = b; city = c; minPrice = mn; maxPrice = mx;
        minYear = 0; maxYear = 9999;
    }

    void setBrand(string b)    { brand    = b; }
    void setCity(string c)     { city     = c; }
    void setMinPrice(double p) { minPrice = p; }
    void setMaxPrice(double p) { maxPrice = p; }
    void setYearRange(int a, int b) { minYear = a; maxYear = b; }

    string getBrand()    { return brand; }
    string getCity()     { return city; }
    double getMinPrice() { return minPrice; }
    double getMaxPrice() { return maxPrice; }

    bool passes(Listing& lst) {
        if (brand != "" && lst.getCar().getBrand() != brand) return false;
        if (city  != "" && lst.getCity() != city)            return false;
        if (lst.getPrice() < minPrice || lst.getPrice() > maxPrice) return false;
        if (lst.getCar().getYear() < minYear || lst.getCar().getYear() > maxYear) return false;
        return true;
    }

    void showFilter() {
        cout << "Filter: Brand=" << brand << " City=" << city
             << " Price=" << minPrice << "-" << maxPrice << endl;
    }

    void clear() {
        brand = ""; city = ""; minPrice = 0; maxPrice = 99999999;
        cout << "Filters cleared." << endl;
    }
};


// =============================================
// CLASS 10: Marketplace
// Main controller - manages all data
// Constant member: name
// Arrays of objects: listings, sellers, buyers, messages, reviews
// =============================================
class Marketplace {
private:
    const string name;       
    Listing  listings[MAX];
    Seller   sellers[MAX];
    Buyer    buyers[MAX];
    Message  messages[MAX_MSG];
    Review   reviews[MAX_MSG];
    Admin    admin;
    int lCount, sCount, bCount, mCount, rCount;

public:
    Marketplace(string n, Admin a) : name(n), admin(a) {
        lCount = 0; sCount = 0; bCount = 0; mCount = 0; rCount = 0;
    }

    string getName() { return name; }

    void addSeller(Seller s) {
        if (sCount < MAX) { sellers[sCount++] = s; cout << "Seller registered: " << s.getName() << endl; }
    }

    void addBuyer(Buyer b) {
        if (bCount < MAX) { buyers[bCount++] = b; cout << "Buyer registered : " << b.getName() << endl; }
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
            if (listings[i].getID() == lid) { listings[i].deactivate(); return; }
        }
        cout << "Listing not found." << endl;
    }

    void searchByKeyword(string keyword) {
        cout << "\n-- Search: " << keyword << " --" << endl;
        int found = 0;
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getIsActive() && listings[i].getIsApproved()
                && listings[i].matchesKeyword(keyword)) {
                listings[i].display(); found++;
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
                listings[i].display(); found++;
            }
        }
        if (found == 0) cout << "No results found." << endl;
        else cout << found << " result(s) found." << endl;
    }

    void saveFavorite(int buyerIndex, int listingID) {
        if (buyerIndex < bCount) buyers[buyerIndex].saveFavorite(listingID);
    }

    void showFavorites(int buyerIndex) {
        if (buyerIndex < bCount) buyers[buyerIndex].showFavorites();
    }

    void sendMessage(int senderID, int receiverID, int listingID, string text) {
        if (mCount >= MAX_MSG) { cout << "Message limit reached." << endl; return; }
        Message msg(senderID, receiverID, listingID, text);
        messages[mCount++] = msg;
        cout << "Message sent! (Msg #" << msg.getMsgID() << ")" << endl;
    }

    void showMessages(int userID) {
        cout << "\n-- Messages for User #" << userID << " --" << endl;
        int found = 0;
        for (int i = 0; i < mCount; i++) {
            if (messages[i].isForUser(userID)) { messages[i].display(); found++; }
        }
        if (found == 0) cout << "No messages." << endl;
    }

    void approveListing(int listingID) {
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getID() == listingID) { admin.approveListing(listings[i]); return; }
        }
        cout << "Listing not found." << endl;
    }

    void removeListing(int listingID) {
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getID() == listingID) { admin.removeListing(listings[i]); return; }
        }
        cout << "Listing not found." << endl;
    }

    void showAllListings() {
        cout << "\n===== All Listings on " << name << " =====" << endl;
        int count = 0;
        for (int i = 0; i < lCount; i++) {
            if (listings[i].getIsActive() && listings[i].getIsApproved()) {
                listings[i].display(); count++;
            }
        }
        cout << "Total: " << count << " listing(s)" << endl;
    }

    void addReview(int buyerID, int sellerID, int listingID, int stars, string comment) {
        if (rCount >= MAX_MSG) { cout << "Review limit reached." << endl; return; }
        Review r(buyerID, sellerID, listingID, stars, comment);
        reviews[rCount++] = r;
        cout << "Review #" << r.getReviewID() << " submitted! (" << stars << "/5 stars)" << endl;
    }

    void showReviewsForSeller(int sellerID) {
        cout << "\n-- Reviews for Seller#" << sellerID << " --" << endl;
        int found = 0;
        for (int i = 0; i < rCount; i++) {
            if (reviews[i].isForSeller(sellerID)) { reviews[i].display(); found++; }
        }
        if (found == 0) cout << "No reviews yet." << endl;
    }

    void showStats() {
        cout << "\n===== Platform Stats =====" << endl;
        cout << "Platform : " << name                << endl;
        cout << "Listings : " << Listing::getTotal() << " total" << endl;
        cout << "Sellers  : " << Seller::getTotal()  << endl;
        cout << "Buyers   : " << Buyer::getTotal()   << endl;
        cout << "Messages : " << Message::getTotal() << endl;
        cout << "Reviews  : " << Review::getTotal()  << endl;
    }
};


// =============================================
// MAIN
// =============================================
int main() {
    cout << "=============================" << endl;
    cout << "   Car Marketplace System    " << endl;
    cout << "=============================" << endl;

    Admin admin(1, "Victor", "Moderator");
    Marketplace market("PakWheels Clone", admin);

    // register sellers
    Seller s1("Girdhari Lal", "0300-1111111", "Lahore");
    Seller s2("Sara",         "0311-2222222", "Karachi");
    market.addSeller(s1);
    market.addSeller(s2);

    // register buyers
    Buyer b1("M.AL",   "0321-3333333", 2500000);
    Buyer b2("Usmani", "0332-4444444", 1800000);
    market.addBuyer(b1);
    market.addBuyer(b2);

    // create cars
    Car c1("Toyota", "Corolla", 2019, 45000, "White",  "Petrol");
    Car c2("Honda",  "Civic",   2021, 30000, "Black",  "Petrol");
    Car c3("Suzuki", "Alto",    2020, 20000, "Silver", "Petrol");
    Car c4("Toyota", "Vitz",    2018, 55000, "Red",    "Petrol");

    // create addresses
    Address a1("Lahore",    "Gulberg", "Punjab", 54000);
    Address a2("Karachi",   "Clifton", "Sindh",  75000);
    Address a3("Lahore",    "DHA",     "Punjab", 54600);
    Address a4("Islamabad", "F-10",    "ICT",    44000);

    // post listings
    cout << "\n--- Posting Listings ---" << endl;
    Listing l1(c1, a1, 2200000, "Used", s1.getID());
    Listing l2(c2, a2, 3500000, "Used", s1.getID());
    Listing l3(c3, a3, 1600000, "Used", s2.getID());
    Listing l4(c4, a4, 1900000, "Used", s2.getID());

    int id1 = market.addListing(l1);
    int id2 = market.addListing(l2);
    int id3 = market.addListing(l3);
    int id4 = market.addListing(l4);

    // admin approves listings
    cout << "\n--- Admin Approving ---" << endl;
    market.approveListing(id1);
    market.approveListing(id2);
    market.approveListing(id3);
    market.approveListing(id4);

    // show all listings
    market.showAllListings();

    // keyword search
    cout << "\n--- Keyword Search: Toyota ---" << endl;
    market.searchByKeyword("Toyota");

    // filtered search
    SearchFilter f("Toyota", "Lahore", 0, 2500000);
    market.searchWithFilter(f);

    // save favorites
    cout << "\n--- Saving Favorites ---" << endl;
    market.saveFavorite(0, id1);
    market.saveFavorite(0, id3);
    market.saveFavorite(1, id2);
    market.showFavorites(0);
    market.showFavorites(1);

    // send messages
    cout << "\n--- Sending Messages ---" << endl;
    market.sendMessage(b1.getID(), s1.getID(), id1, "Hello, is Corolla still available?");
    market.sendMessage(b2.getID(), s1.getID(), id2, "Interested in Civic. Whats the price?");
    market.showMessages(s1.getID());

    // update price
    cout << "\n--- Updating Price ---" << endl;
    market.updatePrice(id1, 2100000);

    // admin removes a listing
    cout << "\n--- Admin Removing Listing ---" << endl;
    market.removeListing(id4);
    market.searchByKeyword("Vitz");

    // buyers leave reviews
    cout << "\n--- Leaving Reviews ---" << endl;
    market.addReview(b1.getID(), s1.getID(), id1, 5, "Very smooth deal. Car was as described!");
    market.addReview(b2.getID(), s1.getID(), id2, 4, "Good seller, quick response. Recommended.");
    market.showReviewsForSeller(s1.getID());

    // platform stats
    market.showStats();

    cout << "\n=============================" << endl;
    cout << "         Program End         " << endl;
    cout << "=============================" << endl;

    return 0;
}