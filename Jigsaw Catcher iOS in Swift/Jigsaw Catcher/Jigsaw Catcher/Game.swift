//
//  Game.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 20/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit.UIImage

class Game {
    
    var gameID:String?
    var createdBy: String?
    var generalLocation: String?
    var name: String?
    var numParts: Int?
    var dateCreated: String?
    var dateFinished: String?
    var numberPlayers: Int?
    var radius: Double?
    var image: UIImage?
    var imageDownloadURL: String?
    var latitude: Double?
    var longitude: Double?
    
    init(){
        
    }
    
    deinit{
        self.gameID = nil
        self.createdBy = nil
        self.generalLocation = nil
        self.name = nil
        self.numParts = nil
        self.dateCreated = nil
        self.dateFinished = nil
        self.numberPlayers = nil
        self.radius = nil
        self.image = nil
        self.imageDownloadURL = nil
        self.latitude = nil
        self.longitude = nil
    }
    
    init(createdBy:String, dateCreated:String, generalLocation:String, name:String, numParts:Int,  radius:Double, numPlayers:Int, imageDownloadURL:String) {
        self.numberPlayers = numPlayers
        self.generalLocation = generalLocation
        self.name = name
        self.numParts = numParts
        self.dateCreated = dateCreated
        self.createdBy = createdBy
        self.radius = radius
        self.imageDownloadURL = imageDownloadURL
    }
}
