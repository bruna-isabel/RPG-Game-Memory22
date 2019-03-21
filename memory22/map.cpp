#include "map.h"
#include "textures.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

map::map(SDL_Renderer* ren)
{
    //All of the textures
    grass = textureCreator::loadTexture("mossover.png", ren);
    water = textureCreator::loadTexture("ice.png", ren);
    tree = textureCreator::loadTexture("tree.png", ren);
    
    //Position of rect starts at 0,0
    src_rect.x = src_rect.y = 0;
    //Width and height of rectangle
    src_rect.w = src_rect.h = dest_rect.w = dest_rect.h = 32;
}

//Transforms text file in array
std::vector<std::string> map::createArray(std::string textFile)
{
    //opening file that contains array
    std::ifstream field(textFile);
    std::vector<std::string> mapField;
    std::string line;
    
    // read the next line from File until it reaches the end.
    while (std::getline(field, line))
    {
        // line contains string of length > 0 then save it in vector
        if(line.size() > 0)
            mapField.push_back(line);
    }
    //close The File
    field.close();
    
    return mapField;
}

//renderes map on screen
void map::drawMap(SDL_Renderer* ren, std::string textFile)
{
    std::vector<std::string> arrayMap = createArray("field.txt");
    
    for (int i = 0; i<arrayMap.size(); i++)
    {
        std::string line = arrayMap[i];
        for(std::string::iterator it = line.begin(); it != line.end(); it = next(it)) {
        
            if (*it == '0')
            {
                std::cout << *it;
                textureCreator::draw(ren, grass, src_rect, dest_rect);
            }
        }
    }
    /*
    int type = 0;
    
    for(int row=0; row<32; row++)
    {
            //type = arrayMap[32];
            //dest_rect.x = col * 25;
            dest_rect.y = row * 25;
            
            switch(type)
            {
                case 0:
                    textureCreator::draw(ren, grass, src_rect, dest_rect);
                    break;
                case 1:
                    textureCreator::draw(ren, water, src_rect, dest_rect);
                    break;
                case 2:
                    textureCreator::draw(ren, tree, src_rect, dest_rect);
                default:
                    break;
            }
        }
    }*/
}
