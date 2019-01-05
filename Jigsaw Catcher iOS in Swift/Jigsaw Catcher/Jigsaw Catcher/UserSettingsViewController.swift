//
//  UserSettingsViewController.swift
//  Jigsaw Catcher
//
//  Created by Josep Brugués i Pujolràs on 12/10/17.
//  Copyright © 2017 Josep Brugués i Pujolràs. All rights reserved.
//

import UIKit
import Firebase
import FirebaseAuth
import StoreKit

class UserSettingsViewController: UITableViewController, SKProductsRequestDelegate, SKPaymentTransactionObserver {
    
    /*
    In app purchases stuff */
    @IBOutlet weak var purchaseButton: UIButton!
    @IBOutlet weak var restorePurchaseButton: UIButton!
    
    var productIDs : [String] = []
    var productsArray : [SKProduct] = []
    var transactionInProgress = false
    var didUserPurchaseNoAds = UserDefaults.standard.bool(forKey: "ads")
    
    func restorePurchase() {
        if (SKPaymentQueue.canMakePayments()) {
            SKPaymentQueue.default().restoreCompletedTransactions()
        }
    }
    
    func requestProductInfo(){
        if SKPaymentQueue.canMakePayments(){
            let productIdentifiers = NSSet(array: productIDs)
            let productRequest = SKProductsRequest(productIdentifiers: productIdentifiers as! Set<String>)
            
            productRequest.delegate = self
            productRequest.start()
        }else{
            print("No payment")
        }
    }
    
    
    func productsRequest(_ request: SKProductsRequest, didReceive response: SKProductsResponse) {
        print("request")
        if response.products.count != 0{
            print("request2")
            for product in response.products{
                productsArray.append(product)
            }
        }
    }
    
    func paymentQueue(_ queue: SKPaymentQueue, updatedTransactions transactions: [SKPaymentTransaction]) {
        print("here in updatedTransations")
        for transaction in transactions {
            switch transaction.transactionState {
            case SKPaymentTransactionState.purchased, SKPaymentTransactionState.restored:
                print("Transaction completed successfully")
                SKPaymentQueue.default().finishTransaction(transaction)
                transactionInProgress = false
                
                didUserPurchaseNoAds = true
                
                UserDefaults.standard.set(true, forKey: "ads")
                UserDefaults.standard.synchronize()
                
                break
                
            case SKPaymentTransactionState.failed:
                print("Transaction Failed");
                SKPaymentQueue.default().finishTransaction(transaction)
                transactionInProgress = false
                
                break
                
            default:
                print("default")
                print(transaction.transactionState.rawValue)
            }
        }
    }
    
    func purchaseNoAds() {
        if transactionInProgress {
            return
        }
        
        let actionSheetController = UIAlertController(title: "Purchase", message: "Did you want to purchase No Ads?", preferredStyle: UIAlertControllerStyle.actionSheet)
        
        let buyAction = UIAlertAction(title: "Yes, Purchase", style: UIAlertActionStyle.default) { (action) -> Void in
            
            //This code calls the Purchase transaction state of the IAP
            //We set the productsArray to 0 because there is only one element in the array. If there were more items, we would have to determine which item the user wants to buy
            //let payment = SKPayment(product: self.productsArray[0] as SKProduct)
            //SKPaymentQueue.default().add(payment)
            //self.transactionInProgress = true
            
        }
        
        let cancelAction = UIAlertAction(title: "Cancel", style: UIAlertActionStyle.cancel) { (action) -> Void in
            
        }
        
        actionSheetController.addAction(buyAction)
        actionSheetController.addAction(cancelAction)
        
        present(actionSheetController, animated: true, completion: nil)
        
    }
    
    
    //No-ad purchase actions.
    @IBAction func restorePurchase(_ sender: UIButton) {
        restorePurchase()
    }
    
    @IBAction func purchaseNoAds(_ sender: UIButton) {
        purchaseNoAds()
    }
    
    //End of app purchases stuff

    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.

        requestProductInfo()
        productIDs.append("Purchases.No.Ads")
        
        SKPaymentQueue.default().add(self)
        
        if #available(iOS 11.0, *) {
            self.navigationController?.navigationBar.prefersLargeTitles = true
        } else {
            // Fallback on earlier versions
        }        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func logoutAction(_ sender: UIButton) {
        do {
            try Auth.auth().signOut()
        } catch let error {
            // handle error here
            print("Error trying to sign out of Firebase: \(error.localizedDescription)")
        }
    }
    
    @IBAction func changeEmailAction(_ sender: UIButton) {
        if(isEmailAuthenticated()){
            self.performSegue(withIdentifier: "changeEmail", sender: nil)
        }else{
            googleAuthenticatedAlert()
        }
    }
    
    @IBAction func changePasswordAction(_ sender: UIButton) {
        if(isEmailAuthenticated()){
            self.performSegue(withIdentifier: "changePassword", sender: nil)
        }else{
            googleAuthenticatedAlert()
        }
    }
    
    @IBAction func passwordRecoveryAction(_ sender: UIButton) {
        if(isEmailAuthenticated()){
            self.performSegue(withIdentifier: "recoverPassword", sender: nil)
        }else{
            googleAuthenticatedAlert()
        }
    }
    
    func isEmailAuthenticated() -> Bool{
        if(Auth.auth().currentUser?.displayName == nil){
            return true
        }else{
            return false
        }
    }
    
    func googleAuthenticatedAlert(){
        let alertController = UIAlertController(title: NSLocalizedString("AlertTitle", comment: "Alert Title"), message: NSLocalizedString("googleAuth", comment: "Google Auth"), preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        self.present(alertController, animated: true, completion: nil)
    }
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        switch section {
        case 1:
            return 5
        case 2:
            return 2
        case 3:
            return 2
        default:
            return 0
        }
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        // your cell coding
        return UITableViewCell()
    }
    
    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        // cell selected code here
        print("Una casa")
        print("Hola" + String(describing: indexPath))
    }
}

