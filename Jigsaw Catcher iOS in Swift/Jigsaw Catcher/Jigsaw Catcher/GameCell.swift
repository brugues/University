//
//  GameCell.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 19/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit

class GameCell: UITableViewCell {
    @IBOutlet weak var gameImage: UIImageView!
    @IBOutlet weak var gameName: UITextField!
    @IBOutlet weak var numberPieces: UITextField!
    @IBOutlet weak var numberPlayers: UITextField!
    @IBOutlet weak var gameLocation: UITextField!
}

