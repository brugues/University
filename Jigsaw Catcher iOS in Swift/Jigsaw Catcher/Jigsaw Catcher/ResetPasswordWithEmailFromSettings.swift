//
//  ResetPasswordWithEmailFromSettings.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 8/2/18.
//  Copyright © 2018 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import FirebaseAuth

class ResetPasswordWithEmailFromSettings:UIViewController{
    
    @IBOutlet weak var recoveryEmailTextField: UITextField!
    
    @IBOutlet weak var sendEmailButton: UIButton!
    
    @IBAction func sendEmail(_ sender: UIButton) {
        if let email = recoveryEmailTextField.text{
            if email == Auth.auth().currentUser!.email!{
                Auth.auth().sendPasswordReset(withEmail: email, completion: { (error) in
                    if(error != nil){
                        print("Error: " + String(describing: error))
                    }else{
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
                    }
                })
            }else{
                // Email provided is different than account's email
                providedEmailIsDifferentAlert()
            }
        }
    }
    
    func providedEmailIsDifferentAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("AlertTitle", comment: "Alert Title"), message: NSLocalizedString("providedEmailIsDifferent", comment: "Provided Email is different"), preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        self.present(alertController, animated: true, completion: nil)
    }
}
