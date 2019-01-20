//
//  SignInViewController.swift
//  ImmobilizerCapstone
//
//  Created by Farez Halim on 2019-01-09.
//  Copyright © 2019 Farez Halim. All rights reserved.
//

import UIKit

class SignInViewController: UIViewController {

    @IBOutlet weak var userNameTextField: UITextField!
    @IBOutlet weak var userPasswordTextField: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    @IBAction func registerNewAccountButtonTapped(_ sender: Any) {
        print("Register button tapped")
        
        // performSegue(withIdentifier: "registerSegue", sender: self)
        
        let registerViewController = self.storyboard?.instantiateViewController(withIdentifier:
            "RegisterUserViewController") as! RegisterUserViewController
        
        self.present(registerViewController, animated: true)
        
    }
    
    
    @IBAction func signInButtonTapped(_ sender: Any) {
        print("Sign in button tapped")
        
        // read values from text fields
        
        let userName = userNameTextField.text
        let userPassword = userPasswordTextField.text
        
        if (userName?.isEmpty)! || (userPassword?.isEmpty)! {
            print("Username \(String(describing: userName)) or password \(String(describing: userPassword)) is empty")
            displayMessage(userMessage: "One of the required fields is missing")
            return
        } else {
            
            
            // wrong password
            displayMessage(userMessage: "Incorrect username or password")
            return
        }
        

        
        //  activity indicator
        let myActivityIndicator = UIActivityIndicatorView(style: UIActivityIndicatorView.Style.gray)
        myActivityIndicator.center = view.center
        myActivityIndicator.hidesWhenStopped = false // to prevent from hiding when stopAnimating() is called
        myActivityIndicator.startAnimating()
        view.addSubview(myActivityIndicator)
        
        
    }
    
    func displayMessage(userMessage:String) -> Void {
        DispatchQueue.main.async {
            let alertController = UIAlertController(title: "Alert", message: userMessage, preferredStyle: .alert)
            
            let OKAction = UIAlertAction(title: "OK", style: .default)
            { (action:UIAlertAction!) in
                print("OK Button Tapped")
                DispatchQueue.main.async {
                    self.dismiss(animated: true, completion: nil)
                }
            }
            alertController.addAction(OKAction)
            self.present(alertController, animated: true, completion: nil)
        }
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
