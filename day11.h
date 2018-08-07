#ifndef DAY11_H
#define DAY11_H

#include <algorithm>
#include <cassert>
#include <list>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class Item {
public:
    enum class itemType {
        // This will also be sorting order so keep alphabetical.
        CHIP, GEN
    };

private:
    itemType type;
    std::string name;

public:
    Item( itemType t, std::string n ) : type( t ), name( n ) {};

    itemType getType() const { return type; }
    std::string getName() const { return name; }

    std::string toString() const {
        std::string s( name );
        if ( type == itemType::GEN ) {
            s += "-gen";
        } else {
            s += "-chip";
        }
        return s;
    }

    friend bool operator<( const Item& l, const Item& r ) {
        return std::tie( l.name, l.type )
             < std::tie( r.name, r.type );
    }

    friend bool operator==( const Item& l, const Item& r ) {
        return std::tie( l.name, l.type )
            == std::tie( r.name, r.type );
    }

    friend bool operator!=( const Item& l, const Item& r ) {
        return ! ( l == r);
    }
};

class Floor {
    std::set<Item> items;
    unsigned numGenerators = 0;
    unsigned numChips = 0;

public:
    void insert( Item i ) {
        items.insert( i );
        if ( i.getType() == Item::itemType::GEN ) {
            numGenerators ++;
        } else {
            numChips ++;
        }
    }

    void remove( const Item& i ) {
        unsigned numErased = items.erase( i );
        assert( numErased == 1 );
        if ( i.getType() == Item::itemType::GEN ) {
            numGenerators --;
        } else {
            numChips --;
        }
    }

    size_t size() const { return items.size(); }
    const std::set<Item>& getItemSet() const { return items; }

    std::string toString() const {
        std::ostringstream floorContents;

        for ( const auto& item : items ) {
            if ( floorContents.str().size() ) floorContents << " ";
            floorContents << item.toString();
        }
        return floorContents.str();
    }

    // Create a string representation of a floor with normalized names.  This
    // will be used as a map or set key to prune floors we have already seen.
    //
    // It turns out that multiple floor combinations have the same number of
    // steps to the final solutions so we can normalize the names for pruning.
    //
    // For example, the following two sets of floors both take the same amount
    // of steps to complete, just the the a and b devices are swapped.
    //
    // floor 1: a-gen a-chip
    // floor 2: b-gen b-chip
    //
    // floor 1: b-gen b-chip
    // floor 2: a-gen a-chip
    //
    // The caller needs to pass an empty map when serializing the first Floor
    // and call us with the same map for each additional floor that is
    // serialized.
    //
    // The normalized floor names will be change the item names to numbers.
    //
    std::string toNormalizedString(
        std::map<std::string,std::string>& normalizePairs ) const {

        std::ostringstream floorContents;

        for ( const auto& item : items ) {
            if ( floorContents.str().size() ) floorContents << " ";

            // NB. This won't insert if it already exists.
            auto p = normalizePairs.insert( { item.getName(),
                         std::to_string( normalizePairs.size() ) } );

            Item normalizedItem( item.getType(), (p.first)->second );
            floorContents << normalizedItem.toString();
        }
        return floorContents.str();
    }

    bool isSafe() const {
        for ( const auto& item : this->items ) {
            if ( item.getType() == Item::itemType::CHIP ) {
                Item gen( Item::itemType::GEN, item.getName() );

                // Chip's generator exists.  Chip is safe.
                if ( this->items.find( gen ) != items.end() ) continue;

                // Other generators exist, chip is not safe.
                if ( this->numGenerators != 0 ) return false;
            }
        }

        return true;
    }

