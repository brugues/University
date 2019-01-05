//
//  ImageSplitter.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 2/2/18.
//  Copyright © 2018 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit

class ImageSplitter{
    var image : UIImage?
    var width : Int?
    var height : Int?
    var parts : Int?
    var pieces : [UIImage] = []
    
    init(image:UIImage, width:Int, height:Int, parts:Int){
        self.image = image
        self.width = width
        self.height = height
        self.parts = parts
    }
    
    deinit{
        self.image = nil
        self.width = nil
        self.height = nil
        self.parts = nil
        self.pieces.removeAll()
        
        print("Image Splitter is being deallocated")
    }
    
    
    func split() -> [UIImage] {
        if (parts != 0) {
            let nParts : Int = Int(sqrt(Double(parts!)))
            
            let w_inc : Int = Int(width! / nParts)
            let h_inc : Int = height! / nParts
            
            //xCoord and yCoord are the pixel positions of the image chunks
            var yCoord : Int = 0
            
            for _ in 0..<nParts{
                var xCoord : Int = 0
                
                for _ in 0..<nParts{
                    let rect : CGRect = CGRect(x: xCoord, y: yCoord, width: w_inc, height: h_inc)
                    // Create bitmap image from context using the rect
                    let imageRef = image?.cgImage?.cropping(to: rect)
                    
                    pieces.append(UIImage(cgImage: imageRef!))
                    xCoord += w_inc
                }
                yCoord += h_inc
            }
        
            pieces.append(image!)
        }
        
        return pieces
    }
}
