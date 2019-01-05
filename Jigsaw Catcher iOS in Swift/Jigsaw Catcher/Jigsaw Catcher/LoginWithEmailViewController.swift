//
//  LoginWithEmailViewController.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 19/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import Firebase
import FirebaseAuth
import FirebaseDatabase

protocol LoginViewControllerProtocol {
    func dismissViewController()
}

class LoginWithEmailViewController: UIViewController {
    
    var delegate:LoginViewControllerProtocol!
    @IBOutlet weak var userEmail: UITextField!
    @IBOutlet weak var userPassword: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.hideKeyboardWhenTappedAround()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    @IBAction func loginButton(_ sender: UIButton) {
        if self.userEmail.text == "" || self.userPassword.text == "" {
            
            //Alert to tell the user that there was an error because they didn't fill anything in the textfields because they didn't fill anything in
            
            let alertController = UIAlertController(title: "Error", message: "Please enter an email and password.", preferredStyle: .alert)
            
            let defaultAction = UIAlertAction(title: "OK", style: .cancel, handler: nil)
            alertController.addAction(defaultAction)
        } else {
            Auth.auth().signIn(withEmail: self.userEmail.text!, password: self.userPassword.text!) { (user, error) in
                if error == nil {
                    
                    //Print into the console if successfully logged in
                    print("You have successfully logged in")
                    
                    //Go to the HomeViewController if the login is sucessful
                    if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Main") as? UITabBarController{
                        self.present(vc, animated: true, completion:{
                            print("Main View Controller presented")
                        })
                    }
                } else {
                    
                    //Tells the user that there is an error and then gets firebase to tell them the error
                    let alertController = UIAlertController(title: "Error", message: error?.localizedDescription, preferredStyle: .alert)
                    
                    let defaultAction = UIAlertAction(title: "OK", style: .cancel, handler: nil)
                    alertController.addAction(defaultAction)
                    
                    self.present(alertController, animated: true, completion: nil)
                }
            }
        }
    }

    @IBAction func resetPasswordAction(_ sender: UITextField) {
        if let vc = self.storyboard?.instantiateViewController(withIdentifier: "ResetPassword"){
            self.present(vc, animated: true, completion:{
                print("ResetPassword View Controller Presented")
            })
        }
    }
    
    @IBAction func registerAction(_ sender: UITextField) {
        if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Register"){
            self.present(vc, animated: true, completion:{
                print("Register with Email View Controller Presented")
            })
        }
    }
}

extension UIViewController {
    func hideKeyboardWhenTappedAround() {
        let tap: UITapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(UIViewController.dismissKeyboard))
        tap.cancelsTouchesInView = false
        view.addGestureRecognizer(tap)
    }
    
    @objc func dismissKeyboard() {
        view.endEditing(true)
    }
}