    // Generate all possible 1 and 2 item combinations to load on the elevator.
    std::set<Floor> generateElevatorCombos() const {

        // NB.  itemsOnThisFloor is sorted because items is a sorted set.
        std::vector<Item> itemsOnThisFloor( items.begin(), items.end() );

        // Each item can be sent alone in the elevator.
        std::set<Floor> elevatorCombos;
        for ( const auto& i : itemsOnThisFloor ) {
            Floor elevatorContents;
            elevatorContents.insert( i );
            elevatorCombos.insert( elevatorContents );
        }

        // Generate pairs of items to send in the elevator.
        if ( itemsOnThisFloor.size() > 1 ) {
            for ( auto iterFirst = itemsOnThisFloor.cbegin() ;
                  iterFirst != ( itemsOnThisFloor.cend() - 1 ); ++iterFirst ) {

                for ( auto iterSecond = iterFirst + 1;
                      iterSecond != itemsOnThisFloor.cend(); ++iterSecond ) {
                    Floor elevatorContents;
                    elevatorContents.insert( *iterFirst );
                    elevatorContents.insert( *iterSecond );
                    elevatorCombos.insert( elevatorContents );
                }
            }
        }

        return elevatorCombos;
    }

    friend bool operator<( const Floor& l, const Floor& r ) {
        std::string ls = l.toString();
        std::string rs = r.toString();
        return ls < rs;
    }

    friend bool operator==( const Floor& l, const Floor& r ) {
        std::string ls = l.toString();
        std::string rs = r.toString();
        return ls == rs;
    }

    friend bool operator!=( const Floor& l, const Floor& r ) {
        return ! ( l == r );
    }
};

class ContainmentFloors {
    unsigned numSteps = 0;
    unsigned elevatorFloor = 0;
    std::vector<Floor> floors;

public:
    ContainmentFloors( unsigned ef ) : elevatorFloor( ef ) {}

    void parse( std::istream& is ) {
        const std::regex reChip( "([[:alpha:]]+)-compatible microchip" );
        const std::regex reGenerator( "([[:alpha:]]+) generator" );

        unsigned floorNum = 0;
        std::string line;
        while ( getline( is, line ) ) {
            if ( floors.size() < floorNum + 1 ) {
                floors.resize( floorNum + 1 );
            }

            std::string lineCopy( line );
            std::smatch match;
            while( std::regex_search( lineCopy, match, reChip ) ) {
                floors[ floorNum ].insert( { Item::itemType::CHIP, match[1] } );
                lineCopy = match.suffix().str();
            }

            lineCopy = line;
            while( std::regex_search( lineCopy, match, reGenerator ) ) {
                floors[ floorNum ].insert( { Item::itemType::GEN, match[1] } );
                lineCopy = match.suffix().str();
            }

            floorNum++;
        }
    }

    unsigned getNumSteps() const { return numSteps; }
    void incNumSteps() { numSteps++; }

    unsigned getElevatorFloor() const { return elevatorFloor; }
    void setElevatorFloor( unsigned floor ) { elevatorFloor = floor; }

    unsigned getNumFloors() const { return floors.size(); }

    Floor getFloor( unsigned floorNum ) const {
        return floors[ floorNum ];
    }

    void setFloor( unsigned floorNum, Floor floor ) {
        floors[ floorNum ] = floor;
    }

    bool allItemsOnTopFloor() const {
        assert( floors.size() != 0 );
        auto topFloorIter = floors.cend() - 1;
        for ( auto iter = floors.cbegin(); iter != topFloorIter; ++iter ) {
            if ( iter->size() != 0 ) return false;
        }
        return true;
    }

    std::string toString() const {

        std::ostringstream out;
        out << elevatorFloor << "\n";

        for ( unsigned floorNum = 0; floorNum < floors.size(); floorNum ++ ) {
            out << floorNum << " ";
            out << floors[ floorNum ].toString() << "\n";
        }

        return out.str();
    }

