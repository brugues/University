//
//  ResetPasswordViewController.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 19/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import FirebaseAuth

class ResetPasswordViewController: UIViewController {
    @IBOutlet weak var titleText: UITextView!
    @IBOutlet weak var userEmail: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.hideKeyboardWhenTappedAround()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func resetPasswordAction(_ sender: UIButton) {
        if let email = userEmail.text{
            if(email == ""){
                //No email provided
                noEmailProvidedAlert()
            }else{
                Auth.auth().sendPasswordReset(withEmail: email, completion: { (error) in
                    if(error != nil){
                        //Error when sending email
                        self.errorWhenSendingEmail(error : String(describing: error))
                    }else{
                        //Recovery Email sent
                        self.recoveryEmailSentAlert()
                    }
                })
                userEmail.text = ""
            }
        }
    }
    
    func noEmailProvidedAlert(){
        let alertController = UIAlertController(title: "Error", message: NSLocalizedString("noEmailProvided", comment: "No Email Provided"), preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        present(alertController, animated: true, completion: nil)
    }
    
    func errorWhenSendingEmail(error : String){
        let alertController = UIAlertController(title: "Error", message: error, preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        self.present(alertController, animated: true, completion: nil)
    }
    
    func recoveryEmailSentAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("completed", comment: "Completed"), message: NSLocalizedString("recoveryEmailSent", comment: "Recovery Email Sent"), preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        self.present(alertController, animated: true, completion: nil)
    }
    
    @IBAction func loginAction(_ sender: UITextField) {
        if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Login"){
            self.present(vc, animated: true, completion:{
                print("Login View Controller Presented")
            })
        }
    }
    
    @IBAction func registerAction(_ sender: UITextField) {
        if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Register"){
            self.present(vc, animated: true, completion:{
                print("Register View Controller Presented")
            })
        }
    }
}
