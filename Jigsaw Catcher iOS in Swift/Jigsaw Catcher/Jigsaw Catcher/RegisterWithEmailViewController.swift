//
//  RegisterViewController.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 19/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import Firebase
import FirebaseDatabase
import FirebaseAuth

class RegisterWithEmailViewController: UIViewController {
    
    @IBOutlet weak var userEmail: UITextField!
    @IBOutlet weak var userName: UITextField!
    @IBOutlet weak var userPassword: UITextField!
    @IBOutlet weak var forgotPassword: UITextField!
    @IBOutlet weak var userLogin: UITextField!
    @IBOutlet weak var progressIndicator: UIActivityIndicatorView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.hideKeyboardWhenTappedAround()
        self.progressIndicator.stopAnimating()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func createAccountAction(_ sender: UIButton) {
        if self.userEmail.text == "" || self.userPassword.text == "" || self.userEmail.text == "" {
            
            //Alert to tell the user that there was an error because they didn't fill anything in the textfields because they didn't fill anything in
            dataNotProvidedAlert()
        } else {
            let database = Database.database()
            let databaseReference = database.reference()
            
            databaseReference.child("users").observeSingleEvent(of: .value, with: { (snapshot) in
                if snapshot.hasChild(self.userName.text!){
                    //Username already exists.
                    self.usernameAlreadyExistsAlert()
                }else{
                    self.forgotPassword.isHidden = true
                    self.userLogin.isHidden = true
                    self.progressIndicator.isHidden = false
                    
                    //Username does not exist. We proceed creating the user
                    Auth.auth().createUser(withEmail: self.userEmail.text!, password: self.userPassword.text!, completion: { (user, error) in
                        if error == nil{
                            //Create things in database.
                            self.progressIndicator.startAnimating()
                            
                            if let user = Auth.auth().currentUser{
                                databaseReference.child("users").child(self.userName.text!).child("email").setValue(self.userEmail.text!)
                                databaseReference.child("users").child(self.userName.text!).child("userID").setValue(user.uid)
                            }
                            
                            self.progressIndicator.stopAnimating()
                            if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Main") as? UITabBarController{
                                self.present(vc, animated: true, completion:{
                                    print("Main View Controller presented")
                                })
                            }
                        }else{
                            //Error when creating user
                            self.errorWhenCreatingUserAlert(error : (error?.localizedDescription)!)
                        }
                    })
                }
            })
        }
    }
    
    func dataNotProvidedAlert(){
        let alertController = UIAlertController(title: "Error", message: NSLocalizedString("errorCreatingAccount", comment: "Error Creating Account"), preferredStyle: .alert)
        let defaultAction = UIAlertAction(title: "OK", style: .cancel, handler: nil)
        alertController.addAction(defaultAction)
        self.present(alertController, animated: true, completion: nil)
    }
    
    func usernameAlreadyExistsAlert(){
        let alertController = UIAlertController(title: "Error", message: NSLocalizedString("usernameAlreadyExists", comment: "Username Already Exists"), preferredStyle: .alert)
        let defaultAction = UIAlertAction(title: "OK", style: .cancel, handler: nil)
        alertController.addAction(defaultAction)
        self.present(alertController, animated: true, completion: nil)
    }
    
    func errorWhenCreatingUserAlert(error : String){
        let alertController = UIAlertController(title: "Error", message: error, preferredStyle: .alert)
        let defaultAction = UIAlertAction(title: "OK", style: .cancel, handler: nil)
        alertController.addAction(defaultAction)
        self.present(alertController, animated: true, completion: nil)
    }
    
    @IBAction func resetPasswordAction(_ sender: UITextField) {
        if let vc = self.storyboard?.instantiateViewController(withIdentifier: "ResetPassword"){
            self.present(vc, animated: true, completion:{
                print("Reset Password View Controller Presented")
            })
        }
    }
    
    @IBAction func loginAction(_ sender: UITextField) {
        if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Login"){
            self.present(vc, animated: true, completion:{
                print("Login View Controller Presented")
            })
        }
    }
}
