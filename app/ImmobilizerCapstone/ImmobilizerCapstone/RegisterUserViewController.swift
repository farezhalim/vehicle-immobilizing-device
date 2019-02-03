//
//  RegisterUserViewController.swift
//  ImmobilizerCapstone
//
//  Created by Farez Halim on 2019-01-13.
//  Copyright © 2019 Farez Halim. All rights reserved.
//

import UIKit
import Firebase

class RegisterUserViewController: UIViewController {

    @IBOutlet weak var firstNameTextField: UITextField!
    @IBOutlet weak var lastNameTestField: UITextField!
    @IBOutlet weak var emailAddressTextField: UITextField!
    @IBOutlet weak var passwordTextField: UITextField!
    @IBOutlet weak var repeatPasswordTextField: UITextField!
    
    func removeActivityIndicator(activityIndicator: UIActivityIndicatorView) {
        DispatchQueue.main.async {
            activityIndicator.stopAnimating()
            activityIndicator.removeFromSuperview()
        }
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
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    @IBAction func cancelButtonTapped(_ sender: Any) {
        print("cancel button tapped")
        self.dismiss(animated: true, completion: nil)
    }
    
    @IBAction func singupButtonTapped(_ sender: Any) {
        print("sign up button tapped")
        if (firstNameTextField.text?.isEmpty)! || (lastNameTestField.text?.isEmpty)! || (emailAddressTextField.text?.isEmpty)! || (passwordTextField.text?.isEmpty)! {
            displayMessage(userMessage: "All fields are required to be filled in")
            return
        }
        
        if ((passwordTextField.text?.elementsEqual(repeatPasswordTextField.text!)))! != true {
            displayMessage(userMessage: "Passwords do not match")
            return
        } else {
            Auth.auth().createUser(withEmail: emailAddressTextField.text!, password: passwordTextField.text!)
            self.dismiss(animated: true, completion: nil)
        }
        
    }
            
        
        
        
//        //  activity indicator
//        let myActivityIndicator = UIActivityIndicatorView(style: UIActivityIndicatorView.Style.gray)
//        myActivityIndicator.center = view.center
//        myActivityIndicator.hidesWhenStopped = false // to prevent from hiding when stopAnimating() is called
//        myActivityIndicator.startAnimating()
//        view.addSubview(myActivityIndicator)
//
//        let myUrl = URL(string: "http://localhost:8080/api/users")
//        var request = URLRequest(url:myUrl!)
//        request.httpMethod = "POST" // compose a query string
//        request.addValue("application/json", forHTTPHeaderField: "content-type")
//        request.addValue("application/json", forHTTPHeaderField: "Accept")
//
//        let postString = ["firstName": firstNameTextField.text!,
//                          "lastName": lastNameTestField.text!,
//                          "userName": emailAddressTextField.text!,
//                          "userPassword": passwordTextField.text!,] as [String: String]
//
//        do {
//            request.httpBody = try JSONSerialization.data(withJSONObject: postString, options: .prettyPrinted)
//        } catch let error {
//            print(error.localizedDescription)
//            displayMessage(userMessage: "Something went wrong. Try again.")
//        }
//
//        let task = URLSession.shared.dataTask(with: request) { (data: Data?, response: URLResponse?, error: Error?) in
//            self.removeActivityIndicator(activityIndicator: myActivityIndicator)
//
//            if error != nil {
//                self.displayMessage(userMessage: "Could not perform this request. Please try again.")
//                print("error = \(String(describing: error))")
//                return
//            }
//
//            do {
//                let json = try JSONSerialization.jsonObject(with: data!, options: .mutableContainers) as? NSDictionary
//
//                if let parseJSON = json {
//
//
//                    let userId = parseJSON["userId"] as? String
//                    print("User id: \(String(describing: userId!))")
//
//                    if (userId?.isEmpty)!
//                    {
//                        // Display an Alert dialog with a friendly error message
//                        self.displayMessage(userMessage: "Could not successfully perform this request. Please try again later")
//                        return
//                    } else {
//                        self.displayMessage(userMessage: "Successfully Registered a New Account. Please proceed to Sign in")
//                    }
//
//                } else {
//                    //Display an Alert dialog with a friendly error message
//                    self.displayMessage(userMessage: "Could not successfully perform this request. Please try again later")
//                }
//            } catch {
//
//                self.removeActivityIndicator(activityIndicator: myActivityIndicator)
//
//                // Display an Alert dialog with a friendly error message
//                self.displayMessage(userMessage: "Could not successfully perform this request. Please try again later")
//                print(error)
//            }
//        }
//
//            task.resume()
//
    
    
    
    
    
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}


