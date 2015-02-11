package com.nscc.a2_quizgame;

import java.util.ArrayList;

import android.support.v7.app.ActionBarActivity;

import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

public class QuizActivity extends ActionBarActivity {
	
	QuizGame quizGame;
	String name;
	RadioGroup radioBtnGroup;
	Button btnNext; 
	TextView txtView; 
	ArrayList<RadioButton> radBtns;
	
	// Counter to count correct answers
	int correctAnswerCount = 0;
	
	// Answer radio buttons
	RadioButton answOne; 
	RadioButton answTwo;
	RadioButton answThree;
	RadioButton answFour;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_quiz);
			
		// =============== LINK FORM ELEMENTS =================//
		txtView = (TextView) findViewById(R.id.txtQuestion); 
		btnNext = (Button) findViewById(R.id.btnNext);
		answOne = (RadioButton) findViewById(R.id.radioAnswerOne);
		answTwo = (RadioButton) findViewById(R.id.radioAnswerTwo);
		answThree = (RadioButton) findViewById(R.id.radioAnswerThree);
		answFour = (RadioButton) findViewById(R.id.radioAnswerFour);
		radioBtnGroup = (RadioGroup) findViewById(R.id.radioGroupAnswers);
		//======================================================//
		
		// Add ArrayList of the radio buttons
		radBtns = new ArrayList<RadioButton>();
		radBtns.add(answOne);
		radBtns.add(answTwo);
		radBtns.add(answThree);
		radBtns.add(answFour); 
		
		// Handle IO
		try { 
			
			 // get this context (for IO operations)
			Context ctx = this.getApplicationContext();
			 // get handle on the resource id (for questions)
			int i = this.getResources().getIdentifier("questions","raw", this.getPackageName());
			 // the quiz game (controller) will handle the questions
			quizGame = new QuizGame(ctx, i);
		} // End try
		// Catch if no file found
		catch(Resources.NotFoundException e) { 
			Log.e("MISSING_FILE", "No valid questions file.", e);
		} // End catch
		
		// Create new intent for bundle
		Intent intent = getIntent(); 
		Bundle extras= intent.getExtras(); 
		// Name to be passed along
		name = extras.getString("userName");
		// Display the question
		setCurrentQuestionText(); 
		
		
		// Listen for button press
		btnNext.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {

				showQuestionEvaluation(); 
											
				if (!quizGame.isQuizOver()) {
					// Go to next question
					quizGame.nextQuestion(); 
					// Set current question
					setCurrentQuestionText();
					// Remove all selections
					answOne.setChecked(false);
					answTwo.setChecked(false);
					answThree.setChecked(false);
					answFour.setChecked(false);
				} // End if 
				else {
					gameFinished();
				} // End else
			} // End method onClick
		}); // End onClickListener 
		
	} // End method onCreate
	
	/* handles end of game state, sends bundle to evaluation and resets score*/
	public void gameFinished() {
		
		// Create new intent
    	Intent i = new Intent(this, EvaluationActivity.class);
		
    	// Send score and name to be evaluated
		// Create bundle
    	Bundle extras = new Bundle();
    	// Fill the bundle
		extras.putString("numCorrect",  String.valueOf(correctAnswerCount));
		extras.putString("totalQuestions",  String.valueOf(quizGame.getTotalQuestions()));
		extras.putString("userName", name);
		i.putExtras(extras);
		
		// Reset the quiz
		quizGame.shuffleQuestions();
		correctAnswerCount = 0;		
		startActivity(i);
	} // End method gameFinished
	
	// Display current question and answers (4)
	private void setCurrentQuestionText() {

		// Set the current question
		txtView.setText(quizGame.getCurrentQuestion());
		// Create answer ArrayList
		ArrayList<String> answerList = quizGame.getCurrentAnswers();
		
		/*** ADDED TO FIX SELECTION ISSUE BUG ***/
		answOne.setChecked(true);
		answOne.setChecked(false);
		
		// Assign each radio button an answer
		for(int i = 0; i < radBtns.size(); i++) { 
			radBtns.get(i).setText(answerList.get(i));
		} // End for
	} // End method setCurrentQuestionText
	
	// show question evaluation in toast
	private void showQuestionEvaluation() {

		String answer;
		// ID of selected radio button
		int selectedId = radioBtnGroup.getCheckedRadioButtonId();
		RadioButton selectedRadButton = (RadioButton) findViewById(selectedId);
		// Check if the user selected a button
		if (answOne.isChecked() || answTwo.isChecked() || answThree.isChecked() || answFour.isChecked()) {
			// Set the answer to the text of radio button
			answer = (String) selectedRadButton.getText();
			// Check if they got the correct answer
			if (quizGame.isCorrectAnswer(answer)) {
				correctAnswerCount++;
			} // End if
		} // End if
		// If user didn't select a radio button, assign them a blank answer (incorrect)
		else {
			answer = "";
		} // End else
		
	} // End method showQuestionEvaluation
	
} // End class QuizActivity
