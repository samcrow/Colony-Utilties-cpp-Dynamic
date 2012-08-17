#include "colony.hpp"

//Default constructor: Set everything to zero and false
Colony::Colony(QObject * parent) :
    QObject(parent)
{
    Colony(0, 0, 0, false);
}

Colony::Colony(int id, double x, double y, bool active) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->active = active;

    updateModifiedDate();
}

double Colony::getX() const {
    return x;
}

double Colony::getY() const {
    return y;
}

int Colony::getID() const {
    return id;
}

bool Colony::isActive() const {
    return active;
}

bool Colony::isVisited() const {
    return visited;
}

void Colony::setX(double x) {
    this->x = x;
    updateModifiedDate();
}

void Colony::setY(double y) {
    this->y = y;
    updateModifiedDate();
}

void Colony::setActive(bool active) {
    this->active = active;
    updateModifiedDate();
}

void Colony::setVisited(bool visited) {
    this->visited = visited;
    updateModifiedDate();
}

void Colony::updateModifiedDate() {

    //Get the value that modified points to; set the current date/time to that value
    modified = QDateTime::currentDateTime();
    emit dataChanged();
}

QDateTime Colony::getModifiedDate() const {
    //If the modified date/time is valid, return it
    if(modified.isValid()) {
        return modified;
    }
    else {
        //Return an invalid date/time
        return QDateTime();
    }
}

QVariantMap Colony::toVariant() const {
    QVariantMap map;

    map.insert("id", id);
    map.insert("x", x);
    map.insert("y", y);
    map.insert("active", active);
    map.insert("visited", visited);

    //Modified date/time in ISO 8601 format
    map.insert("modified", modified.toString(Qt::ISODate));

    return map;
}

void Colony::fromVariant(QVariantMap data) {

    bool idOk;
    id = data.value("id", id).toInt(&idOk);
    if(!idOk) {
        id = 0;//Set ID to 0 if it parsing failed
    }

    bool xOk;
    x = data.value("x", x).toInt(&xOk);
    if(!xOk) {
        x = 0;
    }

    bool yOk;
    y = data.value("y", y).toInt(&yOk);
    if(!yOk) {
        y = 0;
    }


    active = data.value("active", active).toBool();
    visited = data.value("visited", visited).toBool();

    //Modified date/time in ISO 8601 format

    //Date string: Either "null" or a formatted date
    QString dateString = data.value("modified").toString();
    if(!dateString.isEmpty()) {
        QDateTime newDate = QDateTime::fromString(dateString, Qt::ISODate);
        if(newDate.isValid()) {
            modified = newDate;//Set the value of modified to the new date
        }
        else {
            //Invalid date string
            modified = QDateTime();//Make it new and invalid
        }
    }
    else {
        modified = QDateTime();//Make it new and invalid
    }

    emit dataChanged();
}

QString Colony::toString() {
    QString string;
    QTextStream stream(&string);

    QString activeString = active ? "true" : "false";
    QString visitedString = visited ? "true" : "false";

    stream << "Colony #" << id << " at (" << x << ", " << y << "), visited=" << visitedString << ", active=" << activeString << ".";
    return string;
}

bool Colony::equals(Colony *other) {
    if(!other) return false;
    if(this->getID() == other->getID()) return true;
    return false;
}

bool Colony::operator == (const Colony &other) {
    return getID() == other.getID();
}

bool Colony::operator > (const Colony &other) {
    return getID() > other.getID();
}

void Colony::operator = (const Colony &other) {
    id = other.getID();
    x = other.getX();
    y = other.getY();
    visited = other.isVisited();
    active = other.isActive();
    modified = other.getModifiedDate();
}

Colony::~Colony() {

}
