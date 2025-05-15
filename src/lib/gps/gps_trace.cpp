#include "gps_trace.hpp"

namespace fcpp {

namespace gps {

gps_trace::gps_trace(const std::string &src_gpx_file, const vec<2> origin)
{
    this->origin = origin;
    if (!load_gpx_file(src_gpx_file))
    {
        std::cout << "gps_trace() - Error while opening the gpx file";
    }
};

bool gps_trace::load_gpx_file(const std::string& src) {
    std::ifstream file(src);
    if (!file.is_open()) {
        std::cout << "load_gpx_file() - Failed to open file";
        return false; // Failed to open file
    }

    // Save file to string stream for processing
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    try {
        rapidxml::xml_document<> doc;
        doc.parse<0>(&content[0]);

        rapidxml::xml_node<> *gpx_node = doc.first_node("gpx");
        if (!gpx_node) { return false; }

        rapidxml::xml_node<> *trk_node = gpx_node->first_node("trk");
        if (!trk_node) { return false; }

        for (rapidxml::xml_node<>* trkseg_node = trk_node->first_node("trkseg"); 
        trkseg_node; 
        trkseg_node = trkseg_node->next_sibling("trkseg")) {
                
            for (rapidxml::xml_node<>* trkpt_node = trkseg_node->first_node("trkpt"); 
            trkpt_node; 
            trkpt_node = trkpt_node->next_sibling("trkpt")) {

                rapidxml::xml_attribute<>* lat = trkpt_node->first_attribute("lat");
                rapidxml::xml_attribute<>* lon = trkpt_node->first_attribute("lon");

                if (lat && lon) {
                    vec<2> pos;
                    if (track.empty()) {
                        pos = make_vec(0.0, 0.0);
                    } else {
                        pos = coord_to_meters(std::stod(lat->value()), std::stod(lon->value()), track[0].lat, track[0].lon);
                    }
                    
                    trkpt point;
                    point.lat = pos[0];
                    point.lon = pos[1];

                    track.push_back(point);
                    print_trkpt(point);
                }
            }
        }

    } catch (const rapidxml::parse_error& e) {
        return false;
    } catch (const std::exception& e) {
        return false;
    }

    return !track.empty(); // Return true if at least one point was loaded
}

void gps_trace::print_trkpt(trkpt t) {
    std::cout << std::setprecision(17);
    std::cout << t.lat << " - " << t.lon << std::endl;
}

vec<2> gps_trace::coord_to_meters(double lat, double lon, double ref_lat, double ref_lon) {
    const double EARTH_RADIUS = 6371000.0;

    // todo: update PI with appropriate value
    //calculates the distance between points
    double d_lat = (lat * 3.14 / 180.0) - (ref_lat * 3.14 / 180.0);
    double d_lon = (lon * 3.14 / 180.0) - (ref_lon * 3.14 / 180.0);

    double x = EARTH_RADIUS * std::cos(ref_lat) * d_lon;
    double y = EARTH_RADIUS * d_lat;

    return make_vec(x, y);
}

}
}