//
//  SecondViewController.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 12/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import Photos
import CoreLocation
import FirebaseAuth
import FirebaseDatabase
import FirebaseStorage

class CreateGameViewController: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate, UIPickerViewDelegate, UIPickerViewDataSource, CLLocationManagerDelegate {
    
    @IBOutlet weak var createGame: UIButton!
    @IBOutlet weak var cameraButton: UIBarButtonItem!
    @IBOutlet weak var gameLocationSegmentedControl: UISegmentedControl!
    @IBOutlet weak var gameName: UITextField!
    @IBOutlet weak var gameLocation: UITextField!
    @IBOutlet weak var gameParts: UIPickerView!
    @IBOutlet weak var gameRadius: UITextField!
    @IBOutlet weak var selectImage: UIButton!
    
    var locationManager = CLLocationManager()
    var newGame = Game()
    var pickerData : [String] = ["4 Pieces", "9 Pieces", "16 Pieces", "25 Pieces", "36 pieces"]
    var location: CLLocation?
    var creatingGamePopup : UIAlertController?

    
    override func viewWillAppear(_ animated: Bool) {
        askForPhotosPermissions()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        if #available(iOS 11.0, *) {
            self.navigationController?.navigationBar.prefersLargeTitles = false
        } else {
            // Fallback on earlier versions
        }
        
        self.hideKeyboardWhenTappedAround()
        
        self.gameParts.delegate = self
        self.gameParts.dataSource = self
        
        gameParts.selectRow(2, inComponent: 0, animated: false)
        newGame.numParts = 16
        
