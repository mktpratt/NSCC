package com.nscc.movietrailer;

import java.util.ArrayList;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RatingBar;
import android.widget.Spinner;
import android.widget.Toast;
import android.widget.RatingBar.OnRatingBarChangeListener;

import com.example.movietrailer.R;
import com.nscc.movietrailer.Movie;
import com.nscc.movietrailer.MySQLiteHelper;

public class ActivityAdd extends Activity{
	
	Button submitButton;
	Spinner movieSpinner;
	EditText titleEditText;
	EditText descEditText;
	ImageView iconImageView;
	RatingBar ratingBar;
	
	MySQLiteHelper db = new MySQLiteHelper(this);
	
	private ArrayList<String> list;
	private float mRating = (float)0;
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
       	super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add);
        
        submitButton = (Button) findViewById(R.id.btnSubmit);
        titleEditText = (EditText) findViewById(R.id.editTitle);
        descEditText = (EditText) findViewById(R.id.editDesc);
        iconImageView = (ImageView) findViewById(R.id.icon);
        movieSpinner = (Spinner) findViewById(R.id.spinnerMovie);
        ratingBar = (RatingBar) findViewById(R.id.ratingBar);
        
        Intent getI=getIntent();
        
        // Get trailer list from main activity
        list = getI.getStringArrayListExtra("list");
        
        // Check if list is empty
        if(!list.isEmpty()){
        	// If not empty, add options to spinner
        	addItemsOnSpinner();
        }else{
        	// If list is empty, display alert and return to main activity
        	AlertDialog.Builder builder = new AlertDialog.Builder(this);
        	builder.setMessage("There are no movies to add!")
        	       .setCancelable(false)
        	       .setPositiveButton("OK", new DialogInterface.OnClickListener() {
        	           public void onClick(DialogInterface dialog, int id) {
        					Intent i=new Intent();	    		
        		    		i.putStringArrayListExtra("list", list);
        		    		setResult(android.app.Activity.RESULT_OK,i);
        					finish();
        	           }
        	       });
        	AlertDialog alert = builder.create();
        	alert.show();
        }
        
        
        // Assign on click listener
        submitButton.setOnClickListener(oclSubmitButton);
        movieSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
    	    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) { 
    	    	
    	    	// When movie is selected from spinner, display image
    	    	String imageName = movieSpinner.getSelectedItem().toString();
    			int resID = getResources().getIdentifier(imageName, "drawable", getPackageName());
    			iconImageView.setImageResource(resID);
    			
    	    } 

    	    public void onNothingSelected(AdapterView<?> adapterView) {
    	        return;
    	    } 
    	});
        
      // If rating value is changed
      ratingBar.setOnRatingBarChangeListener(new OnRatingBarChangeListener() {
      	public void onRatingChanged(RatingBar ratingBar, float rating,
      			boolean fromUser) {
      				
      				// Get the rating
      				mRating = ratingBar.getRating();
      	 
      			}
      		});
	
	}
	
	private void addItemsOnSpinner(){		
		
		// Add movies to spinner from list
		ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this,
			android.R.layout.simple_spinner_item, list);
		dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		movieSpinner.setAdapter(dataAdapter);
		
	}	
	
	
	// Button listener        
    OnClickListener oclSubmitButton = new OnClickListener(){
		public void onClick(View v){			
			
			// Convert edit text to strings
			String title = titleEditText.getText().toString();
			String desc = descEditText.getText().toString();
			
			// Trim string of whitespace
			title = title.trim();
			desc = desc.trim();
			
			// If name is empty, toast to enter name
			if(title.equals("")){
				Toast toast = Toast.makeText(getApplicationContext(), 
						"Please enter a title to continue",Toast.LENGTH_SHORT);
				toast.show();
				titleEditText.setText("");
			//if description is empty, toast to enter description
			}else if(desc.equals("")){
				Toast toast = Toast.makeText(getApplicationContext(), 
						"Please enter a description to continue",Toast.LENGTH_SHORT);
				toast.show();
				descEditText.setText("");				
			}else{			
				// Get movie from spinner
				String clip = movieSpinner.getSelectedItem().toString();
				
				// Get the image location based on movie name
				int image = getResources().getIdentifier(clip, "drawable", getPackageName());
				
				// Add info to database
				db.addMovie(new Movie(title, desc, image, clip, mRating));
				
				// Remove movie from add list
				list.remove(movieSpinner.getSelectedItemPosition());				
				
				// Pass updated list back to main activity
				Intent i=new Intent();	    		
	    		i.putStringArrayListExtra("list", list);
	    		setResult(android.app.Activity.RESULT_OK,i);
				finish();
				
			}
		} // End method onClick
	}; // End class OnClickListener


}
