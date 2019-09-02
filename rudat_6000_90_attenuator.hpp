#ifndef MINICIRCUITS_RUDAT_6000_90_PROGRAMMABLE_ATTENUATOR_HPP
#define MINICIRCUITS_RUDAT_6000_90_PROGRAMMABLE_ATTENUATOR_HPP

#include "programmable_attenuator_interface.hpp"
#include <hidapi/hidapi.h>
#include <string>

// This simple abstract base class defines the interface to an RF programmable attenuator.
// This generic interface is not specific to any particular communications technology or
// any specific product or manufacturer. Users should derive from this base class and 
// implement the specifics required for their particular devices.

namespace md1tech
{
    /// Abstract base class defining the interface to an RF programmable attenuator
    class Rudat6k90 : public RfProgrammableAttenuator
    {
    public:
        Rudat6k90( hid_device * pHandle ) ;
        virtual ~Rudat6k90( ) ;
        
        virtual bool getSerialNumber( std::string& serial_number ) ;

        virtual bool getPartNumber  ( std::string & part_number ) ;

        virtual double minimumAttenuation( ) ;

        virtual double maximumAttenuation( ) ;

        virtual double stepAttenuation( ) ;

        virtual bool readAttenuation( double& attenuation_db ) ;

        virtual bool setAttenuation ( double attenuation_db ) ;

    private:
        static const double kMinAttenation ;
        static const double kMaxAttenation ;
        static const double kStepAttenuation ;
        static unsigned short kVendorId ;
        static unsigned short kProductId ;

        hid_device * m_pHandle ;        //< A local copy of the USB hid device to use

        unsigned char m_txBuffer[64] ;    //!< A buffer used to send data to attenuator over USB
        unsigned char m_rxBuffer[64] ;    //!< A buffer used to read data from attenuator over USB

    } ;
}

#endif
