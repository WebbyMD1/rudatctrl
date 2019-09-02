#ifndef PROGRAMMABLE_ATTENUATOR_INTERFACE_HPP
#define PROGRAMMABLE_ATTENUATOR_INTERFACE_HPP

// This simple abstract base class defines the interface to an RF programmable attenuator.
// This generic interface is not specific to any particular communications technology or
// any specific product or manufacturer. Users should derive from this base class and 
// implement the specifics required for their particular devices.
#include <string>

namespace md1tech
{
    /// Abstract base class defining the interface to an RF programmable attenuator
    class RfProgrammableAttenuator
    {
    public:
        /// Obtain the serial number of the device as an ascii encoded string
        virtual bool getSerialNumber( std::string& serial_number ) = 0 ;

        /// Obtain the part of the device as an ascii encoded string
        virtual bool getPartNumber  ( std::string & part_number ) = 0 ;

        /// Discover the maximum possible attenuation the device provides
        virtual double minimumAttenuation( ) = 0 ;

        /// Discover the minimum possible attenuation the device provides
        virtual double maximumAttenuation( ) = 0 ;

        /// Discover the minimum step size attenuation can be set as
        virtual double stepAttenuation( ) = 0 ;

        /// Read the current attenuation the device is set to
        virtual bool readAttenuation( double& attenation_db ) = 0 ;

        /// Set a new attenuation reading in to the device
        virtual bool setAttenuation ( double attenuation_db ) = 0 ;

    } ;
}

#endif
