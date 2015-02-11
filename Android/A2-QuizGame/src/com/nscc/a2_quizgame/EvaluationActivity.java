package com.nscc.a2_quizgame;

import android.support.v7.app.ActionBarActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class EvaluationActivity extends ActionBarActivity {

	TextView tvEvaluation;
	String name;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_evaluation);
		
		tvEvaluation = (TextView) findViewById(R.id.txtEvaluation);
		
		// Get intent
		Intent intent = getIntent(); 
		// Get the bundle from the intent 
		Bundle extras= intent.getExtras(); 
		
		// Set the evaluation text box
		name = extras.getString("userName");
		String correct = extras.getString("numCorrect");
		String total = extras.getString("totalQuestions");
		String evalString = "";
		
		// Set string based off score
		switch(correct) {
		case "0":
		case "1":
		case "2":
			evalString = "Oh no, " + name + "! You scored " + correct + " out of " + total + "!";
			break;
		case "3":
		case "4":
		case "5":
		case "6":
			evalString = "Good job, " + name + "! You scored " + correct + " out of " + total + "!";
			break;
		case "7":
		case "8":
		case "9":
			evalString = "Awesome, " + name + "! You scored " + correct + " out of " + total + "!";
			break;
		case "10":
			evalString = "Excellent job, " + name + "! You scored a perfect " + correct + " out of " + total + "!";
			break;
		} // End switch
				
		 // Display the score
		tvEvaluation.setText(evalString);
		
	} // End method onCreate
	
	// Go back to start
	public void restart(View view) {
    
    		Intent i = new Intent(this, MainActivity.class);
    		// Create bundle
    		Bundle extras = new Bundle();
    		// Fill bundle
    		extras.putString("userName",  name);
    		// Put extras in the bundle
    		i.putExtras(extras);
    		// Send bundle to new activity
    		startActivity(i);
    } // End method restart
} // End class EvaluationActivity
