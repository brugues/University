//
//  GameList.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 12/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import FirebaseAuth
import FirebaseDatabase
import FirebaseStorage
import Foundation.NSData

class GameList: UITableViewController {
    
    var gameSessionsRef: DatabaseReference!
    var gameRef: DatabaseReference!
    var loggedUser: AnyObject!
    var games : [Game] = []
    var listOfGameID : [String] = []
    var images : [UIImage] = []
    var searchActive : Bool = false
    var gameHasJustLaunched = true
    
    override func viewWillAppear(_ animated: Bool) {
        let prefs = UserDefaults.standard
        if(prefs.bool(forKey: "gameCreated") == true){
            self.games.removeAll()
            self.listOfGameID.removeAll()
            self.images.removeAll()
            getUserActiveGames()
            prefs.set(false, forKey: "gameCreated")
            prefs.synchronize()
        }else if gameHasJustLaunched{
            gameHasJustLaunched = false
            getUserActiveGames()
        }
        
        if #available(iOS 11.0, *) {
            self.navigationController?.navigationBar.prefersLargeTitles = false
        } else {
            // Fallback on earlier versions
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view, typically from a nib.
        
        //Get current user
        if let loggedUser = Auth.auth().currentUser{
            self.loggedUser = loggedUser
        }
        
        self.hideKeyboardWhenTappedAround()
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    
    
    func getUserActiveGames(){
        print("Entered getUserActiveGames()")
        gameSessionsRef = Database.database().reference().child("jigsaw_session/" + loggedUser.uid)
        gameRef = Database.database().reference().child("jigsaws/")
        
        gameSessionsRef.observeSingleEvent(of: .value, with: { (snapshot) in
            if let result = snapshot.children.allObjects as? [DataSnapshot] {
                for child in result {
                    self.listOfGameID.append(child.key)
                }
                self.gameRef.observeSingleEvent(of: .value, with: { snapshot in
                    print("EEEEEEEEEEEEEEEO " + String(describing: snapshot.children.allObjects.count))
                    for rest in snapshot.children.allObjects as! [DataSnapshot] {
                        guard let restDict = rest.value as? [String: Any] else { continue }
                        if(self.listOfGameID.contains(rest.key)){
                            let createdBy = restDict["createdBy"] as? String
                            let dateCreated = restDict["dateCreated"] as? String
                            let generalLocation = restDict["generalLocation"] as? String
                            let gameName = restDict["gameName"] as? String
                            let numParts = restDict["numParts"] as? Int
                            let numPlayers = restDict["numPlayers"] as? Int
                            let radius = restDict["radius"] as? Double
                            let imageDownloadURL = restDict["imageDownloadURL"] as? String
                            let latitude = restDict["latitude"] as? Double
                            let longitude = restDict["longitude"] as? Double
                                                        
                            let tempGame = Game(createdBy: createdBy!, dateCreated: dateCreated!, generalLocation: generalLocation!, name: gameName!, numParts: numParts!, radius: radius!, numPlayers: numPlayers!, imageDownloadURL: imageDownloadURL!)
                            tempGame.gameID = rest.key
                            tempGame.longitude = longitude
                            tempGame.latitude = latitude
                            
                            self.downloadImage(game: tempGame)
                        }
                    }
                })
            } else {
                print("No results")
            }
        }) { (error) in
            print(error.localizedDescription)
        }
    }
    
    func downloadImage(game : Game) {
        let storageReference = Storage.storage().reference(forURL: game.imageDownloadURL!)
        storageReference.getData(maxSize: 5 * 1024 * 1024) { (data, error) -> Void in
            // Create a UIImage, add it to the array
            let pic = UIImage(data: data!)
            game.image = pic!
            print(game.image!)
            self.games.append(game)
            //Refresh view
            DispatchQueue.main.async {
                self.tableView.reloadData()
            }
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "toGameController" {
            if let indexPath = self.tableView.indexPathForSelectedRow {
                let selectedGame = self.games[indexPath.row]
                let destinationViewController = segue.destination as! GameViewController
                destinationViewController.game = selectedGame
            }
        }
    }
    
    /* Table View Delegates */
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.games.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let game = games[indexPath.row]
        let cellID = "gameCell"
        
        let cell = tableView.dequeueReusableCell(withIdentifier: cellID, for: indexPath) as! GameCell
        
        if let image = game.image{
            cell.gameImage.image = image
        }
        cell.gameLocation.text = game.generalLocation
        cell.gameName.text = game.name
        cell.numberPieces.text = "Pieces: " + String(describing: game.numParts!)
        cell.numberPlayers.text = "Players: " + String(describing: game.numberPlayers!)
        
        return cell
    }
}
