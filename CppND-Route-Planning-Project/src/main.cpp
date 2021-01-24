#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include <limits>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}

int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    //Declare floats 'start_x', 'start_y', 'end_x', 'end_y'
    float start_x, start_y, end_x, end_y;

    std::cout <<" Taking User Inputs...\n";
    std::cout <<" Please enter : start_x, start_y, end_x, and end_y in order\n";
    std::cout <<" Input the start_x \n";
    std::cin >> start_x;
    
    //if start_x is the range below 0 and more than 100, take the input again.
    while( !(std::cin) || start_x < 0 || start_x > 100){
        std::cout << "Invalid Input, Enter start_x from 0 to 100";
        std::cin.clear();
        // https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> start_x;
    }

    std::cout <<" Input the start_y \n";
    std::cin >> start_y;

    //If start_y is the range below 0 and more than 100, take the input again.
    while( !(std::cin) || start_y < 0 || start_y > 100){
        std::cout << "Invalid Input, Enter start_y from 0 to 100";
        std::cin.clear();
        // https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> start_y;
    }

    std::cout << " Input the end_x \n";
    std::cin >> end_x;
    //If end_x is the range below 0 and more than 100, take the input again. 
    while( !(std::cin) || end_x < 0 || end_x > 100){
        std::cout << "Invalid Input, Enter end_x from 0 to 100";
        std::cin.clear();
        // https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> end_x;
    }

    std::cout << " Input the end_y \n";
    std::cin >> end_y;

    while(!(std::cin) || end_y < 0 || end_y > 100){
        std::cout << "Invalid Input, Enter end_y from 0 to 100";
        std::cin.clear();
        // https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> end_y;
    }

    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
