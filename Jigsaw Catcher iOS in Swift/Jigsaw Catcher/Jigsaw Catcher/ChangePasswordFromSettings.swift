//
//  ChangePasswordFromSettings.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 8/2/18.
//  Copyright © 2018 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import FirebaseAuth
import Firebase

class ChangePasswordFromSettings:UIViewController{
    
    @IBOutlet weak var newPasswordTextField: UITextField!
    @IBOutlet weak var newPasswordRepeatedTextField: UITextField!
    @IBOutlet weak var changePasswordButton: UIButton!
    
    
    @IBAction func changePassword(_ sender: UIButton) {
        if let newPassword = newPasswordTextField.text{
            if let newPasswordRepeated = newPasswordRepeatedTextField.text{
                if(newPassword == newPasswordRepeated){
                    Auth.auth().currentUser?.updatePassword(to: newPassword, completion: { (error) in
                        if(error != nil){
                            print("Error: " + String(describing: error))
                        }else{
                            let alertController = UIAlertController(title: NSLocalizedString("passwordChanged", comment: "Password Changed"), message: NSLocalizedString("passwordChangedMessage", comment: "Password Changed Correctly"), preferredStyle: .alert)
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
                    })
                }else if(newPassword.count <= 5){
                    let alertController = UIAlertController(title: "Error", message: NSLocalizedString("shortPassword", comment: "Short Password"), preferredStyle: .alert)
                    let action = UIAlertAction(title: "OK", style: .default, handler: nil)
                    alertController.addAction(action)
                    self.present(alertController, animated: true, completion: nil)
                }
            }
        }
    }
}