    // Create string representation with normalized item names.  See
    // Floor::toNormalizedString() comments for more details about this.
    std::string toNormalizedString() const {
        std::map<std::string,std::string> normalizePairs;

        std::ostringstream out;
        out << elevatorFloor << "\n";

        for ( unsigned floorNum = 0; floorNum < floors.size(); floorNum ++ ) {
            out << floorNum << " ";
            out << floors[ floorNum ].toNormalizedString( normalizePairs )
                << "\n";
        }

        return out.str();
    }

    // Are all floors safe?
    bool isSafe() const {
        for ( const auto& floor : floors ) {
            if ( ! floor.isSafe() ) {
                return false;
            }
        }
        return true;
    }
};

// Perform a breadth first simulation of all possible moves required to move
// everything safely to the top floor.
class Simulate {
    std::set<std::string> alreadySimulated;

public:
    unsigned simulate( const ContainmentFloors& initialFloors ) {
        std::list<ContainmentFloors> floorQueue;
        floorQueue.push_back( initialFloors );

        std::string s = initialFloors.toNormalizedString();
        alreadySimulated.insert( s );
        while ( ! floorQueue.empty() ) {
            auto iter = floorQueue.cbegin();

            if ( iter->allItemsOnTopFloor() ) {
                return iter->getNumSteps();
            }

            // Generate elevator contents
            unsigned elevatorFloorNum = iter->getElevatorFloor();
            Floor elevatorFloorItems = iter->getFloor( elevatorFloorNum );
            std::set<Floor> elevatorCombos =
                elevatorFloorItems.generateElevatorCombos();

            // For each elevator contents, send to above and below floors (if
            // floor exists).
            unsigned numFloors = iter->getNumFloors();
            for ( const auto& combo : elevatorCombos ) {
                if ( elevatorFloorNum != 0 ) {
                    ContainmentFloors newCF( *iter );
                    newCF.incNumSteps();

                    unsigned nextFloorNum = elevatorFloorNum - 1;
                    Floor elevatorFloorItems = newCF.getFloor( elevatorFloorNum );
                    Floor nextFloorItems = newCF.getFloor( nextFloorNum );
                    for ( const auto& item : combo.getItemSet() ) {
                        nextFloorItems.insert( item );
                        elevatorFloorItems.remove( item );
                    }

                    newCF.setFloor( nextFloorNum, nextFloorItems );
                    newCF.setFloor( elevatorFloorNum, elevatorFloorItems );
                    newCF.setElevatorFloor( nextFloorNum );

                    // Insert the new floor set into the simulation queue if
                    // we haven't seen it or one of its aliases.
                    std::string s = newCF.toNormalizedString();
                    if ( newCF.isSafe() ) {
                        auto p = alreadySimulated.insert( s );
                        if ( p.second == true ) {
                            floorQueue.push_back( newCF );
                        }
                    }
                }

                if ( elevatorFloorNum != numFloors - 1 ) {
                    ContainmentFloors newCF( *iter );
                    newCF.incNumSteps();

                    unsigned nextFloorNum = elevatorFloorNum + 1;
                    Floor elevatorFloorItems = newCF.getFloor( elevatorFloorNum );
                    Floor nextFloorItems = newCF.getFloor( nextFloorNum );
                    for ( const auto& item : combo.getItemSet() ) {
                        nextFloorItems.insert( item );
                        elevatorFloorItems.remove( item );
                    }

                    newCF.setFloor( nextFloorNum, nextFloorItems );
                    newCF.setFloor( elevatorFloorNum, elevatorFloorItems );
                    newCF.setElevatorFloor( nextFloorNum );

                    // Insert the new floor set into the simulation queue if
                    // we haven't seen it or one of its aliases.
                    std::string s = newCF.toNormalizedString();
                    if ( newCF.isSafe() ) {
                        auto p = alreadySimulated.insert( s );
                        if ( p.second == true ) {
                            floorQueue.push_back( newCF );
                        }
                    }
                }
            }
            floorQueue.pop_front();
        }

        // We shouldn't get here.
        assert( ! "Got to invalid location" );
        return 0;
    }
};

#endif // DAY11_H
