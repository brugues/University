//
//  GameSession.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 20/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

class GameSession {
    
    var dateStart:String?
    var partsFound:Int?

    func getDateStart()->String{
        return self.dateStart!
    }
    
    func getPartsFround()->Int{
        return self.partsFound!
    }
    
    init(dateStart:String, partsFound:Int){
        self.dateStart = dateStart;
        self.partsFound = partsFound;
    }
    
    deinit{
        self.dateStart = nil
        self.partsFound = nil
    }
}
