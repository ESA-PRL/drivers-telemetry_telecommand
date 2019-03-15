#ifndef _TMTC_MESSAGES_HPP_
#define _TMTC_MESSAGES_HPP_

#include <iostream>
#include <base/Time.hpp>
#include <string>

namespace telemetry_telecommand
{
    namespace messages
    {

        enum Producer
        {
            PANCAM,
            NAVCAM,
            LOCCAM,
            MAST,
            LIDAR,
            FRONT,
            TOF,
            HAZCAM,
            REAR,
            AUTONAV // This is not a sensor but the software component we refer to as producer of different processed products. Typically AutoNav would be using the images coming from the NavCam.
        };

        enum ProductType // Be careful when changing this enum. 3DROCS uses corresponding integer numbers to select the type. Changing the enum will need to modify 3DROCS TC command. 
        {
            IMAGE,
            DISTANCE,
            POINT_CLOUD,
            DEM,
            ALL,
            STEREO, // used to ask for stereo images
            STEREO_LEFT, // used to mark provided images
            STEREO_RIGHT,
            PARTIAL_NAVMAP, // AutoNav-specific product
            NAVMAP,         // AutoNav-specific product
            TRAJMAP         // AutoNav-specific product
        };

        enum Mode  // Be careful when changing this enum. 3DROCS uses corresponding integer numbers to select the type. Changing the enum will need to modify 3DROCS TC command. 
        {
            CONTINUOUS=-2,
            STOP=-1,
            ONE_SHOT=0,
            PERIODIC=1
        };

        struct Telemetry
        {
            std::string productPath;  // path to product file
            Producer productSource;   // (sensor ID/name)
            ProductType type;         // (image, distance image, point cloud, DEM, ..)
            long sequenceCounter;
            base::Time timestamp;
        };

        struct Telecommand
        {
            ProductType productType;
            Mode productMode;
            uint64_t usecPeriod; // only applicable for mode==PERIODIC
        };

    }
}

#endif // _TMTC_MESSAGES_HPP_
