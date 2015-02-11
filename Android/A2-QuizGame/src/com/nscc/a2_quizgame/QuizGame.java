package com.nscc.a2_quizgame;

import java.util.ArrayList;

import android.content.Context;

public class QuizGame {
	
	int currentQuestion;// handles current question
	Questions questions; // handles questions
	
	// Default constructor
	public QuizGame(Context activityContext, int txtResourceID) {
		this.questions = new Questions(txtResourceID, activityContext);
		this.currentQuestion = 0;
	} // End constructor
	
	// Randomize the questions
	public void shuffleQuestions(){
		this.questions.shuffleQuestions();
	} // End method shuffleQuestions
	
	// Get the number of questions
	public int getTotalQuestions(){
		return this.questions.getNumberOfQuestions();
	} // End method getTotalQuestions
	
	// Get the current question
	public String getCurrentQuestion(){
		return this.questions.getQuestion(currentQuestion); // returns currentQuestion
	} // End method getCurrentQuestion

	// Get 4 possible answers (one correct)
	public ArrayList<String> getCurrentAnswers(){
		return  this.questions.getAnswers(currentQuestion);
	} // End method getCurrentAnswers
	
	// Check if answer is correct compared to hash map
	public boolean isCorrectAnswer(String answer){
		return questions.checkAnswer(this.getCurrentQuestion(), answer);
	} // End method isCorrectAnswer
	
	// Check if current question is the last one
		public boolean isQuizOver() {
			return this.currentQuestion == questions.getNumberOfQuestions() - 1;
		} // End method isQuizOver
	
	// Go to next question
	public void nextQuestion() {
		int numberOfQuestions = questions.getNumberOfQuestions();
		if(this.currentQuestion + 1 < numberOfQuestions) {
			this.currentQuestion++;
		} // End if
	} // End method nextQuestion	
	
	// Remove the last question (So it won't repeat)
	public void removeQuestionFromList(){
		this.questions.removeQuestion();
	} // End method removeQuestionFromList
	
	// move the current question back
	public void previousQuestion(){
		if(this.currentQuestion > 0){
			this.currentQuestion--;
		} // End if
	} // End method previousQuestion
} // End class QuizGame
