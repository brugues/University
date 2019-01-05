//
//  LogoutViewController.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 31/1/18.
//  Copyright © 2018 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import FirebaseAuth
import Firebase

class LogoutViewController: UIViewController{
    @IBOutlet weak var logoutTextField: UITextField!
    @IBOutlet weak var activityIndicator: UIActivityIndicatorView!
    
    override func viewDidLoad() {
        //Logout user
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
    
    override func viewWillAppear(_ animated: Bool) {
        if #available(iOS 11.0, *) {
            self.navigationController?.navigationBar.prefersLargeTitles = false
        } else {
            // Fallback on earlier versions
        }
    }
}
