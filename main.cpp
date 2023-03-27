#include <iostream>
#include "tinyxml2.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <bitset>
using namespace tinyxml2;
int main() {
    XMLDocument doc;

    std::vector<std::string> ID; 
    std::vector<std::string> first_grid;
    std::string dir;
    dir= "Output";
    std::filesystem::create_directories(dir);
    int ii=0;
    for(const auto& f : std::filesystem::directory_iterator("map_pro_tmx")) {
        if(f.path().extension() != ".tmx") continue;
        doc.LoadFile(f.path().string().c_str());
        std::ofstream outfile(dir+"/"+"map"+std::to_string(ii++)+ ".txt");
        std::cout<<"Map name: "<< f.path().stem().string()<<std::endl;
        //std::cout << "\nmap info:\n----------------------------------\n " << std::endl;
        XMLElement* map = doc.FirstChildElement("map");
        int width = map->IntAttribute("width");
        int height = map->IntAttribute("height");
        std::cout << "Tile width: " << width << std::endl;
        std::cout << "Tile height: " << height << std::endl;
        outfile << f.path().stem().string() << "\n";
        outfile << width << " " << height << "\n";
        //std::cout << "\nmap sources:\n----------------------------------\n " << std::endl;
        XMLElement* tileset = map->FirstChildElement("tileset");
        int total = 0;
        while (tileset != nullptr) {
            // std::cout << "Tileset:" << std::endl;
            // std::cout << "  firstgid: " << tileset->Attribute("firstgid") << std::endl;
            // std::cout << "  source: " << tileset->Attribute("source") << std::endl;
            std::string c = tileset->Attribute("source");
            c = c.substr(c.find_last_of("/")+1,c.find_last_of(".")-c.find_last_of("/")-1);
            //outfile << i++ <<" "<<tileset->Attribute("firstgid")<<" "<< c << "\n";
            first_grid.push_back(tileset->Attribute("firstgid"));
            ID.push_back(c);
            total++;
            tileset = tileset->NextSiblingElement("tileset");   
        }
        outfile << total << "\n";
        for(int i=0;i<total;i++){
            outfile <<first_grid[i]<<" "<< ID[i] << "\n";
        }
        ID.clear();
        first_grid.clear();
        std::vector<std::string> grid;
        int i=0;
        XMLElement* layer = map->FirstChildElement("layer");
        while(layer != nullptr){
            layer = layer->NextSiblingElement("layer");  
            i++;
        }
        layer = map->FirstChildElement("layer");
        outfile << i << "\n";
        while (layer != nullptr) {
            const char* name = layer->Attribute("name");
            const char* csv = layer->FirstChildElement("data")->GetText();

            // std::cout << "Layer name: " << name << std::endl;
            // std::cout << "Layer data: " << csv << std::endl;

            std::stringstream ss(csv);
            int tileid;
            char comma;
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x)
                 {
                    ss >> tileid >> comma;
                    outfile << tileid;
                    if (x < width - 1) {
                        outfile << " ";
                    }
                }
                outfile << "\n";
            }
            outfile << "\n";
            layer = layer->NextSiblingElement("layer");        
        }
        outfile.close();
        std::ofstream outfile2(dir+"/"+ "mapsize.txt");
        for(const auto& f : std::filesystem::directory_iterator("map_pro_tmx/res")) {
            doc.LoadFile(f.path().string().c_str());
            XMLElement* tileset = doc.FirstChildElement("tileset");
            int tilecount = tileset->IntAttribute("tilecount");
            std::string c = f.path().stem().string();
            outfile2 << c << " " << tilecount << "\n";
        }
        outfile2.close();
    }
    return 0;
}