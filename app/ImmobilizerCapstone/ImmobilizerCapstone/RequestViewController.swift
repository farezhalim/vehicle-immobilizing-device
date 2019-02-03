//
//  RequestViewController.swift
//  ImmobilizerCapstone
//
//  Created by Farez Halim on 2019-01-09.
//  Copyright © 2019 Farez Halim. All rights reserved.
//

import UIKit
import Firebase
import FirebaseDatabase

class RequestViewController: UIViewController {

    @IBOutlet weak var macAddressTextField: UITextField!
    @IBOutlet weak var bluetoothPairKeyLabel: UILabel!
    
    var ref : DatabaseReference!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        ref = Database.database().reference(withPath: "devices")
        

        // Do any additional setup after loading the view.
    }
    
    @IBAction func signOutButtonTapped(_ sender: Any) {
        print("sign out button tapped")
        
        do {
            try Auth.auth().signOut()
            self.dismiss(animated: true, completion: nil)
        } catch let signOutError as NSError {
            print("Error signing out: %@", signOutError)
        }
        
    }
    @IBAction func requestKeyButtonTapped(_ sender: Any) {
        print("requestKey button tapped")
        
       let mac = macAddressTextField.text
        
        ref.queryOrdered(byChild: "MAC").queryEqual(toValue: mac).observeSingleEvent(of: .value, with: { (snapshot) in
           print(snapshot.value as Any)
           // let device = snapshot.value as? NSDictionary
           // let password = device?["unlockPass"] as? String ?? ""
           // print(password)
            
            var pass: String = "empty"
            
            let userDict = snapshot.value as! [String: Any]
            for each in userDict as [String:AnyObject]{
                
                pass = each.value["unlockPass"] as! String
                print(pass)
                
            }
            
            self.bluetoothPairKeyLabel.text = pass
            
            //let device = userDict["MAC"] as! String
            
            
        })

        
       // let query = ref.queryOrdered(byChild: "devices/MAC").queryEqual(toValue: mac).queryEqual(toValue: true)
       // print(query)
            
//            .observeSingleEvent(of: .value, with: { (snapshot) in
//            // Get user value
//            let value = snapshot.value().MAC
//            let pass = snapshot.value().unlockPass
//            print(value)
//            // ...
//        }) { (error) in
//            print(error.localizedDescription)
//        }
//
//
//
        
    }
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
