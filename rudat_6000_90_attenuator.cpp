#include "rudat_6000_90_attenuator.hpp"
#include <cstdlib>

namespace md1tech
{
    const double   Rudat6k90::kMinAttenation   =  0.00  ;
    const double   Rudat6k90::kMaxAttenation   = 90.00  ;
    const double   Rudat6k90::kStepAttenuation =  0.25 ;
    unsigned short Rudat6k90::kVendorId        = 0x20ce ;
    unsigned short Rudat6k90::kProductId       = 0x0023 ;

    Rudat6k90::Rudat6k90( hid_device * pHandle ) :
        m_pHandle( pHandle ),
        m_txBuffer( ),
        m_rxBuffer( )
    {
    }

    Rudat6k90::~Rudat6k90( )
    {
    }
    
    bool Rudat6k90::getSerialNumber( std::string& serial_number )
    {
        bool retval = false ;

        if ( m_pHandle != 0 )
        {
            m_txBuffer[0] = 41 ;

            if ( hid_write( m_pHandle, &m_txBuffer[0], 64 ) != -1 ) // ask the attenuator to provide its serial number
            {
                if ( hid_read( m_pHandle, &m_rxBuffer[0], 64 ) != -1 )    // read the serial number back from the device
                {
                    std::string tmp( reinterpret_cast< const char* >( &m_rxBuffer[1] ) ) ;
                    serial_number.clear() ;
                    serial_number = tmp ;
                    retval = true ;
                }
            }
        }

        return retval ;
    }

    bool Rudat6k90::getPartNumber( std::string & part_number )
    {
        bool retval = false ;

        if ( m_pHandle != 0 )
        {
            m_txBuffer[0] = 40 ;

            if ( hid_write( m_pHandle, &m_txBuffer[0], 64 ) != -1 ) // ask the attenuator to provide its serial number
            {
                if ( hid_read( m_pHandle, &m_rxBuffer[0], 64 ) != -1 )    // read the serial number back from the device
                {
                    std::string tmp( reinterpret_cast< const char* >( &m_rxBuffer[1] ) ) ;
                    part_number.clear() ;
                    part_number = tmp ;
                    retval = true ;
                }
            }
        }

        return retval ;
    }

    double Rudat6k90::minimumAttenuation( )
    {
        return kMinAttenation ;
    }

    double Rudat6k90::maximumAttenuation( )
    {
        return kMaxAttenation ;
    }

    double Rudat6k90::stepAttenuation( )
    {
        return kStepAttenuation ;
    }

    bool Rudat6k90::readAttenuation( double& attenuation_db )
    {
        bool retval = false ;

        if ( m_pHandle != 0 )
        {
            m_txBuffer[0] = 18 ;

            if ( hid_write( m_pHandle, &m_txBuffer[0], 64 ) != -1 ) // ask the attenuator to provide its serial number
            {
                if ( hid_read( m_pHandle, &m_rxBuffer[0], 64 ) != -1 )    // read the serial number back from the device
                {
                    attenuation_db = static_cast< double >( m_rxBuffer[1] ) + ( 0.25 * static_cast<double >( m_rxBuffer[2] ) ) ;
                    retval = true ;
                }
            }
        }

        return retval ;
    }

    bool Rudat6k90::setAttenuation ( double attenuation_db )
    {
        bool retval = false ;

        if ( m_pHandle != 0 && attenuation_db >= kMinAttenation && attenuation_db <= kMaxAttenation )
        {
            m_txBuffer[0] = 19 ;
            m_txBuffer[1] = static_cast< unsigned char >( attenuation_db ) ;
            m_txBuffer[2] = static_cast< unsigned char >( (attenuation_db - static_cast< double >( m_txBuffer[1] ) ) * 4.0 ) ;
            m_txBuffer[3] = 1 ; //set channel number to 1

            if ( hid_write( m_pHandle, &m_txBuffer[0], 64 ) != -1 ) // ask the attenuator to provide its serial number
            {
                if ( hid_read( m_pHandle, &m_rxBuffer[0], 64 ) != -1 )    // read the serial number back from the device
                {
                    retval = true ;
                }
            }
        }

        return retval ;
    }
}
