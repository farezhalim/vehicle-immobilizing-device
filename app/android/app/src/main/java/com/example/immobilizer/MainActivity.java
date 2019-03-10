package com.example.immobilizer;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.Toast;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;

public class MainActivity extends AppCompatActivity {

   // FirebaseApp.initializeApp(this);

    private EditText emailAddress,password;
    private Button signInButton;
    private ProgressBar signInProgress;
    private FirebaseAuth mAuth;
    private Intent HomeActivity;

    @Override
    public void onStart() {
        super.onStart();
        // Check if user is signed in (non-null) and update UI accordingly.
         // FirebaseUser currentUser = mAuth.getCurrentUser();
//          updateUI(currentUser);
    }

//    private void updateUI(FirebaseUser currentUser) {
//    }



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        emailAddress = findViewById(R.id.emailAddressEditText);
        password = findViewById(R.id.passwordEditText);
        signInButton = findViewById(R.id.signInButton);
        signInProgress = findViewById(R.id.signInProgress);
        signInProgress.setVisibility(View.INVISIBLE);
        mAuth = FirebaseAuth.getInstance();

        HomeActivity = new Intent(this, com.example.immobilizer.HomeActivity.class);

        signInButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                signInProgress.setVisibility(View.VISIBLE);
                signInButton.setVisibility(View.INVISIBLE );
                Log.d("btn", "sign in button clicked");

                String email = emailAddress.getText().toString();
                String pass = password.getText().toString();
                if (email.isEmpty() || pass.isEmpty()) {
                    showMessage("One of the required fields is empty");
                    Log.d("btn", "empty fields");

                    signInProgress.setVisibility(View.INVISIBLE);
                    signInButton.setVisibility(View.VISIBLE );

                } else {
                    signIn(email,pass);
                }

            }
        });

    }



    private void signIn(String email, String pass) {
        mAuth.signInWithEmailAndPassword(email,pass).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
            @Override
            public void onComplete(@NonNull Task<AuthResult> task) {
                if (task.isSuccessful()) {
                    signInProgress.setVisibility(View.INVISIBLE);
                    signInButton.setVisibility(View.VISIBLE);
                    updateUI();
                } else {
                    showMessage(task.getException().getMessage());
                    Log.d("btn", "invalid");
                    signInProgress.setVisibility(View.INVISIBLE);
                    signInButton.setVisibility(View.VISIBLE );
                }
            }
        });
    }

    private void updateUI() {

        startActivity(HomeActivity);
        finish();
    }

    private void showMessage(String s) {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

}
