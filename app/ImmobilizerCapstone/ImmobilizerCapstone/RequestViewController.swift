//
//  RequestViewController.swift
//  ImmobilizerCapstone
//
//  Created by Farez Halim on 2019-01-09.
//  Copyright © 2019 Farez Halim. All rights reserved.
//

import UIKit
import Firebase

class RequestViewController: UIViewController {

    @IBOutlet weak var macAddressTextField: UITextField!
    @IBOutlet weak var bluetoothPairKeyLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()

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
