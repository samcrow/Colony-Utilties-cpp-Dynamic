#ifndef COLONY_HPP
#define COLONY_HPP

#include <QObject>
#include <QtGlobal>
#include <QTextStream>
#include <QDateTime>

#include "colonyutils_global.hpp"

/**
  Stores data for a single colony
  */
class COLONYUTILSSHARED_EXPORT Colony : public QObject
{
    Q_OBJECT

public:
    explicit Colony(QObject *parent = 0);

    ~Colony();

    /**
     * Constructor
     *
     * @param id
     *            The colony's identifier
     * @param x
     *            The colony's X location in meters
     * @param y
     *            The colony's Y location in meters
     */
    explicit Colony(int id, double x, double y, bool active);

    /** Get the colony's X location */
    double getX() const;

    /** Get the colony's Y location */
    double getY() const;

    /** Get the colony's ID */
    int getID() const;

    /** Set the colony's X location */
    void setX(double x);

    /** Set the colony's Y location */
    void setY(double y);

    /** Get if the colony is active */
    bool isActive() const;

    /** Set if the colony is active */
    void setActive(bool active);

    /** Get if this colony has been visited */
    bool isVisited() const;

    /** Set if this colony has been visited */
    void setVisited(bool visited);

    /**
      Get the date/time that this colony was modified.
      If this colony does not have a modified date/time, this function returns an invalid date & time.
     */
    QDateTime getModifiedDate() const;


    /**
      Copy this colony's data into a QVariantMap.
      This is useful for JSON exporting.
      */
    QVariantMap toVariant() const;

    /**
      Set this colony's data from a QVariantMap.
      */
    void fromVariant(QVariantMap data);

    /** Get a string representation of this colony */
    QString toString();

    /**
      Check if this colony is equal to another.
      Returns false if other == NULL.
      Returns true if this->getID() == other->getID();
      Otherwise returns false.
      */
    bool equals(Colony *other);

    /** Assignment operator: Assign all properties of this colony to match those of another. */
    void operator = (const Colony &other);
    /** Comparison: Returns true if the IDs of the two colonies match */
    bool operator == (const Colony &other);
    /** Greater/less comparisons: Compare IDs */
    bool operator > (const Colony &other);

signals:

    /** Emitted when any data of this colony (except the modified date/time) is changed */
    void dataChanged();

public slots:

protected:

    /** The colony's ID */
    int id;

    /** The colony's X-axis location in meters east of the southwest corner */
    double x;

    /** The colony's Y-axis location in meters north of the southwest corner */
    double y;

    /** If the colony is currently active */
    volatile bool active;

    /** If the colony has been visited as part of the census */
    volatile bool visited;

    /**
     The time when the colony was modified by a user's operation on the mobile device,
     or an invalid date/time if the device didn't modify this colony
     */
    QDateTime modified;

    /**
      Call this in each method that modifies this colony's data.
      This sets the modified date to the current time.
     */
    void updateModifiedDate();
};

#endif // COLONY_HPP
