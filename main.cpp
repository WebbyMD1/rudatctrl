#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <hidapi/hidapi.h>
#include "rudat_6000_90_attenuator.hpp"
#include <cxxopts.hpp>

static unsigned short sVendorId  = 0x20ce ;
static unsigned short sProductId = 0x0023 ;

// RUDAT programmable attenuators are represented in the Linux filesystem as:
// /dev/hidraw0 ... /dev/hidraw1 etc
// However with multiple attenuators in a system we can never know which device
// is enumerated as hidraw0 or hidraw1. On this basis we must identify attenuators
// based upon their serial number as these are the only ID unique to an individual
// attenuator.

int main( int argc, char* argv[] )
{
    int retval = 0 ;
    cxxopts::Options options( "rudatctrl", "Control of mini-circuits Rudat 6000 USB attenuators" ) ;
    options.add_options()
        ( "l,list",   "List serial numbers of connected attenuators" )
        ( "h,help",   "Dislpay help"                                 )
        ( "s,serial", "Serial number", cxxopts::value<std::string>() )
        ( "a,atten",  "Attenuation",   cxxopts::value<int>()         ) ;

    auto result = options.parse( argc, argv ) ;
    int hidinit = hid_init() ;

    if ( hidinit == -1 )
    {
        std::cerr << "hidapi library error" << std::endl ;
        retval = -1 ;
    }

    if ( result.count( "help" ) )
    {
        std::cout << options.help() << std::endl ;
        retval = 0 ;
    }
    else if ( result.count( "list" ) )
    {
        // List all of the Rudat attenuators in the system
        struct hid_device_info * dev     = 0 ;
        struct hid_device_info * cur_dev = 0 ;

        dev = hid_enumerate( sVendorId, sProductId ) ;
        cur_dev = dev ;
        while ( cur_dev )
        {
            hid_device * pHandle = hid_open_path( cur_dev->path ) ;

            if ( pHandle != 0 )
            {
                md1tech::Rudat6k90 attenuator( pHandle ) ;        
                std::string serstr( "" ) ;
                attenuator.getSerialNumber( serstr ) ;
                std::cout << serstr << std::endl ;
                hid_close( pHandle ) ;
            }
        
            cur_dev = cur_dev->next ;
        }

        retval = 0 ;
    }
    else if ( result.count( "serial" ) )
    {
        std::string serialstring = result[ "serial" ].as<std::string>() ;

        // to get here the command line doesn't contain help or list, but does
        // contain serial. Work out if it's get or set and then execute upon it
        if ( result.count( "atten" ) )
        {
            int atten = result[ "atten" ].as<int>() ;

            // Set attenuation command
            struct hid_device_info * dev     = 0 ;
            struct hid_device_info * cur_dev = 0 ;

            dev = hid_enumerate( sVendorId, sProductId ) ;
            cur_dev = dev ;
            bool found = false ;
            while ( cur_dev && found == false )
            {
                hid_device * pHandle = hid_open_path( cur_dev->path ) ;

                if ( pHandle != 0 )
                {
                    md1tech::Rudat6k90 attenuator( pHandle ) ;        
                    std::string serstr( "" ) ;
                    attenuator.getSerialNumber( serstr ) ;
                    
                    if ( serstr == serialstring )
                    {
                        double a = 0 ;
                        if ( attenuator.setAttenuation( atten ) != true )
                        {
                            std::cerr << "attenuation out of range" << std::endl ;
                        }
                        else
                        {
                            found = true ;
                        }
                    }

                    hid_close( pHandle ) ;
                }
            
                cur_dev = cur_dev->next ;
            }

            if ( found == true ) { retval =  0 ; }
            else                 { retval = -1 ; }
        }
        else
        {
            // Get attenuation command
            struct hid_device_info * dev     = 0 ;
            struct hid_device_info * cur_dev = 0 ;

            dev = hid_enumerate( sVendorId, sProductId ) ;
            cur_dev = dev ;
            bool found = false ;
            while ( cur_dev && found == false )
            {
                hid_device * pHandle = hid_open_path( cur_dev->path ) ;

                if ( pHandle != 0 )
                {
                    md1tech::Rudat6k90 attenuator( pHandle ) ;        
                    std::string serstr( "" ) ;
                    attenuator.getSerialNumber( serstr ) ;
                    
                    if ( serstr == serialstring )
                    {
                        double a = 0 ;
                        if ( attenuator.readAttenuation( a ) != true )
                        {
                            std::cerr << "error reading attenuation" << std::endl ;
                        }
                        else
                        {
                            std::cout << a << std::endl ;
                            found = true ;
                        }

                        
                    }

                    hid_close( pHandle ) ;
                }
            
                cur_dev = cur_dev->next ;
            }

            if ( found == true ) { retval =  0 ; }
            else                 { retval = -1 ; }
        }
    }
    else
    {
        std::cout << options.help() << std::endl ;
        retval = -1 ;   
    }

    hid_exit() ;
    return retval ;
}
