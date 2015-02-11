package com.nscc.a2_quizgame;

import android.support.v7.app.ActionBarActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;


public class MainActivity extends ActionBarActivity {

	// Name EditText
	EditText eText; 
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    } // End method onCreate

    /** Called when the user clicks the Send button */
    /** Defined in the MainActivity.XML */
    
	public void sendName(View view) {
    	
    	eText = (EditText) findViewById(R.id.edtTextName);
    	// Get the text from EditText
    	String name = eText.getText().toString(); 
    	
    	if(name != null && !name.trim().equals("") && name.length() < 25){
    		Intent i = new Intent(this, QuizActivity.class);
    		// Create bundle
    		Bundle extras = new Bundle();
    		// Fill bundle
    		extras.putString("userName",  name);
    		// Put extras in the bundle
    		i.putExtras(extras);
    		// Send bundle to new activity
    		startActivity(i);
    	} // End if 
    	else { 
    		Toast.makeText(getApplicationContext(), "Invalid format for name!",
    				// Display toast
    				Toast.LENGTH_LONG).show();
    	} // End else    
    } // End sendName method

} // End class MainActivity
