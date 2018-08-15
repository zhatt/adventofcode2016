/*
 * Machine for day 12.
*/

#include <cassert>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class Machine;
typedef std::map<std::string,int64_t> Registers;

// Empty register set.
const Registers defaultRegisters;

struct MachineState {
    unsigned pc = 0;
    Registers registers;

    MachineState( const Registers& registers ) :
        pc( 0 ),
        registers( registers )
        {}

    void dump( std::ostream& os ) const {

        unsigned id = 0;
        const auto iter = registers.find( "p" );
        if ( iter != registers.end() ) {
            id = iter->second;
        }

        os << id << ":pc=" << this->pc << "\n";

        for ( const auto& val : this->registers ) {
            os << id << ":" << val.first << "=" << val.second << "\n";
        }
    }
};

class Instruction {
    unsigned numReg_;
    std::string xregim_;
    std::string yregim_;

    public:
    Instruction() :
                 numReg_( 0 ) {}

    Instruction( std::string x ) :
                 numReg_( 1 ), xregim_( x ) {}

    Instruction(  std::string x, std::string y ) :
                 numReg_( 2 ), xregim_( x ), yregim_( y ) {}

    virtual void execute( MachineState& machine ) = 0;

    private:
    int64_t val( const std::string& v,
                 const std::map<std::string,int64_t>& registers ) {
        std::istringstream parser( v );
        int value;

        if ( parser >> value ) {
            return value;
        } else {
            auto iter = registers.find( v );
            if ( iter != registers.end() ) {
                return iter->second;
            } else {
                return 0;
            }
        }
    }

    public:
    int64_t xval( const std::map<std::string,int64_t>& registers ) {
        assert( numReg_ >= 1 );
        return val( xregim_, registers );
    }

    int64_t yval( const std::map<std::string,int64_t>& registers ) {
        assert( numReg_ >= 2 );
        return val( yregim_, registers );
    }

    std::string xregName() {
        assert( numReg_ >= 1 );
        return xregim_;
    }

    std::string yregName() {
        assert( numReg_ >= 1 );
        return yregim_;
    }
};


class Inc : public Instruction {
    public:
    Inc( std::string x ) : Instruction( x ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] ++;
        state.pc ++;
    }
};

class Dec : public Instruction {
    public:
    Dec( std::string x ) : Instruction( x ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] --;
        state.pc ++;
    }
};

class Jnz : public Instruction {
    public:
    Jnz( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        if ( xval( state.registers ) != 0 ) {
            state.pc += yval( state.registers );
        } else {
            state.pc ++;
        }
    }
};

class Cpy : public Instruction {
    public:
    Cpy( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ yregName() ] = xval( state.registers );
        state.pc ++;
    }
};

class Dmp : public Instruction {
    std::ostream& os_;
    public:
    Dmp( std::ostream& os ) : Instruction(), os_(os) {}

    virtual void execute( MachineState& state ) override {

        state.dump( os_ );

        state.pc ++;
    }
};

struct Program : std::vector<Instruction*> {

    void parse( std::istream& is, std::ostream& os ) {
        std::string line;
        while ( getline( is, line ) ) {
            std::istringstream parser( line );

            std::string cmd;
            std::string val1, val2;

            parser >> cmd;
            parser >> val1;
            parser >> val2;

            if ( cmd == "cpy" ) {
                push_back( new Cpy( val1, val2 ) );
            } else if ( cmd == "inc" ) {
                push_back( new Inc( val1 ) );
            } else if ( cmd == "dec" ) {
                push_back( new Dec( val1 ) );
            } else if ( cmd == "jnz" ) {
                push_back( new Jnz( val1, val2 ) );
            } else if ( cmd == "dmp" ) {
                push_back( new Dmp( os ) );
            } else {
                assert( !"Unknown instruction" );
            }
        }
    }

    Program() {}
};

class Machine {
    MachineState state_;
    const std::vector<Instruction*>& program_;

public:
    Machine ( const Registers& initialRegisters,
              const Program& program ) :
        state_( initialRegisters ),
        program_( program ) {}

    bool pastEnd() { return state_.pc >= program_.size(); }

    void execute() {
        assert( program_.size() > state_.pc );
        program_[ state_.pc ]->execute( state_ );
    }

    unsigned pc() {
        return state_.pc;
    }

    int64_t getReg( const std::string& reg ) {
        return state_.registers[ reg ];
    }

    void dump( std::ostream& os ) const {
        return state_.dump( os );
    }
};

