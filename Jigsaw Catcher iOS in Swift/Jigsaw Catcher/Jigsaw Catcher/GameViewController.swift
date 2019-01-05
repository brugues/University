//
//  GameController.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 20/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import CoreLocation
import GoogleMobileAds
import FirebaseDatabase
import FirebaseStorage
import FirebaseAuth
import MapKit

class GameViewController:UIViewController, CLLocationManagerDelegate,
    MKMapViewDelegate, GADBannerViewDelegate{
    
    @IBOutlet weak var partsFoundTextField: UITextField!
    
    var window: UIWindow?
    var gameMap : MKMapView?
    var parts : [PartInfo] = []
    var game : Game!
    var gameSession : GameSession!
    var locationManager = CLLocationManager()
    var addBanner : GADBannerView!
    var partsRetrieved = 0
    var gameFinishedAlert = false
    var partsLocation = PartLocationList()
    var partsLocationList = PartLocationList().parts
    var partImages : [UIImage] = []
    
    let COORDINATES_DIFF : Double = 0.00008998233
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        print("Going to List of Games")
        self.locationManager.stopUpdatingLocation()
        self.locationManager.stopMonitoringSignificantLocationChanges()
        self.gameFinishedAlert = false
        self.game = nil
        self.gameSession = nil
        self.parts.removeAll()
        self.partsLocationList.removeAll()
        self.partImages.removeAll()
        self.gameMap = nil
        self.window = nil
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view, typically from a nib.
        self.hideKeyboardWhenTappedAround()
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        self.partsRetrieved = 0
        self.parts.removeAll()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        print("ViewWillAppear")
        self.title = game.name
        
        if #available(iOS 11.0, *) {
            self.navigationController?.navigationBar.prefersLargeTitles = false
        } else {
            // Fallback on earlier versions
        }
        
        if CLLocationManager.locationServicesEnabled() {
            switch(CLLocationManager.authorizationStatus()) {
            case .notDetermined:
                locationManager.requestWhenInUseAuthorization()
                
                break
            case .restricted, .denied:
                let locationAccessMessage = NSLocalizedString("locationAccesMessage", comment: "Location Access Message")
                let errorMessageLocationAccess = NSLocalizedString("errorMessageLocationAccess", comment: "Message Location Access Error")
                
                let alertController = UIAlertController(title: locationAccessMessage, message: errorMessageLocationAccess, preferredStyle: UIAlertControllerStyle.alert)
                let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
                alertController.addAction(alertAction)
                
                present(alertController, animated: true, completion: nil)
                break
                
                
            case .authorizedWhenInUse, .authorizedAlways:
                //Retrieve user info
                //Prepare partInfo list
                prepareLocationManager()
                retrieveGameInfo()
                break
            }
        }
    }
    
    func locationManager(manager: CLLocationManager, didChangeAuthorizationStatus status: CLAuthorizationStatus) {
        if (status == CLAuthorizationStatus.denied) {
            // The user denied authorization
        } else if (status == CLAuthorizationStatus.authorizedAlways) {
            prepareLocationManager()
            retrieveGameInfo()
        }
    }
    
    func addRadiusCircle(location: CLLocation){
        let circle = MKCircle(center: location.coordinate, radius: 1000*self.game.radius!)
        self.gameMap!.add(circle)
    }
    
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        /*if(self.partsRetrieved == self.game.numParts!){
            if self.gameSession.partsFound! != self.game.numParts!{
                //Game not finished
                for i in 0..<self.parts.count{
                    if(self.parts[i].found == false){
                        //Image not found yet

                        if(isWithinRange(partLatitude: self.parts[i].latitude!, partLongitude: self.parts[i].longitude!, location: locations.first!)){
                            //Image within range
                            self.parts[i].found = true
                            var reference : DatabaseReference
                            
                            if let gameID = self.game.gameID{
                                if(i < 10){
                                    reference = Database.database().reference().child("images/"+gameID+"/part_0"+String(i))
                                }else{
                                    reference = Database.database().reference().child("images/"+gameID+"/part_0"+String(i))
                                }
                                
                                //Updating part in database
                                reference.updateChildValues([
                                    "found": true])
                                
                                Database.database().reference().child("jigsaw_session/"+(Auth.auth().currentUser?.uid)!+"/"+gameID+"/game_session").updateChildValues(["partsFound" : self.gameSession.partsFound! + 1])

                                self.partsLocation.addLocation(partInfo: self.parts[i], index: i)
                                self.partsLocationList = self.partsLocation.parts
                                self.gameMap!.addAnnotation(self.partsLocationList.last!)
                                
                                self.partsFoundTextField.text! = "Parts found: " + String(describing: self.gameSession.partsFound! + 1) + "/" + String(describing: self.game.numParts!)
                                
                                if(self.gameSession.partsFound! + 1 == self.game.numParts!){
                                    self.generateGameFinishedAlert()
                                }
                            }
                        }
                    }
                }
            }else{
                //Game finished
                //Check if game ended alert has been issued before
                if !gameFinishedAlert{
                    self.generateGameFinishedAlert()
                }
            }
        }*/
    }
    
    func isWithinRange(partLatitude : Double, partLongitude : Double, location : CLLocation)->Bool{
        /*print("Checking if it's within range")
        print("Piece location: " + String(describing: partLatitude) + String(describing: partLongitude))
        print("Current location: " + String(describing: location.coordinate.latitude) + String(describing: location.coordinate.longitude))*/
        let latDiff = abs(location.coordinate.latitude - partLatitude)
        let longDiff = abs(location.coordinate.longitude - partLongitude)
        
        if(latDiff <= COORDINATES_DIFF && longDiff <= COORDINATES_DIFF){
            return true
        }else{
            return false
        }
    }
    
    func downloadPartImage(part : PartInfo, index : Int){
        let storageReference = Storage.storage().reference(forURL: part.imageDownloadURL!)
        storageReference.getData(maxSize: 1 * 1024 * 1024) { (data, error) -> Void in
            let pic = UIImage(data: data!)
            part.image = pic!
            self.parts[index] = part
            self.partImages.append(part.image!)
            self.partsRetrieved += 1
            
            if(self.partsRetrieved == self.game.numParts!){
                self.createMap()
            }
        }
    }

    func generateErrorRetrievingGameAlert() -> Void{
        let errorMessage = NSLocalizedString("generateErrorRetrievingGameAlert", comment: "Error Retrieving Message")
        
        let alertController = UIAlertController(title: "Error", message: errorMessage, preferredStyle: .alert)
        let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(alertAction)
        present(alertController, animated: true, completion: nil)
    }
    
    func generateGameFinishedAlert() -> Void{
        let gameFinishedMessage = NSLocalizedString("generateGameFinishAlert", comment: "Game Finished Alert")
        let gameFinishedTitle = NSLocalizedString("generateGameFinishTitle", comment: "Game Finished Title")
        
        let alertController = UIAlertController(title: gameFinishedTitle, message: gameFinishedMessage, preferredStyle: .alert)
        let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(alertAction)
        present(alertController, animated: true, completion: nil)
        
        self.gameFinishedAlert = true
    }
    
    func prepareLocationManager(){
        self.locationManager.delegate = self
        self.locationManager.startMonitoringSignificantLocationChanges()
        self.locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation
        self.locationManager.distanceFilter = kCLDistanceFilterNone
        self.locationManager.allowsBackgroundLocationUpdates = false
        self.locationManager.startUpdatingLocation()
    }
    
    func retrieveGameInfo(){
        for _ in 0..<game.numParts! {
            self.parts.append(PartInfo())
        }
        
        if let gameID = game.gameID{
            Database.database().reference().child("jigsaw_session/"+(Auth.auth().currentUser?.uid)!+"/"+gameID).observeSingleEvent(of: .value, with: { (snapshot) in
                for rest_session in snapshot.children.allObjects as! [DataSnapshot]{
                    guard let restSessionDict = rest_session.value as? [String:Any] else { continue }
                    
                    let partsFound = restSessionDict["partsFound"] as? Int
                    let dateStart = restSessionDict["dateStart"] as? String
                    
                    if let partsFound = partsFound{
                        if let dateStart = dateStart{
                            self.gameSession = GameSession(dateStart: dateStart, partsFound: partsFound)
                            
                            self.partsFoundTextField.text! = "Parts found: " + String(describing: self.gameSession.partsFound!) + "/" + String(describing: self.game.numParts!)
                        }else{
                            self.generateErrorRetrievingGameAlert()
                        }
                    }else{
                        self.generateErrorRetrievingGameAlert()
                    }
                }
            })
            
            
            Database.database().reference().child("images/"+gameID).observeSingleEvent(of: DataEventType.value, with: { (snapshot) in
                for rest_parts in snapshot.children.allObjects as! [DataSnapshot] {
                    guard let restDict = rest_parts.value as? [String: Any] else { continue }
                    
                    let found = restDict["found"] as? Bool
                    let latitude = restDict["latitude"] as? Double
                    let longitude = restDict["longitude"] as? Double
                    let imageDownloadURL = restDict["imageDownloadURL"] as? String
                    
                    let tempPart = PartInfo(found: found!, latitude: latitude!, longitude: longitude!, imageDownloadURL: imageDownloadURL!)
                                        
                    let partArray = rest_parts.key.characters.split{$0 == "_"}.map(String.init)
                    
                    if let found = found{
                        if found{
                            self.partsLocation.addLocation(partInfo: tempPart, index: Int(partArray[1])!)
                            self.partsLocationList = self.partsLocation.parts
                        }
                        self.downloadPartImage(part: tempPart, index: Int(partArray[1])!)
                    }
                }
            })
        }
    }
    
    
    //MapKit delegates & Map initialisation
    
    func createMap(){
        self.window = UIWindow(frame: UIScreen.main.bounds)
        self.view.backgroundColor = UIColor.white
        
        self.gameMap = MKMapView(frame: CGRect(x: CGFloat(0), y: CGFloat(20), width: CGFloat(self.window!.frame.width), height: CGFloat(self.window!.frame.height)))
        self.view.addSubview(self.gameMap!)
        
        self.gameMap?.addSubview(self.partsFoundTextField)
        self.partsFoundTextField.isHidden = false

        addBanner = GADBannerView(adSize: kGADAdSizeBanner)
        addBannerViewToMap(adBanner: addBanner)
        //addBanner.adUnitID = "ca-app-pub-4659614920279439/4181945605"
        addBanner.adUnitID = "ca-app-pub-3940256099942544/2934735716"
        addBanner.rootViewController = self
        addBanner.load(GADRequest())
        addBanner.delegate = self
        
        self.gameMap!.delegate = self
        self.gameMap!.showsUserLocation = true
        self.gameMap!.showsScale = true
        self.gameMap!.showsCompass = true
        gameMap!.addAnnotations(self.partsLocationList)
        
        /*let center = CLLocationCoordinate2D(latitude: (self.locationManager.location?.coordinate.latitude)!, longitude: (self.locationManager.location?.coordinate.longitude)!)
        let region = MKCoordinateRegion(center: center, span: MKCoordinateSpan(latitudeDelta: 0.02, longitudeDelta: 0.02))
        self.gameMap!.setRegion(region, animated: true)*/
        
        let center = CLLocationCoordinate2D(latitude: self.game.latitude!, longitude: self.game.longitude!)
        let region = MKCoordinateRegion(center: center, span: MKCoordinateSpan(latitudeDelta: 0.02, longitudeDelta: 0.02))
        self.gameMap!.setRegion(region, animated: true)
        self.addRadiusCircle(location: CLLocation(latitude: self.game.latitude!, longitude: self.game.longitude!))
    }
    
    
    func mapView(_ mapView: MKMapView!, rendererFor overlay: MKOverlay!) -> MKOverlayRenderer! {
        if overlay is MKCircle {
            let circle = MKCircleRenderer(overlay: overlay)
            circle.strokeColor = UIColor.blue
            circle.fillColor = UIColor(red: 0.0, green: 0.0, blue: 255.0/255.0, alpha: 0.05)
            circle.lineWidth = 1
            return circle
        } else {
            return MKPolylineRenderer()
        }
    }
    
    func mapView(_ mapView: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView? {
        if let annotation = annotation as? PartLocation{
            
            if let view = mapView.dequeueReusableAnnotationView(withIdentifier: annotation.identifier!){
                return view
            }else{
                let view = MKAnnotationView(annotation: annotation, reuseIdentifier: annotation.identifier)
                view.image = resizeImage(image: parts[Int(annotation.identifier!)!].image!, targetSize: CGSize(width: 30.0, height: 30.0))
                view.isEnabled = true
                view.canShowCallout = true
                view.leftCalloutAccessoryView = UIImageView(image: parts[Int(annotation.identifier!)!].image!)
                return view
            }
        }
        return nil
    }
    
    func resizeImage(image: UIImage, targetSize: CGSize) -> UIImage {
        let size = image.size
        
        let widthRatio  = targetSize.width  / size.width
        let heightRatio = targetSize.height / size.height
        
        // Figure out what our orientation is, and use that to form the rectangle
        var newSize: CGSize
        if(widthRatio > heightRatio) {
            newSize = CGSize(width: size.width * heightRatio, height: size.height * heightRatio)
        } else {
            newSize = CGSize(width: size.width * widthRatio,  height: size.height * widthRatio)
        }
        
        // This is the rect that we've calculated out and this is what is actually used below
        let rect = CGRect(x: 0, y: 0, width: newSize.width, height: newSize.height)
        
        // Actually do the resizing to the rect using the ImageContext stuff
        UIGraphicsBeginImageContextWithOptions(newSize, false, 1.0)
        image.draw(in: rect)
        let newImage = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        
        return newImage!
    }
    
    
    //AD STUFF
    func addBannerViewToMap(adBanner : GADBannerView){
        adBanner.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(adBanner)
        view.addConstraints(
            [NSLayoutConstraint(item: adBanner,
                                attribute: .bottom,
                                relatedBy: .equal,
                                toItem: bottomLayoutGuide,
                                attribute: .top,
                                multiplier: 1,
                                constant: 0),
             NSLayoutConstraint(item: adBanner,
                                attribute: .centerX,
                                relatedBy: .equal,
                                toItem: view,
                                attribute: .centerX,
                                multiplier: 1,
                                constant: 0)
            ])
    }
    
    func adViewDidReceiveAd(_ bannerView: GADBannerView) {
        // Add banner to view and add constraints as above.
        bannerView.alpha = 0
        UIView.animate(withDuration: 1, animations: {
            bannerView.alpha = 1
        })
        addBannerViewToMap(adBanner: bannerView)
    }
    
    func adView(_ bannerView: GADBannerView, didFailToReceiveAdWithError error: GADRequestError) {
        print(error)
    }
}