        gameLocationSegmentedControl.setEnabled(true, forSegmentAt: 0)
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        print("Location updated")
    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print(error)
    }
    
    @objc func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        
        if let pickedImage = info[UIImagePickerControllerEditedImage] as? UIImage {
            self.newGame.image = pickedImage
            self.selectImage.isHidden = true
            self.createGame.isHidden = false
        }
        dismiss(animated: true, completion: nil)
    }
    
    public func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        self.dismiss(animated: true, completion: nil)
    }
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    // The number of rows of data
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return pickerData.count
    }
    
    
    // The data to return for the row and component (column) that's being passed in
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return pickerData[row]
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        switch row {
        case 0:
            newGame.numParts = 4
        case 1:
            newGame.numParts = 9
        case 2:
            newGame.numParts = 16
        case 3:
            newGame.numParts = 25
        case 4:
            newGame.numParts = 36
        default:
            newGame.numParts = 4
        }
    }
    
    func askForPhotosPermissions() {
        PHPhotoLibrary.requestAuthorization { [unowned self] (authStatus) in
            DispatchQueue.main.async {
                if authStatus == .authorized {
                    //Tells the user that there is an error and then gets firebase to tell them the error
                    print("Authorisation granted")
                } else {
                    //Tells the user that there is an error and then gets firebase to tell them the error
                    let alertController = UIAlertController(title: "Error", message: "We don't have permission to acces your photos. If you want to create a game, give permission to access your photos in the Settings App.", preferredStyle: .alert)
                    
                    let defaultAction = UIAlertAction(title: "OK", style: .cancel, handler: nil)
                    alertController.addAction(defaultAction)
                    
                    self.present(alertController, animated: true, completion: nil)
                }
            }
        }
    }
    
    func getCoordinatesFromWrittenLocation(gameLocation : String){
        print("In getCoordinatesFromWrittenLocation")
        let geocoder = CLGeocoder()
        
        geocoder.geocodeAddressString(gameLocation) { (place, error) in
            if let error = error {
                print("Unable to Forward Geocode Address (\(error))")
            } else {
                print("Trying for Geocode Address")
                if let placemarks = place, placemarks.count > 0 {
                    if let location = placemarks.first!.location{
                        self.location = location
                        self.newGame.latitude = Double(self.location!.coordinate.latitude)
                        self.newGame.longitude = Double(self.location!.coordinate.longitude)
                        self.creatingGamePopup = self.displayCreatingGamePendingAlert()
                        self.uploadGameToCloud()
                    }
                }
            }
        }
    }
    
    func getWrittenLocationFromCoordinates(location: CLLocation){
        let reverseGeocoder = CLGeocoder()
        
        reverseGeocoder.reverseGeocodeLocation(location) { (places, error) in
            if let _ = error{
                let alertController = UIAlertController(title: "Locarion error", message: "We are unable to find your location", preferredStyle: .alert)
                let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
                alertController.addAction(alertAction)
                self.present(alertController, animated: true, completion: nil)
            }else{
                var location : String?
                if let placemarks = places, placemarks.count > 0{
                    location = placemarks.first?.locality!
                    self.gameLocation.text = location
                }
            }
        }
    }
    
    @IBAction func gameLocationSegmentedControl(_ sender: UISegmentedControl) {
        switch(gameLocationSegmentedControl.selectedSegmentIndex){
        case 0:
            gameLocation.text = ""
            break
        case 1:
            print("case 1 in segmented control")
            if CLLocationManager.locationServicesEnabled() {
                switch(CLLocationManager.authorizationStatus()) {
                case .notDetermined:
                    locationManager.requestWhenInUseAuthorization()
                    break
                case .restricted, .denied:
                    let alertController = UIAlertController(title: "Location Acces", message: "Give acces to location in the Settings App in order create a game in your current location", preferredStyle: UIAlertControllerStyle.alert)
                    let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
                    alertController.addAction(alertAction)
                    
                    present(alertController, animated: true, completion: nil)
                    break
                case .authorizedWhenInUse, .authorizedAlways:
                    locationManager.delegate = self
                    locationManager.startMonitoringSignificantLocationChanges()
                    locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation
                    locationManager.distanceFilter = kCLDistanceFilterNone
                    locationManager.allowsBackgroundLocationUpdates = false
                    locationManager.requestLocation()
                    getWrittenLocationFromCoordinates(location: locationManager.location!)
                    locationManager.stopMonitoringSignificantLocationChanges()
                    break
                }
            }
            break
        default:
            break
        }
    }
    
    
    @IBAction func createGame(_ sender: UIButton) {
        if gameName.text != "" {
            if gameRadius.text != "" {
                if gameLocation.text != "" {
                    if let user = Auth.auth().currentUser{
                        if self.newGame.image != nil{
                            if(gameRadius.text!.contains(",")){
                                gameRadius.text! = gameRadius.text!.replacingOccurrences(of: ",", with: ".")
                            }
                            
                            newGame.name = gameName.text
                            newGame.radius = Double(gameRadius.text!)
                            newGame.generalLocation = gameLocation.text!
                            newGame.numberPlayers = 1
                            newGame.createdBy = user.uid
                            let date = Date()
                            let calendar = Calendar.current
                            let components = calendar.dateComponents([.year, .month, .day], from: date)
                            
                            newGame.dateCreated = String(describing: components.day!) + "/" + String(describing: components.month!) + "/" + String(describing: components.year!)
                            
                            if(gameLocationSegmentedControl.selectedSegmentIndex == 0){
                                getCoordinatesFromWrittenLocation(gameLocation : gameLocation.text!)
                            }else{
                                self.location = self.locationManager.location!
                                self.newGame.latitude = Double(self.locationManager.location!.coordinate.latitude)
                                self.newGame.longitude = Double(self.locationManager.location!.coordinate.longitude)
                                self.creatingGamePopup = displayCreatingGamePendingAlert()
                                uploadGameToCloud()
                            }
                        }else{
                            print("Image could not be retrieved")
                        }
                    }else{
                        //Problem with server
                        problemWithServerAlert()
                    }
                }else{
                    //Game has no location
                    noLocationProvidedAlert()
                }
            }else{
                //Game has no radius
                noRadiusProvidedAlert()
            }
        }else{
            //Game has no name
            noGameNameProvidedAlert()
        }
    }
    
    func problemWithServerAlert(){
        let alertController = UIAlertController(title: "Error", message: NSLocalizedString("serverProblem", comment: "Problem with Server"), preferredStyle: .alert)
        let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(alertAction)
        present(alertController, animated: true, completion: nil)
    }
    
    func noLocationProvidedAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("invalidLocation", comment: "Location is Invalid"), message: NSLocalizedString("invalidLocationMessage", comment: "Invalid Location Message"), preferredStyle: .alert)
        let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(alertAction)
        present(alertController, animated: true, completion: nil)
    }
    
    func noRadiusProvidedAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("invalidRadius", comment: "Invalid Radius"), message: NSLocalizedString("invalidRadiusMessage", comment: "Invalid Radius Message"), preferredStyle: .alert)
        let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(alertAction)
        present(alertController, animated: true, completion: nil)
    }
    
    func noGameNameProvidedAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("invalidName", comment: "Invalid Name"), message: NSLocalizedString("invalidNameMessage", comment: "Invalid Name Message"), preferredStyle: .alert)
        let alertAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(alertAction)
        present(alertController, animated: true, completion: nil)
    }
    
    func uploadGameToCloud(){
        let storageReference = Storage.storage().reference()
        var databaseReference = Database.database().reference()
        
        databaseReference = databaseReference.child("jigsaws").childByAutoId()
        newGame.gameID = databaseReference.key
        
        let splitter = ImageSplitter(image: self.newGame.image!, width: Int(self.newGame.image!.size.width), height: Int(self.newGame.image!.size.height), parts: self.newGame.numParts!)
        
        let images : [UIImage] = splitter.split()
        var imagesData : [Data] = []
        
        for i in 0..<images.count{
            imagesData.append(UIImageJPEGRepresentation(images[i], 0.50)!)
        }
        
        var storageReferences : [StorageReference] = []
        var databaseReferences : [DatabaseReference] = []
        var imagesLocations : [CLLocation] = []
        var partsInfo : [PartInfo] = []
        var uploadTasks : [StorageUploadTask] = []
        var partsInfoDic : [[String:Any]] = []
        
        for i in 0..<images.count{
            imagesLocations.append(generateRandomLoc(l: self.location!, radius: newGame.radius!))
            partsInfo.append(PartInfo(found: false, latitude: imagesLocations[i].coordinate.latitude, longitude: imagesLocations[i].coordinate.longitude))
            if(i < 10){
                databaseReferences.append(Database.database().reference().child("images").child(newGame.gameID!).child("part_0" + String(describing: i)))
            }else{
                databaseReferences.append(Database.database().reference().child("images").child(newGame.gameID!).child("part_" + String(describing: i)))
            }
            
            var tempDic = [String : Any]()
            tempDic.updateValue(partsInfo[i].getLatitude(), forKey: "latitude")
            tempDic.updateValue(partsInfo[i].getLongitude(), forKey: "longitude")
            tempDic.updateValue(partsInfo[i].isFound(), forKey: "found")
            partsInfoDic.append(tempDic)
        }
        
        let databaseSessionReference = Database.database().reference().child("jigsaw_session")
        let gameSession = GameSession(dateStart: newGame.dateCreated!, partsFound: 0)
        
        var gameSessionDic = [String:Any]()
        gameSessionDic.updateValue(gameSession.getDateStart(), forKey: "dateStart")
        gameSessionDic.updateValue(gameSession.getPartsFround(), forKey: "partsFound")
        
        databaseSessionReference.child((Auth.auth().currentUser?.uid)!).child(newGame.gameID!).child("game_session").setValue(gameSessionDic, withCompletionBlock: { (error, databaseReference) in
            if(error != nil){
                print("Account-Storage Error: \(String(describing:error?.localizedDescription))\n")
            }
        })
        
        for i in 0..<images.count{
            if(i < images.count - 1){
                if(i < 10){
                    storageReferences.append(storageReference.child(newGame.gameID! + "/part_0" + String(describing: i)))
                }else{
                    storageReferences.append(storageReference.child(newGame.gameID! + "/part_" + String(describing: i)))
                }
            }else{
                storageReferences.append(storageReference.child(newGame.gameID! + "/part_original"))
            }
            
            let uploadMetadata = StorageMetadata()
            uploadMetadata.contentType = "image/jpeg"
            
            uploadTasks.append(storageReferences[i].putData(imagesData[i], metadata: uploadMetadata, completion: { (metadata, error) in
                if(error != nil){
                    print("Account-Storage Error: \(String(describing:error?.localizedDescription))\n")
                }else{
                    print("Upload of " + String(describing: i) + "completed")
                    if(i < images.count - 1){
                        print(String(describing: uploadTasks[i].snapshot.metadata!.downloadURL()!))
                        partsInfo[i].setImageDownloadURL(imageDownloadURL: String(describing: uploadTasks[i].snapshot.metadata!.downloadURL()!))
                        partsInfoDic[i].updateValue(partsInfo[i].getImageDownloadURL(), forKey: "imageDownloadURL")
                        
                        databaseReferences[i].updateChildValues(partsInfoDic[i], withCompletionBlock: {
                            (error, user) in
                            if error != nil{
                                print("Account-Database Error: \(String(describing:error?.localizedDescription))\n")
                            }
                        })
                        if(i == (images.count - 2)){
                            self.creatingGamePopup?.dismiss(animated: true, completion: nil)
                        }
                    }else{
                        if let url = metadata?.downloadURL(){
                            self.newGame.imageDownloadURL = String(describing: url)
                            
                            var jigsawDict = [String:Any]()
                            
                            //Here you can use a dictionary method to update the keys and matching values. The values are the ones from your UserAccount model's properties and the keys are what I decided I wanted them to be named in FirebaseDatabase. You use these keys to extract the values
                            jigsawDict.updateValue(self.newGame.createdBy!, forKey: "createdBy")
                            jigsawDict.updateValue(self.newGame.dateCreated!, forKey: "dateCreated")
                            jigsawDict.updateValue(self.newGame.name!, forKey: "gameName")
                            jigsawDict.updateValue(self.newGame.generalLocation!, forKey: "generalLocation")
                            jigsawDict.updateValue(self.newGame.longitude!, forKey: "longitude")
                            jigsawDict.updateValue(self.newGame.latitude!, forKey: "latitude")
                            jigsawDict.updateValue(self.newGame.numParts!, forKey: "numParts")
                            jigsawDict.updateValue(self.newGame.numberPlayers!, forKey: "numPlayers")
                            jigsawDict.updateValue(self.newGame.radius!, forKey: "radius")
                            jigsawDict.updateValue(self.newGame.imageDownloadURL!, forKey: "imageDownloadURL")
                            
                            
                            //Here you upload your dictionary with the keys and values you set above. Your database will hold these key/value pairs under the "userAccount" node. userAccountRef (you set it above) is the constant that has that node value
                            databaseReference.updateChildValues(jigsawDict, withCompletionBlock: {
                                (error, user) in
                                if error != nil{
                                    print("Account-Database Error: \(String(describing:error?.localizedDescription))\n")
                                }
                            })
                        }
                    }
                }
            }))
        }
        
        let prefs = UserDefaults.standard
        prefs.set(true, forKey: "gameCreated")
        prefs.synchronize()
        createGame.isHidden = true
        selectImage.isHidden = false
        gameName.text = ""
        gameRadius.text = ""
        gameLocation.text = ""
        gameLocationSegmentedControl.setEnabled(true, forSegmentAt: 0)
        gameLocationSegmentedControl.setEnabled(false, forSegmentAt: 1)
    }
    
    func displayCreatingGamePendingAlert() -> UIAlertController {
        //create an alert controller
        let alert = UIAlertController(title: NSLocalizedString("creatingGame", comment: "Creating Game"), message: nil, preferredStyle: .alert)
        
        let activityIndicator = UIActivityIndicatorView(activityIndicatorStyle: UIActivityIndicatorViewStyle.gray)
        activityIndicator.frame = activityIndicator.frame.offsetBy(dx: 8, dy: CGFloat(alert.view.bounds.height - activityIndicator.frame.height)/2)
        activityIndicator.autoresizingMask = [.flexibleRightMargin, .flexibleTopMargin, .flexibleBottomMargin]
        activityIndicator.startAnimating()
        
        alert.view.addSubview(activityIndicator)
        self.present(alert, animated: true, completion: nil)
        
        return alert
    }
    
    @IBAction func selectImageAction(_ sender: UIButton) {
        if(PHPhotoLibrary.authorizationStatus() == .authorized){
            let imagePicker = UIImagePickerController()
            imagePicker.sourceType = UIImagePickerControllerSourceType.photoLibrary
            imagePicker.allowsEditing = true
            imagePicker.delegate = self
            imagePicker.modalPresentationStyle = .popover
            
            let ppc = imagePicker.popoverPresentationController
            ppc?.barButtonItem = self.cameraButton
            ppc?.permittedArrowDirections = .any
            
            present(imagePicker, animated: true, completion: nil)
        }else{
            askForPhotosPermissions()
        }
    }
    
    func generateRandomLoc(l : CLLocation, radius : Double) -> CLLocation {
    
        let x0 : Double = l.coordinate.longitude
        let y0 : Double = l.coordinate.latitude
    
        // Convert radius from meters to degrees
        let radiusInDegrees : Double = radius / 111.3
    
        
        let u : Double = Double(CGFloat(Float(arc4random()) / Float(UINT32_MAX)))
        let v : Double = Double(CGFloat(Float(arc4random()) / Float(UINT32_MAX)))
        let w : Double = radiusInDegrees * sqrt(u)
        let t : Double = 2 * Double.pi * v
        let x : Double = w * cos(t)
        let y : Double = w * sin(t)
        
        // Adjust the x-coordinate for the shrinking of the east-west distances
        let new_x : Double  = x / cos(y0)
    
        let foundLongitude : Double = new_x + x0
        let foundLatitude : Double = y + y0
    
        let coordinates = CLLocationCoordinate2DMake(CLLocationDegrees(foundLatitude), CLLocationDegrees(foundLongitude))
        
        return CLLocation(latitude: coordinates.latitude, longitude: coordinates.longitude)
    }
}
