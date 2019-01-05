//
//  ChangeEmailFromSettings.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 8/2/18.
//  Copyright © 2018 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import FirebaseAuth

class ChangeEmailFromSettings:UIViewController{
    @IBOutlet weak var emailTextField: UITextField!
    @IBOutlet weak var emailRepeatedTextField: UITextField!
    @IBOutlet weak var changeEmailButton: UIButton!
    
    @IBAction func changeEmail(_ sender: UIButton) {
        if let email = emailTextField.text{
            if(email != ""){
                if let repeatedEmail = emailRepeatedTextField.text{
                    if(repeatedEmail != ""){
                        if(email == repeatedEmail){
                            if(email == Auth.auth().currentUser?.email!){
                                Auth.auth().currentUser?.updateEmail(to: email, completion: { (error) in
                                    if(error != nil){
                                        print("Error: " + String(describing: error))
                                    }else{
                                        self.emailHasBeenChangedCorrectlyAlert()
                                    }
                                })
                            }else{
                                // Provided email is different from account's email
                                providedEmailIsDifferentAlert()
                            }
                        }else{
                            // The two emails provided are different
                            emailsProvidedAreDifferentAlert()
                        }
                    }else{
                        // Need to provided an email
                        needToProvideEmailAlert()
                    }
                }
            }else{
                // Need to provide an email
                needToProvideEmailAlert()
            }
        }
    }
    
    func needToProvideEmailAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("AlertTitle", comment: "Alert Title"), message: NSLocalizedString("needToProvideEmailAlertMessage", comment: "Need To Provide Email Alert Message"), preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        self.present(alertController, animated: true, completion: nil)
    }
    
    func emailsProvidedAreDifferentAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("AlertTitle", comment: "Alert Title"), message: NSLocalizedString("providedEmailsAreDifferent", comment: "Provided Emails are different"), preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        self.present(alertController, animated: true, completion: nil)
    }
    
    func providedEmailIsDifferentAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("AlertTitle", comment: "Alert Title"), message: NSLocalizedString("providedEmailIsDifferent", comment: "Provided Email is different"), preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        self.present(alertController, animated: true, completion: nil)
    }
    
    func emailHasBeenChangedCorrectlyAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("EmailChanged", comment: "Email Changed"), message: NSLocalizedString("PasswordChangedCorrectly", comment: "Short Password"), preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: { (action) in
            do {
                try Auth.auth().signOut()
                if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Welcome"){
                    self.present(vc, animated: true, completion:{
                        print("Welcome View Controller Presented")
                    })
                }
            } catch let error {
                // handle error here
                print("Error trying to sign out of Firebase: \(error.localizedDescription)")
            }
        })
        alertController.addAction(action)
        self.present(alertController, animated: true, completion: nil)
    }
}
