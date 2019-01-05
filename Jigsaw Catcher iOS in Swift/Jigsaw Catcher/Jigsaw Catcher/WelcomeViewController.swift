//
//  WelcomeViewController.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 10/2/18.
//  Copyright © 2018 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import GoogleSignIn
import FirebaseAuth
import FirebaseDatabase

class WelcomeViewController: UIViewController, GIDSignInUIDelegate {
    
    @IBOutlet weak var googleSignInButton: GIDSignInButton!
    @IBOutlet weak var emailSignInButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //GIDSignIn.sharedInstance().clientID = FirebaseApp.app()?.options.clientID
        GIDSignIn.sharedInstance().uiDelegate = self

        // TODO(developer) Configure the sign-in button look/feel
        //googleSignInButton.style = GIDSignInButtonStyle.standard
        
        googleSignInButton.addTarget(self, action: #selector(btnSignInPressed), for: UIControlEvents.touchUpInside)
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        Auth.auth().addStateDidChangeListener { auth, user in
            if let _ = user {
                if(Auth.auth().currentUser?.displayName != nil){
                    let separator = Auth.auth().currentUser?.email!.split(separator: "@")
                    let email = Auth.auth().currentUser?.email!
                    
                    if let username = separator?.first{
                        Database.database().reference().child("users").observeSingleEvent(of: .value, with: { (snapshot) in
                            if snapshot.hasChild(String(username)){
                            }else{
                                Database.database().reference().child("users").child(String(username)).updateChildValues(["email" : email!])
                                Database.database().reference().child("users").child(String(username)).updateChildValues(["userID" : Auth.auth().currentUser?.uid ?? ""])
                            }
                        })
                    }
                }
                
                if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Main") as? UITabBarController{
                    self.present(vc, animated: true, completion:{
                        print("Main View Controller presented")
                    })
                }
            } else {
                print("User has not signed in")
            }
        }
    }
    
    @objc func btnSignInPressed() {
        GIDSignIn.sharedInstance().signIn()
    }
    
    
    @IBAction func emailSignIn(_ sender: UIButton) {
        if let vc = self.storyboard?.instantiateViewController(withIdentifier: "Login"){
            self.present(vc, animated: true, completion:{
                print("Login View Controller Presented")
            })
        }
    }
}
