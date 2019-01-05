//
//  PartInfo.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 20/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit.UIImage

public class PartInfo {
    
    var image:UIImage?
    var longitude:Double?
    var latitude:Double?
    var found:Bool?
    var imageDownloadURL:String?

    func getImageDownloadURL()->String{
        return self.imageDownloadURL!
    }
    
    func getLongitude()->Double{
        return self.longitude!
    }
    
    func getLatitude()->Double{
        return self.latitude!
    }
    
    func getImage()->UIImage?{
        if let image = self.image{
            return image
        }
        return nil
    }
    
    func isFound()->Bool{
        return self.found!
    }
    
    func setImageDownloadURL(imageDownloadURL:String)->Void{
        self.imageDownloadURL = imageDownloadURL
    }
    
    func setImage(image:UIImage){
        self.image = image
    }
    
    func setLongitude(longitude:Double)->Void{
        self.longitude = longitude
    }
    
    func setLatitude(latitude:Double)->Void{
        self.latitude = latitude
    }

    func setFound(found:Bool)->Void{
        self.found = found
    }
    
    init(){
        
    }
    
    init(found:Bool, latitude:Double, longitude:Double, imageDownloadURL:String){
        self.longitude = longitude
        self.latitude = latitude
        self.found = found
        self.imageDownloadURL = imageDownloadURL
    }
    
    init(image:UIImage, found:Bool, latitude:Double, longitude:Double){
        self.longitude = longitude
        self.latitude = latitude
        self.found = found
        self.image = image
    }
    
    init(found:Bool, latitude:Double, longitude:Double){
        self.longitude = longitude
        self.latitude = latitude
        self.found = found
    }
    
    deinit{
        self.longitude = nil
        self.latitude = nil
        self.found = nil
        self.imageDownloadURL = nil
        self.image = nil
        print("Part Info is being deallocated")
    }
}

