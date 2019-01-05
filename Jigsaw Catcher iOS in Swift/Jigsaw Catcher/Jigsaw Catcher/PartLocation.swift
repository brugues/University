//
//  PartLocation.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 8/2/18.
//  Copyright © 2018 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import MapKit

class PartLocation: NSObject, MKAnnotation{
    var identifier : String?
    var title: String?
    var coordinate: CLLocationCoordinate2D
    init(name : String, lat : CLLocationDegrees, long : CLLocationDegrees, id : String){
        title = name
        coordinate = CLLocationCoordinate2DMake(lat, long)
        identifier = id
    }
    
    deinit{
        self.identifier = nil
        self.title = nil
        print("PartLocation is being deallocated")
    }
}

class PartLocationList: NSObject {
    var parts = [PartLocation]()
    
    override init(){
        
    }
    
    deinit{
        parts.removeAll()
        print("PartLocationList is being deallocated")
    }
    
    func addLocation(partInfo: PartInfo, index: Int){
        parts += [PartLocation(name:"Part " + String(describing: index),lat: partInfo.getLatitude(), long: partInfo.getLongitude(), id: String(describing: index))]
    }
}
