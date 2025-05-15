
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include <vector>
#include <fstream>
#include <sstream> 
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include "../data/vec.hpp"  // Updated to use the correct relative path


#include "rapidxml.hpp" // RapidXML header


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

namespace gps {
/**
 * @brief Class handling
 */
class gps_trace {
    public: // visible by net objects and the main program
        struct trkpt
        {
            double lat;
            double lon;

            //todo: add timestamp management
            //todo: trkpt can also have elevation from <ele> child
        };

        
        /**
         * @brief Main constructor.
         * 
         * @param src_gpx_file The src of the gpx file to load
         */
        gps_trace(const std::string& src_gpx_file, const vec<2> origin);


        /**
         * @brief Load and read a gpx file
         * 
         * @param src The src of the gpx file to load
         */
        bool load_gpx_file(const std::string& src);


        /**
         * @brief print a trkpt lat and lon in the console
         */
        void print_trkpt(trkpt t);


        /**
         * @brief Haversine formula to convert lat/lon to meters
         */
        vec<2> coord_to_meters(double lat, double lon, double ref_lat, double ref_lon);

    private:
        std::vector<trkpt> track;
        vec<2> origin;
};

}
}