// ==============================================================
//  This file is part of MegaGlest (www.megaglest.org)
//
//  Copyright (C) 2014 Sebastian Riedel
//
//  You can redistribute this code and/or modify it under
//  the terms of the GNU General Public License as published
//  by the Free Software Foundation; either version 2 of the
//  License, or (at your option) any later version
// ==============================================================

#include "renderer.h"
//good idea?
#include "mainWindow.h"
#include "tile.h"
#include "mapManipulator.h"

#include <QGraphicsScene>
#include <QAction>
//#include "map_preview.h"
#include <iostream>

namespace MapEditor {
    Renderer::Renderer(MapManipulator *mapman, Status *status){
        this->status = status;
        this->filename = "";
        this->mapman = mapman;
        mapman->setRenderer(this);
        this->map = new Shared::Map::MapPreview();
        this->map->resetFactions(1);//otherwise this map can’t be loaded later
        this->scene = new QGraphicsScene();
        this->historyPos = 0;
        this->width = this->map->getW();
        this->height = this->map->getH();
        this->createTiles();

        this->recalculateAll();
    }

    Renderer::~Renderer(){
        this->removeTiles();
        delete this->map;
        delete this->mapman;
    }

    void Renderer::open(string path){
        this->filename = path;
        this->addHistory();
        this->map->loadFromFile(path);
        if(this->width == this->map->getW() && this->height == this->map->getH()){
            this->updateMap();
            this->recalculateAll();
        }else{
            this->resize();
        }
    }

    //destroys the whole map, takes some time
    void Renderer::resize(){
        this->removeTiles();
        this->width = this->map->getW();
        this->height = this->map->getH();
        this->createTiles();
        this->recalculateAll();//TODO: do we need an .update() ?
        this->scene->setSceneRect(this->scene->itemsBoundingRect());
    }

    void Renderer::save(){
        if(this->isSavable()){//save as last saved or opened file
            this->save(this->filename);
        }
    }

    void Renderer::save(std::string path){
        this->filename = path;//maybe this is the first time we save/open
        std::cout << "save to " << path << std::endl;
        this->map->saveToFile(path);
    }

    bool Renderer::isSavable(){
        return this->filename != "";
    }

    std::string Renderer::getFilename() const{
        return this->filename;
    }

    void Renderer::resetFilename(){
        this->filename = "";
    }


    //‘recalculate’ which borders are necessary, if water is visible etc … for every tile
    void Renderer::recalculateAll(){
        for(int column = 0; column < this->width; column++){
            for(int row = 0; row < this->height; row++){
                this->Tiles[column][row]->recalculate();
            }
        }
    }

    //let all tiles update their cached height
    void Renderer::updateMap(){
        for(int column = 0; column < this->width; column++){
            for(int row = 0; row < this->height; row++){
                this->Tiles[column][row]->updateHeight();
            }
        }
    }


    int Renderer::getHeight() const{
        return this->height;
    }

    int Renderer::getWidth() const{
        return this->width;
    }

    Shared::Map::MapPreview *Renderer::getMap() const{
        return this->map;
    }

    MapManipulator *Renderer::getMapManipulator() const{
        return this->mapman;
    }

    QGraphicsScene *Renderer::getScene() const{
        return this->scene;
    }

    Tile *Renderer::at(int column, int row) const{
        return this->Tiles[column][row];
    }

    Status *Renderer::getStatus() const{
        return status;
    }

    void Renderer::createTiles(){
        this->Tiles = new Tile**[this->width];
        for(int column = 0; column < this->width; column++){
            this->Tiles[column] = new Tile*[this->height];
            for(int row = 0; row < this->height; row++){
                this->Tiles[column][row] = new Tile(this->scene, this, column, row);
            }
        }
    }

    void Renderer::removeTiles(){
        for(int column = 0; column < this->width; column++){
            for(int row = 0; row < this->height; row++){
                delete this->Tiles[column][row];
            }
            delete[] this->Tiles[column];
        }
        delete[] this->Tiles;
    }

    void Renderer::addHistory(){
        this->history.push_back(this->map);
    }

}
