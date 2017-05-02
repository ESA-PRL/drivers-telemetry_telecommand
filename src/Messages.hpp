#ifndef _TMTC_MESSAGES_HPP_
#define _TMTC_MESSAGES_HPP_

#include <iostream>
#include <base/time.h>
#include <string>

namespace telemetry_telecommand
{
    namespace messages
    {

        enum Producer
        {
            MAST,
            LIDAR,
            FRONT,
            TOF,
            HAZCAM,
            REAR
        };

        enum ProductType
        {
            IMAGE,
            DISTANCE,
            POINT_CLOUD,
            DEM,
            ALL
        };

        enum Mode
        {
            CONTINUOUS=-2,
            STOP=-1,
            ONE_SHOT=0,
            PERIODIC=1
        };

        typedef struct
        {
            std::string productPath;  // path to product file
            Producer productSource;   // (sensor ID/name)
            ProductType type;         // (image, distance image, point cloud, DEM, ..)
            long sequenceCounter;
            base::Time timestamp;
        } Telemetry;

        typedef struct
        {
            ProductType productType;
            Mode productMode;
            uint64_t usecPeriod; // only applicable for mode==PERIODIC
        } Telecommand;

    }
}

#endif // _TMTC_MESSAGES_HPP_
