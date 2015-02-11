package com.nscc.a2_quizgame;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.StringTokenizer;

import android.content.Context;
import android.util.Log;

public class Questions {

	// Number of answers listed per question
	final int NUM_ANSWERS = 4;
	// Hash map the questions and answers
	private Map<String, String> answerMap;
	// Question objects to handle quiz questions
	private ArrayList<Question> questions;

	// Default Constructor
	public Questions(int resId, Context ctx) {
		// Read in questions from text file
		createQuestions(ctx, resId);
		// Create the answer hash
		hashQuestionAnswers();
		// Randomize the answers
		randomizeQuizQuestions();
		// Shuffle questions
		shuffleQuestions();
	}

	// Create question list
	public void createQuestions(Context ctx, int resId) {
		// Create a new list each time
		this.questions = new ArrayList<Question>();
		// String to hold the line
		String line;

		try {
			// Create InputStream
			InputStream inputStream = ctx.getResources().openRawResource(resId);
			// Create InputStreamReader
			InputStreamReader inputStreamReader = new InputStreamReader(
					inputStream);
			// Must have BufferedReader to read individual lines
			BufferedReader bufferedReader = new BufferedReader(
					inputStreamReader);

			// Loop while there are more lines
			while ((line = bufferedReader.readLine()) != null) {
				// Add a different question for each line
				questions.add(new Question());
				// Tokenize line
				StringTokenizer token = new StringTokenizer(line, "|");
				// Loop while there are more tokens
				while (token.hasMoreTokens()) {
					String lineToAdd = token.nextToken();
					if (lineToAdd != null) {
						// Determine if the line is a question or answer
						if (token.hasMoreTokens()) {
							// Add the question to the correct question
							questions.get(questions.size() - 1).setQuestion(
									lineToAdd);
						} // End if
						else {
							// Add the answer to current question
							questions.get(questions.size() - 1)
									.setCorrectAnswer(lineToAdd);
						} // End else
					} // End if
				} // End nested while
			} // End while

			// Close the streams
			bufferedReader.close();
			inputStreamReader.close();
			inputStream.close();
		} // End try

		catch (IOException e) {
			Log.e("MISSING_FILE", "No valid questions file.", e);
		}

	} // End method createQuestions

	// Create hash map for answers
	private void hashQuestionAnswers() {
		this.answerMap = new HashMap<String, String>(this.questions.size());

		for (Question q : questions) {
			answerMap.put(q.getQuestion(), q.getAnswer());
		} // End for
	} // End method hashQuestionAnswers

	// Shuffle the order of questions/answers
	public void shuffleQuestions() {

		// Shuffle the questions
		Collections.shuffle(questions);

		for (Question q : questions) {
			// Shuffle the answers
			q.shuffleAnswers();
		} // End for
	} // End method shuffleQuestions

	// Randomize the questions
	public void randomizeQuizQuestions() {

		Random randomNumberGenerator = new Random();
		int randomDefinition = 0;

		// Loop until all questions are checked
		for (int i = 0; i < questions.size(); i++) {
			// Loop until the all questions with an answer are added
			while (questions.get(i).getAnswers().size() < NUM_ANSWERS) {
				randomDefinition = randomNumberGenerator.nextInt(questions
						.size());
				// Get the answer for each random question
				String answerToAdd = questions.get(randomDefinition)
						.getAnswer();
				// Add the answer if there currently isn't one
				if (!questions.get(i).getAnswers().contains(answerToAdd)) {
					questions.get(i).addAnswer(answerToAdd);
				} // End if
			} // End while
		} // End for
	} // End method randomizeQuizQuestions

	// Return the answers to the questions
	public ArrayList<String> getAnswers(int questionNumber) {
		return this.questions.get(questionNumber).getAnswers();
	} // End method getAnswers

	// Get a question
	public String getQuestion(int questionNumber) {
		return this.questions.get(questionNumber).getQuestion();
	} // End method getQuestion

	// Get the total number of questions
	public int getNumberOfQuestions() {
		return this.questions.size();
	} // End method getNumberOfQuestions

	// Remove question (So no duplicates)
	public void removeQuestion() {
		if (this.questions.size() > 0) {
			questions.remove(0);
		} // End if
	} // End method removeQuestion

	// Return if the answer is correct or incorrect
	public boolean checkAnswer(String questionText, String answer) {
		return this.answerMap.get(questionText).equals(answer);
	} // End method checkAnswer

	private class Question {

		// The question itself
		private String question;
		// The answer
		private String correctAnswer;
		// An ArrayList of incorrect answers
		private ArrayList<String> answers;

		// Default Constructor
		public Question() {
			this.answers = new ArrayList<String>();
		}

		// Set the question
		public void setQuestion(String question) {
			this.question = question;
		}

		// Set the correct answer
		public void setCorrectAnswer(String correctAnswer) {
			this.correctAnswer = correctAnswer;
			addAnswer(correctAnswer);
		}

		// Add the answer
		public void addAnswer(String answerText) {
			this.answers.add(answerText);
		}
		
		// Get the question
		public String getQuestion() {
			return this.question;
		}

		// Get the correct answer
		public String getAnswer() {
			return this.correctAnswer;
		}

		// Get all of the possible answers
		public ArrayList<String> getAnswers() {
			return this.answers;
		}

		// Put the answers in random order
		public void shuffleAnswers() {
			Collections.shuffle(this.answers);
			Collections.shuffle(this.answers);
		}

	} // End private class Question
} // End class Questions
